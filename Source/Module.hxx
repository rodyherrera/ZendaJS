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

namespace Zenda::JavaScript::Modules{
    static v8::MaybeLocal<v8::Promise> CallDynamic(v8::Local<v8::Context> Context, v8::Local<v8::ScriptOrModule> Referrer, v8::Local<v8::String> Specifier);
    static inline v8::MaybeLocal<v8::Module> CallResolve(v8::Local<v8::Context> Context, v8::Local<v8::String> Specifier, v8::Local<v8::Module> Referrer);
    static v8::Local<v8::Value> Execute(v8::Local<v8::Module> Module, v8::Local<v8::Context> Context, const bool NsObject);
    static v8::Local<v8::Module> Check(v8::MaybeLocal<v8::Module> MaybeModule, v8::Local<v8::Context> Context);
    static v8::MaybeLocal<v8::Module> Load(const std::string Code, const std::string Name, v8::Local<v8::Context> Context);

    static v8::MaybeLocal<v8::Module> Load(const std::string Code, const std::string Name, v8::Local<v8::Context> Context){
        v8::Local<v8::String> VMCode = Zenda::Shortcuts::V8String(Context->GetIsolate(), Code).As<v8::String>();
        v8::ScriptOrigin Origin(
            Zenda::Shortcuts::V8String(Context->GetIsolate(), Name),
            Zenda::Shortcuts::V8Integer(Context->GetIsolate(), 0),
            Zenda::Shortcuts::V8Integer(Context->GetIsolate(), 0),
            v8::False(Context->GetIsolate()),
            v8::Local<v8::Integer>(),
            v8::Local<v8::Value>(),
            v8::False(Context->GetIsolate()),
            v8::False(Context->GetIsolate()),
            v8::True(Context->GetIsolate())
        );
        v8::Context::Scope ContextScope(Context);
        v8::ScriptCompiler::Source Source(VMCode, Origin);
        v8::MaybeLocal<v8::Module> LModule;
        LModule = v8::ScriptCompiler::CompileModule(Context->GetIsolate(), &Source);
        return LModule;
    }

    static v8::Local<v8::Module> Check(v8::MaybeLocal<v8::Module> MaybeModule, v8::Local<v8::Context> Context){
        v8::Local<v8::Module> Module;
        if(!MaybeModule.ToLocal(&Module)){
            std::cout << " * An error ocurred while loading the modules." << std::endl;
            exit(EXIT_FAILURE);
        }
        v8::Maybe<bool> Result = Module->InstantiateModule(Context, CallResolve);
        if(Result.IsNothing()){
            std::cout << " * An error occurred while loading the modules." << std::endl;
            exit(EXIT_FAILURE);
        }
        return Module;
    }

    static v8::Local<v8::Value> Execute(v8::Local<v8::Module> Module, v8::Local<v8::Context> Context, const bool NsObject = false){
        v8::Local<v8::Value> ReturnValue;
        v8::TryCatch try_catch(Context->GetIsolate());
        if(!Module->Evaluate(Context).ToLocal(&ReturnValue)){
            assert(try_catch.HasCaught());
            Zenda::Shortcuts::ReportException(&try_catch);
            exit(EXIT_FAILURE);
        }
        assert(!try_catch.HasCaught());
        if(NsObject)
            return Module->GetModuleNamespace();
        else
            return ReturnValue;
    }

    static inline v8::MaybeLocal<v8::Module> CallResolve(v8::Local<v8::Context> Context, v8::Local<v8::String> Specifier, v8::Local<v8::Module> Referrer){
        v8::String::Utf8Value VStr(Context->GetIsolate(), Specifier);
        const std::string Str = std::string(*VStr);
        if(Zenda::FileSystem::FileExists(Str))
            return Load(Zenda::FileSystem::ReadFile(Str), Str, Context);
        else if(Zenda::FileSystem::FileExists(Zenda::Definitions::PackagesFolder + Str)){
            const std::string MaybePackageModule = Zenda::Definitions::PackagesFolder + Str;
            return Load(Zenda::FileSystem::ReadFile(MaybePackageModule), MaybePackageModule, Context);
        }
        const std::string MaybeSourceCodeModule = Zenda::Algorithms::SourceCodeLocation() + "/" + Str;
        return Load(Zenda::FileSystem::ReadFile(MaybeSourceCodeModule), MaybeSourceCodeModule, Context);
    }

    static v8::MaybeLocal<v8::Promise> CallDynamic(v8::Local<v8::Context> Context, v8::Local<v8::ScriptOrModule> Referrer, v8::Local<v8::String> Specifier){
        v8::Local<v8::Promise::Resolver> Resolver = v8::Promise::Resolver::New(Context).ToLocalChecked();
        v8::MaybeLocal<v8::Promise> LPromise(Resolver->GetPromise());
        v8::String::Utf8Value VName(Context->GetIsolate(), Specifier);
        std::string Name = std::string(*VName);
        v8::Local<v8::Module> Module = Check(Load(Zenda::FileSystem::ReadFile(Name), Name, Context), Context);
        v8::Local<v8::Value> ReturnValue = Execute(Module, Context, true);
        v8::Maybe<bool> MResolve = Resolver->Resolve(Context, ReturnValue);
        return LPromise;
    }
};