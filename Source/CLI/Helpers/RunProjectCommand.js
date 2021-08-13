/***
 * Copyright (C) Rodolfo Herrera Hernandez. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root 
 * for full license information.
 *
 * =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
 *
 * CLI/Helpers/RunProjectCommand.js: This file allows you to load a command defined in the project's .json
 * 
 * For related information - https://github.com/rodiihernandezz/ZendaJS/
 *
 * =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
 ****/

const 
    SplittedCurrentPath = System.CurrentWorkingDirectory().split('/'),
    MaybeJSON = SplittedCurrentPath[SplittedCurrentPath.length - 1];

if(FileSystem.FileExists(MaybeJSON + '.json')){
    const
        Arguments = System.Arguments(), 
        Commands = JSON.parse(FileSystem.QuickReadFile(MaybeJSON + '.json'))['Commands'];
    Arguments.forEach((Argument) => 
        Object.keys(Commands).includes(Argument) ? System.Execute(Commands[Argument]) : null
    );
}else{
    Console.Error(
        Console.GetStyle('bold') +
` => Error loading JSON.
     
    - Could not find the project json, then the following causes.
    
    - It is likely that in the current directory where 
    - you are there is no Zenda compatible project, you 
    - can create one using Zenda init.

    - If you are in a Zenda project, it is likely that 
    - the .json does not have the same name as the project, please 
    - check the name of the folder that contains the project 
    - and compare it with the .json of the same.
                        |
                        |
      =| Detected directory <${MaybeJSON}> |=
    
    - There really is a ${MaybeJSON}.json in current directory?

 => Current directory anantomy`,
    );
    FileSystem.ListDirectory(System.CurrentWorkingDirectory()).forEach((File) => {
        Console.Error(
            Console.GetStyle('bold') +
            '    ->', File, 
            File.endsWith('.json') ? (
                Console.GetColor('green') + 
                `Probably JSON file, try to rename it to ${MaybeJSON}.json` +
                Console.GetColor('red')
            ) : '');
    });
    Console.SetStyle('normal');
}