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

namespace Zenda::JavaScript::Objects::Console{
    static void Log(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void Error(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void Warning(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void Information(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void Success(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void SetColor(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void SetStyle(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void SetBackground(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void GetBackground(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void GetStyle(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void GetColor(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void Clear(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static void Input(const v8::FunctionCallbackInfo<v8::Value>& Arguments);

    static void Log(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        for(unsigned short int Iterator = 0; Iterator < Arguments.Length(); Iterator++){
            v8::HandleScope Scope(Arguments.GetIsolate());
            if(Iterator > 0) std::cout << " ";
            v8::String::Utf8Value Text(Arguments.GetIsolate(), Arguments[Iterator]);
            std::cout << std::string(*Text);
        }
        std::cout << std::endl;
    }

    static inline void Error(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        std::cout << Zenda::Shared::ConsoleColor("red");
        Log(Arguments);
        std::cout << Zenda::Shared::ConsoleStyle("normal");
    }

    static inline void Warning(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        std::cout << Zenda::Shared::ConsoleColor("yellow");
        Log(Arguments);
        std::cout << Zenda::Shared::ConsoleStyle("normal");
    }

    static inline void Information(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        std::cout << Zenda::Shared::ConsoleColor("beige");
        Log(Arguments);
        std::cout << Zenda::Shared::ConsoleStyle("normal");
    }

    static inline void Success(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        std::cout << Zenda::Shared::ConsoleColor("green");
        Log(Arguments);
        std::cout << Zenda::Shared::ConsoleStyle("normal");
    }

    static inline void SetColor(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if(Arguments[0]->IsUndefined())
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "You need to send a color to be able to set it on the .");
        else{
            v8::String::Utf8Value ColorIdentifier(Arguments.GetIsolate(), Arguments[0]);
            const std::string CharColorIdentifier = std::string(*ColorIdentifier);
            std::cout << Zenda::Shared::ConsoleColor(CharColorIdentifier);
        }
    }

    static inline void SetStyle(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if(Arguments[0]->IsUndefined())
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(),  "You need to send a style to be able to set it on the .");
        else{
            v8::String::Utf8Value StyleIdentifier(Arguments.GetIsolate(), Arguments[0]);
            const std::string CharStyleIdentifier = std::string(*StyleIdentifier);
            std::cout << Zenda::Shared::ConsoleStyle(CharStyleIdentifier);
        }
    }

    static inline void SetBackground(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if(Arguments[0]->IsUndefined())
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "You need to send a background to be able to set it on the .");
        else{
            v8::String::Utf8Value BackgroundIdentifier(Arguments.GetIsolate(), Arguments[0]);
            const std::string CharBackgroundIdentifier = std::string(*BackgroundIdentifier);
            std::cout << Zenda::Shared::ConsoleBackground(CharBackgroundIdentifier);
        }
    }

    static inline void GetBackground(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if(Arguments[0]->IsUndefined())
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "You need to submit a color to get its return value.");
        else{
            v8::String::Utf8Value BackgroundIdentifier(Arguments.GetIsolate(), Arguments[0]);
            const std::string CharBackgroundIdentifier = std::string(*BackgroundIdentifier);
            Arguments.GetReturnValue().Set(Zenda::Shortcuts::V8String(Arguments.GetIsolate(), Zenda::Shared::ConsoleBackground(CharBackgroundIdentifier)));
        }
    }

    static inline void GetStyle(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if(Arguments[0]->IsUndefined())
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "You need to submit a style to get its return value.");
        else{
            v8::String::Utf8Value StyleIdentifier(Arguments.GetIsolate(), Arguments[0]);
            const std::string CharStyleIdentifier = std::string(*StyleIdentifier);
            Arguments.GetReturnValue().Set(Zenda::Shortcuts::V8String(Arguments.GetIsolate(), Zenda::Shared::ConsoleStyle(CharStyleIdentifier)));
        }
    }

    static inline void GetColor(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if(Arguments[0]->IsUndefined())
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "You need to submit a color to get its return value.");
        else{
            v8::String::Utf8Value ColorIdentifier(Arguments.GetIsolate(), Arguments[0]);
            const std::string CharColorIdentifier = std::string(*ColorIdentifier);
            Arguments.GetReturnValue().Set(Zenda::Shortcuts::V8String(Arguments.GetIsolate(), Zenda::Shared::ConsoleColor(CharColorIdentifier)));
        }
    }

    static inline void Clear(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        Zenda::Shared::ClearConsole();
    }
            
    static void Input(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        unsigned short int ArgumentsLength = Arguments.Length();
        if(ArgumentsLength == 0)
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "You need to enter a value to ask/report the user.");
        else{
            for(unsigned short int Iterator = 0; Iterator < Arguments.Length(); Iterator++){
                v8::HandleScope scope(Arguments.GetIsolate());
                if(Iterator > 0) std::cout << " ";
                v8::String::Utf8Value Text(Arguments.GetIsolate(), Arguments[Iterator]);
                const std::string CharText = std::string(*Text);
                std::cout << CharText;
            }
            std::string Response;
            std::getline(std::cin, Response);
            Arguments.GetReturnValue().Set(Zenda::Shortcuts::V8String(Arguments.GetIsolate(), Response));
        }
    }
};