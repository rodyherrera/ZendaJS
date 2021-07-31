static void SystemExecute(const FunctionCallbackInfo<Value>& Arguments){
    for(unsigned short int i = 0; i < Arguments.Length(); i++){
        HandleScope Scope(Arguments.GetIsolate());
        String::Utf8Value Command(Arguments.GetIsolate(), Arguments[i]);
        const char* CharCommand = ToCString(Command);
        system(CharCommand);
    }
}

static void SystemPlatform(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    string OS = OperativeSystem();
    Arguments.GetReturnValue().Set(
        String::NewFromUtf8(
            Arguments.GetIsolate(),
            OS.c_str(),
            NewStringType::kNormal,
            static_cast<int>(OS.length())
        ).ToLocalChecked()
    );
}