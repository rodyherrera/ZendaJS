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

namespace Zenda::FileSystem{
    namespace Native = std::experimental::filesystem;
    
    static inline const std::vector<std::string> ListDirectory(const std::string Path);
    static inline const unsigned int CountLines(const std::string FilePath);
    static inline const bool Move(const std::string ActualPath, const std::string NextPath);
    static inline const bool Rename(const std::string OldName, const std::string NewName);
    static inline void CreateFile(const std::string Filename);
    static inline const bool FileExists(const std::string& Path);
    static const std::string ReadFile(const std::string Filename);
    static inline const bool WriteFile(const std::string Filename, const std::string Content);
    static inline const bool RewriteFile(const std::string Filename, const std::string Content);
    static inline const int FileSize(const std::string Filename);

    static inline const std::vector<std::string> ListDirectory(const std::string Path){
        std::vector<std::string> Content;
        for(const auto& Entry : Native::directory_iterator(Path))
            Content.push_back(Zenda::Algorithms::StringStartAt(Entry.path(), std::string(Path).length()));
        return Content;
    }

    static inline const unsigned int CountLines(const std::string FilePath){
        unsigned int Lines = 0;
        std::ifstream File(FilePath);
        std::string Buffer;
        while(getline(File, Buffer))
            ++Lines;
        File.close();
        return Lines;
    }

    static inline const bool Move(const std::string ActualPath, const std::string NextPath){
        return rename(ActualPath.c_str(), NextPath.c_str());
    }

    static inline const bool Rename(const std::string OldName, const std::string NewName){
        return rename(OldName.c_str(), NewName.c_str());
    }

    static inline void CreateFile(const std::string Filename){
        std::ofstream File(Filename);
        File.close();
    }

    static inline const bool FileExists(const std::string& Path){
        std::ifstream File(Path);
        if(File.is_open()){
            File.close();
            return true;
        }
        return false;
    }

    static const std::string ReadFile(const std::string Filename){
        std::ifstream File;
        File.open(Filename, std::ifstream::ate);
        char* Contents;
        if(!File)
            return "Unable to open the file.";
        else{
            size_t FileSize = File.tellg();
            File.seekg(0);
            std::filebuf* FileBuffer = File.rdbuf();
            Contents = new char[FileSize + 1]();
            FileBuffer->sgetn(Contents, FileSize);
            File.close();
            return Contents;
        }
    }

    static inline const bool WriteFile(const std::string Filename, const std::string Content){
        std::fstream File(Filename, std::ios_base::app | std::ios_base::in);
        if(!File)
            return false;
        else{
            File << Content;
            File.close();
            return true;
        }
    }

    static inline const bool RewriteFile(const std::string Filename, const std::string Content){
        std::ofstream File(Filename);
        if(!File)
            return false;
        else{
            File << Content;
            File.close();
            return true;
        }
    }

    static inline const int FileSize(const std::string Filename){
        std::streampos Begin, End;
        std::ifstream File(Filename, std::ios::binary);
        if(!File)
            return -1;
        else{
            Begin = File.tellg();
            File.seekg(0, std::ios::end);
            End = File.tellg();
            File.close();
            return (End - Begin);
        }
    }
};