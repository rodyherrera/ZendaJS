#include <iostream>

#include <v8.h>
#include <libplatform/libplatform.h>

#ifdef __WIN32
	#include <Windows.h>
#else
	#include <unistd.h>
#endif

#define PY_SSIZE_T_CLEAN
#include <Python.h>

// Utils folder files libraries used.
#include <cassert>
#include <fstream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;
using namespace v8;

#include "Global.hxx"

#include "utils/String.hxx"
#include "utils/Shared.hxx"
#include "Installation.hxx"

#include "Module.hxx"

class ObjectCreator{
    private:
        Isolate* isolate;
        Local<String> name;
        Local<ObjectTemplate> ObjectInstance;

    public:
        ObjectCreator(Isolate * isolate, const char* objectname){
            this->isolate = isolate;
            this->ObjectInstance = ObjectTemplate::New(this->isolate);
            this->name = String::NewFromUtf8(
                this->isolate, objectname, NewStringType::kNormal
            ).ToLocalChecked();
        }

        ObjectCreator SetPropertyMethod(const char* propertymethod, void (*callback)(const FunctionCallbackInfo<Value>& Arguments)){
            this->ObjectInstance->Set(
                String::NewFromUtf8(this->isolate, propertymethod, NewStringType::kNormal).ToLocalChecked(),
                FunctionTemplate::New(this->isolate, callback)
            );
            return *this;
        }

        void Register(){
            Local<Object> Instance = this->ObjectInstance->NewInstance(
                this->isolate->GetCurrentContext()
            ).ToLocalChecked();
            this->isolate->GetCurrentContext()->Global()->Set(
                this->isolate->GetCurrentContext(),
                this->name,
                Instance
            ).FromJust();
        }
};

static inline ObjectCreator CreateObject(const char* ObjectName){
    ObjectCreator ObjectCreatorInstance(ZendaIsolate, ObjectName);
    return ObjectCreatorInstance;
}

// By declaring the function and 
// then defining them and not having order 
// errors due to the use of a functional programming paradigm.
static inline void CreatheMethod(const char* MethodName, void(*Callback)(const FunctionCallbackInfo<Value>& Arguments));
static inline void AddCoreJavascriptFile(string Path);
static inline void CreateGlobalEnvironment();
static inline Local<Context> CreateLocalContext();
static void CreatePlatform(char* argv[]);
static void Initialize(int argc, char* argv[]);
static bool ExecuteString(Local<String> Source, const char* Filename);
static void Shell(Local<Context> SContext, Platform* SPlatform);
static void CreateVirtualMachine();
static void ShutdownVirtualMachine();
static void LoadCoreJavascriptFiles();
static void EngineEnvironMethods();
static bool ExecuteFile(const char* Filename);
static void EngineEnvironObjects();
static void EngineEnvironCoreJavascriptFiles();

static inline void CreateMethod(const char* MethodName, void(*Callback)(const FunctionCallbackInfo<Value>& Arguments)){
    ZendaGlobal->Set(
        String::NewFromUtf8(ZendaIsolate, MethodName, NewStringType::kNormal).ToLocalChecked(),
        FunctionTemplate::New(ZendaIsolate, Callback)
    );
}

static inline Local<Context> CreateLocalContext(){
    return Context::New(ZendaIsolate, NULL, ZendaGlobal);
}

static inline void AddCoreJavascriptFile(string Path){
    ZendaJavascriptCoreFiles.push_back(Path);
}

static void CreatePlatform(char* argv[]){
    V8::InitializeICUDefaultLocation(argv[0]);
    V8::InitializeExternalStartupData(argv[0]);
    ZendaPlatform = platform::NewDefaultPlatform();
    V8::InitializePlatform(ZendaPlatform.get());
    V8::Initialize();
}

static void CreateVirtualMachine(){
    ZendaCreateParams.array_buffer_allocator = ArrayBuffer::Allocator::NewDefaultAllocator();
    ZendaIsolate = Isolate::New(ZendaCreateParams);
    ZendaIsolate->SetHostImportModuleDynamicallyCallback(CallDynamic);
}

static void ShutdownVirtualMachine(){
    ZendaIsolate->Dispose();
    V8::Dispose();
    V8::ShutdownPlatform();
    delete ZendaCreateParams.array_buffer_allocator;
}

static bool ExecuteString(Local<String> Source, const char* Filename){
    TryCatch try_catch(ZendaIsolate);
    ScriptOrigin origin(
        String::NewFromUtf8(ZendaIsolate, Filename, NewStringType::kNormal).ToLocalChecked()
    );
    Local<Script> LSCript;

    if(!Script::Compile(ZendaIsolate->GetCurrentContext(), Source, &origin).ToLocal(&LSCript)){
        ReportException(&try_catch);
        return false;
    }else{
        Local<Value> Output;
        if(!LSCript->Run(ZendaIsolate->GetCurrentContext()).ToLocal(&Output)){
            assert(try_catch.HasCaught());
            ReportException(&try_catch);
            return false;
        }else{
            assert(!try_catch.HasCaught());
            return true;
        }
    }
}

