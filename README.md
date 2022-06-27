# ZendaJS
##### Lightweight and fast Javascript environment on the server side.
ZendaJS is a fast execution environment for the JavScript language, based on Google's amazing v8 engine, it's where this environment runs under the C/C++ language, isn't it great to have access to JavaScript on the server side? try Zenda, learn and create better things!

This environment integrates Zenda Z8, which we can see as a library that will be executed in the core of this technology every time you run a script or use the console, allowing you to access various useful features so that you do not have to use external libraries or write them yourself, we are talking about data structures, implementations to native classes along with data types. Within the anatomy of the source code of this software, you will find a folder called 'Examples', which contains examples of each of the functionality that this fantastic environment offers you, where you can find the different new implementations that Z8 does in JavaScript!

## Requirements
The simple and the minimalistic is the best, why have to install a lot of dependencies by yourself? You only have to have the python3 interpreter installed on your machine, so that it is possible to execute a script that does the entire installation process. by you!

```bash
# For MacOS <Not tested>
brew install python
# For Linux
sudo apt-get install python3
```

## Installation
Next, the series of commands that you must execute on your machine for the installation of this JavaScript environment will be shown, make sure you do not leave any out, it is likely that this will take time, since dependencies will be installed.
```bash
# Clone Zenda repo
git clone https://github.com/codewithrodi/ZendaJS.git
# Enter to Zenda source code
cd ZendaJS 
# It will allow you to run Zenda from anywhere in your file branch.
export PATH=$PATH:`pwd` 
# For save changes in PATH
source ~/.bashrc 
# Update packages
sudo apt update
# To install necessary packages for build
python3 Helper.py --BuildDependencies 
# For install runtime dependencies
python3 Helper.py --RuntimeDependencies
# For build Zenda and make executable (Optional)
# make
```
After executing these series of commands, you just have to type "Zenda" in your terminal to see that the software has already been installed, When executing "Zenda" in your terminal, a help will be displayed about the available commands that you can use!

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
## Problems with the executable and compatibility
If you followed all the steps and the executable gives you problems or you suffer problems when compiling, it is likely that you are testing on Windows or MacOS, Zenda has only been tested on Linux distributions, the development of this JavaScript environment has been purely in Linux, it has never been tested in another operating system, so the correct operation in the different alternatives to Linux-based distributions is unknown, so, if you're on Windows or MacOS, you shouldn't get frustrated in case your console gets full of errors when trying to open the executable that already comes in the source code anatomy or when trying to compile the software.

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
This execution environment, Zenda, was created without any profit, just practice, you can learn or use the code of this software as you want, you can improve it or create your own environment from it, I leave you the invitation made to you can learn much more about this world, if you want advice, buy comfort because you will cry a lot solving bugs wuajaj:)

## License
[MIT](https://choosealicense.com/licenses/mit/)

### Remember drink water bby <3