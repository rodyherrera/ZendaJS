static void PythonQuickString(const FunctionCallbackInfo<Value>& Arguments){
    for(unsigned short int i = 0; i < Arguments.Length(); i++){
        HandleScope Scope(Arguments.GetIsolate());
        String::Utf8Value Code(Arguments.GetIsolate(), Arguments[i]);
        char const* CharCode = ToCString(Code);
        Py_Initialize();
            PyRun_SimpleString(CharCode);
        Py_Finalize();
    }
}

static void PythonQuickFile(const FunctionCallbackInfo<Value>& Arguments){
    for(unsigned short int i = 0; i < Arguments.Length(); i++){
        HandleScope Scope(Arguments.GetIsolate());
        String::Utf8Value File(Arguments.GetIsolate(), Arguments[i]);
        char const* CharFile = ToCString(File);
        Py_Initialize();
            FILE* PyFile;
            PyFile = fopen(CharFile, "r");
            if(PyFile == NULL)
                cout << "ZendaJS -> An error ocurred while trying open <" << CharFile << "> in pythonFile() function." << endl;
            else
                PyRun_SimpleFile(PyFile, CharFile);
            fclose(PyFile);
        Py_Finalize();
    }
}

static void PythonFancyFile(const FunctionCallbackInfo<Value>& Arguments){
    for(unsigned short int i = 0; i < Arguments.Length(); i++){
        HandleScope Scope(Arguments.GetIsolate());
        String::Utf8Value File(Arguments.GetIsolate(), Arguments[i]);
        char const* CharFile = ToCString(File);
        ExecutePythonFileFromNative(CharFile);
    }
}