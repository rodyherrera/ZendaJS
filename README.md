# ZendaJS
##### Lightweight and fast Javascript environment on the server side.
##### Just tested in Linux
ZendaJS is a javascript environment that allows you to execute the language on the server side and not on the client side, this technology works using Google's V8 engine in C++, in some processes Zenda can achieve a higher performance compared to other environments on the side. from the server like NodeJS or Deno.

As this technology is not 100% developed and is only in beta versions, you have the possibility to interact with the Python programming language from your JavaScript files, that's great, you can see each of the functionalities of this technology in the folder From examples, when interacting with Python you can do everything, Python is a language with which you can achieve anything.

Z8, Zenda integrates extra functionalities to already predefined JavaScript objects, such as Arrays, Strings etc ..., What the Z8 does is integrate new methods to these objects, also data structures and even algorithms for cryptography, you just have to check the folder examples and head to Z8!

## Requirements
You only need to have Python3 installed, this to make possible the installation of the necessary packages both to compile and to run Zenda, from the Helper.py file located in the source code all the magic happens so that you do not have to install each package yourself.

```bash
# For MacOS <Not tested>
brew install python
# For Linux
sudo apt-get install python3
```

## Installation

```bash
# Clone Zenda repo
git clone https://github.com/codewithrodi/ZendaJS.git
# Enter to Zenda source code
cd ZendaJS 
# It will allow you to run Zenda from anywhere in your file branch.
export PATH=$PATH:`pwd` 
# For save changes in PATH
source ~/.bashrc 
# To install necessary packages for build
python3 Helper.py --BuildDependencies 
 # For install runtime dependencies
python3 Helper.py --RuntimeDependencies
make # For build Zenda and make executable
```
After executing these series of commands, you just have to type "Zenda" in your terminal to see that the software has already been installed!

## Getting started
ZendaJS provides you with a large number of example files, you can use those files to learn how to use this technology, these files are commented, where the code you are seeing has an explanation, next we will make a quick example so that you have your first Hello World!
```bash
# Creating a file where we will write the code.
nano Script.js
```
Once the previous command is executed, a basic text editor will open in your terminal, it is there where we will write our javascript code to be able to do our first hello world.
```JS
// Showing a message in the terminal, using the Log method of the Console object, it receives the messages to be printed as parameters, for each parameter that is sent it will be a space.
Console.Log('Hello world from ZendaJS');
```
## Problems with the executable
If you followed all the steps and the executable gives you problems or you suffer problems when compiling, it is likely that you are testing on Windows or MacOS, Zenda has only been tested on Linux distributions.

## Compatibility
Zenda has only been tested on Linux.

Executable commands
```bash
# For get help about valid arguments for executable
Zenda Help 
# For get current version
Zenda Version 
# For get creator information
Zenda Creator 
# For run Zenda Shell <Like Browser JS Console>
Zenda Shell 
 # For run javascript files
Zenda Run MyFolder/MyFile.js
# For create a Zenda project
Zenda Init 
 # For get information about project
Zenda About
# For execute command of some project
Zenda Command <MODE> 
```
Using example file from source code directory
```bash
Zenda Run Examples/Computer.js
OR
Zenda Run YourJavaScriptFileLocationHere.js
```
## Note
You should not delete the installation folder of this software, because it is configured with the PATH and the system at the time you execute the command "Zenda" looks for its executable, if you delete the folder it will not find it.
If you want to learn Zenda you can look at the "Examples" folder found in the source code, you have at your fingertips a clear and brief explanation about what the functionality is, in that folder you will find all the Zenda functionalities, except project structures For this you should use "Zenda Init" and start modeling your project.
You are likely to encounter runtime errors, Zenda is not on a stable version.

## Contributing
ZendaJS was created to test my knowledge when developing things from scratch, it is likely that over time it will improve as I read, understand and study the documentation of the Google V8 engine <3.

## License
[MIT](https://choosealicense.com/licenses/mit/)

### Remember drink water bby <3
