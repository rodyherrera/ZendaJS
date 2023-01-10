# ***
# * Copyright (C) Rodolfo Herrera Hernandez. All rights reserved.
# * Licensed under the MIT license. See LICENSE file in the project root 
# * for full license information.
# *
# * =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
# *
# * For related information - https://github.com/codewithrodi/ZendaJS/
# *
# * =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
# ****/

from os import system
from time import sleep
import sys, platform

# Just tested in Linux Mint
kSupportedOperativeSystems = ['Darwin', 'Linux']

kOperativeSystem = platform.system()

kRequiredPackages = {
    'Build': {
        'Linux': [
            'sudo apt-get install make',
            'sudo apt-get install python3.8-dev',
            'sudo apt-get install g++',
            'sudo apt-get install python3',
            'sudo apt-get install gtk+-3.0',
            'sudo apt-get install webkit2gtk-4.0',
            'sudo apt-get install libpoco-dev',
            'sudo apt-get install libcurl4-openssl-dev',
            'sudo apt-get install libuv1-dev'
        ],
        
        'Darwin': [
            'brew install make',
            'brew install gcc',
            'brew install python',
            'brew install poco',
            'brew install webkitgtk',
            'brew install gtk+3',
            'brew install libuv'
        ]
    },

    'Dependencies': {
        'Linux': [
            'sudo apt-get install python3-pip',
            'pip install python3-tk'
            'pip install python3.7-tk'
        ],

        'Darwin': [
            'brew install python-tk'
        ]
    }
}

def FinishScript() -> None:
    print('\n\n * Remember drink water <3\n\n')
    sys.exit()

def ClearScreen() -> None:
    if kOperativeSystem == 'Windows':
        system('cls')
    else:
        system('clear')

def ContinueOrExit() -> None:
    ContinueOrExit = input('\n * Do you want continue[Y/n] > ')
    
    if ContinueOrExit.lower() != 'y' and not len(ContinueOrExit) == 0:
        FinishScript()

def InstallPackages(PackageList = 'Dependencies') -> None:
    kPackageList = kRequiredPackages[PackageList][kOperativeSystem]

    for kCommand in kPackageList:
        print(f' * Installing <{kCommand}>\n')
        system(kCommand)
        ClearScreen()

def SupportedOperativeSystemOrExit() -> None:
    if not kOperativeSystem in kSupportedOperativeSystems:
        print(f' * Error, not supported OS<{kOperativeSystem}>.')
        FinishScript()
    else:
        print(f'\n > Compatible <{kOperativeSystem}>')

def InstallationSuccess() -> None:
        print('''\
 * Installation completed
   - Remember to follow the instructions you have in 
   - the Github repository, because you have to 
   - execute a series of commands so that you can 
   - install Zenda correctly on your system 
   - along with its required packages.

 * If you have mistakes...
   - Mail => contact@codewithrodi.com
   - Website => https://codewithrodi.com/
   - Repository => https://github.com/codewithrodi/ZendaJS/

 - If you are installing Zenda remember to correctly follow the 
 - instructions indicated in the Github repository.

 > Remember drink water :3.''')

def DisplayPackagesToInstall(PackageList = 'Dependencies') -> None:
    print('\n * Packages\n')

    for kPackage in kRequiredPackages[PackageList][kOperativeSystem]:
        print(f' -> {kPackage}')

    print('\n > Installing packages in the next 7 seconds...')

    sleep(7)

    ClearScreen()

try:
    kScriptCallArguments = sys.argv
    
    ClearScreen()

    if '--RuntimeDependencies' in kScriptCallArguments:
        print('''\
 * ZendaJS -> Install

  - Welcome to the installation of Zenda in your machine, next the 
  - necessary packages will be installed so that Zenda works 
  - correctly in your computer.

 * Attention
        
 - There are processes that you must execute yourself from the 
 - console, we cannot do everything from the programming 
 - language, in the same way if you do not carry out these 
 - steps, they are in the README.md of Github so that you 
 - can execute them and finish the installation of Zenda.

 * Now what?
        
 - Then you must decide if you want to install Zenda on 
 - your computer or not, for this you must enter (y) or (Y) 
 - in case you do not want to install and want to finish the 
 - installer use (n) or (N) or any other character.''')

        ContinueOrExit()

        ClearScreen()

        print('''\
 * Perfect
   - Then the program will check the operating 
   - system, if it is compatible you can 
   - continue with the installation.\n''')

        SupportedOperativeSystemOrExit()

        DisplayPackagesToInstall('Dependencies')

        InstallPackages('Dependencies')
        
        InstallationSuccess()
    
    elif '--BuildDependencies' in kScriptCallArguments:

        print('''\
 * Zenda -> Installer packages required to build the software.
 > Warning: This is a beta version not fully tested.

  -> What will happen next?
     - Next, the necessary packages will be installed to 
     - compile Zenda, depending on your operating 
     - system, different packages will be installed, not all 
     - operating systems are supported, therefore a check 
     - will be made before so that if it is not 
     - compatible the execution of the program will end.

  -> Why compile?
     - It is likely that if you want to alter the source 
     - code of Zenda, you will need to compile, but you 
     - will also need to compile in case you are on a 
     - system whose kernel is different from Linux, ZendaJS 
     - comes with a ready executable, which you can integrate 
     - into your operating system from Easy way using the 
     - commands that you find in Github, but it is likely 
     - that you will get errors if you are on MacOS, to 
     - solve these errors you need to compile the program.''')

        ContinueOrExit()

        ClearScreen()

        print('''\
 * Perfect
   - Then the program will check the operating 
   - system, if it is compatible you can 
   - continue with the installation.\n''')   

        SupportedOperativeSystemOrExit()
        
        DisplayPackagesToInstall('Build')

        InstallPackages('Build')

        InstallationSuccess()
 
    else:
        print('''\
 * Error running Helper script

   - To use the helper you need to specify a command which will execute 
   - a series of actions for you, for example if you want to install 
   - the dependencies that Zenda needs to be able to execute all its 
   - functionalities without problems you should write the following 
   - in your command line "python3 Helper.py --RuntimeDependencies", as you
   - as you will see the command you are indicating is" --RuntimeDependencies"
   - which is captured in the script taking the arguments with which 
   - you have called the Helper, through that you decide what 
   - to do and what not to do.

 * Commands
   
   => --RuntimeDependencies
      - It installs the necessary dependencies to run a Zenda script 
      - without problems, it may or may not be necessary but it is 
      - recommended that it be installed to avoid future problems at runtime.

   => --BuildDependencies
      - Install all the necessary dependencies to be able to build the source 
      - code of Zenda and thus build a new executable, this can be useful
      - if you want to implement new functionalities to the technology, either 
      - to contribute or for personal profit, you can also make use of this 
      - command if You have problems when executing the executable and you 
      - have to create a new one according to your operating system, this 
      - could happen in MacOS and derivatives.''')

except Exception as Error:
    print(f'''\
 * An error occurred when the Helper was running :(.
 > {Error}''')

except KeyboardInterrupt:
    ClearScreen(), FinishScript()
