# ZendaJS
##### Lightweight and fast Javascript environment on the server side.
Zenda is a Javascript runtime software which will allow you to execute the language as a backend and not on the client side, ZendaJS works directly with it V8 JavaScript engine developed by Google, it is likely that Zenda performs processes faster than NodeJS and Deno, learn and have fun!

Zenda not only allows you to run Javascript, but it also allows you to include Python code in your javascript files, you can see use cases and learn how to use Zenda in the files that you have available in examples folder.

## Installation

```bash
git clone https://github.com/RodiiHernandezz/ZendaJS
cd ZendaJS
export PATH=$PATH:`pwd`
Zenda install-it
```

Or you can use
```bash
git clone https://github.com/RodiiHernandezz/ZendaJS && cd ZendaJS && export PATH=$PATH:`pwd` && Zenda install-it
```

In case when executing the already compiled Zenda file you get an error, you can try building Zenda again, using the [make] command, but you need install dependencies.

```bash
# Inside ZendaJS Diretory for make
python3 Build.py
make
```

Or

```bash
python3 Build.py && make
```

Manually:

```bash
sudo apt-get install make # For use makefile
sudo apt-get install g++ # For compile
sudo apt-get install python3 # For -lpython3.8 flag
```
Or
```bash
sudo apt-get install make && apt-get install g++ && apt-get install python3
```

If you have MacOS (Not tested)
```bash
brew install make # For use makefile
brew install gcc # For compile, if it dont work use g++
brew install python3 # For -lpython3.8 flag
```
Or 
```bash
brew install make && brew install gcc && brew install python3
```

When you run (Zenda install-it) you will install the necessary dependencies and the executable will be added to the PATH of your system, so that you can run Zenda from anywhere on your computer without having to work with the source code, you can compile the I code using the make command from the directory where you have the code.

## Usage

To use ZendaJS you need to execute the file [Zenda] that was generated once the makefile was executed, when you execute the file [Zenda] you must indicate the address of the JavaScript file you want to execute, for example [./Zenda run my_script.js],
In case an error occurs in the execution or the file does not exist, this will be reported in the console, you have example files in the examples folder with the functions that ZendaJS has.

Executable commands
```bash
Zenda install-it # For install Zenda dependencies
Zenda help # For get help about valid arguments for executable
Zenda version # For get current version
Zenda creator # For get creator information
Zenda shell # For run Zenda Shell <Like Browser JS Console>
Zenda run my_folder/my_file.js # For run javascript files
Zenda init # For create a Zenda project
Zenda about # For get information about project
Zenda command <mode> # For execute command of some project
Zenda run-examples # For run all Zenda samples files.
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