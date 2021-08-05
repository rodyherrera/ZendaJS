static inline void Version(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    cout << ZendaVersion << endl;
}

static inline void Creator(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    cout << ZendaCreator << endl;
}

static void Sleep(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    String::Utf8Value SleepTime(Arguments.GetIsolate(), Arguments[0]);
    char const* CharSleepTime = ToCString(SleepTime);
    sleep(stoi(CharSleepTime) / 1000);
}