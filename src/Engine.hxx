#include <iostream>
#include "Utility.hxx"
using namespace std;

#include <v8.h>
#include <libplatform/libplatform.h>
using namespace v8;

#include <cassert>
#include <cstdlib>

#ifdef __WIN32
	#include <Windows.h>
#else
	#include <unistd.h>
#endif

#include <Python.h>

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

        ObjectCreator SetPropertyMethod(const char* propertymethod, void (*callback)(const FunctionCallbackInfo<Value>& args)){
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

        static void Version(const FunctionCallbackInfo<Value>& args){
            PrintVersion();
        }

        static void Creator(const FunctionCallbackInfo<Value>& args){
            PrintCreator();
        }

        static void PythonString(const FunctionCallbackInfo<Value>& args){
            Py_Initialize();
            
            for(unsigned short int i = 0; i < args.Length(); i++){
                String::Utf8Value Code(args.GetIsolate(), args[i]);

                char const* CharCode = ToCString(Code);

                PyRun_SimpleString(CharCode);
            }

            Py_Finalize();
        }

        static void PythonFile(const FunctionCallbackInfo<Value>& args){
            Py_Initialize();

            for(unsigned short int i = 0; i < args.Length(); i++){
                String::Utf8Value File(args.GetIsolate(), args[i]);

                char const* CharFile = ToCString(File);

                FILE* PyFile;

                PyFile = fopen(CharFile, "r");

                if(PyFile == NULL)
                    cout << "ZendaJS -> An error ocurred while trying open <" << CharFile << "> in pythonFile() function." << endl;
                else
                    PyRun_SimpleFile(PyFile, CharFile);
            }

            Py_Finalize();
        }

        static void Sleep(const FunctionCallbackInfo<Value>& args){
            String::Utf8Value SleepTime(args.GetIsolate(), args[0]);

            char const* CharSleepTime = ToCString(SleepTime);

            sleep(stoi(CharSleepTime));
        }

        static void ConsoleLog(const FunctionCallbackInfo<Value>& args){
            for(unsigned short int i = 0; i < args.Length(); i++){
                if(i > 0) cout << " ";

                String::Utf8Value Text(args.GetIsolate(), args[i]);

                const char* CharText = ToCString(Text);

                cout << CharText;
            }

            cout << endl;
        }

        static void ConsoleSetColor(const FunctionCallbackInfo<Value>& args){
            String::Utf8Value ColorIdentifier(args.GetIsolate(), args[0]);
            
            const char* CharColorIdentifier = ToCString(ColorIdentifier);
            
            cout << ConsoleColor(CharColorIdentifier);
        }

        static void ConsoleSetStyle(const FunctionCallbackInfo<Value>& args){
            String::Utf8Value StyleIdentifier(args.GetIsolate(), args[0]);

            const char* CharStyleIdentifier = ToCString(StyleIdentifier);

            cout << ConsoleStyle(CharStyleIdentifier);
        }

        static void ConsoleSetBackground(const FunctionCallbackInfo<Value>& args){
            String::Utf8Value BackgroundIdentifier(args.GetIsolate(), args[0]);
            
            const char* CharBackgroundIdentifier = ToCString(BackgroundIdentifier);
            
            cout << ConsoleBackground(CharBackgroundIdentifier);
        }

        static void ConsoleGetBackground(const FunctionCallbackInfo<Value>& args){
            String::Utf8Value BackgroundIdentifier(args.GetIsolate(), args[0]);

            const char* CharBackgroundIdentifier = ToCString(BackgroundIdentifier);

            string Background = ConsoleBackground(CharBackgroundIdentifier);

            args.GetReturnValue().Set(
                String::NewFromUtf8(
                    args.GetIsolate(),
                    Background.c_str(),
                    NewStringType::kNormal,
                    static_cast<int>(Background.length())
                ).ToLocalChecked()
            );
        }

        static void ConsoleGetStyle(const FunctionCallbackInfo<Value>& args){
            String::Utf8Value StyleIdentifier(args.GetIsolate(), args[0]);
            
            const char* CharStyleIdentifier = ToCString(StyleIdentifier);
            
            string Style = ConsoleStyle(CharStyleIdentifier);
            
            args.GetReturnValue().Set(
                String::NewFromUtf8(
                    args.GetIsolate(),
                    Style.c_str(),
                    NewStringType::kNormal,
                    static_cast<int>(Style.length())
                ).ToLocalChecked()
            );
        }

        static void ConsoleGetColor(const FunctionCallbackInfo<Value>& args){
            String::Utf8Value ColorIdentifier(args.GetIsolate(), args[0]);

            const char* CharColorIdentifier = ToCString(ColorIdentifier);

            string Color = ConsoleColor(CharColorIdentifier);

            args.GetReturnValue().Set(
                String::NewFromUtf8(
                    args.GetIsolate(),
                    Color.c_str(),
                    NewStringType::kNormal,
                    static_cast<int>(Color.length())
                ).ToLocalChecked()
            );
        }

        static void ConsoleClear(const FunctionCallbackInfo<Value>& args){
            ClearConsole();
        }
        
        static void ConsoleInput(const FunctionCallbackInfo<Value>& args){
            for(unsigned short int i = 0; i < args.Length(); i++){
                HandleScope scope(args.GetIsolate());

                if(i > 0) cout << " ";

                String::Utf8Value Text(args.GetIsolate(), args[i]);

                const char* CharText = ToCString(Text);

                cout << CharText;
            }

            string Response;

            getline(cin, Response);

            args.GetReturnValue().Set(
                String::NewFromUtf8(
                    args.GetIsolate(),
                    Response.c_str(),
                    NewStringType::kNormal,
                    static_cast<int>(Response.length())
                ).ToLocalChecked()
            );
        }

        static void SystemExecute(const FunctionCallbackInfo<Value>& args){
            for(unsigned short int i = 0; i < args.Length(); i++){
                HandleScope Scope(args.GetIsolate());

                String::Utf8Value Command(args.GetIsolate(), args[i]);

                const char* CharCommand = ToCString(Command);

                system(CharCommand);
            }
        }

        static void SystemPlatform(const FunctionCallbackInfo<Value>& args){
            string OS = OperativeSystem();

            args.GetReturnValue().Set(
                String::NewFromUtf8(
                    args.GetIsolate(),
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
        }

        void ShutdownVM(){
            this->isolate->Dispose();
            
            V8::Dispose();
            
            V8::ShutdownPlatform();
            
            delete this->create_params.array_buffer_allocator;
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

            if(!this->ReadFile(Filename).ToLocal(&Source))
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

        MaybeLocal<String> ReadFile(const char* Filename){
            FILE* File = fopen(Filename, "rb");

            if(File == NULL)
                return MaybeLocal<String>();

                fseek(File, 0, SEEK_END);

                size_t Size = ftell(File);

                rewind(File);

                char* Characters = new char[Size + 1];

                Characters[Size] = '\0';

                for(size_t i = 0; i < Size;){
                    i += fread(&Characters[i], 1, Size - i, File);

                    if(ferror(File)){
                        fclose(File);
                        
                        return MaybeLocal<String>();
                    }
                }

                fclose(File);

                MaybeLocal<String> Content = String::NewFromUtf8(
                    this->GetIsolate(), Characters, NewStringType::kNormal, static_cast<int>(Size)
                );

                delete[] Characters;

                return Content;
        }

        void CreateMethod(const char* MethodName, void(*Callback)(const FunctionCallbackInfo<Value>& args)){
            this->GetGlobal()->Set(
                String::NewFromUtf8(this->GetIsolate(), MethodName, NewStringType::kNormal).ToLocalChecked(),
                
                FunctionTemplate::New(this->GetIsolate(), Callback)
            );
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
                        auto FileExecution = this->ExecuteFile(Argument);

                        if(!FileExecution)
                            cout << "ZendaJS -> An error ocurred while trying to open the file <" << Argument << ">." << endl;
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