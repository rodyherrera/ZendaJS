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

import { Project } from 'Source/External/Project/Controller.js'
import { SafeStringInConsole } from 'Source/External/Arguments/Controller.js'

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
    
  => Starting`
);

Console.Log('\n * Enter a project name, for example "Hello World Project"');
Project.JsonAnatomy.Project.Name = Console.Input(' - Project name > ').replaceAll(' ', '-');

Console.Log('\n * ¡Yeah!, now enter the version of your project, for example: "1.0.0"');
Project.JsonAnatomy.Project.Version = Console.Input(' - Project version > ').replaceAll(' ', '-');

Console.Log('\n * Enter a description for your project, for example: "Is a hello world script"');
Project.JsonAnatomy.Project.Description = Console.Input(' - Project description > ');

Console.Log('\n * ¡Perfect!, enter a project website, for example: "https://google.com/"');
Project.JsonAnatomy.Project.Website = Console.Input(' - Project website > ');

Console.Log('\n * Author name, for example: "Rodolfo Herrera Hernandez"');
Project.JsonAnatomy.Author.Name = Console.Input(' - Author > ');

Console.Log('\n * Email address, for example: "JohnDoe@microsoft.com"');
Project.JsonAnatomy.Author.Email = Console.Input(' - Author email > ');

Console.Log('\n * Enter a author website, for example: "https://rodiihernandez.vercel.app/"');
Project.JsonAnatomy.Author.Website = Console.Input(' - Author website > ');

Project.CreateInCurrentDirectory();

Project.CreateFileInside(`${Project.JsonAnatomy.Project.Name}.json`);

Project.CreateFileInside(`Index.js`);

Project.InitializeProjectPackages();

Project.SetValueToEmptyJsonAnatomyValues();

Project.LoadJson();

Project.WriteFileInside('Index.js', 
`/***
 * You can expand the anatomy of ${Project.JsonAnatomy.Project.Name} as you want, this is 
 * an example file which if you write something like 
 * "Zenda command start" in the console this file will be executed, you 
 * can delete and / or add more commands in ${Project.JsonAnatomy.Project.Name}.json
 ****/

Console.Log('Hello world from ZendaJS BETA');`);

Console.Clear();

Console.Log(
` => ${SafeStringInConsole(Project.JsonAnatomy.Project.Name)} has been created!
    
  * Analyzing the anatomy
    
    - ${SafeStringInConsole(Project.JsonAnatomy.Project.Name)}.json
      = Save information related to the project.

    - Index.js
      = It is an example file used to run the "Zenda command start" 
      = command defined in ${SafeStringInConsole(Project.JsonAnatomy.Project.Name)}.json

    - Packages
      = Inside the Packages folder are all the 
      = files and/or dependencies that your project uses, here 
      = you will also find ready-made Zenda packages 
      = for you to use.

    - Starting with example file
      = cd ${Project.JsonAnatomy.Project.Name}
      = Zenda command Start

 => Happy hacking and remember drink water!`);