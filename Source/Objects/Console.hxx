/***
 * Copyright (C) Rodolfo Herrera Hernandez. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root 
 * for full license information.
 *
 * =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
 *
 * Objects/Console.hxx: File containing methods for JS related to the Console.
 *
 * Available methods to manipulate and/or interact with the console from JS.
 *
 * For related information - https://github.com/rodiihernandezz/ZendaJS/
 *
 * =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
 ****/

static void ConsoleLog(const FunctionCallbackInfo<Value>& Arguments);
static void ConsoleError(const FunctionCallbackInfo<Value>& Arguments);
static void ConsoleWarning(const FunctionCallbackInfo<Value>& Arguments);
static void ConsoleInformation(const FunctionCallbackInfo<Value>& Arguments);
static void ConsoleSuccess(const FunctionCallbackInfo<Value>& Arguments);
static void ConsoleSetColor(const FunctionCallbackInfo<Value>& Arguments);
static void ConsoleSetStyle(const FunctionCallbackInfo<Value>& Arguments);
static void ConsoleSetBackground(const FunctionCallbackInfo<Value>& Arguments);
static void ConsoleGetBackground(const FunctionCallbackInfo<Value>& Arguments);
static void ConsoleGetStyle(const FunctionCallbackInfo<Value>& Arguments);
static void ConsoleGetColor(const FunctionCallbackInfo<Value>& Arguments);
static void ConsoleClear(const FunctionCallbackInfo<Value>& Arguments);
static void ConsoleInput(const FunctionCallbackInfo<Value>& Arguments);

static void ConsoleLog(const FunctionCallbackInfo<Value>& Arguments){
    unsigned short int Iterator = 0;
    for(Iterator; Iterator < Arguments.Length(); Iterator++){
        HandleScope Scope(Arguments.GetIsolate());
        if(Iterator > 0) cout << " ";
        String::Utf8Value Text(Arguments.GetIsolate(), Arguments[Iterator]);
        cout << ToCString(Text);
    }
    cout << endl;
}

static void ConsoleError(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    cout << ConsoleColor("red");
    ConsoleLog(Arguments);
    cout << ConsoleStyle("normal");
}

static void ConsoleWarning(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    cout << ConsoleColor("yellow");
    ConsoleLog(Arguments);
    cout << ConsoleStyle("normal");
}

static void ConsoleInformation(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    cout << ConsoleColor("beige");
    ConsoleLog(Arguments);
    cout << ConsoleStyle("normal");
}

static void ConsoleSuccess(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    cout << ConsoleColor("green");
    ConsoleLog(Arguments);
    cout << ConsoleStyle("normal");
}

static void ConsoleSetColor(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    String::Utf8Value ColorIdentifier(Arguments.GetIsolate(), Arguments[0]);
    const char* CharColorIdentifier = ToCString(ColorIdentifier);
    cout << ConsoleColor(CharColorIdentifier);
}

static void ConsoleSetStyle(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    String::Utf8Value StyleIdentifier(Arguments.GetIsolate(), Arguments[0]);
    const char* CharStyleIdentifier = ToCString(StyleIdentifier);
    cout << ConsoleStyle(CharStyleIdentifier);
}

static void ConsoleSetBackground(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    String::Utf8Value BackgroundIdentifier(Arguments.GetIsolate(), Arguments[0]);
    const char* CharBackgroundIdentifier = ToCString(BackgroundIdentifier);
    cout << ConsoleBackground(CharBackgroundIdentifier);
}

static void ConsoleGetBackground(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    String::Utf8Value BackgroundIdentifier(Arguments.GetIsolate(), Arguments[0]);
    const char* CharBackgroundIdentifier = ToCString(BackgroundIdentifier);
    string Background = ConsoleBackground(CharBackgroundIdentifier);
    Arguments.GetReturnValue().Set(
        String::NewFromUtf8(
            Arguments.GetIsolate(),
            Background.c_str(),
            NewStringType::kNormal,
            static_cast<int>(Background.length())
        ).ToLocalChecked()
    );
}

static void ConsoleGetStyle(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    String::Utf8Value StyleIdentifier(Arguments.GetIsolate(), Arguments[0]);
    const char* CharStyleIdentifier = ToCString(StyleIdentifier);
    string Style = ConsoleStyle(CharStyleIdentifier);
    Arguments.GetReturnValue().Set(
        String::NewFromUtf8(
            Arguments.GetIsolate(),
            Style.c_str(),
            NewStringType::kNormal,
            static_cast<int>(Style.length())
        ).ToLocalChecked()
    );
}

static void ConsoleGetColor(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    String::Utf8Value ColorIdentifier(Arguments.GetIsolate(), Arguments[0]);
    const char* CharColorIdentifier = ToCString(ColorIdentifier);
    string Color = ConsoleColor(CharColorIdentifier);
    Arguments.GetReturnValue().Set(
        String::NewFromUtf8(
            Arguments.GetIsolate(),
            Color.c_str(),
            NewStringType::kNormal,
            static_cast<int>(Color.length())
        ).ToLocalChecked()
    );
}

static void ConsoleClear(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    ClearConsole();
}
        
static void ConsoleInput(const FunctionCallbackInfo<Value>& Arguments){
    unsigned short int Iterator = 0;
    for(Iterator; Iterator < Arguments.Length(); Iterator++){
        HandleScope scope(Arguments.GetIsolate());
        if(Iterator > 0) cout << " ";
        String::Utf8Value Text(Arguments.GetIsolate(), Arguments[Iterator]);
        const char* CharText = ToCString(Text);
        cout << CharText;
    }
    string Response;
    getline(cin, Response);
    Arguments.GetReturnValue().Set(
        String::NewFromUtf8(
            Arguments.GetIsolate(),
            Response.c_str(),
            NewStringType::kNormal,
            static_cast<int>(Response.length())
        ).ToLocalChecked()
    );
}