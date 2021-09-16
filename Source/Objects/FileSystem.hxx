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

namespace Zenda::JavaScript::Objects::FileSystem{
    static inline void FileExists(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static void ListDirectory(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void Copy(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void Move(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void CopyFileContent(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void IsEmptyDirectory(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void Rename(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static void Remove(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void CountLines(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void IsFile(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void IsDirectory(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void IsBlockFile(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void IsCharacterFile(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void IsFifo(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void IsSocket(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void IsSymLink(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static void CreateFile(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static void CreateFolder(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static void RemoveFile(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static void RemoveFolder(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void QuickReadFile(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void ReadFile(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void QuickFileSize(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static void FileSize(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void QuickWriteFile(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static void WriteFile(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void QuickRewriteFile(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static void RewriteFile(const v8::FunctionCallbackInfo<v8::Value>& Arguments);

    static inline void FileExists(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if(Arguments[0]->IsUndefined())
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "You must enter a file in order to verify its existence.");
        else{
            v8::String::Utf8Value File(Arguments.GetIsolate(), Arguments[0]);
            Arguments.GetReturnValue().Set(Zenda::Shortcuts::V8Boolean(Arguments.GetIsolate(), Zenda::FileSystem::FileExists(std::string(*File))));
        }
    }

    static void ListDirectory(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if(Arguments[0]->IsUndefined())
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "You must indicate a directory to be able to list it.");
        else{
            v8::String::Utf8Value DirectoryPath(Arguments.GetIsolate(), Arguments[0]);
            std::vector<std::string> DetectedContent = Zenda::FileSystem::ListDirectory(std::string(*DirectoryPath));
            v8::Local<v8::Array> ReturnValue = v8::Array::New(Arguments.GetIsolate(), DetectedContent.size());
            for(unsigned short int Iterator = 0; Iterator < DetectedContent.size(); Iterator++)
                v8::Maybe<bool> SetValue = ReturnValue->Set(
                    Arguments.GetIsolate()->GetCurrentContext(), Iterator,
                    Zenda::Shortcuts::V8String(Arguments.GetIsolate(), DetectedContent.at(Iterator)));
            Arguments.GetReturnValue().Set(ReturnValue);
        }
    }

    static inline void Copy(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if( (Arguments[0]->IsUndefined()) || (Arguments[1]->IsUndefined()) )
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "To copy files you need to send two parameters where the first is the file to be copied and the second is the new path where you want to send the file.");
        else{
            v8::String::Utf8Value TargetOne(Arguments.GetIsolate(), Arguments[0]);
            v8::String::Utf8Value TargetTwo(Arguments.GetIsolate(), Arguments[1]);
            Zenda::FileSystem::Native::copy(
                std::string(*TargetOne), std::string(*TargetTwo), Zenda::FileSystem::Native::copy_options::recursive);
        }
    }

    static inline void Move(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if( (Arguments[0]->IsUndefined()) || (Arguments[1]->IsUndefined()) )
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "To move files you need to send two parameters where the first is the file to move and the second is the new path where you want to send the file.");
        else{
            v8::String::Utf8Value ActualPath(Arguments.GetIsolate(), Arguments[0]);
            v8::String::Utf8Value NextPath(Arguments.GetIsolate(), Arguments[1]);
            Zenda::FileSystem::Move(std::string(*ActualPath), std::string(*NextPath));
        }
    }

    static inline void CopyFileContent(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if( (Arguments[0]->IsUndefined()) || (Arguments[1]->IsUndefined()) )
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "To copy the content of a file to another file you need to send two parameters where the first is the file that contains the content and the second is the file you want to send content to.");
        else{
            v8::String::Utf8Value TargetOne(Arguments.GetIsolate(), Arguments[0]);
            v8::String::Utf8Value TargetTwo(Arguments.GetIsolate(), Arguments[1]);
            Zenda::FileSystem::Native::copy_file(std::string(*TargetOne), std::string(*TargetTwo));
        }
    }

    static inline void IsEmptyDirectory(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if(Arguments[0]->IsUndefined())
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "To check if a directory is empty, you must indicate it as a parameter, we are not fortune tellers.");
        else{
            v8::String::Utf8Value Directory(Arguments.GetIsolate(), Arguments[0]);
            Arguments.GetReturnValue().Set(
                Zenda::Shortcuts::V8Boolean(Arguments.GetIsolate(), Zenda::FileSystem::Native::is_empty(std::string(*Directory))));
        }
    }

    static inline void Rename(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if( (Arguments[0]->IsUndefined()) || (Arguments[1]->IsUndefined()) )
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "If you want to rename a file, you must send two parameters where the first is the path where the file to be renamed is located and the second is the name that will be assigned to the sent file.");
        else{
            v8::String::Utf8Value OriginalFilename(Arguments.GetIsolate(), Arguments[0]);
            v8::String::Utf8Value NewFilename(Arguments.GetIsolate(), Arguments[1]);
            Arguments.GetReturnValue().Set(Zenda::Shortcuts::V8Boolean(Arguments.GetIsolate(), Zenda::FileSystem::Rename(std::string(*OriginalFilename), std::string(*NewFilename))));
        }
    }

    static void Remove(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        if(Arguments[0]->IsUndefined())
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "You need to pass at least one parameter to 's remove method.");
        else{
            unsigned short int Operations = 0;
            for(unsigned short int Iterator = 0; Iterator < Arguments.Length(); Iterator++){
                v8::HandleScope Scope(Arguments.GetIsolate());
                v8::String::Utf8Value Who(Arguments.GetIsolate(), Arguments[Iterator]);
                Operations += Zenda::FileSystem::Native::remove_all(std::string(*Who));
            }
            Arguments.GetReturnValue().Set(Zenda::Shortcuts::V8Number(Arguments.GetIsolate(), Operations));
        }
    }

    static inline void CountLines(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if(Arguments[0]->IsUndefined())
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "You need to indicate a file to count its lines.");
        else{
            v8::String::Utf8Value Filename(Arguments.GetIsolate(), Arguments[0]);
            Arguments.GetReturnValue().Set(Zenda::Shortcuts::V8Number(Arguments.GetIsolate(), Zenda::FileSystem::CountLines(std::string(*Filename))));
        }
    }

    static inline void IsFile(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if(Arguments[0]->IsUndefined())
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "You need to send at least one parameter to check if this as path is a file or not.");
        else{
            v8::String::Utf8Value MaybeRegularFile(Arguments.GetIsolate(), Arguments[0]);
            Arguments.GetReturnValue().Set(
                Zenda::Shortcuts::V8Boolean(Arguments.GetIsolate(), Zenda::FileSystem::Native::is_regular_file(std::string(*MaybeRegularFile))));
        }
    }

    static inline void IsDirectory(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if(Arguments[0]->IsUndefined())
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "You must send at least one parameter to check if this path is a directory or not.");
        else{
            v8::String::Utf8Value MaybeDirectory(Arguments.GetIsolate(), Arguments[0]);
            Arguments.GetReturnValue().Set(
                Zenda::Shortcuts::V8Boolean(Arguments.GetIsolate(), Zenda::FileSystem::Native::is_directory(std::string(*MaybeDirectory))));
        }
    }

    static inline void IsBlockFile(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if(Arguments[0]->IsUndefined())
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "You need to indicate a file to indicate if it is a file or not.");
        else{
            v8::String::Utf8Value MaybeBlockFile(Arguments.GetIsolate(), Arguments[0]);
            Arguments.GetReturnValue().Set(Zenda::Shortcuts::V8Boolean(
                Arguments.GetIsolate(), Zenda::FileSystem::Native::is_block_file(std::string(*MaybeBlockFile))));
        }
    }

    static inline void IsCharacterFile(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if(Arguments[0]->IsUndefined())
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "You need to indicate a file to indicate if it is a character file or not.");
        else{
            v8::String::Utf8Value MaybeCharacterFile(Arguments.GetIsolate(), Arguments[0]);
            Arguments.GetReturnValue().Set(Zenda::Shortcuts::V8Boolean(
                Arguments.GetIsolate(), Zenda::FileSystem::Native::is_character_file(std::string(*MaybeCharacterFile))));
        }
    }

    static inline void IsFifo(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if(Arguments[0]->IsUndefined())
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "You need to indicate a file to indicate if it is a fifo file or not.");
        else{
            v8::String::Utf8Value MaybeFifoFile(Arguments.GetIsolate(), Arguments[0]);
            Arguments.GetReturnValue().Set(
                Zenda::Shortcuts::V8Boolean(Arguments.GetIsolate(), Zenda::FileSystem::Native::is_fifo(std::string(*MaybeFifoFile))));
        }
    }

    static inline void IsSocket(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if(Arguments[0]->IsUndefined())
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "You need to indicate a file to indicate if it is a socket or not.");
        else{
            v8::String::Utf8Value MaybeSocketFile(Arguments.GetIsolate(), Arguments[0]);
            Arguments.GetReturnValue().Set(
                Zenda::Shortcuts::V8Boolean(Arguments.GetIsolate(), Zenda::FileSystem::Native::is_socket(std::string(*MaybeSocketFile))));
        }
    }

    static inline void IsSymLink(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if(Arguments[0]->IsUndefined())
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "You need to indicate a file to indicate if it is a symlink or not.");
        else{
            v8::String::Utf8Value MaybeSymlink(Arguments.GetIsolate(), Arguments[0]);
            Arguments.GetReturnValue().Set(
                Zenda::Shortcuts::V8Boolean(Arguments.GetIsolate(), Zenda::FileSystem::Native::is_symlink(std::string(*MaybeSymlink))));
        }
    }

    static void CreateFile(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        if(Arguments[0]->IsUndefined())
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "You must enter at least one file in order to create a file..");
        else
            for(unsigned short int Iterator = 0; Iterator < Arguments.Length(); Iterator++){
                v8::HandleScope Scope(Arguments.GetIsolate());
                v8::String::Utf8Value Filename(Arguments.GetIsolate(), Arguments[Iterator]);
                Zenda::FileSystem::CreateFile(std::string(*Filename));
            }
    }

    static void CreateFolder(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        if(Arguments[0]->IsUndefined())
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "You need to indicate one or more parameters which will be used to create the directories in the CreateFolder method.");
        else
            for(unsigned short int Iterator = 0; Iterator < Arguments.Length(); Iterator++){
                v8::HandleScope Scope(Arguments.GetIsolate());
                v8::String::Utf8Value FolderName(Arguments.GetIsolate(), Arguments[Iterator]);
                mkdir(*FolderName, 0777);
            }
    }

    static void RemoveFile(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        if(Arguments[0]->IsUndefined())
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "You need to indicate as parameters one or more files to delete in the RemoveFile method.");
        else
            for(unsigned short int Iterator = 0; Iterator < Arguments.Length(); Iterator++){
                v8::HandleScope Scope(Arguments.GetIsolate());
                v8::String::Utf8Value PathToRemove(Arguments.GetIsolate(), Arguments[Iterator]);
                remove(*PathToRemove);
            }
    }

    static void RemoveFolder(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        if(Arguments[0]->IsUndefined())
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "You need to indicate as parameters one or more folders to delete in the RemoveFolder method.");
        else
            for(unsigned short int Iterator = 0; Iterator < Arguments.Length(); Iterator++){
                v8::HandleScope Scope(Arguments.GetIsolate());
                v8::String::Utf8Value PathToRemove(Arguments.GetIsolate(), Arguments[Iterator]);
                rmdir(*PathToRemove);
            }
    }

    static inline void QuickReadFile(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if(Arguments[0]->IsUndefined())
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "You need to specify a file as a parameter to be able to read it in the QuickReadFile method.");
        else{
            v8::String::Utf8Value Filename(Arguments.GetIsolate(), Arguments[0]);
            const std::string CharFilename = std::string(*Filename), ReadResult = Zenda::FileSystem::ReadFile(CharFilename);
            Arguments.GetReturnValue().Set(Zenda::Shortcuts::V8String(Arguments.GetIsolate(), std::string(ReadResult)));
        }
    }

    static inline void ReadFile(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if( (Arguments[0]->IsUndefined()) || (Arguments[1]->IsUndefined()) )
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "You need to indicate the file to read and a function like Callback that will receive two parameters where the first is a Boolean data that indicates if there was an error when opening the file and the second is a string that indicates the content of the file.");
        else{
            v8::String::Utf8Value Filename(Arguments.GetIsolate(), Arguments[0]);
            const std::string CharFilename = std::string(*Filename);
            std::string Content = "";
            bool Error = true;
            if(Zenda::FileSystem::FileExists(CharFilename)){
                Error = false;
                Content = Zenda::FileSystem::ReadFile(CharFilename);
            }
            v8::Local<v8::Value> Argv[] = {Zenda::Shortcuts::V8Boolean(Arguments.GetIsolate(), Error), Zenda::Shortcuts::V8String(Arguments.GetIsolate(), std::string(Content))};
            v8::MaybeLocal<v8::Value> FunctionCall = Zenda::Shortcuts::V8CallJSFunction(
                Arguments.GetIsolate()->GetCurrentContext(), Arguments[1].As<v8::Function>(),
                Zenda::Shortcuts::V8Boolean(Arguments.GetIsolate(), true), 2, Argv);
        }
    }

    static inline void QuickFileSize(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if(Arguments[0]->IsUndefined())
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "You need to indicate a file to be able to obtain its weight in bytes, this in the QuickFileSize method.");
        else{
            v8::String::Utf8Value Filename(Arguments.GetIsolate(), Arguments[0]);
            const std::string CharFilename = std::string(*Filename);
            Arguments.GetReturnValue().Set(Zenda::Shortcuts::V8Number(Arguments.GetIsolate(), Zenda::FileSystem::FileSize(CharFilename)));
        }
    }

    static void FileSize(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if( (Arguments[0]->IsUndefined()) || (Arguments[1]->IsUndefined()) )
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "You need to send two parameters to the FileSize method, where the first is the path of the file to obtain the size and the second is a function that acts as a callback that receives two parameters where the first is a Boolean data that indicates if there was an error when opening the file. file and the second is an integer that indicates the size in bytes of the file.");
        else{
            v8::String::Utf8Value Filename(Arguments.GetIsolate(), Arguments[0]);
            const std::string CharFilename = std::string(*Filename);
            unsigned int SizeResult = Zenda::FileSystem::FileSize(CharFilename);
            bool Error = false;
            if(SizeResult == -1)
                Error = true;
            v8::Local<v8::Value> Argv[] = {Zenda::Shortcuts::V8Boolean(Arguments.GetIsolate(), true), Zenda::Shortcuts::V8Number(Arguments.GetIsolate(), SizeResult)};
            v8::MaybeLocal<v8::Value> FunctionCall = Zenda::Shortcuts::V8CallJSFunction(
                Arguments.GetIsolate()->GetCurrentContext(), Arguments[1].As<v8::Function>(),
                Zenda::Shortcuts::V8Boolean(Arguments.GetIsolate(), true), 2, Argv);
        }
    }

    static inline void QuickWriteFile(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if( (Arguments[0]->IsUndefined()) || (Arguments[1]->IsUndefined()) )
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "In order to use the QuickWriteFile function you need to indicate a file to which you want to write and as second parameter the content to add.");
        else{
            v8::String::Utf8Value Filename(Arguments.GetIsolate(), Arguments[0]);
            v8::String::Utf8Value Content(Arguments.GetIsolate(), Arguments[1]);
            const std::string CharFilename = std::string(*Filename), CharContent = std::string(*Content);
            Arguments.GetReturnValue().Set(Zenda::Shortcuts::V8Boolean(Arguments.GetIsolate(), Zenda::FileSystem::WriteFile(CharFilename, CharContent)));
        }
    }

    static void WriteFile(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if( (Arguments[0]->IsUndefined()) || (Arguments[1]->IsUndefined()) )
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "In order to use the WriteFile method you need to send it two parameters where the first is the name of the file in which you want to write and the second is a function that acts as a callback which receives two parameters where the first is a Boolean data that indicates if there was any error when opening the file and the second is a string that contains the content of the file before writing and / or adding new content to it.");
        else{
            v8::String::Utf8Value Filename(Arguments.GetIsolate(), Arguments[0]);
            const std::string CharFilename = std::string(*Filename);
            std::string OldContent = "";
            bool Error = true;
            if(Zenda::FileSystem::FileExists(CharFilename)){
                Error = false;
                OldContent = Zenda::FileSystem::ReadFile(CharFilename);
            }
            v8::Local<v8::Value> Argv[] = {Zenda::Shortcuts::V8Boolean(Arguments.GetIsolate(), Error), Zenda::Shortcuts::V8String(Arguments.GetIsolate(), std::string(OldContent))};
            v8::MaybeLocal<v8::Value> FunctionCall = Zenda::Shortcuts::V8CallJSFunction(
                Arguments.GetIsolate()->GetCurrentContext(), Arguments[1].As<v8::Function>(),
                Zenda::Shortcuts::V8Boolean(Arguments.GetIsolate(), true), 2, Argv);
            v8::String::Utf8Value Content(Arguments.GetIsolate(), FunctionCall.ToLocalChecked().As<v8::Value>());
            Zenda::FileSystem::WriteFile(CharFilename, std::string(*Content));
        }
    }

    static inline void QuickRewriteFile(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if( (Arguments[0]->IsUndefined()) || (Arguments[1]->IsUndefined()) )
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "To use the QuickRewriteFile method, you need to indicate the file to be overwritten as a parameter and the new content that said file will have as a second parameter.");
        else{
            v8::String::Utf8Value Filename(Arguments.GetIsolate(), Arguments[0]);
            v8::String::Utf8Value Content(Arguments.GetIsolate(), Arguments[1]);
            Arguments.GetReturnValue().Set(Zenda::Shortcuts::V8Boolean(Arguments.GetIsolate(), Zenda::FileSystem::RewriteFile(std::string(*Filename), std::string(*Content))));
        }
    }

