/***
 * Copyright (C) Rodolfo Herrera Hernandez. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root 
 * for full license information.
 *
 * =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
 *
 * Objects/FileSystem.hxx: File containing methods for JS related to the file system.
 *
 * Methods available to interact with the filesystem from Javascript
 *
 * For related information - https://github.com/rodiihernandezz/ZendaJS/
 *
 * =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
 ****/

static void FileSystemListDirectory(const FunctionCallbackInfo<Value>& Arguments);
static void FileSystemCopy(const FunctionCallbackInfo<Value>& Arguments);
static void FileSystemMove(const FunctionCallbackInfo<Value>& Arguments);
static void FileSystemCopyFileContent(const FunctionCallbackInfo<Value>& Arguments);
static void FileSystemIsEmptyDirectory(const FunctionCallbackInfo<Value>& Arguments);
static void FileSystemRename(const FunctionCallbackInfo<Value>& Arguments);
static void FileSystemRemove(const FunctionCallbackInfo<Value>& Arguments);
static void FileSystemCountLines(const FunctionCallbackInfo<Value>& Arguments);
static void FileSystemIsFile(const FunctionCallbackInfo<Value>& Arguments);
static void FileSystemIsDirectory(const FunctionCallbackInfo<Value>& Arguments);
static void FileSystemIsBlockFile(const FunctionCallbackInfo<Value>& Arguments);
static void FileSystemIsCharacterFile(const FunctionCallbackInfo<Value>& Arguments);
static void FileSystemIsFifo(const FunctionCallbackInfo<Value>& Arguments);
static void FileSystemIsSocket(const FunctionCallbackInfo<Value>& Arguments);
static void FileSystemIsSymlink(const FunctionCallbackInfo<Value>& Arguments);
static void FileSystemCreateFile(const FunctionCallbackInfo<Value>& Arguments);
static void FileSystemCreateFolder(const FunctionCallbackInfo<Value>& Arguments);
static void FileSystemRemoveFile(const FunctionCallbackInfo<Value>& Arguments);
static void FileSystemRemoveFolder(const FunctionCallbackInfo<Value>& Arguments);
static void FileSystemQuickReadFile(const FunctionCallbackInfo<Value>& Arguments);
static void FileSystemReadFile(const FunctionCallbackInfo<Value>& Arguments);
static void FileSystemQuickFileSize(const FunctionCallbackInfo<Value>& Arguments);
static void FileSystemFileSize(const FunctionCallbackInfo<Value>& Arguments);
static void FileSystemQuickWriteFile(const FunctionCallbackInfo<Value>& Arguments);
static void FileSystemWriteFile(const FunctionCallbackInfo<Value>& Arguments);
static void FileSystemQuickRewriteFile(const FunctionCallbackInfo<Value>& Arguments);
static void FileSystemRewriteFile(const FunctionCallbackInfo<Value>& Arguments);
static void FileSystemFileExists(const FunctionCallbackInfo<Value>& Arguments);

static void FileSystemFileExists(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    if(Arguments[0]->IsUndefined())
        Arguments.GetIsolate()->ThrowException(
            String::NewFromUtf8(
                Arguments.GetIsolate(),
                "You must enter a file in order to verify its existence."
            ).ToLocalChecked()
        );
    else{
        String::Utf8Value File(Arguments.GetIsolate(), Arguments[0]);
        Arguments.GetReturnValue().Set(
            Boolean::New(
                Arguments.GetIsolate(),
                FSFileExists(ToCString(File))
            )
        );
    }
}

static void FileSystemListDirectory(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    if(Arguments[0]->IsUndefined())
        Arguments.GetIsolate()->ThrowException(
            String::NewFromUtf8(
                Arguments.GetIsolate(),
                "You must indicate a directory to be able to list it.",
                NewStringType::kNormal
            ).ToLocalChecked()
        );
    else{
        String::Utf8Value DirectoryPath(Arguments.GetIsolate(), Arguments[0]);
        vector<string> DetectedContent = FSListDirectory(ToCString(DirectoryPath));
        Local<Array> ReturnValue = Array::New(Arguments.GetIsolate(), DetectedContent.size());
        unsigned int Iterator = 0;
        for(Iterator; Iterator < DetectedContent.size(); Iterator++)
            Maybe<bool> SetValue = ReturnValue->Set(
                Arguments.GetIsolate()->GetCurrentContext(),
                Iterator,
                String::NewFromUtf8(
                    Arguments.GetIsolate(),
                    DetectedContent.at(Iterator).c_str(),
                    NewStringType::kNormal
                ).ToLocalChecked()
            );
        Arguments.GetReturnValue().Set(
            ReturnValue
        );
    }
}

