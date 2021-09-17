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

namespace Zenda::JavaScript::Objects::System{
    static inline void Threads(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void SourceCodeLocation(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static void CommandOutput(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static void Execute(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void Platform(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static void Arguments(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void CurrentWorkignDirectory(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void ExitFailure(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void ExitSuccess(const v8::FunctionCallbackInfo<v8::Value>& Arguments);

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

    static inline void ExitFailure(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        exit(EXIT_FAILURE);
    }

    static inline void ExitSuccess(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        exit(EXIT_SUCCESS);
    }
};
