/***
 * Copyright (C) Rodolfo Herrera Hernandez. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root 
 * for full license information.
 *
 * =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
 *
 * Installation.hxx: Zenda installation.
 *
 * This file allows you to install Zenda on the machine.
 *
 * For related information - https://github.com/rodiihernandezz/ZendaJS/
 *
 * =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
 ****/

static vector<string> GetNecessaryPackages();
static void InstallNecessaryPackages();
static void InstallZendaJS();
static void EndZendaInstallation();

static vector<string> GetNecessaryPackages(){
   vector<string> Packages;
   const char* OS = OperativeSystem();
   if(!strcmp("LINUX", OS)){
      Packages.push_back("sudo apt-get install python3");
      Packages.push_back("sudo apt-get install python3-pip");
      Packages.push_back("pip install python3-tk");
   }else if(!strcmp("APPLE", OS)){
      Packages.push_back("brew install python");
      Packages.push_back("brew install python-tk");
   }
   Packages.push_back("pip install turtle");
   return Packages;
}

static void InstallZendaJS(){
   ClearConsole();
   const char* OS = OperativeSystem();
   if( (!strcmp("LINUX", OS)) || (!strcmp("APPLE", OS)) ){
      cout << R"""( * ZendaJS -> Install

   - Welcome to the installation of Zenda in your 
   - machine, next the necessary packages will be 
   - installed so that Zenda works correctly in your computer.

 * Attention
   
   - There are processes that you must execute yourself 
   - from the console, we cannot do everything from 
   - the programming language, in the same way if you do 
   - not carry out these steps, they are in the README.md of 
   - Github so that you can execute them and finish the 
   - installation of Zenda.

 * Now what?
   
   - Then you must decide if you want to install Zenda on 
   - your computer or not, for this you must enter (y) or (Y) 
   - in case you do not want to install and want to finish the 
   - installer use (n) or (N) or any other character.

 * Do you want continue[Y/n] > )""";
      string ContinueAnswer;
      getline(cin, ContinueAnswer);
      ClearConsole();
      if(!strcmp("y", StringToLower(ContinueAnswer).c_str()))
         InstallNecessaryPackages();
      else{
         cout << "Remember drink much water!" << endl;
         exit(EXIT_SUCCESS);
      }
   }else{
      cout << "Not Supported Operative System." << endl;
      exit(EXIT_FAILURE);
   }
}

static void InstallNecessaryPackages(){
   vector<string> Packages = GetNecessaryPackages();
   unsigned short int Iterator = 0;
   for(Iterator; Iterator < Packages.size(); Iterator++){
      const char* CurrentPackage = Packages.at(Iterator).c_str();
      cout << endl << " * Installing -> " << CurrentPackage << endl << endl;
      system(CurrentPackage);
      ClearConsole();
   }
   EndZendaInstallation();
}

static void EndZendaInstallation(){
   cout << R"""( * Finalizing the installation

   - The installation is finished, if you have 
   - followed the correct steps that are in the README 
   - (which you can see in Github) and the automatic processes 
   - performed from Zenda, you should be able to run any 
   - file compatible with Zenda.

 * Remember
   
   - Remember not to delete this directory, because here 
   - is the export PATH that you have made so that you can 
   - run Zenda from anywhere in your file branch 
   - of your operating system.

 * Starting with examples files
   
   - In this directory...
     - Zenda run examples/arguments.js
     - Zenda run examples/fake_data_generator.js
     - Zenda run examples/person_creator.js
     - Zenda run examples/console.js

 * Valid commands for the executable
   
   - Zenda help (Get valid help about commands)
   - Zenda version (Get current Zenda version)
   - Zenda shell (Execute the Shell)
   - Zenda run some_folder/some_script.js (Execute file)
   - Zenda install-it (Install Zenda)
   - Zenda init (Initialize Zenda anatomy for project)
   - Zenda command <mode> (Run command defined in <Project>.json)

 * Happy hacking and drink water.
   - https://codewithrodi.com/
   - contact@codewithrodi.com
   - https://github.com/rodiihernandezz/ZendaJS/)""" << endl;
}