static void FileSystemCopy(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    if( (Arguments[0]->IsUndefined()) || (Arguments[1]->IsUndefined()) )
        Arguments.GetIsolate()->ThrowException(
            String::NewFromUtf8(
                Arguments.GetIsolate(),
                "To copy files you need to send two parameters where the first is the file to be copied and the second is the new path where you want to send the file.",
                NewStringType::kNormal
            ).ToLocalChecked()
        );
    else{
        String::Utf8Value TargetOne(Arguments.GetIsolate(), Arguments[0]);
        String::Utf8Value TargetTwo(Arguments.GetIsolate(), Arguments[1]);
        FSCopy(ToCString(TargetOne), ToCString(TargetTwo));
    }
}

static void FileSystemMove(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    if( (Arguments[0]->IsUndefined()) || (Arguments[1]->IsUndefined()) )
        Arguments.GetIsolate()->ThrowException(
            String::NewFromUtf8(
                Arguments.GetIsolate(),
                "To move files you need to send two parameters where the first is the file to move and the second is the new path where you want to send the file.",
                NewStringType::kNormal
            ).ToLocalChecked()
        );
    else{
        String::Utf8Value ActualPath(Arguments.GetIsolate(), Arguments[0]);
        String::Utf8Value NextPath(Arguments.GetIsolate(), Arguments[1]);
        FSMove(ToCString(ActualPath), ToCString(NextPath));
    }
}

static void FileSystemCopyFileContent(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    if( (Arguments[0]->IsUndefined()) || (Arguments[1]->IsUndefined()) )
        Arguments.GetIsolate()->ThrowException(
            String::NewFromUtf8(
                Arguments.GetIsolate(),
                "To copy the content of a file to another file you need to send two parameters where the first is the file that contains the content and the second is the file you want to send content to.",
                NewStringType::kNormal
            ).ToLocalChecked()
        );
    else{
        String::Utf8Value TargetOne(Arguments.GetIsolate(), Arguments[0]);
        String::Utf8Value TargetTwo(Arguments.GetIsolate(), Arguments[1]);
        FSCopyFileContents(ToCString(TargetOne), ToCString(TargetTwo));
    }
}

static void FileSystemIsEmptyDirectory(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    if(Arguments[0]->IsUndefined())
        Arguments.GetIsolate()->ThrowException(
            String::NewFromUtf8(
                Arguments.GetIsolate(),
                "To check if a directory is empty, you must indicate it as a parameter, we are not fortune tellers.",
                NewStringType::kNormal
            ).ToLocalChecked()
        );
    else{
        String::Utf8Value Directory(Arguments.GetIsolate(), Arguments[0]);
        Arguments.GetReturnValue().Set(
            Boolean::New(
                Arguments.GetIsolate(),
                FSDirectoryIsEmpty(ToCString(Directory))
            )
        );
    }
}

static void FileSystemRename(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    if( (Arguments[0]->IsUndefined()) || (Arguments[1]->IsUndefined()) )
        Arguments.GetIsolate()->ThrowException(
            String::NewFromUtf8(
                Arguments.GetIsolate(),
                "If you want to rename a file, you must send two parameters where the first is the path where the file to be renamed is located and the second is the name that will be assigned to the sent file.",
                NewStringType::kNormal
            ).ToLocalChecked()
        );
    else{
        String::Utf8Value OriginalFilename(Arguments.GetIsolate(), Arguments[0]);
        String::Utf8Value NewFilename(Arguments.GetIsolate(), Arguments[1]);
        Arguments.GetReturnValue().Set(
            Boolean::New(
                Arguments.GetIsolate(),
                FSRename(ToCString(OriginalFilename), ToCString(NewFilename))
            )
        );
    }
}

static void FileSystemRemove(const FunctionCallbackInfo<Value>& Arguments){
    if(Arguments[0]->IsUndefined())
        Arguments.GetIsolate()->ThrowException(
            String::NewFromUtf8(
                Arguments.GetIsolate(),
                "You need to pass at least one parameter to FileSystem's remove method.",
                NewStringType::kNormal
            ).ToLocalChecked()
        );
    else{
        unsigned int Operations = 0;
        unsigned short int Iterator = 0;
        for(Iterator; Iterator < Arguments.Length(); Iterator++){
            HandleScope Scope(Arguments.GetIsolate());
            String::Utf8Value Who(Arguments.GetIsolate(), Arguments[Iterator]);
            Operations += FSRemove(ToCString(Who));
        }
        Arguments.GetReturnValue().Set(
            Number::New(
                Arguments.GetIsolate(),
                Operations
            )
        );
    }
}

