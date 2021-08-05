static bool MatchWithArgument(const char* Argument, Local<Context> LContext, const char* MaybeFile);

static bool MatchWithArgument(const char* Argument, Local<Context> LContext, const char* MaybeFile){
    bool SomeFileHasBeenExecuted = false;
    if(!strcmp(Argument, "--creator")){
        ArgCreator();
        return true;
    }else if(!strcmp(Argument, "--version")){
        ArgVersion();
        return true;
    }else if(!strcmp(Argument, "shell")){
        ArgShell(LContext);
        return true;
    }else if(!strcmp(Argument, "install-it")){
        ArgRunInstallation();
        return true;
    }else if(!strcmp(Argument, "run")){
        if(ArgExecute(LContext, MaybeFile)){
            SomeFileHasBeenExecuted = true;
        }
        return true;
    }else{
        if(!SomeFileHasBeenExecuted)
            NotValidArgument();
        exit(EXIT_SUCCESS);
    }
}