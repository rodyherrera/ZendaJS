/***
 * Copyright (C) Rodolfo Herrera Hernandez. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root 
 * for full license information.
 *
 * =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
 *
 * CLI/Helpers/InitializeProject.js: File that allows you to create a schematic for your Zenda application.
 *
 * For related information - https://github.com/rodiihernandezz/ZendaJS/
 *
 * =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
 ****/

const JsonAnatomy = {
    Project: {
        Name: '',
        Version: '',
        Description: '',
        Website: '',
        CreationDate: new Date(),
    },
    Author: {
        Name: '',
        Email: '',
        Website: '',
    },
    Commands: {
        Start: 'Zenda run Index.js',
    },
};

// Arrow functions
const
    CreateProjectRootFolder = () => FileSystem.CreateFolder(JsonAnatomy.Project.Name),
    CreateFolderInProject = (Path) => FileSystem.CreateFolder(`${JsonAnatomy.Project.Name}/${Path}`),
    CreateFileInProject = (Path) => FileSystem.CreateFile(`${JsonAnatomy.Project.Name}/${Path}`),
    WriteFileInProject = (Path, Content) => FileSystem.QuickWriteFile(`${JsonAnatomy.Project.Name}/${Path}`, Content),
    LoadProjectJson = () => FileSystem.QuickRewriteFile(`${JsonAnatomy.Project.Name}/${JsonAnatomy.Project.Name}.json`, JSON.stringify(JsonAnatomy, null, '\t')),
    SafeStringInConsole = (Str) => Str.length > 60 ? Str.slice(0, 60) + '...' : Str;

function CreateProjectAnatomy(){
    CreateProjectRootFolder();
    CreateFileInProject(`${JsonAnatomy.Project.Name}.json`);
    CreateFileInProject('Index.js');
    CreateFolderInProject('Packages');
    WriteFileInProject('Index.js', 
`/***
 * You can expand the anatomy of ${JsonAnatomy.Project.Name} as you want, this is 
 * an example file which if you write something like 
 * "Zenda command start" in the console this file will be executed, you 
 * can delete and / or add more commands in ${JsonAnatomy.Project.Name}.json
 ****/

Console.Log('Hello world from ZendaJS');`);
}

function StartProjectInitializer(){
    Console.Clear();
    Console.Log(
` => Creating a new project...
     
     - When you create a project you have 
     - access to new Zenda functions, such as 
     - access to customized Packages to facilitate development 
     - with this technology, a .json that allows people to show 
     - more information about your project, custom commands etc ...

  => A little more
     
     - This is one of the first versions of ZendaJS, it is 
     - likely that the anatomy that is generated in future versions 
     - will be different, the same with the contents 
     - of the Packages folder.

  =| Starting |=`);

    Console.Log('\nEnter a project name, for example "Hello World Project"');
    JsonAnatomy.Project.Name = Console.Input('Project name > ').replaceAll(' ', '-');
    Console.Log('\n¡Yeah!, now enter the version of your project, for example: "1.0.0"');
    JsonAnatomy.Project.Version = Console.Input('Project version > ').replaceAll(' ', '-');
    Console.Log('\nEnter a description for your project, for example: "Is a hello world script"');
    JsonAnatomy.Project.Description = Console.Input('Project description > ');
    Console.Log('\n¡Perfect!, enter a project website, for example: "https://google.com/"');
    JsonAnatomy.Project.Website = Console.Input('Project website > ');

    Console.Log('\nAuthor name, for example: "Rodolfo Herrera Hernandez"');
    JsonAnatomy.Author.Name = Console.Input('Author > ');
    Console.Log('\nEmail address, for example: "JohnDoe@microsoft.com"');
    JsonAnatomy.Author.Email = Console.Input('Author email > ');
    Console.Log('\nEnter a author website, for example: "https://rodiihernandez.vercel.app/"');
    JsonAnatomy.Author.Website = Console.Input('Author website > ');

    CreateProjectAnatomy();
    LoadProjectJson();

    Console.Clear();
    Console.Log(
` => ${SafeStringInConsole(JsonAnatomy.Project.Name)} has been created!
    
  * Analyzing the anatomy
    
    - ${SafeStringInConsole(JsonAnatomy.Project.Name)}.json
      = Save information related to the project.

    - Index.js
      = It is an example file used to run the "Zenda command start" 
      = command defined in ${SafeStringInConsole(JsonAnatomy.Project.Name)}.json

    - Packages
      = Inside the Packages folder are all the 
      = files and/or dependencies that your project uses, here 
      = you will also find ready-made Zenda packages 
      = for you to use.

 => Happy hacking and remember drink water!`);
}

StartProjectInitializer();