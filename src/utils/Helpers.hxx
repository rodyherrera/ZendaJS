void InstallDependencies(){
    ClearConsole();
    string OS = OperativeSystem();
    cout << " Detected -> [" << OS << "]" << endl << R"""(
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
    if(StringStartEndAt(OS, 0, 3) == "WIN"){
        cout << "Forgive us, but at the moment we cannot do the automatic installation in <Windows>." << endl;
        exit(EXIT_FAILURE);
    }
    string Answer;
    cout << R"""(
 > Then you must respond by entering the letter (Y) if you want to continue 
 with the installation of the packages, or enter the 
 letter (N) if you want to exit the installation.
    )""" << endl;
    cout << "Do you want to install the packages? [Y/n]: ";
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
        ClearConsole();
        cout << R"""(
 * The installation of the packages has finished, 
 you can check if your scripts work correctly, if so, congratulations.
 
 - Remember drink water and happy hacking!
        )""" << endl;
    }else{
        ClearConsole();
        cout << endl << "Remember drink water!" << endl << endl;
    }
    exit(EXIT_SUCCESS);
}

void ShowHelp(){
    cout << endl << R"""(
 * Help - Valid arguments for the executable.
    )""" << endl << R"""(
 * --shell
    Usage -> ./Zenda --shell
    For -> You get a shell to be able to run 
    javascript to experiment with native functions.

 * --version
    Usage -> ./Zenda --version
    For -> You get the current version of Zenda.

 * --creator
    Usage -> ./Zenda --creator
    For -> You get the ZendaJS creator.

 * --execute
    Usage -> ./Zenda --execute some_folder/some_file.js
    For -> It allows you to run a Zenda compatible Javascript file.

 * --install-dependencies
    Usage -> ./Zenda --install-dependencies
    For -> It allows you to install the necessary dependencies 
    so that you can run your scripts that use Zenda without problems.

 * --help
    Usage -> ./Zenda --help
    For -> It allows you to get help on the valid 
    parameters that the Zenda executable accepts.
    )""" << endl << endl;
}

void SetCallArguments(int argc, char* argv[]){
    for(unsigned short int i = 2; i < argc; ++i)
        CallArguments.push_back(argv[i]);
}