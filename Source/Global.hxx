/***
 * Copyright (C) Rodolfo Herrera Hernandez. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root 
 * for full license information.
 *
 * =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
 *
 * For related information - https://github.com/rodiihernandezz/ZendaJS/
 *
 * =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
 ****/

#define ZENDA_CREATOR "Rodolfo Herrera Hernandez"
#define ZENDA_VERSION "1.0.8"

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
    - https://github.com/rodiihernandezz/ZendaJS/
)""",

        InvalidArgumentFormatText = R"""(
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
)""",

        HelpText = R"""(
 * Help - Valid arguments for the executable.

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

 * help
   - Usage => Zenda help
   - For => It allows you to get help on the valid 
   - parameters that the Zenda executable accepts.
                
 * If you need more advanced help...
   - Mail => contact@codewithrodi.com
   - Website => https://codewithrodi.com/
   - Repository => https://github.com/rodiihernandezz/ZendaJS/
)""";
};