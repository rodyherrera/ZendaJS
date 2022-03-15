/***
 * Copyright (C) Rodolfo Herrera Hernandez. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root 
 * for full license information.
 *
 * =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
 *
 * For related information - https://github.com/codewithrodi/ZendaJS/
 *
 * =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
 ****/

namespace Zenda::JavaScript::Objects::System{
    static inline void Threads(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void SourceCodeLocation(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static void CommandOutput(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static void Execute(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void Platform(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static void Arguments(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void CurrentWorkignDirectory(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void Exit(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void GetPID(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void GetHeapStatistics(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void ChangeWorkingDirectory(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void SetEnvironmentVariable(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void UnsetEnvironmentVariable(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
    static inline void GetV8Version(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void KillProcess(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void SetUID(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void GetUID(const v8::FunctionCallbackInfo<v8::Value>& Arguments);

    static inline void GetUID(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        Arguments.GetReturnValue().Set(Zenda::Shortcuts::V8Integer(Arguments.GetIsolate(), getuid()));
    }

    static inline void SetUID(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if(Arguments[0]->IsUndefined())
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "To set a new UID you must send it as a parameter.");
        else
            Arguments.GetReturnValue().Set(Zenda::Shortcuts::V8Integer(
                Arguments.GetIsolate(), setuid(v8::Local<v8::Integer>::Cast(Arguments[0])->Value())));
    }

    static inline void KillProcess(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if(Arguments[0]->IsUndefined())
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "To kill the process you must send its PID as a parameter.");
        else{
            pid_t PID = v8::Local<v8::Integer>::Cast(Arguments[0])->Value();
            Arguments.GetReturnValue().Set(Zenda::Shortcuts::V8Integer(Arguments.GetIsolate(), kill(PID, SIGKILL)));
        }
    }

    static inline void GetV8Version(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        Arguments.GetReturnValue().Set(Zenda::Shortcuts::V8String(
                Arguments.GetIsolate(), std::string(v8::V8::GetVersion())));
    }
>>>>>>> New methods for the console and system.
>>>>>>> New methods for the console and system.
>>>>>>> New method in console object and new integrations to the system object.

    static inline void UnsetEnvironmentVariable(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if(Arguments[0]->IsUndefined()){
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "You must indicate the name of the variable that you want to remove from the environment variable of the operating system <PATH>.");
        }else{
            v8::String::Utf8Value Variable(Arguments.GetIsolate(), Arguments[0]);
            unsetenv(*Variable);
        }
    }

    static inline void SetEnvironmentVariable(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if(Arguments[0]->IsUndefined() || Arguments[1]->IsUndefined())
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "You must indicate the name of the variable next to its value to be able to add them to the variable environment of your operating system <PATH>.");
        else{
            v8::String::Utf8Value Variable(Arguments.GetIsolate(), Arguments[0]);
            v8::String::Utf8Value Value(Arguments.GetIsolate(), Arguments[1]);
            setenv(*Variable, *Value, 1);
        }
    }

    static inline void ChangeWorkingDirectory(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if(Arguments[0]->IsUndefined())
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "To be able to change directory, you must send the new working directory as a parameter.");
        else{
            v8::String::Utf8Value Path(Arguments.GetIsolate(), Arguments[0]);
            Arguments.GetReturnValue().Set(Zenda::Shortcuts::V8Integer(Arguments.GetIsolate(), chdir(*Path)));
        }
    }

    static inline void GetHeapStatistics(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::Isolate* Isolate = Arguments.GetIsolate();
        v8::Local<v8::Context> Context = Isolate->GetCurrentContext();
        v8::HandleScope Scope(Isolate);
        v8::HeapStatistics HeapStatistics;
        Isolate->GetHeapStatistics(&HeapStatistics);
        v8::Local<v8::Object> Data = v8::Object::New(Isolate);
        Zenda::Shortcuts::Set(Data, Isolate, "TotalHeapSize", HeapStatistics.total_heap_size());
        Zenda::Shortcuts::Set(Data, Isolate, "UsedHeapSize", HeapStatistics.used_heap_size());
        Zenda::Shortcuts::Set(Data, Isolate, "ExternalMemory", HeapStatistics.external_memory());
        Zenda::Shortcuts::Set(Data, Isolate, "DoesZapGarbage", HeapStatistics.does_zap_garbage());
        Zenda::Shortcuts::Set(Data, Isolate, "HeapSizeLimit", HeapStatistics.heap_size_limit());
        Zenda::Shortcuts::Set(Data, Isolate, "MallocedMemory", HeapStatistics.malloced_memory());
        Zenda::Shortcuts::Set(Data, Isolate, "NumberOfDetachedContexts", HeapStatistics.number_of_detached_contexts());
        Zenda::Shortcuts::Set(Data, Isolate, "NumberOfNativeContexts", HeapStatistics.number_of_native_contexts());
        Zenda::Shortcuts::Set(Data, Isolate, "PeakMallocedMemory", HeapStatistics.peak_malloced_memory());
        Zenda::Shortcuts::Set(Data, Isolate, "TotalAvailableSize", HeapStatistics.total_available_size());
        Zenda::Shortcuts::Set(Data, Isolate, "TotalHeapSizeExecutable", HeapStatistics.total_heap_size_executable());
        Arguments.GetReturnValue().Set(Data);
    }

    static inline void GetPID(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        Arguments.GetReturnValue().Set(Zenda::Shortcuts::V8Integer(Arguments.GetIsolate(), getpid()));
    }

    static inline void Threads(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        Arguments.GetReturnValue().Set(
            Zenda::Shortcuts::V8Number(Arguments.GetIsolate(), std::thread::hardware_concurrency()));
    }

    static inline void SourceCodeLocation(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        Arguments.GetReturnValue().Set(Zenda::Shortcuts::V8String(Arguments.GetIsolate(), Zenda::Algorithms::SourceCodeLocation()));
    }

    static void CommandOutput(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if(Arguments[0]->IsUndefined())
            Zenda::Shortcuts::V8String(Arguments.GetIsolate(), "You need enter a command for get their output.");
        else{
            v8::String::Utf8Value Command(Arguments.GetIsolate(), Arguments[0]);
            Arguments.GetReturnValue().Set(
                Zenda::Shortcuts::V8String(Arguments.GetIsolate(), Zenda::Algorithms::GetOutputOfCommand(
                    std::string(*Command))));
        }
    }

    static void Execute(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        if(Arguments[0]->IsUndefined())
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "You need to enter one or more commands to the Execute method so that you can execute them in the operating .");
        else
            for(unsigned short int Iterator = 0; Iterator < Arguments.Length(); Iterator++){
                v8::HandleScope Scope(Arguments.GetIsolate());
                v8::String::Utf8Value Command(Arguments.GetIsolate(), Arguments[Iterator]);
                system(*Command);
            }
    }

    static inline void Platform(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        Arguments.GetReturnValue().Set(Zenda::Shortcuts::V8String(Arguments.GetIsolate(), Zenda::Shared::OperativeSystem()));
    }

    static void Arguments(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        v8::Local<v8::Context> ArgumentsContext = v8::Context::New(Zenda::Definitions::Isolate);
        v8::Local<v8::Array> ArgumentList = v8::Array::New(Zenda::Definitions::Isolate, Zenda::Definitions::CallArguments.size());
        for(unsigned short int Iterator = 0; Iterator < Zenda::Definitions::CallArguments.size(); Iterator++){
            v8::Local<v8::String> SomeArgument = v8::String::NewFromUtf8(
                Zenda::Definitions::Isolate, Zenda::Definitions::CallArguments.at(Iterator).c_str()).ToLocalChecked();
            v8::Maybe<bool> ArgumentAdded = ArgumentList->Set(ArgumentsContext, Iterator, SomeArgument);
        }
        Arguments.GetReturnValue().Set(ArgumentList);
    }

    static inline void CurrentWorkignDirectory(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        Arguments.GetReturnValue().Set(Zenda::Shortcuts::V8String(Arguments.GetIsolate(), Zenda::Definitions::WorkingDirectory));
    }

    static inline void Exit(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if(Arguments[0]->IsUndefined())
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "In order to exit with a status code you must send it as a parameter.");
        else
            exit(v8::Local<v8::Integer>::Cast(Arguments[0])->Value());
    }
};
