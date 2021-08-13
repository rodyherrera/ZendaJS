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
    unsigned short int Iterator = 0;
    for(Iterator; Iterator < Arguments.Length(); Iterator++){
        HandleScope Scope(Arguments.GetIsolate());
        String::Utf8Value File(Arguments.GetIsolate(), Arguments[Iterator]);
        char* CharFile = strdup(ToCString(File));
        char* Contents = strdup(FSReadFile(CharFile));
        Local<Module> LModule = CheckModule(LoadModule(Contents, CharFile, Arguments.GetIsolate()->GetCurrentContext()), Arguments.GetIsolate()->GetCurrentContext());
        Local<Value> Returned = ExecuteModule(LModule, Arguments.GetIsolate()->GetCurrentContext());
    }
}

static void Sleep(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    String::Utf8Value SleepTime(Arguments.GetIsolate(), Arguments[0]);
    char const* CharSleepTime = ToCString(SleepTime);
    sleep(stoi(CharSleepTime) / 1000);
}