static void ShowHelp();
static void ArgCreator();
static void ArgVersion();
static void ArgShell(Local<Context> LContext);
static void ArgRunInstallation();
static void NotValidArgument();
static bool ArgExecute(Local<Context> LContext, const char* MaybeFile);

static void ShowHelp(){
   cout << endl << R"""(
 * Help - Valid arguments for the executable.
   )""" << endl << R"""(
 * shell
    Usage -> Zenda shell
    For -> You get a shell to be able to run 
    javascript to experiment with native functions.

 * --version
    Usage -> Zenda --version
    For -> You get the current version of Zenda.

 * --creator
    Usage -> Zenda --creator
    For -> You get the ZendaJS creator.

 * run
    Usage -> Zenda run some_folder/some_file.js
    For -> It allows you to run a Zenda compatible Javascript file.

 * install-it
    Usage -> Zenda install-it
    For -> It allows you to install the necessary dependencies 
    so that you can run your scripts that use Zenda without problems.

 * --help
    Usage -> Zenda --help
    For -> It allows you to get help on the valid 
    parameters that the Zenda executable accepts.
   )""" << endl << endl;
}

static void ArgCreator(){
    cout << ZendaCreator << endl;
}

static void ArgVersion(){
    cout << ZendaVersion << endl;
}

static void ArgShell(Local<Context> LContext){
    WorkingDirectory = CurrentWorkingDirectory();
    LoadCoreJavascriptFiles(LContext);
    Shell(LContext, ZendaPlatform.get());
}

static void ArgRunInstallation(){
    InstallZenda();
}

static bool ArgExecute(Local<Context> LContext, const char* MaybeFile){
    if(FileExists(MaybeFile)){
        LoadCoreJavascriptFiles(LContext);
        WorkingDirectory = CurrentWorkingDirectoryInScript(MaybeFile);
        char* Contents = ReadFile(strdup(MaybeFile));
        Local<Module> LModule = CheckModule(LoadModule(Contents, strdup(MaybeFile), LContext), LContext);
        Local<Value> Returned = ExecuteModule(LModule, LContext);
        return true;
    }else{
        cout << "The requested file <" << MaybeFile << "> was not found." << endl;
        return false;
    }
}

static void NotValidArgument(){
    ShowHelp();
}