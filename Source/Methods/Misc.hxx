/***
 * Copyright (C) Rodolfo Herrera Hernandez. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root 
 * for full license information.
 *
 * =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
 *
 * Methods/Misc.hxx: File that groups dynamic methods to be used in JS.
 *
 * For related information - https://github.com/rodiihernandezz/ZendaJS/
 *
 * =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
 ****/

static inline void Version(const FunctionCallbackInfo<Value>& Arguments);
static inline void Creator(const FunctionCallbackInfo<Value>& Arguments);
static void ExecuteJavascriptFile(const FunctionCallbackInfo<Value>& Arguments);
static void Sleep(const FunctionCallbackInfo<Value>& Arguments);

static inline void Version(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    cout << ZendaVersion << endl;
}

static inline void Creator(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    cout << ZendaCreator << endl;
}

static void ExecuteJavascriptFile(const FunctionCallbackInfo<Value>& Arguments){
    if(Arguments[0]->IsUndefined())
        Arguments.GetIsolate()->ThrowException(
            String::NewFromUtf8(
                Arguments.GetIsolate(),
                "To be able to execute one or more files you must first indicate them as a parameter, we are not guessers.",
                NewStringType::kNormal
            ).ToLocalChecked()
        );
    else{
        unsigned short int Iterator = 0;
        for(Iterator; Iterator < Arguments.Length(); Iterator++){
            HandleScope Scope(Arguments.GetIsolate());
            String::Utf8Value RequestedFile(Arguments.GetIsolate(), Arguments[Iterator]);
            char* CharFile = strdup(ToCString(RequestedFile));
            char* Contents = strdup(FSReadFile(CharFile));
            Local<Module> LModule = CheckModule(LoadModule(Contents, CharFile, Arguments.GetIsolate()->GetCurrentContext()), Arguments.GetIsolate()->GetCurrentContext());
            Local<Value> Returned = ExecuteModule(LModule, Arguments.GetIsolate()->GetCurrentContext());
        }
    }
}

static void Sleep(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    if(Arguments[0]->IsUndefined())
        Arguments.GetIsolate()->ThrowException(
            String::NewFromUtf8(
                Arguments.GetIsolate(),
                "In order to sleep you need to indicate the time in milliseconds.",
                NewStringType::kNormal
            ).ToLocalChecked()
        );
    else{
        unsigned int SleepTime = Arguments[0]->NumberValue(Arguments.GetIsolate()->GetCurrentContext()).FromJust();
        sleep(SleepTime / 1000);
    }
}