static void FileSystemCountLines(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    if(Arguments[0]->IsUndefined())
        Arguments.GetIsolate()->ThrowException(
            String::NewFromUtf8(
                Arguments.GetIsolate(),
                "You need to indicate a file to count its lines.",
                NewStringType::kNormal
            ).ToLocalChecked()
        );
    else{
        String::Utf8Value Filename(Arguments.GetIsolate(), Arguments[0]);
        Arguments.GetReturnValue().Set(
            Number::New(
                Arguments.GetIsolate(),
                FSCountLines(ToCString(Filename))
            )
        );
    }
}

static void FileSystemIsFile(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    if(Arguments[0]->IsUndefined())
        Arguments.GetIsolate()->ThrowException(
            String::NewFromUtf8(
                Arguments.GetIsolate(),
                "You need to send at least one parameter to check if this as path is a file or not.",
                NewStringType::kNormal
            ).ToLocalChecked()
        );
    else{
        String::Utf8Value MaybeRegularFile(Arguments.GetIsolate(), Arguments[0]);
        Arguments.GetReturnValue().Set(
            Boolean::New(
                Arguments.GetIsolate(),
                FSIsRegularFile(ToCString(MaybeRegularFile))
            )
        );
    }
}

static void FileSystemIsDirectory(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    if(Arguments[0]->IsUndefined())
        Arguments.GetIsolate()->ThrowException(
            String::NewFromUtf8(
                Arguments.GetIsolate(),
                "You must send at least one parameter to check if this path is a directory or not.",
                NewStringType::kNormal
            ).ToLocalChecked()
        );
    else{
        String::Utf8Value MaybeDirectory(Arguments.GetIsolate(), Arguments[0]);
        Arguments.GetReturnValue().Set(
            Boolean::New(
                Arguments.GetIsolate(),
                FSIsDirectory(ToCString(MaybeDirectory))
            )
        );
    }
}

static void FileSystemIsBlockFile(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    if(Arguments[0]->IsUndefined())
        Arguments.GetIsolate()->ThrowException(
            String::NewFromUtf8(
                Arguments.GetIsolate(),
                "You need to indicate a file to indicate if it is a file or not.",
                NewStringType::kNormal
            ).ToLocalChecked()
        );
    else{
        String::Utf8Value MaybeBlockFile(Arguments.GetIsolate(), Arguments[0]);
        Arguments.GetReturnValue().Set(
            Boolean::New(
                Arguments.GetIsolate(),
                FSIsBlockFile(ToCString(MaybeBlockFile))
            )
        );
    }
}

static void FileSystemIsCharacterFile(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    if(Arguments[0]->IsUndefined())
        Arguments.GetIsolate()->ThrowException(
            String::NewFromUtf8(
                Arguments.GetIsolate(),
                "You need to indicate a file to indicate if it is a character file or not.",
                NewStringType::kNormal
            ).ToLocalChecked()
        );
    else{
        String::Utf8Value MaybeCharacterFile(Arguments.GetIsolate(), Arguments[0]);
        Arguments.GetReturnValue().Set(
            Boolean::New(
                Arguments.GetIsolate(),
                FSIsCharacterFile(ToCString(MaybeCharacterFile))
            )
        );   
    }
}

static void FileSystemIsFifo(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    if(Arguments[0]->IsUndefined())
        Arguments.GetIsolate()->ThrowException(
            String::NewFromUtf8(
                Arguments.GetIsolate(),
                "You need to indicate a file to indicate if it is a fifo file or not.",
                NewStringType::kNormal
            ).ToLocalChecked()
        );
    else{
        String::Utf8Value MaybeFifoFile(Arguments.GetIsolate(), Arguments[0]);
        Arguments.GetReturnValue().Set(
            Boolean::New(
                Arguments.GetIsolate(),
                FSIsFifo(ToCString(MaybeFifoFile))
            )
        );
    }
}

