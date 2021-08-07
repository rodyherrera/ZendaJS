static void InstallZenda();
static void InstallDependencies();
static void StartUsingZenda();
static inline void ExportPath();

static inline void ExportPath(){
   // DONT WORK, EXPORT PATH AUTOMATICALLY FOR USE ZENDA WITHOUT WORK WITH SOURCE CODE DIRECTORY.
   string ExportPathCommand = "export PATH=$PATH:" + CurrentWorkingDirectory();
   system(ExportPathCommand.c_str());
}

static void InstallZenda(){
   ClearConsole();
   string OS = OperativeSystem();
   if( (OS != "APPLE") && (OS != "LINUX") ){
      cout << "Forgive us, but at the moment we cannot do the automatic installation in <" << OS << ">." << endl;
      exit(EXIT_FAILURE);
   }
   cout << " * Welcome to the ZendaJS installation" << endl;
   cout << " >> Operative System <" << OS << ">" << endl; 
   cout << R"""(
 -> If you continue, you will install dependencies and 
    export ZendaJS PATH so you can run it anywhere on your computer.

 -> It is likely that when installing the necessary 
    packages, the ROOT password of your operating system will be requested.

 -> WARNING
    - If you continue, the PATH for you to run Zenda from any part 
    - of your computer's storage will be located in the current directory, 
    - you will not be able to delete or move this directory because the PATH 
    - will not be deleted and corrected correctly, if you want to locate 
    - the code Zenda source elsewhere creates a folder and moves all files 
    - to it and starts the installation process there, success.
)""";
   cout << endl << "    - Current installation folder" << endl << "      = " << CurrentWorkingDirectory() << endl << endl;
   cout << " /> Do you want to continue? [Y/n]: ";
   string Answer;
   getline(cin, Answer);
   Answer = StringToUpper(Answer);
   if(Answer == "Y"){
      // THIS FUNCTION DOESNT WORK.
      // ExportPath();
      InstallDependencies();
   }else{
      ClearConsole();
      cout << R"""(
 * Remember drink water.
      )""";
   }
}

static void InstallDependencies(){
   ClearConsole();
   string OS = OperativeSystem();
   cout << R"""(
 * Then the following dependencies will be installed to run 
   ZendaJS without problems.
 
   - The installation is automatic for operating systems that 
     are based on Linux or Mac computers.
   
   - If you have another operating system you will have to 
     install the following packages manually...

   > python3
   > pip3

   - Part of the Zenda code is mostly written in C ++, it also 
   - includes Python.h to be able to interpret Python code if 
   - you need to install it, but it is better that you have it
   - installed, it is required.

 * Let's Go
   )""" << endl;
   string Answer;
   cout << R"""(
 > Then you must respond by entering the letter (Y) if you want to continue 
   with the installation of the packages, or enter the 
   letter (N) if you want to exit the installation.

 /> Do you want to install the packages? [Y/n]: )""";
   getline(cin, Answer);
   Answer = StringToUpper(Answer);
   if(Answer == "Y"){
      ClearConsole();
      cout << "Starting the installation for <python3>" << endl << endl;
      if(OS == "APPLE"){
         system("sudo brew install python3");
      }else{
         system("sudo apt install python3");
      }
      ClearConsole();
      cout << "Starting the installation for <pip3>" << endl << endl;
      system("curl https://bootstrap.pypa.io/get-pip.py -o get-pip.py");
      system("python3 get-pip.py");
      system("rm get-pip.py");
      StartUsingZenda();
   }else{
      ClearConsole();
      cout << endl << "Remember drink water!" << endl << endl;
   }
   exit(EXIT_SUCCESS);
}

static void StartUsingZenda(){
   ClearConsole();
   cout << R"""(
 * Apparently everything has gone well, it is time to start using Zenda

   -> You can use the command "Zenda --help" 
      to see the list of available commands

 * Example to start running scripts

   >> Directory anatomy for the example

   - SomeDir (Parent Directory)
     - SomeFolder (Folder within the directory)
       - ScriptOne.js (Javascript file inside SomeFolder directory)
     - ScriptTwo.js (Javascript file inside parent directory)
   
 -> What you should run on your console to run 
    the scripts that are in the example directory

    >> Zenda run SomeDir/SomeFolder/ScriptOne.js
    >> Zenda run SomeDir/ScriptTwo.js

 -> WARNING
    - You cannot delete or move the folder where you 
    - installed ZendaJS because it is the folder where the 
    - PATH was exported so that you can run Zenda from 
    - anywhere on your computer.

    - If you want to remove the folder and have the Zenda source code 
    - located in another part of your computer's storage, you must perform 
    - the installation again in that folder.

 /> Happy Hacking!
)""";
}
