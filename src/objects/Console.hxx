static void ConsoleLog(const FunctionCallbackInfo<Value>& Arguments){
    for(unsigned short int i = 0; i < Arguments.Length(); i++){
        HandleScope Scope(Arguments.GetIsolate());
        if(i > 0) cout << " ";
        String::Utf8Value Text(Arguments.GetIsolate(), Arguments[i]);
        const char* CharText = ToCString(Text);
        cout << CharText;
    }
    cout << endl;
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
    for(unsigned short int i = 0; i < Arguments.Length(); i++){
        HandleScope scope(Arguments.GetIsolate());
        if(i > 0) cout << " ";
        String::Utf8Value Text(Arguments.GetIsolate(), Arguments[i]);
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