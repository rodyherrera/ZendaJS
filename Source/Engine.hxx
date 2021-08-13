/***
 * Copyright (C) Rodolfo Herrera Hernandez. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root 
 * for full license information.
 *
 * =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
 *
 * Engine.hxx: Main file that makes the decisions of the developer when running Zenda.
 *
 * This file imports all the required modules, starts the objects and methods, 
 * decides what to do with the arguments of the call to the executable, this is 
 * the base code, if something fails here the whole program will fail.
 *
 * For related information - https://github.com/rodiihernandezz/ZendaJS/
 *
 * =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
 ****/

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
#include <experimental/filesystem>

using namespace std;
using namespace v8;
namespace FS = experimental::filesystem;

#include "Global.hxx"

#include "Utils/String.hxx"
#include "Utils/Shared.hxx"
#include "Utils/FileSystem.hxx"

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
static inline void CreateMethod(const char* MethodName, void(*Callback)(const FunctionCallbackInfo<Value>& Arguments));
static inline void AddCoreJavascriptFile(string Path);
static inline void CreateGlobalEnvironment();
static inline Local<Context> CreateLocalContext();
static void CreatePlatform(char* argv[]);
static void Initialize(int argc, char* argv[]);
static void ExecuteZendaScript(const char* ScriptLocation, Local<Context> LContext);
static bool ExecuteString(Local<String> Source, const char* Filename);
static void Shell(Local<Context> SContext, Platform* SPlatform);
static void CreateVirtualMachine();
static void ShutdownVirtualMachine();
static void EngineEnvironMethods();
static bool ExecuteFile(const char* Filename);
static void EngineEnvironObjects();

static void ExecuteZendaScript(const char* ScriptLocation, Local<Context> LContext){
    WorkingDirectory = CurrentWorkingDirectory();
    char* Contents = strdup(FSReadFile(ScriptLocation));
    Local<Module> LModule = CheckModule(LoadModule(Contents, strdup(ScriptLocation), LContext), LContext);
    Local<Value> Returned = ExecuteModule(LModule, LContext);    
}

static inline void CreateMethod(const char* MethodName, void(*Callback)(const FunctionCallbackInfo<Value>& Arguments)){
    ZendaGlobal->Set(
        String::NewFromUtf8(ZendaIsolate, MethodName, NewStringType::kNormal).ToLocalChecked(),
        FunctionTemplate::New(ZendaIsolate, Callback)
    );
}

static inline Local<Context> CreateLocalContext(){
    return Context::New(ZendaIsolate, NULL, ZendaGlobal);
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
    if(!FSReadFileUsingV8(Filename, ZendaIsolate).ToLocal(&Source))
        return false;
    if(!ExecuteString(Source, Filename))
        return false;
    return true;
}

static inline void CreateGlobalEnvironment(){
    ZendaGlobal = ObjectTemplate::New(ZendaIsolate);
}

// Methods
#include "Methods/Misc.hxx" 
#include "Methods/Python.hxx"

static void EngineEnvironMethods(){
    CreateMethod("ExecuteJavascriptFile", ExecuteJavascriptFile);
    CreateMethod("Version", Version);
    CreateMethod("Creator", Creator);
    CreateMethod("Sleep", Sleep);
    CreateMethod("PythonString", PythonQuickString);
    CreateMethod("PythonFile", PythonQuickFile);
    CreateMethod("PythonFancyFile", PythonFancyFile);
}

// Objects
#include "Objects/Console.hxx"
#include "Objects/System.hxx"
#include "Objects/FileSystem.hxx"

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
        .SetPropertyMethod("ExitSuccess", SystemExitSuccess)
        .SetPropertyMethod("ExitFailure", SystemExitFailure)
        .SetPropertyMethod("CurrentWorkingDirectory", SystemCurrentWorkignDirectory)
        .Register();
    
    CreateObject("FileSystem")
        .SetPropertyMethod("Copy", FileSystemCopy)
        .SetPropertyMethod("Move", FileSystemMove)
        .SetPropertyMethod("FileExists", FileSystemFileExists)
        .SetPropertyMethod("CountLines", FileSystemCountLines)
        .SetPropertyMethod("CopyFileContent", FileSystemCopyFileContent)
        .SetPropertyMethod("Remove", FileSystemRemove)
        .SetPropertyMethod("Rename", FileSystemRename)
        .SetPropertyMethod("IsFile", FileSystemIsFile)
        .SetPropertyMethod("IsEmptyDirectory", FileSystemIsEmptyDirectory)
        .SetPropertyMethod("IsDirectory", FileSystemIsDirectory)
        .SetPropertyMethod("IsBlockFile", FileSystemIsBlockFile)
        .SetPropertyMethod("IsCharacterFile", FileSystemIsCharacterFile)
        .SetPropertyMethod("IsSymlink", FileSystemIsSymlink)
        .SetPropertyMethod("IsFifo", FileSystemIsFifo)
        .SetPropertyMethod("IsSocket", FileSystemIsSocket)
        .SetPropertyMethod("CreateFile", FileSystemCreateFile)
        .SetPropertyMethod("CreateFolder", FileSystemCreateFolder)
        .SetPropertyMethod("RemoveFile", FileSystemRemoveFile)
        .SetPropertyMethod("RemoveFolder", FileSystemRemoveFolder)
        .SetPropertyMethod("QuickReadFile", FileSystemQuickReadFile)
        .SetPropertyMethod("ReadFile", FileSystemReadFile)
        .SetPropertyMethod("QuickFileSize", FileSystemQuickFileSize)
        .SetPropertyMethod("FileSize", FileSystemFileSize)
        .SetPropertyMethod("QuickWriteFile", FileSystemQuickWriteFile)
        .SetPropertyMethod("WriteFile", FileSystemWriteFile)
        .SetPropertyMethod("QuickRewriteFile", FileSystemQuickRewriteFile)
        .SetPropertyMethod("RewriteFile", FileSystemRewriteFile)
        .SetPropertyMethod("ListDirectory", FileSystemListDirectory)
        .Register();
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

#include "Installation.hxx"
#include "CLI/Functions.hxx"
#include "CLI/Arguments.hxx"

static void Initialize(int argc, char* argv[]){
    SetCallArguments(argc, argv);
    CreatePlatform(argv);
    CreateVirtualMachine();
    {
        Isolate::Scope IsolateScope(ZendaIsolate);
        HandleScope Scope(ZendaIsolate);
        CreateGlobalEnvironment();
        EngineEnvironMethods();
        Local<Context> LContext = CreateLocalContext();
        Context::Scope ContextScope(LContext);
        EngineEnvironObjects();
        MatchWithArgument(LContext);
    }

    ShutdownVirtualMachine();
}