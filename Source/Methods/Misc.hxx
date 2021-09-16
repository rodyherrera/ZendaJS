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

namespace Zenda::JavaScript::Methods::Misc{
    static inline void Version(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void Creator(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static void ExecuteScript(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void Sleep(const v8::FunctionCallbackInfo<v8::Value>& Arguments);

    static inline void Version(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        std::cout << ZENDA_VERSION << std::endl;
    }

    static inline void Creator(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        std::cout << ZENDA_CREATOR << std::endl;
    }

    static void ExecuteScript(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        if(Arguments[0]->IsUndefined())
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "To be able to execute one or more files you must first indicate them as a parameter, we are not guessers.");
        else
            for(unsigned short int Iterator = 0; Iterator < Arguments.Length(); Iterator++){
                v8::HandleScope Scope(Arguments.GetIsolate());
                v8::String::Utf8Value RequestedFile(Arguments.GetIsolate(), Arguments[Iterator]);
                std::string CharFile = std::string(*RequestedFile);
                std::string Contents = Zenda::FileSystem::ReadFile(CharFile);
                v8::Local<v8::Module> LModule = Zenda::JavaScript::Modules::Check(Zenda::JavaScript::Modules::Load(
                    Contents, CharFile, Arguments.GetIsolate()->GetCurrentContext()), Arguments.GetIsolate()->GetCurrentContext());
                v8::Local<v8::Value> Returned = Zenda::JavaScript::Modules::Execute(LModule, Arguments.GetIsolate()->GetCurrentContext());
            }
    }

    static inline void Sleep(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if(Arguments[0]->IsUndefined())
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "In order to sleep you need to indicate the time in milliseconds.");
        else
            sleep(Arguments[0]->NumberValue(Arguments.GetIsolate()->GetCurrentContext()).FromJust() / 1000);
    }
};