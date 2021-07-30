#include <iostream>
#include "Utility.hxx"
using namespace std;

#include <v8.h>
#include <libplatform/libplatform.h>
using namespace v8;

#include <cassert>
#include <cstdlib>
#include <functional>

#ifdef __WIN32
	#include <Windows.h>
#else
	#include <unistd.h>
#endif

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include <vector>

namespace Modules{

    MaybeLocal<Module> CallResolve(Local<Context> MContext, Local<String> Specifier, Local<Module> Referrer);

    MaybeLocal<Module> Load(char Code[], char Name[], Local<Context> MContext){
        Local<String> VMCode = String::NewFromUtf8(MContext->GetIsolate(), Code).ToLocalChecked();

        ScriptOrigin Origin(
            String::NewFromUtf8(MContext->GetIsolate(), Name).ToLocalChecked(),

            Integer::New(MContext->GetIsolate(), 0),

            Integer::New(MContext->GetIsolate(), 0),

            False(MContext->GetIsolate()),

            Local<Integer>(),

            Local<Value>(),

            False(MContext->GetIsolate()),

            False(MContext->GetIsolate()),

            True(MContext->GetIsolate())
        );

        Context::Scope ContextScope(MContext);

        ScriptCompiler::Source LSource(VMCode, Origin);

        MaybeLocal<Module> LModule;

        LModule = ScriptCompiler::CompileModule(MContext->GetIsolate(), &LSource);

        return LModule;
    }

    Local<Module> Check(MaybeLocal<Module> MaybeModule, Local<Context> MContext){
        Local<Module> LModule;

        if(!MaybeModule.ToLocal(&LModule)){
            cout << "Error loading module" << endl;

            exit(EXIT_FAILURE);
        }

        Maybe<bool> Result = LModule->InstantiateModule(MContext, CallResolve);

        if(Result.IsNothing()){
            cout << "Can't instantiate module." << endl;
            
            exit(EXIT_FAILURE);
        }

        return LModule;
    }

    Local<Value> Execute(Local<Module> LModule, Local<Context> MContext, bool NsObject = false){
        Local<Value> ReturnValue;

        if(!LModule->Evaluate(MContext).ToLocal(&ReturnValue)){
            cout << "Error evaluating module." << endl;

            exit(EXIT_FAILURE);
        }

        if(NsObject)
            return LModule->GetModuleNamespace();
        else
            return ReturnValue;
    }

    MaybeLocal<Module> CallResolve(Local<Context> MContext, Local<String> Specifier, Local<Module> Referrer){
        String::Utf8Value Str(MContext->GetIsolate(), Specifier);

        return Load(ReadFile(*Str), *Str, MContext);
    }

    MaybeLocal<Promise> CallDynamic(Local<Context> MContext, Local<ScriptOrModule> Referrer, Local<String> Specifier){
        Local<Promise::Resolver> Resolver = Promise::Resolver::New(MContext).ToLocalChecked();

        MaybeLocal<Promise> LPromise(Resolver->GetPromise());

        String::Utf8Value Name(MContext->GetIsolate(), Specifier);

        Local<Module> LModule = Check(Load(ReadFile(*Name), *Name, MContext), MContext);

        Local<Value> ReturnValue = Execute(LModule, MContext, true);

        Maybe<bool> MResolve = Resolver->Resolve(MContext, ReturnValue);

        return LPromise;
    }

}

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

class ZendaJS{
    private:
        unique_ptr<Platform> platform;

        Isolate::CreateParams create_params;

        Isolate* isolate;

        Local<ObjectTemplate> global;

        vector<string> ZendaJSCoreFiles;

        static void Version(const FunctionCallbackInfo<Value>& Arguments){
            HandleScope Scope(Arguments.GetIsolate());

            PrintVersion();
        }

        static void Creator(const FunctionCallbackInfo<Value>& Arguments){
            HandleScope Scope(Arguments.GetIsolate());

            PrintCreator();
        }

        static void PythonString(const FunctionCallbackInfo<Value>& Arguments){
            Py_Initialize();
            
            for(unsigned short int i = 0; i < Arguments.Length(); i++){
                HandleScope Scope(Arguments.GetIsolate());

                String::Utf8Value Code(Arguments.GetIsolate(), Arguments[i]);

                char const* CharCode = ToCString(Code);

                PyRun_SimpleString(CharCode);
            }

            Py_Finalize();
        }