static void FileSystemIsSocket(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    if(Arguments[0]->IsUndefined())
        Arguments.GetIsolate()->ThrowException(
            String::NewFromUtf8(
                Arguments.GetIsolate(),
                "You need to indicate a file to indicate if it is a socket or not.",
                NewStringType::kNormal
            ).ToLocalChecked()
        );
    else{
        String::Utf8Value MaybeSocketFile(Arguments.GetIsolate(), Arguments[0]);
        Arguments.GetReturnValue().Set(
            Boolean::New(
                Arguments.GetIsolate(),
                FSIsSocket(ToCString(MaybeSocketFile))
            )
        );
    }
}

static void FileSystemIsSymlink(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    if(Arguments[0]->IsUndefined())
        Arguments.GetIsolate()->ThrowException(
            String::NewFromUtf8(
                Arguments.GetIsolate(),
                "You need to indicate a file to indicate if it is a symlink or not.",
                NewStringType::kNormal
            ).ToLocalChecked()
        );
    else{
        String::Utf8Value MaybeSymlink(Arguments.GetIsolate(), Arguments[0]);
        Arguments.GetReturnValue().Set(
            Boolean::New(
                Arguments.GetIsolate(),
                FSIsSymLink(ToCString(MaybeSymlink))
            )
        );
    }
}

static void FileSystemCreateFile(const FunctionCallbackInfo<Value>& Arguments){
    unsigned short int Iterator = 0;
    if(Arguments[0]->IsUndefined())
        Arguments.GetIsolate()->ThrowException(
            String::NewFromUtf8(
                Arguments.GetIsolate(),
                "You must enter at least one file in order to create a file..",
                NewStringType::kNormal
            ).ToLocalChecked()
        );
    else
        for(Iterator; Iterator < Arguments.Length(); Iterator++){
            HandleScope Scope(Arguments.GetIsolate());
            String::Utf8Value Filename(Arguments.GetIsolate(), Arguments[Iterator]);
            FSCreateFile(ToCString(Filename));
        }
}

static void FileSystemCreateFolder(const FunctionCallbackInfo<Value>& Arguments){
    if(Arguments[0]->IsUndefined())
        Arguments.GetIsolate()->ThrowException(
            String::NewFromUtf8(
                Arguments.GetIsolate(),
                "You need to indicate one or more parameters which will be used to create the directories in the CreateFolder method.",
                NewStringType::kNormal
            ).ToLocalChecked()
        );
    else{
        unsigned short int Iterator = 0;
        for(Iterator; Iterator < Arguments.Length(); Iterator++){
            HandleScope Scope(Arguments.GetIsolate());
            String::Utf8Value FolderName(Arguments.GetIsolate(), Arguments[Iterator]);
            mkdir(ToCString(FolderName), 0777);
        }
    }
}

static void FileSystemRemoveFile(const FunctionCallbackInfo<Value>& Arguments){
    if(Arguments[0]->IsUndefined())
        Arguments.GetIsolate()->ThrowException(
            String::NewFromUtf8(
                Arguments.GetIsolate(),
                "You need to indicate as parameters one or more files to delete in the RemoveFile method.", 
                NewStringType::kNormal
            ).ToLocalChecked()
        );
    else{
        unsigned short int Iterator = 0;
        for(Iterator; Iterator < Arguments.Length(); Iterator++){
            HandleScope Scope(Arguments.GetIsolate());
            String::Utf8Value PathToRemove(Arguments.GetIsolate(), Arguments[Iterator]);
            remove(ToCString(PathToRemove));
        }
    }
}

static void FileSystemRemoveFolder(const FunctionCallbackInfo<Value>& Arguments){
    if(Arguments[0]->IsUndefined())
        Arguments.GetIsolate()->ThrowException(
            String::NewFromUtf8(
                Arguments.GetIsolate(),
                "You need to indicate as parameters one or more folders to delete in the RemoveFolder method.", 
                NewStringType::kNormal
            ).ToLocalChecked()
        );
    else{
        unsigned short int Iterator = 0;
        for(Iterator; Iterator < Arguments.Length(); Iterator++){
            HandleScope Scope(Arguments.GetIsolate());
            String::Utf8Value PathToRemove(Arguments.GetIsolate(), Arguments[Iterator]);
            rmdir(ToCString(PathToRemove));
        }
    }
}

