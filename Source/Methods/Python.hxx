/***
 * Copyright (C) Rodolfo Herrera Hernandez. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root 
 * for full license information.
 *
 * =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
 *
 * Methods/Python.hxx: This file contains methods to interact exclusively with 
 * Python from JS.
 *
 * For related information - https://github.com/rodiihernandezz/ZendaJS/
 *
 * =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
 ****/

static void PythonQuickString(const FunctionCallbackInfo<Value>& Arguments);
static void PythonQuickFile(const FunctionCallbackInfo<Value>& Arguments);
static void PythonFancyFile(const FunctionCallbackInfo<Value>& Arguments);

static void PythonQuickString(const FunctionCallbackInfo<Value>& Arguments){
    unsigned short int Iterator = 0;
    for(Iterator; Iterator < Arguments.Length(); Iterator++){
        HandleScope Scope(Arguments.GetIsolate());
        String::Utf8Value Code(Arguments.GetIsolate(), Arguments[Iterator]);
        char const* CharCode = ToCString(Code);
        Py_Initialize();
            PyRun_SimpleString(CharCode);
        Py_Finalize();
    }
}

static void PythonQuickFile(const FunctionCallbackInfo<Value>& Arguments){
    unsigned short int Iterator = 0;
    for(Iterator; Iterator < Arguments.Length(); Iterator++){
        HandleScope Scope(Arguments.GetIsolate());
        String::Utf8Value File(Arguments.GetIsolate(), Arguments[Iterator]);
        char const* CharFile = ToCString(File);
        Py_Initialize();
            FILE* PyFile;
            PyFile = fopen(CharFile, "r");
            if(PyFile == NULL)
                cout << "An error ocurred while trying open <" << CharFile << ">." << endl;
            else
                PyRun_SimpleFile(PyFile, CharFile);
            fclose(PyFile);
        Py_Finalize();
    }
}

static void PythonFancyFile(const FunctionCallbackInfo<Value>& Arguments){
    unsigned short int Iterator = 0;
    for(Iterator; Iterator < Arguments.Length(); Iterator++){
        HandleScope Scope(Arguments.GetIsolate());
        String::Utf8Value File(Arguments.GetIsolate(), Arguments[Iterator]);
        char const* CharFile = ToCString(File);
        ExecutePythonFileFromNative(CharFile);
    }
}