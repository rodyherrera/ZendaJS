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

namespace Zenda::JavaScript::Methods::Python{
    static void QuickString(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static void QuickFile(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static void FancyFile(const v8::FunctionCallbackInfo<v8::Value>& Arguments);

    static void QuickString(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        if(Arguments[0]->IsUndefined())
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "In order to execute one more strings of Python code, you must first enter them as a parameter.");
        else
            for(unsigned short int Iterator = 0; Iterator < Arguments.Length(); Iterator++){
                v8::HandleScope Scope(Arguments.GetIsolate());
                v8::String::Utf8Value Code(Arguments.GetIsolate(), Arguments[Iterator]);
                Py_Initialize();
                    PyRun_SimpleString(std::string(*Code).c_str());
                Py_Finalize();
            }
    }

    static void QuickFile(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        if(Arguments[0]->IsUndefined())
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "In order to execute one or more python files you must first indicate them as a parameter.");
        else
            for(unsigned short int Iterator = 0; Iterator < Arguments.Length(); Iterator++){
                v8::HandleScope Scope(Arguments.GetIsolate());
                v8::String::Utf8Value File(Arguments.GetIsolate(), Arguments[Iterator]);
                Py_Initialize();
                    FILE* PyFile;
                    PyFile = fopen(*File, "r");
                    if(PyFile == NULL)
                        Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "An error ocurred while trying open <" + std::string(*File) + ">.");
                    else
                        PyRun_SimpleFile(PyFile, *File);
                    fclose(PyFile);
                Py_Finalize();
        }
    }

    static void FancyFile(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        if(Arguments[0]->IsUndefined())
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "In order to execute one or more python files you must first indicate them as a parameter.");
        else
            for(unsigned short int Iterator = 0; Iterator < Arguments.Length(); Iterator++){
                v8::HandleScope Scope(Arguments.GetIsolate());
                v8::String::Utf8Value File(Arguments.GetIsolate(), Arguments[Iterator]);
                std::string CharFile = std::string(*File);
                Zenda::Shared::ExecutePythonFileFromNative(CharFile);
            }
    }
}