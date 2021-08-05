static void SystemExecute(const FunctionCallbackInfo<Value>& Arguments){
    unsigned short int Iterator = 0;
    for(Iterator; Iterator < Arguments.Length(); Iterator++){
        HandleScope Scope(Arguments.GetIsolate());
        String::Utf8Value Command(Arguments.GetIsolate(), Arguments[Iterator]);
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

static void SystemArguments(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    Local<Context> ArgumentsContext = Context::New(ZendaIsolate);
    Local<Array> ArgumentList = Array::New(ZendaIsolate, CallArguments.size());
    unsigned short int Iterator = 0;
    for(Iterator; Iterator < CallArguments.size(); Iterator++){
        Local<String> SomeArgument = String::NewFromUtf8(ZendaIsolate, CallArguments.at(Iterator).c_str()).ToLocalChecked();
        Maybe<bool> ArgumentAdded = ArgumentList->Set(ArgumentsContext, Iterator, SomeArgument);
    }
    Arguments.GetReturnValue().Set(
        ArgumentList
    );
}

static void SystemCurrentWorkignDirectory(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    Arguments.GetReturnValue().Set(
        String::NewFromUtf8(
            Arguments.GetIsolate(),
            WorkingDirectory.c_str(),
            NewStringType::kNormal,
            static_cast<int>(WorkingDirectory.length())
        ).ToLocalChecked()
    );
}