        static void PythonFile(const FunctionCallbackInfo<Value>& Arguments){
            Py_Initialize();

            for(unsigned short int i = 0; i < Arguments.Length(); i++){
                HandleScope Scope(Arguments.GetIsolate());

                String::Utf8Value File(Arguments.GetIsolate(), Arguments[i]);

                char const* CharFile = ToCString(File);

                FILE* PyFile;

                PyFile = fopen(CharFile, "r");

                if(PyFile == NULL)
                    cout << "ZendaJS -> An error ocurred while trying open <" << CharFile << "> in pythonFile() function." << endl;
                else
                    PyRun_SimpleFile(PyFile, CharFile);

                fclose(PyFile);
            }

            Py_Finalize();
        }

        static void GetCurrentWorkingDirectory(const FunctionCallbackInfo<Value>& Arguments){
            HandleScope Scope(Arguments.GetIsolate());

            string Directory = CurrentWorkingDirectory();

            Arguments.GetReturnValue().Set(
                String::NewFromUtf8(
                    Arguments.GetIsolate(),
                    Directory.c_str(),
                    NewStringType::kNormal,
                    static_cast<int>(Directory.length())
                ).ToLocalChecked()
            );
        }

        static void Sleep(const FunctionCallbackInfo<Value>& Arguments){
            HandleScope Scope(Arguments.GetIsolate());
            
            String::Utf8Value SleepTime(Arguments.GetIsolate(), Arguments[0]);

            char const* CharSleepTime = ToCString(SleepTime);

            sleep(stoi(CharSleepTime) / 1000);
        }

        static void ConsoleLog(const FunctionCallbackInfo<Value>& Arguments){
            for(unsigned short int i = 0; i < Arguments.Length(); i++){
                HandleScope Scope(Arguments.GetIsolate());
   
                if(i > 0) cout << " ";

                String::Utf8Value Text(Arguments.GetIsolate(), Arguments[i]);

                const char* CharText = ToCString(Text);

                cout << CharText;
            }

            cout << endl;
        }

        static void ConsoleSetColor(const FunctionCallbackInfo<Value>& Arguments){
            HandleScope Scope(Arguments.GetIsolate());

            String::Utf8Value ColorIdentifier(Arguments.GetIsolate(), Arguments[0]);
            
            const char* CharColorIdentifier = ToCString(ColorIdentifier);
            
            cout << ConsoleColor(CharColorIdentifier);
        }

        static void ConsoleSetStyle(const FunctionCallbackInfo<Value>& Arguments){
            HandleScope Scope(Arguments.GetIsolate());

            String::Utf8Value StyleIdentifier(Arguments.GetIsolate(), Arguments[0]);

            const char* CharStyleIdentifier = ToCString(StyleIdentifier);

            cout << ConsoleStyle(CharStyleIdentifier);
        }

        static void ConsoleSetBackground(const FunctionCallbackInfo<Value>& Arguments){
            HandleScope Scope(Arguments.GetIsolate());

            String::Utf8Value BackgroundIdentifier(Arguments.GetIsolate(), Arguments[0]);
            
            const char* CharBackgroundIdentifier = ToCString(BackgroundIdentifier);
            
            cout << ConsoleBackground(CharBackgroundIdentifier);
        }

        static void ConsoleGetBackground(const FunctionCallbackInfo<Value>& Arguments){
            HandleScope Scope(Arguments.GetIsolate());

            String::Utf8Value BackgroundIdentifier(Arguments.GetIsolate(), Arguments[0]);

            const char* CharBackgroundIdentifier = ToCString(BackgroundIdentifier);

            string Background = ConsoleBackground(CharBackgroundIdentifier);

            Arguments.GetReturnValue().Set(
                String::NewFromUtf8(
                    Arguments.GetIsolate(),
                    Background.c_str(),
                    NewStringType::kNormal,
                    static_cast<int>(Background.length())
                ).ToLocalChecked()
            );
        }

        static void ConsoleGetStyle(const FunctionCallbackInfo<Value>& Arguments){
            HandleScope Scope(Arguments.GetIsolate());

            String::Utf8Value StyleIdentifier(Arguments.GetIsolate(), Arguments[0]);
            
            const char* CharStyleIdentifier = ToCString(StyleIdentifier);
            
            string Style = ConsoleStyle(CharStyleIdentifier);
            
            Arguments.GetReturnValue().Set(
                String::NewFromUtf8(
                    Arguments.GetIsolate(),
                    Style.c_str(),
                    NewStringType::kNormal,
                    static_cast<int>(Style.length())
                ).ToLocalChecked()
            );
        }

