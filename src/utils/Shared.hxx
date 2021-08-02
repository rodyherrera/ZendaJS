const char* OperativeSystem(){
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
        #ifdef _WIN64
            return "WIN64"
        #else
            return "WIN32"
        #endif
    #elif __APPLE__
        return "APPLE";
    #elif __linux__
        return "LINUX";
    #elif __unix__
        return "UNIX";
    #elif defined(_POSIX_VERSION)
        return "POSIX";
    #else
        return "UKNOWN";
    #endif
}

void ExecutePythonFileFromNative(const char* CharFile){
    string BufferFileName = "";
    string Command = "python3 " + BufferFileName.assign(CharFile);
    system(Command.c_str());
}

char* ReadFile(char Filename[]){
    ifstream File;
    File.open(Filename, ifstream::ate);
    char* Contents;
    if(!File){
        Contents = new char[1];
        return Contents;
    }
    size_t FileSize = File.tellg();
    File.seekg(0);
    filebuf* FileBuf = File.rdbuf();
    Contents = new char[FileSize + 1]();
    FileBuf->sgetn(Contents, FileSize);
    File.close();
    return Contents;
}

inline bool FileExists(const string& name) {
    ifstream f(name.c_str());
    return f.good();
}

MaybeLocal<String> ReadFileUsingV8(const char* Filename, Isolate* LIsolate){
    FILE* File = fopen(Filename, "rb");
    if(File == NULL)
        return MaybeLocal<String>();
    fseek(File, 0, SEEK_END);
    size_t Size = ftell(File);
    rewind(File);
    char* Characters = new char[Size + 1];
    Characters[Size] = '\0';
    for(size_t i = 0; i < Size;){
        i += fread(&Characters[i], 1, Size - i, File);
        if(ferror(File)){
            fclose(File);
            return MaybeLocal<String>();
        }
    }
    fclose(File);
    MaybeLocal<String> Content = String::NewFromUtf8(
        LIsolate, Characters, NewStringType::kNormal, static_cast<int>(Size)
    );
    delete[] Characters;
    return Content;
}

const char* ToCString(const String::Utf8Value& value) {
    return *value ? *value : "failed TOCSTRING.";
}

const char* ConsoleBackground(string Background){
    map<string, string> Backgrounds;
    map<string, string>::iterator BackgroundsIterator;
    typedef pair<string, string> Pair;
    Backgrounds.insert(Pair("black", "\33[40m"));
    Backgrounds.insert(Pair("red", "\33[41m"));
    Backgrounds.insert(Pair("green", "\33[42m"));
    Backgrounds.insert(Pair("yellow", "\33[43m"));
    Backgrounds.insert(Pair("blue", "\33[44m"));
    Backgrounds.insert(Pair("violet", "\33[45m"));
    Backgrounds.insert(Pair("beige", "\33[46m"));
    Backgrounds.insert(Pair("white", "\33[47m"));
    BackgroundsIterator = Backgrounds.find(
        StringToLower(Background)
    );
    return BackgroundsIterator != Backgrounds.end() ? BackgroundsIterator->second.c_str() :  "";
}

const char* ConsoleStyle(string Style){
    map<string, string> Styles;
    map<string, string>::iterator StylesIterator;
    typedef pair<string, string> Pair;
    Styles.insert(Pair("normal", "\33[0m"));
    Styles.insert(Pair("end", "\n"));
    Styles.insert(Pair("bold", "\33[1m"));
    Styles.insert(Pair("italic", "\33[3m"));
    Styles.insert(Pair("url", "\33[4m"));
    Styles.insert(Pair("blink", "\33[5m"));
    Styles.insert(Pair("blink2", "\33[6m"));
    Styles.insert(Pair("selected", "\33[7m"));
    StylesIterator = Styles.find(
        StringToLower(Style)
    );
    return StylesIterator != Styles.end() ? StylesIterator->second.c_str() :  "";
}

const char* ConsoleColor(string Color){
    map<string, string> Colors;
    map<string, string>::iterator ColorsIterator;
    typedef pair<string, string> Pair;
    Colors.insert(Pair("black", "\33[30m"));
    Colors.insert(Pair("red", "\33[31m"));
    Colors.insert(Pair("green", "\33[32m"));
    Colors.insert(Pair("yellow", "\33[33m"));
    Colors.insert(Pair("blue", "\33[34m"));
    Colors.insert(Pair("violet", "\33[35m"));
    Colors.insert(Pair("beige", "\33[36m"));
    Colors.insert(Pair("white", "\33[37m"));
    Colors.insert(Pair("grey", "\33[90m"));
    ColorsIterator = Colors.find(
        StringToLower(Color)
    );
    return ColorsIterator != Colors.end() ? ColorsIterator->second.c_str() :  "";
}

void ClearConsole(){
    string OS = OperativeSystem();
    (OS == "WIN32") || (OS == "WIN64") ? system("cls") : system("clear");
}

void ReportException(TryCatch* try_catch){
    String::Utf8Value exception(ZendaIsolate, try_catch->Exception());
    const char* ExceptionString = ToCString(exception);
    Local<Message> message = try_catch->Message();
    if(message.IsEmpty())
        cout << ExceptionString << endl;
    else{
        String::Utf8Value Filename(
            ZendaIsolate, message->GetScriptOrigin().ResourceName()
        );
        const char* FilenameString = ToCString(Filename);
        int LineNumber = message->GetLineNumber(
            ZendaIsolate->GetCurrentContext()
        ).FromJust();
        cout << "ZendaJS [Error in line " << to_string(LineNumber) << "] - [" << FilenameString << "]" << endl;
        cout << endl << "-> " << ExceptionString << endl << endl;
        String::Utf8Value SourceLine(
            ZendaIsolate,
                message->GetSourceLine(ZendaIsolate->GetCurrentContext()).ToLocalChecked()
            );
        const char* SourceLineString = ToCString(SourceLine);
        cout << SourceLineString << endl;
        unsigned int 
            Start = message->GetStartColumn(
                ZendaIsolate->GetCurrentContext()
            ).FromJust(),
            End = message->GetEndColumn(
                ZendaIsolate->GetCurrentContext()
            ).FromJust();
            for(unsigned int i = 0; i < Start; i++) 
                fprintf(stderr, " ");
            for(unsigned int i = Start; i < End; i++)
                fprintf(stderr, "^");
            cout << endl;
        }
}