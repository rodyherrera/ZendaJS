/***
 * Copyright (C) Rodolfo Herrera Hernandez. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root 
 * for full license information.
 *
 * =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
 *
 * CLI/Functions.hxx: Necessary functions for the execution of arguments.
 * 
 * When you run Zenda and pass arguments to it, they are processed in CLI/Arguments.hxx 
 * and are redirected to the functions found here according to the valid argument.
 *
 * For related information - https://github.com/rodiihernandezz/ZendaJS/
 *
 * =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
 ****/

static void ShowHelp();
static void CreatorArgument();
static void VersionArgument();
static void ShellArgument(Local<Context> LContext);
static void InstallItArgument();
static void NotValidArgument();
static void CommandArgument(Local<Context> LContext, const char* Mode);
static void InitArgument(Local<Context> LContext);
static void RunArgument(Local<Context> LContext, const char* MaybeFile);
static void AboutArgument(Local<Context> LContext);

static void ShowHelp(){
   cout << endl << R"""(
 * Help - Valid arguments for the executable.
   )""" << endl << R"""(
 * shell
     - Usage => Zenda shell
     - For => You get a shell to be able to run 
     - javascript to experiment with native functions.

 * version
     - Usage => Zenda version
     - For => You get the current version of Zenda.

 * creator
     - Usage => Zenda creator
     - For => You get the ZendaJS creator.

 * run
     - Usage => Zenda run some_folder/some_file.js
     - For => It allows you to run a Zenda compatible Javascript file.

 * init
     - Usage => Zenda init
     - For => Create an outline for your Zenda project.

 * about
     - Usage => Zenda about
     - For => Get information about current project.

 * command <mode>
     - Usage => Zenda command <mode>
     - For => To start or execute a command defined in
     - your <project> .json in "Commands", file 
     - generated with Zenda init.

 * install-it
     - Usage => Zenda install-it
     - For => It allows you to install the necessary dependencies 
     - so that you can run your scripts that use Zenda without problems.

 * help
     - Usage => Zenda --help
     - For => It allows you to get help on the valid 
     - parameters that the Zenda executable accepts.
   )""" << endl << endl;
}

static void CreatorArgument(){
    cout << ZendaCreator << endl;
}

static void VersionArgument(){
    cout << ZendaVersion << endl;
}

static void CommandArgument(Local<Context> LContext, const char* Mode){ // Mode is only for detect next parameter
    string RunProjectCommandScript = ZendaSourceCodeLocation() + "/Source/CLI/Helpers/RunProjectCommand.js";
    ExecuteZendaScript(RunProjectCommandScript.c_str(), LContext);
    ExitSucces();
}

static void AboutArgument(Local<Context> LContext){
    string AboutOfProjectScript = ZendaSourceCodeLocation() + "/Source/CLI/Helpers/AboutOfProject.js";
    ExecuteZendaScript(AboutOfProjectScript.c_str(), LContext);
    ExitSucces();
}

static void InitArgument(Local<Context> LContext){
    string InitializeProjectScript = ZendaSourceCodeLocation() + "/Source/CLI/Helpers/InitializeProject.js";
    ExecuteZendaScript(InitializeProjectScript.c_str(), LContext);
    ExitSucces();
}

static void ShellArgument(Local<Context> LContext){
    WorkingDirectory = CurrentWorkingDirectory();
    Shell(LContext, ZendaPlatform.get());
    ExitSucces();
}

static void InstallItArgument(){
    InstallZendaJS();
    ExitSucces();
}

static void RunArgument(Local<Context> LContext, const char* MaybeFile){
    if(FSFileExists(MaybeFile)){
        WorkingDirectory = CurrentWorkingDirectoryInScript(MaybeFile);
        ExecuteZendaScript(MaybeFile, LContext);
        ExitSucces();
    }else{
        cout << "The requested file <" << MaybeFile << "> was not found." << endl;
        ExitFailure();
    }
}

static void NotValidArgument(){
    ShowHelp();
    ExitFailure();
}