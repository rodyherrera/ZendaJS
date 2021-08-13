/***
 * Copyright (C) Rodolfo Herrera Hernandez. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root 
 * for full license information.
 *
 * =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
 *
 * Utils/FileSystem.hxx: File containing methods related to the file system.
 *
 * This file has methods that interact with the entire Zenda file branch 
 * that require manipulating or interacting with the file system.
 *
 * For related information - https://github.com/rodiihernandezz/ZendaJS/
 *
 * =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
 ****/

static inline void FSCreateFile(const char* Filename);
static inline bool FSFileExists(const string& Path);
static inline bool FSIsRegularFile(const char* Path);
static inline bool FSIsDirectory(const char* Path);
static inline bool FSIsBlockFile(const char* Path);
static inline bool FSIsCharacterFile(const char* Path);
static inline bool FSIsFifo(const char* Path);
static inline bool FSIsSocket(const char* Path);
static inline bool FSIsSymLink(const char* Path);
static inline unsigned int FSRemove(const char* Path);
static inline void FSCopyFileContents(const char* TargetOne, const char* TargetTwo);
static inline void FSCopy(const char* TargetOne, const char* TargetTwo, bool UpdateExisting, bool Recursive , bool DirectoriesOnly);
static inline bool FSRename(const char* OldName, const char* NewName);
static inline bool FSDirectoryIsEmpty(const char* Path);
static inline unsigned int FSCountLines(const char* FilePath);
static const char* FSReadFile(const char* Filename);
static MaybeLocal<String> FSReadFileUsingV8(const char* Filename, Isolate* LIsolate);
static bool FSWriteFile(const char* Filename, const char* Content);
static bool FSRewriteFile(const char* Filename, const char* Content);
static bool FSMove(const char* ActualPath, const char* NextPath);
static int FSFileSize(const char* Filename);
vector<string> FSListDirectory(const char* Path);

vector<string> FSListDirectory(const char* Path){
    vector<string> Content;
    for(const auto& Entry : FS::directory_iterator(Path))
        Content.push_back(
            StringStartAt(Entry.path(), string(Path).length())
        );
    return Content;
}

static inline unsigned int FSCountLines(const char* FilePath){
    unsigned int Lines = 0;
    ifstream File(FilePath);
    string Buffer;
    while(getline(File, Buffer))
        ++Lines;
    File.close();
    return Lines;
}

static bool FSMove(const char* ActualPath, const char* NextPath){
    try{
        FS::copy(ActualPath, NextPath);
        FS::remove(ActualPath);
        return true;
    }catch(FS::filesystem_error& Error){
        return false;
    }
}

static inline bool FSRename(const char* OldName, const char* NewName){
    return rename(OldName, NewName);
}

static inline void FSCopy(const char* TargetOne, const char* TargetTwo){
    FS::copy(TargetOne, TargetTwo, FS::copy_options::update_existing);
}

static inline void FSCopyFileContents(const char* TargetOne, const char* TargetTwo){
    FS::copy_file(TargetOne, TargetTwo);
}

static inline bool FSDirectoryIsEmpty(const char* Path){
    return FS::is_empty(Path);
}

static inline unsigned int FSRemove(const char* Path){
    return FS::remove_all(Path); // Return all affected files.
}

static inline bool FSIsRegularFile(const char* Path){
    return FS::is_regular_file(Path) ? true : false;
}

static inline bool FSIsBlockFile(const char* Path){
    return FS::is_block_file(Path) ? true : false;
}

static inline bool FSIsCharacterFile(const char* Path){
    return FS::is_character_file(Path) ? true : false;
}

static inline bool FSIsFifo(const char* Path){
    return FS::is_fifo(Path) ? true : false;
}

static inline bool FSIsSocket(const char* Path){
    return FS::is_socket(Path) ? true : false;
}

static inline bool FSIsSymLink(const char* Path){
    return FS::is_symlink(Path) ? true : false;
}

static inline void FSCreateFile(const char* Filename){
    ofstream File(Filename);
    File.close();
}

static inline bool FSFileExists(const string& Path){
    ifstream File(Path);
    if(File.is_open()){
        File.close();
        return true;
    }
    return false;
}

static inline bool FSIsDirectory(const char* Path){
    return FS::is_directory(Path) ? true : false;
}

static MaybeLocal<String> FSReadFileUsingV8(const char* Filename, Isolate* LIsolate){
    FILE* File = fopen(Filename, "rb");
    if(File == NULL)
        return MaybeLocal<String>();
    fseek(File, 0, SEEK_END);
    size_t Size = ftell(File);
    rewind(File);
    char* Characters = new char[Size + 1];
    Characters[Size] = '\0';
    for(size_t i = 0; i < Size;){
        i += fread(&Characters[i], 1, Size - i, File);
        if(ferror(File)){
            fclose(File);
            return MaybeLocal<String>();
        }
    }
    fclose(File);
    MaybeLocal<String> Content = String::NewFromUtf8(
        LIsolate, Characters, NewStringType::kNormal, static_cast<int>(Size)
    );
    delete[] Characters;
    return Content;
}

static const char* FSReadFile(const char* Filename){
    ifstream File;
    File.open(Filename, ifstream::ate);
    char* Contents;
    if(!File)
        return "Unable to open the file.";
    else{
        size_t FileSize = File.tellg();
        File.seekg(0);
        filebuf* FileBuffer = File.rdbuf();
        Contents = new char[FileSize + 1]();
        FileBuffer->sgetn(Contents, FileSize);
        File.close();
        return Contents;
    }
}

static bool FSWriteFile(const char* Filename, const char* Content){
    fstream File(Filename, ios_base::app | ios_base::in);
    if(!File)
        return false;
    else{
        File << Content;
        File.close();
        return true;
    }
}

static bool FSRewriteFile(const char* Filename, const char* Content){
    ofstream File(Filename);
    if(!File)
        return false;
    else{
        File << Content;
        File.close();
        return true;
    }
}

static int FSFileSize(const char* Filename){
    streampos Begin, End;
    ifstream File(Filename, ios::binary);
    if(!File)
        return -1;
    else{
        Begin = File.tellg();
        File.seekg(0, ios::end);
        End = File.tellg();
        File.close();
        return (End - Begin);
    }   
}