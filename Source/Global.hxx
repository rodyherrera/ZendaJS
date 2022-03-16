/***
 * Copyright (C) Rodolfo Herrera Hernandez. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root 
 * for full license information.
 *
 * =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
 *
 * For related information - https://github.com/codewithrodi/ZendaJS/
 *
 * =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
 ****/

#define ZENDA_CREATOR "Rodolfo Herrera Hernandez"
#define ZENDA_VERSION "1.0.9"

namespace Zenda::Definitions{
    v8::Isolate* Isolate;
    v8::Local<v8::String> Name;
    v8::Local<v8::ObjectTemplate> Global;
    std::unique_ptr<v8::Platform> Platform;
    v8::Isolate::CreateParams CreateParameters;

    std::string WorkingDirectory = "";
    std::vector<std::string> CallArguments;

    const std::string 
        PackagesFolder = "Packages/",
        Z8 = "/Source/External/Z8.js",

        ShellHeaderText = R"""( * ZendaJS - Interactive Javascript Shell

    > Warning: This is a beta version, not stable.
    - [)""" + std::string(ZENDA_VERSION) + "] - By " + std::string(ZENDA_CREATOR) + R"""(.
    - contact@codewithrodi.com 
    - https://codewithrodi.com/
    - https://github.com/codewithrodi/ZendaJS/
)""",

        InvalidArgumentFormatText = R"""(
 * Error
    
 - An error has just occurred, it is likely that you 
 - have not entered enough arguments to run Zenda.

 - There are commands that require another argument to run, 
 - such as the Zenda run command requires another argument 
 - which would be the file you want to run.
        
 => Zenda Run (Error)
 => Zenda Run MyFile.js (Correct)

 => Zenda Command (Error)
 => Zenda Command MyCommand
)""",

        HelpText = R"""(
 * Help - Valid arguments for the executable.

 * Shell
   - Usage => Zenda Shell
   - For => You get a shell to be able to run 
   - javascript to experiment with native functions.

 * Version
    - Usage => Zenda Version
    - For => You get the current version of Zenda.

 * Creator
    - Usage => Zenda Creator
    - For => You get the ZendaJS creator.

 * Run
   - Usage => Zenda Run SomeFolder/SomeFile.js
   - For => It allows you to run a Zenda compatible Javascript file.

 * Init
   - Usage => Zenda Init
   - For => Create an outline for your Zenda project.

 * About
   - Usage => Zenda About
   - For => Get information about current project.

 * Command <mode>
   - Usage => Zenda Command <MODE>
   - For => To start or execute a command defined in
   - your <project> .json in "Commands", file 
   - generated with Zenda init.

 * Help
   - Usage => Zenda Help
   - For => It allows you to get help on the valid 
   - parameters that the Zenda executable accepts.
                
 * If you need more advanced help...
   - Mail => contact@codewithrodi.com
   - Website => https://codewithrodi.com/
   - Repository => https://github.com/codewithrodi/ZendaJS/
)""";
};
