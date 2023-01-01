/***
 * Copyright (C) Rodolfo Herrera Hernandez. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root 
 * for full license information.
 *
 * =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
 *
 * For related information - https://github.com/codewithrodi/ZendaJS/
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
    static inline const size_t GetLastSlashOfPath(const std::string FullPath);
    static inline const std::string GetFilenameFromPath(std::string Path);
    static inline const std::string GetDirectoryNameFromPath(std::string Path);
    static inline const bool IsAbsolutePath(const std::string Path);

    static inline const bool IsAbsolutePath(const std::string Path){
        #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
            size_t Position = Path.find(':');
            return (Position != std::string::npos);
        #else
            if(Path.length() == 0)
                return false;
            return (Path.at(0) == '/');
        #endif
    }

    static inline const std::string GetDirectoryNameFromPath(std::string Path){
        size_t Position = GetLastSlashOfPath(Path);
        if(Position != std::string::npos)
            Path.erase(Position, Path.length() - Position);
        return Path;
    }

    static inline const std::string GetFilenameFromPath(std::string Path){
        size_t Position = GetLastSlashOfPath(Path);
        if(Position != std::string::npos)
            Path.erase(0, Position + 1);
        return Path;
    }

    static inline const size_t GetLastSlashOfPath(const std::string FullPath){
        size_t Position = FullPath.find_last_of('/');
        if(Position == std::string::npos)
            Position = FullPath.find_last_of('\\');
        return Position;
    }

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