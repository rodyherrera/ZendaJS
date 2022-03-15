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

#define WEBVIEW_IMPLEMENTATION
#include "WebView.hxx"

namespace Zenda::JavaScript::Methods::Misc{
    static inline void Version(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void Creator(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static void ExecuteScript(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void Sleep(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void UseWebView(const v8::FunctionCallbackInfo<v8::Value>& Arguments);

    static inline void UseWebView(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        v8::Local<v8::Object> Configuration = Arguments[0].As<v8::Object>();
        std::string Title = Zenda::Shortcuts::GetKeyValue(Arguments.GetIsolate(), Configuration, "Title", "ZendaJS - Default WebView Window Title");
        std::string Website = Zenda::Shortcuts::GetKeyValue(Arguments.GetIsolate(), Configuration, "Website", "https://github.com/codewithrodi/ZendaJS/");
        std::string Evaluate = Zenda::Shortcuts::GetKeyValue(Arguments.GetIsolate(), Configuration, "Evaluate", "");
        std::string Hint = Zenda::Algorithms::StringToUpper(
                Zenda::Shortcuts::GetKeyValue(Arguments.GetIsolate(), Configuration, "Hint", ""));
        unsigned short int Width = Zenda::Shortcuts::GetKeyValueAsInteger(Arguments.GetIsolate(), Configuration, "Width", "800");
        unsigned short int Height = Zenda::Shortcuts::GetKeyValueAsInteger(Arguments.GetIsolate(), Configuration, "Height", "600");
        unsigned short int SizeMode = WEBVIEW_HINT_NONE;
        if(Hint == "STATIC")
            SizeMode = WEBVIEW_HINT_FIXED;
        else if(Hint == "MAXIMUM")
            SizeMode = WEBVIEW_HINT_MAX;
        else if(Hint == "MINIMUM")
            SizeMode = WEBVIEW_HINT_MIN;
        webview::webview WebView(true, nullptr);
        WebView.set_title(Title);
        WebView.eval(Evaluate);
        WebView.set_size(Width, Height, SizeMode);
        WebView.navigate(Website);
        WebView.run();
    }

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
