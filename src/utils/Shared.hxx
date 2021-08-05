static inline const char* OperativeSystem();
static inline const char* ToCString(const String::Utf8Value& Value);
static inline const char* ConsoleBackground(string Background);
static inline const char* ConsoleStyle(string Style);
static inline const char* ConsoleColor(string Color);
static inline void SetCallArguments(int argc, char* argv[]);
static inline string CurrentWorkingDirectory();
static inline void ClearConsole();
static inline bool FileExists(const string& Filename);
static string CurrentWorkingDirectoryInScript(const char* Script);
static string GetStdoutFromCommand(string Command);
static string ZendaSourceCodeLocation();
static void ExecutePythonFileFromnative(const char* CharFile);
static char* ReadFile(char Filename[]);
static MaybeLocal<String> ReadFileUsingV8(const char* Filename, Isolate*);
static void ReportException(TryCatch* try_catch);

static inline void SetCallArguments(int argc, char* argv[]){
   unsigned short int Iterator = 2;
   for(Iterator; Iterator < argc; ++Iterator)
      CallArguments.push_back(argv[Iterator]);
}

static inline string CurrentWorkingDirectory(){
    char Buffer[256];
    return (getcwd(Buffer, 256) ? string(Buffer) : string(""));
}

static string CurrentWorkingDirectoryInScript(const char* Script){
    vector<string> SubDirectories = SplitString(string(Script), "/");
    string CWD = CurrentWorkingDirectory() + "/";
    unsigned short int Iterator = 0;
    for(Iterator; Iterator < SubDirectories.size() - 1; Iterator++)
        CWD += SubDirectories.at(Iterator);
    return CWD;
}

static string GetStdoutFromCommand(string Command){
    string Data;
    FILE* Stream;
    char Buffer[256];
    Command.append(" 2>&1");
    Stream = popen(Command.c_str(), "r");
    if(Stream){
        while(!feof(Stream))
            if(fgets(Buffer, 256, Stream) != NULL) Data.append(Buffer);
        pclose(Stream);
    }
    return Data;
}

static string ZendaSourceCodeLocation(){
    vector<string> CurrentPaths = SplitString(GetStdoutFromCommand("echo $PATH | tr ':' '\n'"), "\n");
    unsigned short int Iterator = 0;
    for(Iterator; Iterator < CurrentPaths.size(); Iterator++){
        string CurrentBinDirectory = CurrentPaths.at(Iterator);
        if(CurrentBinDirectory.find("ZendaJS") != string::npos)
            return CurrentBinDirectory;
    }
    return "Not Found.";
}

static inline const char* OperativeSystem(){
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

static void ExecutePythonFileFromNative(const char* CharFile){
    string BufferFileName = "";
    string Command = "python3 " + BufferFileName.assign(CharFile);
    system(Command.c_str());
}

static char* ReadFile(char Filename[]){
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

static inline bool FileExists(const string& Filename) {
    ifstream File(Filename.c_str());
    return File.good();
}

static MaybeLocal<String> ReadFileUsingV8(const char* Filename, Isolate* LIsolate){
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

static inline const char* ToCString(const String::Utf8Value& Value) {
    return *Value ? *Value : "failed TOCSTRING.";
}

static inline const char* ConsoleBackground(string Background){
    Background = StringToLower(Background);
    if(Background == "black")
        return "\33[40m";
    else if(Background == "red")
        return "\33[41m";
    else if(Background == "green")
        return "\33[42m";
    else if(Background == "yellow")
        return "\33[43m";
    else if(Background == "blue")
        return "\33[44m";
    else if(Background == "violet")
        return "\33[45m";
    else if(Background == "beige")
        return "\33[46m";
    else if(Background == "white")
        return "\33[47m";
    else
        return "";
}

static inline const char* ConsoleStyle(string Style){
    Style = StringToLower(Style);
    if(Style == "normal")
        return "\33[0m";
    else if(Style == "end")
        return "\n";
    else if(Style == "bold")
        return "\33[1m";
    else if(Style == "italic")
        return "\33[3m";
    else if(Style == "url")
        return "\33[4m";
    else if(Style == "blink")
        return "\33[5m";
    else if(Style == "blink2")
        return "\33[6m";
    else if(Style == "selected")
        return "\33[7m";
    else
        return "";
}

static inline const char* ConsoleColor(string Color){
    Color = StringToLower(Color);
    if(Color == "black")
        return "\33[30m";
    else if(Color == "red")
        return "\33[31m";
    else if(Color == "green")
        return "\33[32m";
    else if(Color == "yellow")
        return "\33[33m";
    else if(Color == "blue")
        return "\33[34m";
    else if(Color == "violet")
        return "\33[35m";
    else if(Color == "beige")
        return "\33[36m";
    else if(Color == "white")
        return "\33[37m";
    else if(Color == "grey")
        return "\33[90m";
    else
        return "";
}

static inline void ClearConsole(){
    string OS = OperativeSystem();
    (OS == "WIN32") || (OS == "WIN64") ? system("cls") : system("clear");
}

static void ReportException(TryCatch* try_catch){
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
            unsigned short int 
                Iterator = 0,
                Jterator = 0;
            for(Iterator; Iterator < Start; Iterator++) 
                fprintf(stderr, " ");
            for(Jterator; Jterator < End; Jterator++)
                fprintf(stderr, "^");
            cout << endl;
        }
}