static void FileSystemQuickReadFile(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    if(Arguments[0]->IsUndefined())
        Arguments.GetIsolate()->ThrowException(
            String::NewFromUtf8(
                Arguments.GetIsolate(),
                "You need to specify a file as a parameter to be able to read it in the QuickReadFile method.",
                NewStringType::kNormal
            ).ToLocalChecked()
        );
    else{
        String::Utf8Value Filename(Arguments.GetIsolate(), Arguments[0]);
        const char* CharFilename = ToCString(Filename);
        const char* ReadResult = FSReadFile(CharFilename);
        Arguments.GetReturnValue().Set(
            String::NewFromUtf8(
                Arguments.GetIsolate(),
                ReadResult,
                NewStringType::kNormal,
                static_cast<int>(string(ReadResult).length())
            ).ToLocalChecked()
        );
    }
}

static void FileSystemReadFile(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    if( (Arguments[0]->IsUndefined()) || (Arguments[1]->IsUndefined()) )
        Arguments.GetIsolate()->ThrowException(
            String::NewFromUtf8(
                Arguments.GetIsolate(),
                "You need to indicate the file to read and a function like Callback that will receive two parameters where the first is a Boolean data that indicates if there was an error when opening the file and the second is a string that indicates the content of the file.",
                NewStringType::kNormal
            ).ToLocalChecked()
        );
    else{
        String::Utf8Value Filename(Arguments.GetIsolate(), Arguments[0]);
        const char* CharFilename = ToCString(Filename);
        const char* Content = "";
        bool Error = true;
        if(FSFileExists(CharFilename)){
            Error = false;
            Content = FSReadFile(CharFilename);
        }
        Local<Value> argv[] = {
            Boolean::New(
                Arguments.GetIsolate(),
                Error
            ),
            String::NewFromUtf8(
                Arguments.GetIsolate(),
                Content,
                NewStringType::kNormal
            ).ToLocalChecked()
        };
        Local<Value> recv = { Boolean::New(Arguments.GetIsolate(), true) };
        MaybeLocal<Value> Resolve = Arguments[1].As<Function>()->Call(
            Arguments.GetIsolate()->GetCurrentContext(),
            recv, 2, argv
        );
    }
}

static void FileSystemQuickFileSize(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    if(Arguments[0]->IsUndefined())
        Arguments.GetIsolate()->ThrowException(
            String::NewFromUtf8(
                Arguments.GetIsolate(),
                "You need to indicate a file to be able to obtain its weight in bytes, this in the QuickFileSize method.",
                NewStringType::kNormal
            ).ToLocalChecked()
        );
    else{
        String::Utf8Value Filename(Arguments.GetIsolate(), Arguments[0]);
        const char* CharFilename = ToCString(Filename);
        auto SizeResult = FSFileSize(CharFilename);
        Arguments.GetReturnValue().Set(
            Number::New(
                Arguments.GetIsolate(),
                SizeResult
            )
        );
    }
}

static void FileSystemFileSize(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    if( (Arguments[0]->IsUndefined()) || (Arguments[1]->IsUndefined()) )
        Arguments.GetIsolate()->ThrowException(
            String::NewFromUtf8(
                Arguments.GetIsolate(),
                "You need to send two parameters to the FileSize method, where the first is the path of the file to obtain the size and the second is a function that acts as a callback that receives two parameters where the first is a Boolean data that indicates if there was an error when opening the file. file and the second is an integer that indicates the size in bytes of the file.",
                NewStringType::kNormal
            ).ToLocalChecked()
        );
    else{
        String::Utf8Value Filename(Arguments.GetIsolate(), Arguments[0]);
        const char* CharFilename = ToCString(Filename);
        auto SizeResult = FSFileSize(CharFilename);
        bool Error = false;
        if(SizeResult == -1)
            Error = true;
        Local<Value> argv[] = {
            Boolean::New(
                Arguments.GetIsolate(),
                Error
            ),
            Number::New(
                Arguments.GetIsolate(),
                SizeResult
            )
        };
        Local<Value> recv= { Boolean::New(Arguments.GetIsolate(), true) };
        MaybeLocal<Value> Resolve = Arguments[1].As<Function>()->Call(
            Arguments.GetIsolate()->GetCurrentContext(),
            recv, 2, argv
        );
    }
}

