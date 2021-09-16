/***
 * Copyright (C) Rodolfo Herrera Hernandez. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root 
 * for full license information.
 *
 * =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
 *
 * For related information - https://github.com/rodiihernandezz/ZendaJS/
 *
 * =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
 ****/

namespace Zenda::Shared{
    static inline const std::string OperativeSystem();
    static inline void ExecutePythonFileFromNative(std::string CharFile);
    static inline const std::string ConsoleBackground(std::string Background);
    static inline const std::string ConsoleStyle(std::string Style);
    static inline const std::string ConsoleColor(std::string Color);

    static inline const std::string OperativeSystem(){
        #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
            #ifdef _WIN64
                return "WIN64"
            #else
                return "WIN32"
            #endif
        #elif __APPLE__
            return "APPLE";
        #elif __linux__
            return "LINUX";
        #elif __unix__
            return "UNIX";
        #elif defined(_POSIX_VERSION)
            return "POSIX";
        #else
            return "UKNOWN";
        #endif
    }

    static inline void ExecutePythonFileFromNative(std::string CharFile){
        system(std::string("python3" + CharFile).c_str());
    }

    static inline const std::string ConsoleBackground(std::string Background){
        Background = Zenda::Algorithms::StringToLower(Background);
        if(Background == "black")
            return "\33[40m";
        else if(Background == "red")
            return "\33[41m";
        else if(Background == "green")
            return "\33[42m";
        else if(Background == "yellow")
            return "\33[43m";
        else if(Background == "blue")
            return "\33[44m";
        else if(Background == "violet")
            return "\33[45m";
        else if(Background == "beige")
            return "\33[46m";
        else if(Background == "white")
            return "\33[47m";
        else
            return "";
    }

    static inline const std::string ConsoleStyle(std::string Style){
        Style = Zenda::Algorithms::StringToLower(Style);
        if(Style == "normal")
            return "\33[0m";
        else if(Style == "end")
            return "\n";
        else if(Style == "bold")
            return "\33[1m";
        else if(Style == "italic")
            return "\33[3m";
        else if(Style == "url")
            return "\33[4m";
        else if(Style == "blink")
            return "\33[5m";
        else if(Style == "blink2")
            return "\33[6m";
        else if(Style == "selected")
            return "\33[7m";
        else
            return "";
    }

    static inline const std::string ConsoleColor(std::string Color){
        Color = Zenda::Algorithms::StringToLower(Color);
        if(Color == "black")
            return "\33[30m";
        else if(Color == "red")
            return "\33[31m";
        else if(Color == "green")
            return "\33[32m";
        else if(Color == "yellow")
            return "\33[33m";
        else if(Color == "blue")
            return "\33[34m";
        else if(Color == "violet")
            return "\33[35m";
        else if(Color == "beige")
            return "\33[36m";
        else if(Color == "white")
            return "\33[37m";
        else if(Color == "grey")
            return "\33[90m";
        else
            return "";
    }

    static inline void ClearConsole(){
        const std::string OS = OperativeSystem();
        (OS == "WIN32") || (OS == "WIN64") ? system("cls") : system("clear");
    }
}