        static void ConsoleGetColor(const FunctionCallbackInfo<Value>& Arguments){
            HandleScope Scope(Arguments.GetIsolate());

            String::Utf8Value ColorIdentifier(Arguments.GetIsolate(), Arguments[0]);

            const char* CharColorIdentifier = ToCString(ColorIdentifier);

            string Color = ConsoleColor(CharColorIdentifier);

            Arguments.GetReturnValue().Set(
                String::NewFromUtf8(
                    Arguments.GetIsolate(),
                    Color.c_str(),
                    NewStringType::kNormal,
                    static_cast<int>(Color.length())
                ).ToLocalChecked()
            );
        }

        static void ConsoleClear(const FunctionCallbackInfo<Value>& Arguments){
            HandleScope Scope(Arguments.GetIsolate());
        
            ClearConsole();
        }
        
        static void ConsoleInput(const FunctionCallbackInfo<Value>& Arguments){
            for(unsigned short int i = 0; i < Arguments.Length(); i++){
                HandleScope scope(Arguments.GetIsolate());

                if(i > 0) cout << " ";

                String::Utf8Value Text(Arguments.GetIsolate(), Arguments[i]);

                const char* CharText = ToCString(Text);

                cout << CharText;
            }

            string Response;

            getline(cin, Response);

            Arguments.GetReturnValue().Set(
                String::NewFromUtf8(
                    Arguments.GetIsolate(),
                    Response.c_str(),
                    NewStringType::kNormal,
                    static_cast<int>(Response.length())
                ).ToLocalChecked()
            );
        }

        static void SystemExecute(const FunctionCallbackInfo<Value>& Arguments){
            for(unsigned short int i = 0; i < Arguments.Length(); i++){
                HandleScope Scope(Arguments.GetIsolate());

                String::Utf8Value Command(Arguments.GetIsolate(), Arguments[i]);

                const char* CharCommand = ToCString(Command);

                system(CharCommand);
            }
        }

        static void SystemPlatform(const FunctionCallbackInfo<Value>& Arguments){
            HandleScope Scope(Arguments.GetIsolate());

            string OS = OperativeSystem();

            Arguments.GetReturnValue().Set(
                String::NewFromUtf8(
                    Arguments.GetIsolate(),
                    OS.c_str(),
                    NewStringType::kNormal,
                    static_cast<int>(OS.length())
                ).ToLocalChecked()
            );
        }

    protected:
        Local<Context> CreateLocalContext(){
            return Context::New(this->isolate, NULL, this->global);
        }
    
        Local<ObjectTemplate> GetGlobal(){
            return this->global;
        }

    public:
        Isolate* GetIsolate(){
            return this->isolate;
        }

        void CreatePlatform(char* argv[]){
                    V8::InitializeICUDefaultLocation(argv[0]);
        
                    V8::InitializeExternalStartupData(argv[0]);
        
                    this->platform = platform::NewDefaultPlatform();
        
                    V8::InitializePlatform(platform.get());
        
                    V8::Initialize();
        }

        void CreateVM(){
            this->create_params.array_buffer_allocator = ArrayBuffer::Allocator::NewDefaultAllocator();
        
            this->isolate = Isolate::New(this->create_params);

            this->isolate->SetHostImportModuleDynamicallyCallback(Modules::CallDynamic);
        }

        void ShutdownVM(){
            this->isolate->Dispose();
            
            V8::Dispose();
            
            V8::ShutdownPlatform();
            
            delete this->create_params.array_buffer_allocator;
        }
        
        void LoadZendaJSFiles(){
            this->ZendaJSFiles();

            for(unsigned short int i = 0; i < this->ZendaJSCoreFiles.size(); i++)
                this->ExecuteFile(this->ZendaJSCoreFiles.at(i).c_str());
        }
        