static void FileSystemQuickWriteFile(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    if( (Arguments[0]->IsUndefined()) || (Arguments[1]->IsUndefined()) )
        Arguments.GetIsolate()->ThrowException(
            String::NewFromUtf8(
                Arguments.GetIsolate(),
                "In order to use the QuickWriteFile function you need to indicate a file to which you want to write and as second parameter the content to add.",
                NewStringType::kNormal
            ).ToLocalChecked()
        );
    else{
        String::Utf8Value Filename(Arguments.GetIsolate(), Arguments[0]);
        const char* CharFilename = ToCString(Filename);
        String::Utf8Value Content(Arguments.GetIsolate(), Arguments[1]);
        const char* CharContent = ToCString(Content);
        Arguments.GetReturnValue().Set(
            Boolean::New(
                Arguments.GetIsolate(),
                FSWriteFile(CharFilename, CharContent)
            )
        );
    }
}

static void FileSystemWriteFile(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    if( (Arguments[0]->IsUndefined()) || (Arguments[1]->IsUndefined()) )
        Arguments.GetIsolate()->ThrowException(
            String::NewFromUtf8(
                Arguments.GetIsolate(),
                "In order to use the WriteFile method you need to send it two parameters where the first is the name of the file in which you want to write and the second is a function that acts as a callback which receives two parameters where the first is a Boolean data that indicates if there was any error when opening the file and the second is a string that contains the content of the file before writing and / or adding new content to it.",
                NewStringType::kNormal
            ).ToLocalChecked()
        );
    else{
        String::Utf8Value Filename(Arguments.GetIsolate(), Arguments[0]);
        String::Utf8Value Content(Arguments.GetIsolate(), Arguments[1].As<String>());
        const char* CharFilename = ToCString(Filename);
        const char* OldContent = "";
        bool Error = true;
        if(FSFileExists(CharFilename)){
            Error = false;
            OldContent = FSReadFile(CharFilename);
            FSWriteFile(CharFilename, ToCString(Content));
        }
        Local<Value> argv[] = {
            Boolean::New(
                Arguments.GetIsolate(),
                Error
            ),
            String::NewFromUtf8(
                Arguments.GetIsolate(),
                OldContent,
                NewStringType::kNormal
            ).ToLocalChecked()
        };
        Local<Value> recv = { Boolean::New(Arguments.GetIsolate(), true) };
        MaybeLocal<Value> Resolve = Arguments[1].As<Function>()->Call(
            Arguments.GetIsolate()->GetCurrentContext(),
            recv, 2, argv
        );
    }
}

static void FileSystemQuickRewriteFile(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    if( (Arguments[0]->IsUndefined()) || (Arguments[1]->IsUndefined()) )
        Arguments.GetIsolate()->ThrowException(
            String::NewFromUtf8(
                Arguments.GetIsolate(),
                "To use the QuickRewriteFile method, you need to indicate the file to be overwritten as a parameter and the new content that said file will have as a second parameter.",
                NewStringType::kNormal
            ).ToLocalChecked()
        );
    else{
        String::Utf8Value Filename(Arguments.GetIsolate(), Arguments[0]);
        String::Utf8Value Content(Arguments.GetIsolate(), Arguments[1]);
        Arguments.GetReturnValue().Set(
            Boolean::New(
                Arguments.GetIsolate(),
                FSRewriteFile(ToCString(Filename), ToCString(Content))
            )
        );
    }
}

static void FileSystemRewriteFile(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
   if( (Arguments[0]->IsUndefined()) || (Arguments[1]->IsUndefined()) )
        Arguments.GetIsolate()->ThrowException(
            String::NewFromUtf8(
                Arguments.GetIsolate(),
                "To use the RewriteFile method you need to indicate two parameters where the first is the path where the file to be overwritten is located and the second is a function that acts as a callback that receives two parameters where the first is a Boolean data that indicates if there was an error when opening the file and the second is a string that contains the old content that the file had before being overwritten.",
                NewStringType::kNormal
            ).ToLocalChecked()
        );
    else{
        String::Utf8Value Filename(Arguments.GetIsolate(), Arguments[0]);
        const char* CharFilename = ToCString(Filename);
        const char* OldContent = "";
        bool Error = true;
        if(FSFileExists(CharFilename)){
            Error = false;
            OldContent = FSReadFile(CharFilename);
        }
        Local<Value> argv[] = {
            Boolean::New(
                Arguments.GetIsolate(),
                Error
            ),
            String::NewFromUtf8(
                Arguments.GetIsolate(),
                OldContent,
                NewStringType::kNormal
            ).ToLocalChecked(),
        };
        Local<Value> recv = { Boolean::New(Arguments.GetIsolate(), true) };
        MaybeLocal<Value> Resolve = Arguments[1].As<Function>()->Call(
            Arguments.GetIsolate()->GetCurrentContext(),
            recv, 2, argv
        );
    }
}