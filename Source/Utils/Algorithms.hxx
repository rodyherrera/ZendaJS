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

namespace Zenda::Algorithms{
    static const std::vector<std::string> SplitString(const std::string &String, const std::string &Delim);
    static const inline std::string CurrentWorkingDirectory();
    static const std::string GetOutputOfCommand(std::string Command);
    static const std::string SourceCodeLocation(const std::string AdditionalPathForConcat);
    static const std::string RandomString(const unsigned short int Length);
    static const inline std::string StringToLower(std::string String);
    static const inline std::string StringToUpper(std::string String);
    static const inline std::string StringStartAt(const std::string String, unsigned int Position);
    static const inline std::string StringEndAt(const std::string String, unsigned int Position);
    static const inline std::string StringStartEndAt(const std::string String, unsigned int StartPosition, const unsigned int EndPosition);
    static const inline std::string StringLeftTrim(const std::string &String, const std::string TrimCharacters);
    static const inline std::string StringRightTrim(const std::string &String, const std::string TrimCharacters);
    static const inline std::string StringTrim(const std::string &String, const std::string LeftTrimCharacters, const std::string RightTrimCharacters);
    static const std::vector<std::string> SplitString(const std::string &String, const std::string &Delim);

    static const inline std::string CurrentWorkingDirectory(){
        char Buffer[256];
        return (getcwd(Buffer, 256) ? std::string(Buffer) : std::string(""));
    }

    static const std::string GetOutputOfCommand(std::string Command){
        std::string Data;
        FILE* Stream;
        char Buffer[256];
        Command.append(" 2>&1");
        Stream = popen(Command.c_str(), "r");
        if(Stream){
            while(!feof(Stream))
                if(fgets(Buffer, 256, Stream) != NULL) Data.append(Buffer);
            pclose(Stream);
        }
        return Data;
    }

    static const std::string SourceCodeLocation(const std::string AdditionalPathForConcat = ""){
        std::vector<std::string> CurrentPaths = SplitString(GetOutputOfCommand("echo $PATH | tr ':' '\n'"), "\n");
        for(unsigned short int Iterator = 0; Iterator < CurrentPaths.size(); Iterator++){
            std::string CurrentBinDirectory = CurrentPaths.at(Iterator);
            if(CurrentBinDirectory.find("ZendaJS") != std::string::npos)
                return CurrentBinDirectory + AdditionalPathForConcat;
        }
        return "Not Found.";
    }

    static const std::string RandomString(const unsigned short int Length){
        char Letters[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
        std::string Random = "";
        for (unsigned short int i = 0; i < Length; i++) 
            Random = Random + Letters[rand() % 26];
        return Random;
    }

    static const inline std::string StringToLower(std::string String){
        transform(String.begin(), String.end(), String.begin(), ::tolower);
        return String;
    }

    static const inline std::string StringToUpper(std::string String){
        transform(String.begin(), String.end(), String.begin(), ::toupper);
        return String;
    }

    static const inline std::string StringStartAt(const std::string String, unsigned int Position){
        std::string Buffer;
        while(String[Position])
            Buffer += String[Position], Position++;
        return Buffer;
    }

    static const inline std::string StringEndAt(const std::string String, unsigned int Position){
        std::string Buffer;
        while(String[Position])
            Buffer += String[Position], Position--;
        return Buffer;
    }

    static const inline std::string StringStartEndAt(const std::string String, unsigned int StartPosition, const unsigned int EndPosition){
        std::string Buffer;
        while( (String[StartPosition]) && (StartPosition <= EndPosition) )
            Buffer += String[StartPosition], StartPosition++;
        return Buffer;
    }

    static const inline std::string StringLeftTrim(const std::string &String, const std::string TrimCharacters = " \n\r\t\f\v"){
        size_t Start = String.find_first_not_of(TrimCharacters);
        return (Start == std::string::npos) ? "" : String.substr(Start);
    }

    static const inline std::string StringRightTrim(const std::string &String, const std::string TrimCharacters = " \n\r\t\f\v"){
        size_t End = String.find_last_not_of(TrimCharacters);
        return (End == std::string::npos) ? "" : String.substr(0, End + 1);
    }

    static const inline std::string StringTrim(const std::string &String, const std::string LeftTrimCharacters = " \n\r\t\f\v", const std::string RightTrimCharacters = " \n\r\t\f\v"){
        return StringRightTrim(StringLeftTrim(String, LeftTrimCharacters), RightTrimCharacters);
    }

    static const std::vector<std::string> SplitString(const std::string &String, const std::string &Delim){
        std::vector<std::string> Tokens;
        size_t Prev = 0, Pos = 0;
        do{
            Pos = String.find(Delim, Prev);
            if(Pos == std::string::npos)
                Pos = String.length();
            std::string Token = String.substr(Prev, Pos - Prev);
            if(!Token.empty())
                Tokens.push_back(StringTrim(Token));
            Prev = Pos + Delim.length();
        }while (Pos < String.length() && Prev < String.length());
        return Tokens;
    }
}