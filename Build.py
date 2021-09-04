# ***
# * Copyright (C) Rodolfo Herrera Hernandez. All rights reserved.
# * Licensed under the MIT license. See LICENSE file in the project root 
# * for full license information.
# *
# * =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
# *
# * For related information - https://github.com/rodiihernandezz/ZendaJS/
# *
# * =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
# ****/

from os import system
from time import sleep
import sys, platform

kSupportedOperativeSystems = ['Darwin', 'Linux']
kOperativeSystem = platform.system()

kRequiredPackages = {
    # Tested
    'Linux': [
        'sudo apt-get install make',
        'sudo apt-get install g++',
        'sudo apt-get install python3'
    ],

    # Not tested
    'MacOS': {
        'brew install make',
        'brew install gcc',
        'brew install python3'
    }
}

def FinishScript() -> None:
    print('\n\nRemember to drink water.\n')
    sys.exit()

def ClearScreen() -> None:
    if kOperativeSystem == 'Windows':
        system('cls')
    else:
        system('clear')

def SupportedOperativeSystemOrExit() -> None:
    if not kOperativeSystem in kSupportedOperativeSystems:
        print(f' * Error, not supported OS<{kOperativeSystem}>.')
        FinishScript()

def InstallPackages() -> None:
    kCommandsToExecute = kRequiredPackages[kOperativeSystem]
    for kCommand in kCommandsToExecute:
        print(f' * Running <{kCommand}>\n')
        system(kCommand)
        ClearScreen()

try:
    ClearScreen()
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
       - solve these errors you need to compile the program.
    '''.rstrip())
    ContinueOrExit = input('\n /> Do you want to continue[Y/n]: ')
    if ContinueOrExit.lower() != 'y':
        FinishScript()
    ClearScreen()
    print('''\
 * Perfect
   - Then the program will check the operating 
   - system, if it is compatible you can 
   - continue with the installation.
    '''.rstrip())
    SupportedOperativeSystemOrExit()
    print(f'''\
\n > Compatible <{kOperativeSystem}>

 * Packages\n
'''.rstrip())
    for kPackage in kRequiredPackages[kOperativeSystem]:
        print(f'  -> {kPackage}')
    print('\n > Installing packages in next 7 seconds...')
    sleep(7)
    ClearScreen()
    InstallPackages()
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
   - Repository => https://github.com/rodiihernandezz/ZendaJS/

 > Remember drink water :3.
    '''.rstrip())
except KeyboardInterrupt:
    ClearScreen()
    FinishScript()