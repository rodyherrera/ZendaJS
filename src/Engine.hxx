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
#include <map>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;
using namespace v8;

#include "Global.hxx"

#include "utils/String.hxx"
#include "utils/Shared.hxx"
#include "utils/Helpers.hxx"

#include "Module.hxx"

#include "methods/Misc.hxx" 
#include "methods/Python.hxx"

#include "objects/Console.hxx"
#include "objects/System.hxx"

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

ObjectCreator CreateObject(const char* ObjectName){
    ObjectCreator ObjectCreatorInstance(ZendaIsolate, ObjectName);
    return ObjectCreatorInstance;
}

// By declaring the function and 
// then defining them and not having order 
// errors due to the use of a functional programming paradigm.
void CreatheMethod(const char* MethodName, void(*Callback)(const FunctionCallbackInfo<Value>& Arguments));
void AddCoreJavascriptFile(string Path);
void CreatePlatform(char* argv[]);
void Initialize(int argc, char* argv[]);
bool ExecuteString(Local<String> Source, const char* Filename);
void Shell(Local<Context> SContext, Platform* SPlatform);
void ReportException(TryCatch* try_catch);
void CreateVirtualMachine();
void CreateGlobalEnvironment();
void ShutdownVirtualMachine();
void LoadCoreJavascriptFiles();
void EngineEnvironMethods();
void EngineEnvironObjects();
void EngineEnvironCoreJavascriptFiles();
Local<Context> CreateLocalContext();

void CreateMethod(const char* MethodName, void(*Callback)(const FunctionCallbackInfo<Value>& Arguments)){
    ZendaGlobal->Set(
        String::NewFromUtf8(ZendaIsolate, MethodName, NewStringType::kNormal).ToLocalChecked(),
        FunctionTemplate::New(ZendaIsolate, Callback)
    );
}

Local<Context> CreateLocalContext(){
    return Context::New(ZendaIsolate, NULL, ZendaGlobal);
}

void AddCoreJavascriptFile(string Path){
    ZendaJavascriptCoreFiles.push_back(Path);
}

void CreatePlatform(char* argv[]){
    V8::InitializeICUDefaultLocation(argv[0]);
    V8::InitializeExternalStartupData(argv[0]);
    ZendaPlatform = platform::NewDefaultPlatform();
    V8::InitializePlatform(ZendaPlatform.get());
    V8::Initialize();
}

void CreateVirtualMachine(){
    ZendaCreateParams.array_buffer_allocator = ArrayBuffer::Allocator::NewDefaultAllocator();
    ZendaIsolate = Isolate::New(ZendaCreateParams);
    ZendaIsolate->SetHostImportModuleDynamicallyCallback(CallDynamic);
}

void ShutdownVirtualMachine(){
    ZendaIsolate->Dispose();
    V8::Dispose();
    V8::ShutdownPlatform();
    delete ZendaCreateParams.array_buffer_allocator;
}

bool ExecuteString(Local<String> Source, const char* Filename){
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

bool ExecuteFile(const char* Filename){
    Local<String> Source;
    if(!ReadFileUsingV8(Filename, ZendaIsolate).ToLocal(&Source))
        return false;
    if(!ExecuteString(Source, Filename))
        return false;
    return true;
}

void LoadCoreJavascriptFiles(){
    EngineEnvironCoreJavascriptFiles();

    for(unsigned short int i = 0; i < ZendaJavascriptCoreFiles.size(); i++)
        ExecuteFile(ZendaJavascriptCoreFiles.at(i).c_str());
}

void CreateGlobalEnvironment(){
    ZendaGlobal = ObjectTemplate::New(ZendaIsolate);
}

void EngineEnvironMethods(){
    CreateMethod("version", Version);
    CreateMethod("creator", Creator);
    CreateMethod("sleep", Sleep);
    CreateMethod("pythonString", PythonQuickString);
    CreateMethod("pythonFile", PythonQuickFile);
    CreateMethod("pythonFancyFile", PythonFancyFile);
}

void EngineEnvironObjects(){
    CreateObject("console")
        .SetPropertyMethod("log", ConsoleLog)
        .SetPropertyMethod("input", ConsoleInput)
        .SetPropertyMethod("clear", ConsoleClear)
        .SetPropertyMethod("setColor", ConsoleSetColor)
        .SetPropertyMethod("setStyle", ConsoleSetStyle)
        .SetPropertyMethod("setBackground", ConsoleSetBackground)
        .SetPropertyMethod("getColor", ConsoleGetColor)
        .SetPropertyMethod("getStyle", ConsoleGetStyle)
        .SetPropertyMethod("getBackground", ConsoleGetBackground)
        .Register();

    CreateObject("system")
        .SetPropertyMethod("platform", SystemPlatform)
        .SetPropertyMethod("execute", SystemExecute)
        .SetPropertyMethod("arguments", SystemArguments)
        .Register();
}

void EngineEnvironCoreJavascriptFiles(){
}

void Shell(Local<Context> SContext, Platform* SPlatform){
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

void Initialize(int argc, char* argv[]){
    bool SomeFileHasBeenExecuted = 0;
    SetCallArguments(argc, argv);
    CreatePlatform(argv);
    CreateVirtualMachine();
    {
        Isolate::Scope IsolateScope(ZendaIsolate);
        HandleScope Scope(ZendaIsolate);
        CreateGlobalEnvironment();
        EngineEnvironMethods();
        for(unsigned short int i = 1; i < argc; ++i){
            const char* Argument = argv[i];
            Local<Context> LContext = CreateLocalContext();
            Context::Scope ContextScope(LContext);
            EngineEnvironObjects();
            LoadCoreJavascriptFiles();
            if(!strcmp(Argument, "--creator")){
                cout << ZendaCreator << endl;
                break;
            }else if(!strcmp(Argument, "--version")){
                cout << ZendaVersion << endl;
                break;
            }else if(!strcmp(Argument, "--shell")){
                Shell(LContext, ZendaPlatform.get());
                break;
            }else if(!strcmp(Argument, "--install-dependencies")){
                InstallDependencies();
                break;
            }else if(!strcmp(Argument, "--execute")){
                const char* MaybeFile = argv[i + 1];
                SomeFileHasBeenExecuted = true;
                if(FileExists(MaybeFile)){
                    char* Contents = ReadFile(strdup(MaybeFile));
                    Local<Module> LModule = CheckModule(LoadModule(Contents, strdup(MaybeFile), LContext), LContext);
                    Local<Value> Returned = ExecuteModule(LModule, LContext);
                }else{
                    cout << "The requested file <" << MaybeFile << "> was not found." << endl;
                }
            }else if( (!SomeFileHasBeenExecuted) || (!strcmp(Argument, "--help")) ){
                ShowHelp();
                if(!SomeFileHasBeenExecuted){
                    exit(EXIT_FAILURE);
                }
            }
        }
    }

    ShutdownVirtualMachine();
}