static bool ExecuteFile(const char* Filename){
    Local<String> Source;
    if(!ReadFileUsingV8(Filename, ZendaIsolate).ToLocal(&Source))
        return false;
    if(!ExecuteString(Source, Filename))
        return false;
    return true;
}

static void LoadCoreJavascriptFiles(Local<Context> LContext){
    EngineEnvironCoreJavascriptFiles();
    string ZendaSRC = ZendaSourceCodeLocation();
    unsigned short int Iterator = 0;
    for(Iterator; Iterator < ZendaJavascriptCoreFiles.size(); Iterator++){
        string FilePath = ZendaSRC + ZendaJavascriptCoreFiles.at(Iterator);
        const char* File = FilePath.c_str();
        if(FileExists(File)){
            char* Contents = ReadFile(strdup(File));
            Local<Module> LModule = CheckModule(LoadModule(Contents, strdup(File), LContext), LContext);
            Local<Value> Returned = ExecuteModule(LModule, LContext);
        }
    }
}

static inline void CreateGlobalEnvironment(){
    ZendaGlobal = ObjectTemplate::New(ZendaIsolate);
}

// Methods
#include "methods/Misc.hxx" 
#include "methods/Python.hxx"

// Objects
#include "objects/Console.hxx"
#include "objects/System.hxx"

static void EngineEnvironMethods(){
    CreateMethod("Version", Version);
    CreateMethod("Creator", Creator);
    CreateMethod("Sleep", Sleep);
    CreateMethod("PythonString", PythonQuickString);
    CreateMethod("PythonFile", PythonQuickFile);
    CreateMethod("PythonFancyFile", PythonFancyFile);
}

static void EngineEnvironObjects(){
    CreateObject("Console")
        .SetPropertyMethod("Log", ConsoleLog)
        .SetPropertyMethod("Error", ConsoleError)
        .SetPropertyMethod("Warning", ConsoleWarning)
        .SetPropertyMethod("Information", ConsoleInformation)
        .SetPropertyMethod("Success", ConsoleSuccess)
        .SetPropertyMethod("Input", ConsoleInput)
        .SetPropertyMethod("Clear", ConsoleClear)
        .SetPropertyMethod("SetColor", ConsoleSetColor)
        .SetPropertyMethod("SetStyle", ConsoleSetStyle)
        .SetPropertyMethod("SetBackground", ConsoleSetBackground)
        .SetPropertyMethod("GetColor", ConsoleGetColor)
        .SetPropertyMethod("GetStyle", ConsoleGetStyle)
        .SetPropertyMethod("GetBackground", ConsoleGetBackground)
        .Register();

    CreateObject("System")
        .SetPropertyMethod("Platform", SystemPlatform)
        .SetPropertyMethod("Execute", SystemExecute)
        .SetPropertyMethod("Arguments", SystemArguments)
        .SetPropertyMethod("CurrentWorkingDirectory", SystemCurrentWorkignDirectory)
        .Register();
}

static void EngineEnvironCoreJavascriptFiles(){
}

static void Shell(Local<Context> SContext, Platform* SPlatform){
    ClearConsole();
    cout << "ZendaJS<Beta> [" << ZendaVersion << "] - By " << ZendaCreator << "." << endl << "Happy hacking!" << endl << endl;
    static const int kBufferSize = 256;
    Context::Scope context_scope(SContext);
    Local<String> name(
        String::NewFromUtf8(SContext->GetIsolate(), "(shell)", NewStringType::kNormal).ToLocalChecked()
    );
    while(true){
        char Buffer[kBufferSize];
        fprintf(stderr, "Console -> ");
        char* Code = fgets(Buffer, kBufferSize, stdin);
        if(Code == NULL) break;
        HandleScope handle_scope(SContext->GetIsolate());
        ExecuteString(
            String::NewFromUtf8(SContext->GetIsolate(), Code).ToLocalChecked(),
            ""
        );
        while(platform::PumpMessageLoop(SPlatform, SContext->GetIsolate()))
            continue;
            cout << endl;
        }
}

#include "cli/Functions.hxx"
#include "cli/Arguments.hxx"

static void Initialize(int argc, char* argv[]){
    SetCallArguments(argc, argv);
    CreatePlatform(argv);
    CreateVirtualMachine();
    {
        Isolate::Scope IsolateScope(ZendaIsolate);
        HandleScope Scope(ZendaIsolate);
        CreateGlobalEnvironment();
        EngineEnvironMethods();
        if(argv[1]){
            unsigned short int Iterator = 1;
            for(Iterator; Iterator < argc; ++Iterator){
                Local<Context> LContext = CreateLocalContext();
                Context::Scope ContextScope(LContext);
                EngineEnvironObjects();
                if(MatchWithArgument(argv[Iterator], LContext, argv[Iterator + 1]))
                    break;
            }
        }else
            ShowHelp();
    }

    ShutdownVirtualMachine();
}