        void Shell(Local<Context> SContext, Platform* SPlatform){
            ClearConsole();
            
            PrintCreator();

            cout << "Running in v" << ZendaVersion << ", Remember drink water and Happy Hacking!" << endl << endl;

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

                this->ExecuteString(
                    String::NewFromUtf8(SContext->GetIsolate(), Code).ToLocalChecked(),
                    ""
                );

                while(platform::PumpMessageLoop(SPlatform, SContext->GetIsolate()))
                    continue;
                
                cout << endl;
            }
        }

        void CreateGlobalEnvironment(){
            this->global = ObjectTemplate::New(this->isolate);
        }

        void ZendaMethods(){
            this->CreateMethod("version", Version);

            this->CreateMethod("creator", Creator);

            this->CreateMethod("getcwd", GetCurrentWorkingDirectory);

            this->CreateMethod("sleep", Sleep);

            this->CreateMethod("pythonString", PythonString);

            this->CreateMethod("pythonFile", PythonFile);
        }

        void ZendaObjects(){
            this->CreateObject("console")
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

            this->CreateObject("system")
                .SetPropertyMethod("platform", SystemPlatform)
                .SetPropertyMethod("execute", SystemExecute)
                .Register();
        }

        void ZendaJSFiles(){
        }

        void ReportException(TryCatch* try_catch){
            String::Utf8Value exception(this->GetIsolate(), try_catch->Exception());

            const char* ExceptionString = ToCString(exception);

            Local<Message> message = try_catch->Message();

            if(message.IsEmpty())
                cout << ExceptionString << endl;
            else {
                String::Utf8Value Filename(
                    this->GetIsolate(), message->GetScriptOrigin().ResourceName()
                );

                const char* FilenameString = ToCString(Filename);

                int LineNumber = message->GetLineNumber(
                    this->GetIsolate()->GetCurrentContext()
                ).FromJust();
                
                cout << "ZendaJS [Error in line " << to_string(LineNumber) << "] - [" << FilenameString << "]" << endl;
                cout << endl << "-> " << ExceptionString << endl << endl;

                String::Utf8Value SourceLine(
                    this->GetIsolate(),
                        message->GetSourceLine(this->GetIsolate()->GetCurrentContext()).ToLocalChecked()
                );

                const char* SourceLineString = ToCString(SourceLine);

                cout << SourceLineString << endl;

                unsigned int 
                    Start = message->GetStartColumn(
                        this->GetIsolate()->GetCurrentContext()
                    ).FromJust(),

                    End = message->GetEndColumn(
                        this->GetIsolate()->GetCurrentContext()
                    ).FromJust();

                    for(unsigned int i = 0; i < Start; i++) 
                        fprintf(stderr, " ");

                    for(unsigned int i = Start; i < End; i++)
                        fprintf(stderr, "^");

                cout << endl;
            }
        }

        bool ExecuteFile(const char* Filename){
            Local<String> Source;

            if(!ReadFileUsingV8(Filename, this->GetIsolate()).ToLocal(&Source))
                return false;

            if(!this->ExecuteString(Source, Filename))
                return false;

            return true;
        }

        bool ExecuteString(Local<String> Source, const char* Filename){
            TryCatch try_catch(this->GetIsolate());

            ScriptOrigin origin(
                String::NewFromUtf8(this->GetIsolate(), Filename, NewStringType::kNormal).ToLocalChecked()
            );

            Local<Script> LScript;

            if(!Script::Compile(this->GetIsolate()->GetCurrentContext(), Source, &origin).ToLocal(&LScript)){
                this->ReportException(&try_catch);
                
                return false;
            }else{
                Local<Value> Output;

                if(!LScript->Run(this->GetIsolate()->GetCurrentContext()).ToLocal(&Output)){
                    assert(try_catch.HasCaught());
                        
                    this->ReportException(&try_catch);
                        
                    return false;
                }else{
                    assert(!try_catch.HasCaught());
                        
                    return true;
                }
            }
        }

        void CreateMethod(const char* MethodName, void(*Callback)(const FunctionCallbackInfo<Value>& Arguments)){
            this->GetGlobal()->Set(
                String::NewFromUtf8(this->GetIsolate(), MethodName, NewStringType::kNormal).ToLocalChecked(),
                
                FunctionTemplate::New(this->GetIsolate(), Callback)
            );
        }


        void AddZendaJSFile(string Path){
            this->ZendaJSCoreFiles.push_back(Path);
        }

        void Initialize(int argc, char* argv[]){
                this->CreatePlatform(argv);

                this->CreateVM();

            {
                Isolate::Scope IsolateScope(this->GetIsolate());

                HandleScope Scope(this->GetIsolate());

                this->CreateGlobalEnvironment();

                this->ZendaMethods();

                for(unsigned short int i = 1; i < argc; ++i){
                    const char* Argument = argv[i];

                    Local<Context> LContext = this->CreateLocalContext();

                    Context::Scope ContextScope(LContext);

                    this->ZendaObjects();

                    this->LoadZendaJSFiles();

                    if(!strcmp(Argument, "--shell")){
                        this->Shell(LContext, platform.get());
                        break;
                    }else if(!strcmp(Argument, "--version")){
                        PrintVersion();
                        break;
                    }else if(!strcmp(Argument, "--creator")){
                        PrintCreator();
                        break;
                    }else{
                        char* Contents = ReadFile(argv[i]);

                        Local<Module> LModule = Modules::Check(Modules::Load(Contents, argv[i], LContext), LContext);

                        Local<Value> Returned = Modules::Execute(LModule, LContext);
                    }
                }
            }

            this->ShutdownVM();
        }
                
        ObjectCreator CreateObject(const char* ObjectName){
            ObjectCreator ObjectCreatorInstance(this->GetIsolate(), ObjectName);

            return ObjectCreatorInstance;
        }
};