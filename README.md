# ZendaJS
##### Lightweight and fast Javascript environment on the server side.
ZendaJS is a javascript environment that allows you to execute the language on the server side and not on the client side, this technology works using Google's V8 engine in C++, in some processes Zenda can achieve a higher performance compared to other environments on the side. from the server like NodeJS or Deno.

As this technology is not 100% developed and is only in beta versions, you have the possibility to interact with the Python programming language from your JavaScript files, that's great, you can see each of the functionalities of this technology in the folder From examples, when interacting with Python you can do everything, Python is a language with which you can achieve anything.

Z8, Zenda integrates extra functionalities to already predefined JavaScript objects, such as Arrays, Strings etc ..., What the Z8 does is integrate new methods to these objects, also data structures and even algorithms for cryptography, you just have to check the folder examples and head to Z8!

## Requirements
You only need to have Python3 installed, this to make possible the installation of the necessary packages both to compile and to run Zenda, from the Helper.py file located in the source code all the magic happens so that you do not have to install each package yourself.

```bash
brew install python # For MacOS
sudo apt-get install python3 # For Linux
```

## Installation

```bash
git clone https://github.com/RodiiHernandezz/ZendaJS.git # Clone Zenda repo
cd ZendaJS # Enter to Zenda source code
export PATH=$PATH:`pwd` # It will allow you to run Zenda from anywhere in your file branch.
source ~/.bashrc # For save changes in PATH
python3 Helper.py --build.dependencies # To install necessary packages for build
python3 Helper.py --runtime.dependencies # For install runtime dependencies
make # For build Zenda and make executable
```
After executing these series of commands, you just have to type "Zenda" in your terminal to see that the software has already been installed!

## Problems with the executable
If you suffer problems when opening the executable it is perhaps necessary that you have to compile the code again, if you followed all the installation steps, do not open any type of problem, you just have to write the command "make" in your terminal, and you can use the executable.

## Compatibility
Zenda has only been tested on Linux Mint and Linux Ubuntu

Executable commands
```bash
Zenda help # For get help about valid arguments for executable
Zenda version # For get current version
Zenda creator # For get creator information
Zenda shell # For run Zenda Shell <Like Browser JS Console>
Zenda run my_folder/my_file.js # For run javascript files
Zenda init # For create a Zenda project
Zenda about # For get information about project
Zenda command <mode> # For execute command of some project
```
Using example file from source code directory
```bash
Zenda run Examples/Computer.js
OR
Zenda run your_javascript_file_location.js
```
## Note
You should not delete the installation folder of this software, because it is configured with the PATH and the system at the time you execute the command "Zenda" looks for its executable, if you delete the folder it will not find it.
If you want to learn Zenda you can look at the "Examples" folder found in the source code, you have at your fingertips a clear and brief explanation about what the functionality is, in that folder you will find all the Zenda functionalities, except project structures For this you should use "Zenda init" and start modeling your project.
You are likely to encounter runtime errors, Zenda is not on a stable version.

## Contributing
ZendaJS was created to test my knowledge when developing things from scratch, it is likely that over time it will improve as I read, understand and study the documentation of the Google V8 engine <3.

## License
[MIT](https://choosealicense.com/licenses/mit/)
