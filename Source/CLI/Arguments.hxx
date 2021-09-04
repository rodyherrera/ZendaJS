/***
 * Copyright (C) Rodolfo Herrera Hernandez. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root 
 * for full license information.
 *
 * =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
 *
 * CLI/Arguments.hxx: File that manages the valid arguments that the executable can receive.
 * 
 * The arguments are received from the Engine, here it is decided if 
 * they are valid or not and other operations, also from here they are 
 * redirected to CLI/Functions.hxx to execute the corresponding 
 * function according to the received argument.
 *
 * For related information - https://github.com/rodiihernandezz/ZendaJS/
 *
 * =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
 ****/

static void MatchWithArgument(Local<Context> LContext);
static const char* GetNextArgument(const char* CurrentArgument);

static const char* GetNextArgument(const char* CurrentArgument){
    try{
        auto CallArgumentsIterator = find(CallArguments.begin(), CallArguments.end(), CurrentArgument);
        if(CallArgumentsIterator != end(CallArguments)){
            unsigned short int IndexOfCurrentArgument = CallArgumentsIterator - CallArguments.begin();
            return CallArguments.at(IndexOfCurrentArgument + 1).c_str();
        }
        throw 0;
    }catch(...){
        cout << R"""(
 * Error
   
  - An error has just occurred, it is likely that you 
  - have not entered enough arguments to run Zenda.

  - There are commands that require another argument to run, 
  - such as the Zenda run command requires another argument 
  - which would be the file you want to run.
    
    => Zenda run (Error)
    => Zenda run MyFile.js (Correct)

    => Zenda command (Error)
    => Zenda command MyCommand
)""" << endl;
        ExitFailure();
        return "";
    }
}

static void MatchWithArgument(Local<Context> LContext){
    if(CallArguments.size() >= 1)
        for(auto&Argument : CallArguments){
            const char* CharArgument = Argument.c_str();
            if(!strcmp(CharArgument, "creator"))
                CreatorArgument();
            else if(!strcmp(CharArgument, "version"))
                VersionArgument();
            else if(!strcmp(CharArgument, "shell"))
                ShellArgument(LContext);
            else if(!strcmp(CharArgument, "command"))
                CommandArgument(LContext, GetNextArgument(CharArgument));
            else if(!strcmp(CharArgument, "init"))
                InitArgument(LContext);
            else if(!strcmp(CharArgument, "about"))
                AboutArgument(LContext);
            else if(!strcmp(CharArgument, "install-it"))
                InstallItArgument();
            else if(!strcmp(CharArgument, "run"))
                RunArgument(LContext, GetNextArgument(CharArgument));
            else if(!strcmp(CharArgument, "run-examples"))
                RunExamples(LContext);
            else
                NotValidArgument();
        }
    else
       NotValidArgument();
}