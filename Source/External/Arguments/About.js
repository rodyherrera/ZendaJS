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

import { IfJsonFileExistsDoItOr } from 'Source/External/Arguments/Controller.js'

const Callbacks = {
    Success: ({ JsonContent }) => {
        const Project = JsonContent.Project;
        const Author = JsonContent.Author;

        Console.Clear();
        Console.Log(`
 * Project
          
   - Name => ${Project['Name']}
   - Version => ${Project['Version']}
   - Description => ${Project['Description']}
   - Website => ${Project['Website']}
   - Created at => ${Project['CreationDate']}
       
 * Author
           
   - Name => ${Author['Name']}
   - Email => ${Author['Email']}
   - Website => ${Author['Website']}
`);
    },

    Error: ({ Directory, ItemsOfCurrentDirectory }) => {
        Console.Error(
            Console.GetStyle('bold') +
` => Error loading JSON.
         
  - Could not find the project json, then the following causes.
        
  - It is likely that in the current directory where 
  - you are there is no Zenda compatible project, you 
  - can create one using <Zenda Init>.
       
  - If you are in a Zenda project, it is likely that 
  - the .json does not have the same name as the project, please 
  - check the name of the folder that contains the project 
  - and compare it with the .json of the same.
                            |
                            |
  =| Detected directory <${Directory}> |=
        
  - There really is a ${Directory}.json in current directory?
       
 => Current directory anantomy`,
);
            ItemsOfCurrentDirectory.forEach((File) => {
                Console.Error(
                    Console.GetStyle('bold') + 
                    '    ->', File,
                    File.endsWith('.json') ? (
                        Console.GetColor('green') +
                        `\n    Probably JSON file, try to rename it to ${Directory}.json\n` +
                        Console.GetColor('red')
                    ) : '');
            });

            Console.SetStyle('normal');
    }
};

IfJsonFileExistsDoItOr({
    IfFileExistsDoIt: Callbacks.Success,
    IfFileDoesntExistsDoIt: Callbacks.Error
});