    static void RewriteFile(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if( (Arguments[0]->IsUndefined()) || (Arguments[1]->IsUndefined()) )
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(),  "To use the RewriteFile method you need to indicate two parameters where the first is the path where the file to be overwritten is located and the second is a function that acts as a callback that receives two parameters where the first is a Boolean data that indicates if there was an error when opening the file and the second is a string that contains the old content that the file had before being overwritten.");
        else{
            v8::String::Utf8Value Filename(Arguments.GetIsolate(), Arguments[0]);
            const std::string CharFilename = std::string(*Filename);
            std::string OldContent = "";
            bool Error = true;
            if(Zenda::FileSystem::FileExists(CharFilename)){
                Error = false;
                OldContent = Zenda::FileSystem::ReadFile(CharFilename);
            }
            v8::Local<v8::Value> Argv[] = {Zenda::Shortcuts::V8Boolean(Arguments.GetIsolate(), Error), Zenda::Shortcuts::V8String(Arguments.GetIsolate(), std::string(OldContent))};
            v8::MaybeLocal<v8::Value> FunctionCall = Zenda::Shortcuts::V8CallJSFunction(
                Arguments.GetIsolate()->GetCurrentContext(), Arguments[1].As<v8::Function>(), Zenda::Shortcuts::V8Boolean(Arguments.GetIsolate(), true), 2, Argv);
        }
    }   
}