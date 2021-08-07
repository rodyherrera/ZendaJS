# ZendaJS

Zenda is a Javascript runtime software which will allow you to execute the language as a backend and not on the client side, ZendaJS works directly with it V8 JavaScript engine developed by Google, it is likely that Zenda performs processes faster than NodeJS and Deno , learn and have fun!

Zenda not only allows you to run Javascript, but it also allows you to include Python code in your javascript files, you can see use cases and learn how to use Zenda in the files that you have available in examples folder.

## Installation

To install Zenda you need to clone the GitHub repository [git clone https://github.com/RodiiHernandezz/ZendaJS],
once cloned you must access the directory that was generated [cd ZendaJS] and finally open the terminal and execute the makefile [make].

```bash
git clone https://github.com/RodiiHernandezz/ZendaJS
cd ZendaJS
./Zenda install-it
```

When you run (./Zenda install-it) you will install the necessary dependencies and the executable will be added to the PATH of your system, so that you can run Zenda from anywhere on your computer without having to work with the source code, you can compile the I code using the make command from the directory where you have the code.

## Usage

To use ZendaJS you need to execute the file [Zenda] that was generated once the makefile was executed, when you execute the file [Zenda] you must indicate the address of the JavaScript file you want to execute, for example [./Zenda run my_script.js],
In case an error occurs in the execution or the file does not exist, this will be reported in the console, you have example files in the examples folder with the functions that ZendaJS has.

Executable commands
```bash
./Zenda install-it # For install Zenda (From source code directory)
./Zenda --help # For get help about valid arguments for executable
./Zenda --version # For get current version
./Zenda --creator # For get creator information
./Zenda shell # For run Zenda Shell <Like Browser JS Console>
./Zenda run my_folder/my_file.js # For run javascript files
```

Using example file from source code directoryy
```bash
./Zenda run examples/computer.js
OR
./Zenda your_javascript_file_location.js
```

## Contributing
ZendaJS was created to test my knowledge when developing things from scratch, it is likely that over time it will improve as I read, understand and study the documentation of the Google V8 engine <3.

## License
[MIT](https://choosealicense.com/licenses/mit/)
