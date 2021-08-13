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
    String::Utf8Value File(Arguments.GetIsolate(), Arguments[0]);
    Arguments.GetReturnValue().Set(
        Boolean::New(
            Arguments.GetIsolate(),
            FSFileExists(ToCString(File))
        )
    );
}

static void FileSystemListDirectory(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
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

static void FileSystemCopy(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    String::Utf8Value TargetOne(Arguments.GetIsolate(), Arguments[0]);
    String::Utf8Value TargetTwo(Arguments.GetIsolate(), Arguments[1]);
    FSCopy(ToCString(TargetOne), ToCString(TargetTwo));
}

static void FileSystemMove(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    String::Utf8Value ActualPath(Arguments.GetIsolate(), Arguments[0]);
    String::Utf8Value NextPath(Arguments.GetIsolate(), Arguments[1]);
    FSMove(ToCString(ActualPath), ToCString(NextPath));
}

static void FileSystemCopyFileContent(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    String::Utf8Value TargetOne(Arguments.GetIsolate(), Arguments[0]);
    String::Utf8Value TargetTwo(Arguments.GetIsolate(), Arguments[1]);
    FSCopyFileContents(ToCString(TargetOne), ToCString(TargetTwo));
}

static void FileSystemIsEmptyDirectory(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    String::Utf8Value Directory(Arguments.GetIsolate(), Arguments[0]);
    Arguments.GetReturnValue().Set(
        Boolean::New(
            Arguments.GetIsolate(),
            FSDirectoryIsEmpty(ToCString(Directory))
        )
    );
}

static void FileSystemRename(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    String::Utf8Value OriginalFilename(Arguments.GetIsolate(), Arguments[0]);
    String::Utf8Value NewFilename(Arguments.GetIsolate(), Arguments[1]);
    Arguments.GetReturnValue().Set(
        Boolean::New(
            Arguments.GetIsolate(),
            FSRename(ToCString(OriginalFilename), ToCString(NewFilename))
        )
    );
}

static void FileSystemRemove(const FunctionCallbackInfo<Value>& Arguments){
    unsigned short int Iterator = 0;
    unsigned int Operations = 0;
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

static void FileSystemCountLines(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    String::Utf8Value Filename(Arguments.GetIsolate(), Arguments[0]);
    Arguments.GetReturnValue().Set(
        Number::New(
            Arguments.GetIsolate(),
            FSCountLines(ToCString(Filename))
        )
    );
}

static void FileSystemIsFile(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    String::Utf8Value MaybeRegularFile(Arguments.GetIsolate(), Arguments[0]);
    Arguments.GetReturnValue().Set(
        Boolean::New(
            Arguments.GetIsolate(),
            FSIsRegularFile(ToCString(MaybeRegularFile))
        )
    );
}

static void FileSystemIsDirectory(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    String::Utf8Value MaybeDirectory(Arguments.GetIsolate(), Arguments[0]);
    Arguments.GetReturnValue().Set(
        Boolean::New(
            Arguments.GetIsolate(),
            FSIsDirectory(ToCString(MaybeDirectory))
        )
    );
}

static void FileSystemIsBlockFile(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    String::Utf8Value MaybeBlockFile(Arguments.GetIsolate(), Arguments[0]);
    Arguments.GetReturnValue().Set(
        Boolean::New(
            Arguments.GetIsolate(),
            FSIsBlockFile(ToCString(MaybeBlockFile))
        )
    );
}

static void FileSystemIsCharacterFile(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    String::Utf8Value MaybeCharacterFile(Arguments.GetIsolate(), Arguments[0]);
    Arguments.GetReturnValue().Set(
        Boolean::New(
            Arguments.GetIsolate(),
            FSIsCharacterFile(ToCString(MaybeCharacterFile))
        )
    );
}

static void FileSystemIsFifo(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    String::Utf8Value MaybeFifoFile(Arguments.GetIsolate(), Arguments[0]);
    Arguments.GetReturnValue().Set(
        Boolean::New(
            Arguments.GetIsolate(),
            FSIsFifo(ToCString(MaybeFifoFile))
        )
    );
}

static void FileSystemIsSocket(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    String::Utf8Value MaybeSocketFile(Arguments.GetIsolate(), Arguments[0]);
    Arguments.GetReturnValue().Set(
        Boolean::New(
            Arguments.GetIsolate(),
            FSIsSocket(ToCString(MaybeSocketFile))
        )
    );
}

static void FileSystemIsSymlink(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    String::Utf8Value MaybeSymlink(Arguments.GetIsolate(), Arguments[0]);
    Arguments.GetReturnValue().Set(
        Boolean::New(
            Arguments.GetIsolate(),
            FSIsSymLink(ToCString(MaybeSymlink))
        )
    );
}

static void FileSystemCreateFile(const FunctionCallbackInfo<Value>& Arguments){
    unsigned short int Iterator = 0;
    for(Iterator; Iterator < Arguments.Length(); Iterator++){
        HandleScope Scope(Arguments.GetIsolate());
        String::Utf8Value Filename(Arguments.GetIsolate(), Arguments[Iterator]);
        FSCreateFile(ToCString(Filename));
    }
}

static void FileSystemCreateFolder(const FunctionCallbackInfo<Value>& Arguments){
    unsigned short int Iterator = 0;
    for(Iterator; Iterator < Arguments.Length(); Iterator++){
        HandleScope Scope(Arguments.GetIsolate());
        String::Utf8Value FolderName(Arguments.GetIsolate(), Arguments[Iterator]);
        mkdir(ToCString(FolderName), 0777);
    }
}

static void FileSystemRemoveFile(const FunctionCallbackInfo<Value>& Arguments){
    unsigned short int Iterator = 0;
    for(Iterator; Iterator < Arguments.Length(); Iterator++){
        HandleScope Scope(Arguments.GetIsolate());
        String::Utf8Value PathToRemove(Arguments.GetIsolate(), Arguments[Iterator]);
        remove(ToCString(PathToRemove));
    }
}

static void FileSystemRemoveFolder(const FunctionCallbackInfo<Value>& Arguments){
    unsigned short int Iterator = 0;
    for(Iterator; Iterator < Arguments.Length(); Iterator++){
        HandleScope Scope(Arguments.GetIsolate());
        String::Utf8Value PathToRemove(Arguments.GetIsolate(), Arguments[Iterator]);
        rmdir(ToCString(PathToRemove));
    }
}

static void FileSystemQuickReadFile(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
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

static void FileSystemReadFile(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
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

static void FileSystemQuickFileSize(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
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

static void FileSystemFileSize(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
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

static void FileSystemQuickWriteFile(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
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

static void FileSystemWriteFile(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
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

static void FileSystemQuickRewriteFile(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    String::Utf8Value Filename(Arguments.GetIsolate(), Arguments[0]);
    String::Utf8Value Content(Arguments.GetIsolate(), Arguments[1]);
    Arguments.GetReturnValue().Set(
        Boolean::New(
            Arguments.GetIsolate(),
            FSRewriteFile(ToCString(Filename), ToCString(Content))
        )
    );
}

static void FileSystemRewriteFile(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
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