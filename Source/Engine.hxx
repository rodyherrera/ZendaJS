/***
 * Copyright (C) Rodolfo Herrera Hernandez. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root 
 * for full license information.
 *
 * =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
 *
 * For related information - https://github.com/rodiihernandezz/ZendaJS/
 *
 * =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
 ****/
 
namespace Zenda::Engine{
    static const std::string GetNextArgument(const std::string CurrentArgument);
    static void MatchWithArgument(v8::Local<v8::Context> Context);
    static inline void ExecuteScript(const std::string ScriptLocation, v8::Local<v8::Context> Context);
    static void Shell(v8::Local<v8::Context> Context);
    static const bool ExecuteString(v8::Local<v8::String> Source);
    static inline void LoadZ8();

    static const std::string GetNextArgument(const std::string CurrentArgument){
        try{
            auto IndexOfCurrentArgument = std::find(Zenda::Definitions::CallArguments.begin(), Zenda::Definitions::CallArguments.end(), CurrentArgument);
            if(IndexOfCurrentArgument != Zenda::Definitions::CallArguments.end())
                return Zenda::Definitions::CallArguments.at(IndexOfCurrentArgument - Zenda::Definitions::CallArguments.begin() + 1);
            throw 0;
        }catch(...){
            std::cout << Zenda::Definitions::InvalidArgumentFormatText << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    static inline void LoadZ8(){
        const std::string SourceFile = Zenda::Algorithms::SourceCodeLocation(Zenda::Definitions::Z8);
        ExecuteString(
            Zenda::Shortcuts::V8String(
                Zenda::Definitions::Isolate, Zenda::FileSystem::ReadFile(SourceFile) + "\n").As<v8::String>());
    }

    static void MatchWithArgument(v8::Local<v8::Context> Context){
        if(Zenda::Definitions::CallArguments.size() >= 1){
            for(auto&Argument : Zenda::Definitions::CallArguments){
                const std::string CharArgument = Argument;
                if(!CharArgument.compare("creator"))
                    std::cout << ZENDA_CREATOR << std::endl;
                else if(!CharArgument.compare("version"))
                    std::cout << ZENDA_VERSION << std::endl;
                else if(!CharArgument.compare("shell"))
                    Shell(Context);
                else if(!CharArgument.compare("command"))
                    ExecuteScript(
                        Zenda::Algorithms::SourceCodeLocation("/Source/External/Arguments/Command.js"), Context);
                else if(!CharArgument.compare("init"))
                    ExecuteScript(
                        Zenda::Algorithms::SourceCodeLocation("/Source/External/Arguments/Initialize.js"), Context);
                else if(!CharArgument.compare("about"))
                    ExecuteScript(
                        Zenda::Algorithms::SourceCodeLocation("/Source/External/Arguments/About.js"), Context);
                    else if(!CharArgument.compare("run")){
                    const std::string MaybeFile = GetNextArgument(CharArgument);
                    if(Zenda::FileSystem::FileExists(MaybeFile)){
                        ExecuteScript(MaybeFile, Context);
                    }else{
                        std::cout << " * The requested file <" << MaybeFile << "> was not found." << std::endl;
                        exit(EXIT_FAILURE);
                    }                   
                }else break;
                exit(EXIT_SUCCESS);
            }
        }

        std::cout << std::endl << Zenda::Definitions::HelpText << std::endl << std::endl;
    }

    static inline void ExecuteScript(const std::string ScriptLocation, v8::Local<v8::Context> Context){
        Zenda::Definitions::WorkingDirectory = Zenda::Algorithms::CurrentWorkingDirectory();
        LoadZ8();
        v8::Local<v8::Module> Module = Zenda::JavaScript::Modules::Check(
            Zenda::JavaScript::Modules::Load(
                Zenda::FileSystem::ReadFile(ScriptLocation),
                ScriptLocation, Context), Context);
        v8::Local<v8::Value> Returned = Zenda::JavaScript::Modules::Execute(Module, Context);    
    }

    static void Shell(v8::Local<v8::Context> Context){
        Zenda::Definitions::WorkingDirectory = Zenda::Algorithms::CurrentWorkingDirectory();
        Zenda::Shared::ClearConsole();
        std::cout << Zenda::Definitions::ShellHeaderText << std::endl;
        LoadZ8();
        while(true){
            std::string Code;
            std::cout << " Console -> ";
            std::getline(std::cin, Code);
            v8::HandleScope Scope(Context->GetIsolate());
            ExecuteString(
                Zenda::Shortcuts::V8String(Context->GetIsolate(), Code).As<v8::String>());

            while(v8::platform::PumpMessageLoop(Zenda::Definitions::Platform.get(), Context->GetIsolate()))
                continue;
            std::cout << std::endl;
        }
    }

    static const bool ExecuteString(v8::Local<v8::String> Source){
        v8::TryCatch try_catch(Zenda::Definitions::Isolate);
        v8::ScriptOrigin origin(Zenda::Shortcuts::V8String(
            Zenda::Definitions::Isolate, ""));
        v8::Local<v8::Script> LSCript;
        if(!v8::Script::Compile(Zenda::Definitions::Isolate->GetCurrentContext(), Source, &origin).ToLocal(&LSCript)){
            Zenda::Shortcuts::ReportException(&try_catch);
            return false;
        }
        v8::Local<v8::Value> Output;
        if(!LSCript->Run(Zenda::Definitions::Isolate->GetCurrentContext()).ToLocal(&Output)){
            assert(try_catch.HasCaught());
            Zenda::Shortcuts::ReportException(&try_catch);
            return false;
        }
        assert(!try_catch.HasCaught());
        return true;
    }
};

static void EngineEnvironMethods();
static void EngineEnvironObjects();

#include "Methods/Misc.hxx" 
#include "Methods/Python.hxx"

#include "Objects/Console.hxx"
#include "Objects/System.hxx"
#include "Objects/FileSystem.hxx"
#include "Objects/PyTurtle.hxx"

static void EngineEnvironMethods(){
    Zenda::Shortcuts::CreateMethod("ExecuteScript", Zenda::JavaScript::Methods::Misc::ExecuteScript);
    Zenda::Shortcuts::CreateMethod("Version", Zenda::JavaScript::Methods::Misc::Version);
    Zenda::Shortcuts::CreateMethod("Creator", Zenda::JavaScript::Methods::Misc::Creator);
    Zenda::Shortcuts::CreateMethod("Sleep", Zenda::JavaScript::Methods::Misc::Sleep);
    Zenda::Shortcuts::CreateMethod("PythonString", Zenda::JavaScript::Methods::Python::QuickString);
    Zenda::Shortcuts::CreateMethod("PythonFile", Zenda::JavaScript::Methods::Python::QuickFile);
    Zenda::Shortcuts::CreateMethod("PythonFancyFile", Zenda::JavaScript::Methods::Python::FancyFile);
}

static void EngineEnvironObjects(){
    Zenda::Shortcuts::CreateObject("PyTurtle")
        .SetPropertyMethod("Write", Zenda::JavaScript::Objects::PyTurtle::Write)
        .SetPropertyMethod("Forward", Zenda::JavaScript::Objects::PyTurtle::Forward)
        .SetPropertyMethod("Backward", Zenda::JavaScript::Objects::PyTurtle::Backward)
        .SetPropertyMethod("Right", Zenda::JavaScript::Objects::PyTurtle::Right)
        .SetPropertyMethod("Left", Zenda::JavaScript::Objects::PyTurtle::Left)
        .SetPropertyMethod("GoTo", Zenda::JavaScript::Objects::PyTurtle::GoTo)
        .SetPropertyMethod("SetX", Zenda::JavaScript::Objects::PyTurtle::SetX)
        .SetPropertyMethod("SetY", Zenda::JavaScript::Objects::PyTurtle::SetY)
        .SetPropertyMethod("SetHeading",Zenda::JavaScript:: Objects::PyTurtle::SetHeading)
        .SetPropertyMethod("Home", Zenda::JavaScript::Objects::PyTurtle::Home)
        .SetPropertyMethod("Circle", Zenda::JavaScript::Objects::PyTurtle::Circle)
        .SetPropertyMethod("Dot", Zenda::JavaScript::Objects::PyTurtle::Dot)
        .SetPropertyMethod("Stamp", Zenda::JavaScript::Objects::PyTurtle::Stamp)
        .SetPropertyMethod("ClearStamps", Zenda::JavaScript::Objects::PyTurtle::ClearStamps)
        .SetPropertyMethod("Undo", Zenda::JavaScript::Objects::PyTurtle::Undo)
        .SetPropertyMethod("Speed", Zenda::JavaScript::Objects::PyTurtle::Speed)
        .SetPropertyMethod("Toward", Zenda::JavaScript::Objects::PyTurtle::Towards)
        .SetPropertyMethod("Distance", Zenda::JavaScript::Objects::PyTurtle::Distance)
        .SetPropertyMethod("Degress", Zenda::JavaScript::Objects::PyTurtle::Degress)
        .SetPropertyMethod("PenDown", Zenda::JavaScript::Objects::PyTurtle::PenDown)
        .SetPropertyMethod("PenUp", Zenda::JavaScript::Objects::PyTurtle::PenUp)
        .SetPropertyMethod("PenSize", Zenda::JavaScript::Objects::PyTurtle::PenSize)
        .SetPropertyMethod("PenColor", Zenda::JavaScript::Objects::PyTurtle::PenColor)
        .SetPropertyMethod("FillColor", Zenda::JavaScript::Objects::PyTurtle::FillColor)
        .SetPropertyMethod("BeginFill", Zenda::JavaScript::Objects::PyTurtle::BeginFill)
        .SetPropertyMethod("EndFill", Zenda::JavaScript::Objects::PyTurtle::EndFill)
        .SetPropertyMethod("Reset", Zenda::JavaScript::Objects::PyTurtle::Reset)
        .SetPropertyMethod("Clear", Zenda::JavaScript::Objects::PyTurtle::Clear)
        .SetPropertyMethod("ShowTurtle", Zenda::JavaScript::Objects::PyTurtle::ShowTurtle)
        .SetPropertyMethod("HideTurtle", Zenda::JavaScript::Objects::PyTurtle::HideTurtle)
        .SetPropertyMethod("Shape", Zenda::JavaScript::Objects::PyTurtle::Shape)
        .SetPropertyMethod("ResizeMode", Zenda::JavaScript::Objects::PyTurtle::ResizeMode)
        .SetPropertyMethod("ShapeSize", Zenda::JavaScript::Objects::PyTurtle::ShapeSize)
        .SetPropertyMethod("ShearFactor", Zenda::JavaScript::Objects::PyTurtle::ShearFactor)
        .SetPropertyMethod("Tilt", Zenda::JavaScript::Objects::PyTurtle::Tilt)
        .SetPropertyMethod("SetTiltAngle", Zenda::JavaScript::Objects::PyTurtle::SetTiltAngle)
        .SetPropertyMethod("Mode", Zenda::JavaScript::Objects::PyTurtle::Mode)
        .SetPropertyMethod("ShapeTransform", Zenda::JavaScript::Objects::PyTurtle::ShapeTransform)
        .SetPropertyMethod("BeginPoly", Zenda::JavaScript::Objects::PyTurtle::BeginPoly)
        .SetPropertyMethod("EndPoly", Zenda::JavaScript::Objects::PyTurtle::EndPoly)
        .SetPropertyMethod("WindowBackgroundColor", Zenda::JavaScript::Objects::PyTurtle::WindowBackgroundColor)
        .SetPropertyMethod("WindowBackgroundImage", Zenda::JavaScript::Objects::PyTurtle::WindowBackgroundImage)
        .SetPropertyMethod("WindowClearScreen", Zenda::JavaScript::Objects::PyTurtle::WindowClearScreen)
        .SetPropertyMethod("WindowResetScreen", Zenda::JavaScript::Objects::PyTurtle::WindowResetScreen)
        .SetPropertyMethod("WindowSize", Zenda::JavaScript::Objects::PyTurtle::WindowSize)
        .SetPropertyMethod("WindowSetWorldCoordinates", Zenda::JavaScript::Objects::PyTurtle::WindowSetWorldCoordinates)
        .SetPropertyMethod("WindowDelay", Zenda::JavaScript::Objects::PyTurtle::WindowDelay)
        .SetPropertyMethod("WindowColorMode", Zenda::JavaScript::Objects::PyTurtle::WindowColorMode)
        .SetPropertyMethod("WindowTracer", Zenda::JavaScript::Objects::PyTurtle::WindowTracer)
        .SetPropertyMethod("WindowUpdate", Zenda::JavaScript::Objects::PyTurtle::WindowUpdate)
        .SetPropertyMethod("WindowBye", Zenda::JavaScript::Objects::PyTurtle::WindowBye)
        .SetPropertyMethod("WindowExitOnClick", Zenda::JavaScript::Objects::PyTurtle::WindowExitOnClick)
        .SetPropertyMethod("WindowTitle", Zenda::JavaScript::Objects::PyTurtle::WindowTitle)
        .SetPropertyMethod("Execute", Zenda::JavaScript::Objects::PyTurtle::Execute)
        .SetPropertyMethod("ClearCodeBuffer", Zenda::JavaScript::Objects::PyTurtle::ClearCodeBuffer)
        .SetPropertyMethod("Initialize", Zenda::JavaScript::Objects::PyTurtle::Initialize)
    .Register();

    Zenda::Shortcuts::CreateObject("Console")
        .SetPropertyMethod("Log",Zenda::JavaScript::Objects::Console::Log)
        .SetPropertyMethod("Error", Zenda::JavaScript::Objects::Console::Error)
        .SetPropertyMethod("Warning", Zenda::JavaScript::Objects::Console::Warning)
        .SetPropertyMethod("Information", Zenda::JavaScript::Objects::Console::Information)
        .SetPropertyMethod("Success", Zenda::JavaScript::Objects::Console::Success)
        .SetPropertyMethod("Input", Zenda::JavaScript::Objects::Console::Input)
        .SetPropertyMethod("Clear", Zenda::JavaScript::Objects::Console::Clear)
        .SetPropertyMethod("SetColor", Zenda::JavaScript::Objects::Console::SetColor)
        .SetPropertyMethod("SetStyle", Zenda::JavaScript::Objects::Console::SetStyle)
        .SetPropertyMethod("SetBackground", Zenda::JavaScript::Objects::Console::SetBackground)
        .SetPropertyMethod("GetColor", Zenda::JavaScript::Objects::Console::GetColor)
        .SetPropertyMethod("GetStyle", Zenda::JavaScript::Objects::Console::GetStyle)
        .SetPropertyMethod("GetBackground", Zenda::JavaScript::Objects::Console::GetBackground)
    .Register();

    Zenda::Shortcuts::CreateObject("System")
        .SetPropertyMethod("Threads", Zenda::JavaScript::Objects::System::Threads)
        .SetPropertyMethod("SourceCodeLocation", Zenda::JavaScript::Objects::System::SourceCodeLocation)
        .SetPropertyMethod("CommandOutput", Zenda::JavaScript::Objects::System::CommandOutput)
        .SetPropertyMethod("Platform", Zenda::JavaScript::Objects::System::Platform)
        .SetPropertyMethod("Execute", Zenda::JavaScript::Objects::System::Execute)
        .SetPropertyMethod("Arguments", Zenda::JavaScript::Objects::System::Arguments)
        .SetPropertyMethod("ExitSuccess", Zenda::JavaScript::Objects::System::ExitSuccess)
        .SetPropertyMethod("ExitFailure", Zenda::JavaScript::Objects::System::ExitFailure)
        .SetPropertyMethod("CurrentWorkingDirectory", Zenda::JavaScript::Objects::System::CurrentWorkignDirectory)
    .Register();
    
    Zenda::Shortcuts::CreateObject("FileSystem")
        .SetPropertyMethod("Copy", Zenda::JavaScript::Objects::FileSystem::Copy)
        .SetPropertyMethod("Move", Zenda::JavaScript::Objects::FileSystem::Move)
        .SetPropertyMethod("FileExists", Zenda::JavaScript::Objects::FileSystem::FileExists)
        .SetPropertyMethod("CountLines", Zenda::JavaScript::Objects::FileSystem::CountLines)
        .SetPropertyMethod("CopyFileContent", Zenda::JavaScript::Objects::FileSystem::CopyFileContent)
        .SetPropertyMethod("Remove", Zenda::JavaScript::Objects::FileSystem::Remove)
        .SetPropertyMethod("Rename", Zenda::JavaScript::Objects::FileSystem::Rename)
        .SetPropertyMethod("IsFile", Zenda::JavaScript::Objects::FileSystem::IsFile)
        .SetPropertyMethod("IsEmptyDirectory", Zenda::JavaScript::Objects::FileSystem::IsEmptyDirectory)
        .SetPropertyMethod("IsDirectory", Zenda::JavaScript::Objects::FileSystem::IsDirectory)
        .SetPropertyMethod("IsBlockFile", Zenda::JavaScript::Objects::FileSystem::IsBlockFile)
        .SetPropertyMethod("IsCharacterFile", Zenda::JavaScript::Objects::FileSystem::IsCharacterFile)
        .SetPropertyMethod("IsSymlink", Zenda::JavaScript::Objects::FileSystem::IsSymLink)
        .SetPropertyMethod("IsFifo", Zenda::JavaScript::Objects::FileSystem::IsFifo)
        .SetPropertyMethod("IsSocket", Zenda::JavaScript::Objects::FileSystem::IsSocket)
        .SetPropertyMethod("CreateFile", Zenda::JavaScript::Objects::FileSystem::CreateFile)
        .SetPropertyMethod("CreateFolder", Zenda::JavaScript::Objects::FileSystem::CreateFolder)
        .SetPropertyMethod("RemoveFile", Zenda::JavaScript::Objects::FileSystem::RemoveFile)
        .SetPropertyMethod("RemoveFolder", Zenda::JavaScript::Objects::FileSystem::RemoveFolder)
        .SetPropertyMethod("QuickReadFile", Zenda::JavaScript::Objects::FileSystem::QuickReadFile)
        .SetPropertyMethod("ReadFile", Zenda::JavaScript::Objects::FileSystem::ReadFile)
        .SetPropertyMethod("QuickFileSize", Zenda::JavaScript::Objects::FileSystem::QuickFileSize)
        .SetPropertyMethod("FileSize", Zenda::JavaScript::Objects::FileSystem::FileSize)
        .SetPropertyMethod("QuickWriteFile", Zenda::JavaScript::Objects::FileSystem::QuickWriteFile)
        .SetPropertyMethod("WriteFile", Zenda::JavaScript::Objects::FileSystem::WriteFile)
        .SetPropertyMethod("QuickRewriteFile", Zenda::JavaScript::Objects::FileSystem::QuickRewriteFile)
        .SetPropertyMethod("RewriteFile", Zenda::JavaScript::Objects::FileSystem::RewriteFile)
        .SetPropertyMethod("ListDirectory", Zenda::JavaScript::Objects::FileSystem::ListDirectory)
    .Register();
}

namespace Zenda::Engine{
    static void Initialize(int argc, char* argv[]);

    static void Initialize(int argc, char* argv[]){
        for(unsigned short int Iterator = 1; Iterator < argc; ++Iterator)
            Zenda::Definitions::CallArguments.push_back(argv[Iterator]);
        
        // * Creating platform
        v8::V8::InitializeICUDefaultLocation(argv[0]);
        v8::V8::InitializeExternalStartupData(argv[0]);
        Zenda::Definitions::Platform = v8::platform::NewDefaultPlatform();
        v8::V8::InitializePlatform(Zenda::Definitions::Platform.get());
        v8::V8::Initialize();

        // * Creating virtual machine
        Zenda::Definitions::CreateParameters.array_buffer_allocator = v8::ArrayBuffer::Allocator::NewDefaultAllocator();
        Zenda::Definitions::Isolate = v8::Isolate::New(Zenda::Definitions::CreateParameters);
        Zenda::Definitions::Isolate->SetHostImportModuleDynamicallyCallback(Zenda::JavaScript::Modules::CallDynamic);

        {
            // * Mounting Zenda
            v8::Isolate::Scope IsolateScope(Zenda::Definitions::Isolate);
            v8::HandleScope Scope(Zenda::Definitions::Isolate);
            Zenda::Definitions::Global = v8::ObjectTemplate::New(Zenda::Definitions::Isolate);
            // * Calling the function that loads the methods
            EngineEnvironMethods();
            v8::Local<v8::Context> Context = v8::Context::New(
                Zenda::Definitions::Isolate, NULL, Zenda::Definitions::Global);
            v8::Context::Scope ContextScope(Context);
            // * Calling the function that loads the objects
            EngineEnvironObjects();
            // * We continue with the execution 
            // * depending on the arguments that were 
            // * given to the executable.
            MatchWithArgument(Context);
        }

        // * Shutdown virtual machine
        Zenda::Definitions::Isolate->Dispose();
        v8::V8::Dispose();
        v8::V8::ShutdownPlatform();
        delete Zenda::Definitions::CreateParameters.array_buffer_allocator;
    }
};
