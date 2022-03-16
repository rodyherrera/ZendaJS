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

namespace Zenda::Shortcuts{
    static inline void CreateMethod(const std::string MethodName, void(*Callback)(const v8::FunctionCallbackInfo<v8::Value>& Arguments));
    v8::Local<v8::Value> V8String(v8::Isolate* Isolate, const std::string String);
    v8::Local<v8::Value> V8Number(v8::Isolate* Isolate, const int Integer);
    v8::Local<v8::Name> V8Name(v8::Isolate* Isolate, const std::string String);
    v8::Local<v8::Value> V8Boolean(v8::Isolate* Isolate, const bool Bool);
    static inline void V8Exception(v8::Isolate* Isolate, const std::string Message);
    v8::MaybeLocal<v8::Value> V8CallJSFunction(v8::Local<v8::Context> Context, v8::Local<v8::Function> LFunction, v8::Local<v8::Value> Recv, const unsigned short int Argc, v8::Local<v8::Value> Arguments[]);
    v8::Local<v8::Data> V8FunctionTemplate(v8::Isolate* Isolate, void(*Callback)(const v8::FunctionCallbackInfo<v8::Value>& Arguments));
    v8::Local<v8::Integer> V8Integer(v8::Isolate* Isolate, const int Integer);
    static void ReportException(v8::TryCatch* try_catch);

    class ObjectCreator{
        private:
            v8::Isolate* Isolate;
            v8::Local<v8::String> Name;
            v8::Local<v8::ObjectTemplate> ObjectInstance;

        public:
            ObjectCreator(v8::Isolate * Isolate, const std::string ObjectName){
                this->Isolate = Isolate;
                this->ObjectInstance = v8::ObjectTemplate::New(this->Isolate);
                this->Name = v8::String::NewFromUtf8(
                    this->Isolate, ObjectName.c_str(), v8::NewStringType::kNormal
                ).ToLocalChecked();
            }

            ObjectCreator SetPropertyMethod(const std::string PropertyMethod, void (*Callback)(const v8::FunctionCallbackInfo<v8::Value>& Arguments)){
                this->ObjectInstance->Set(
                    v8::String::NewFromUtf8(this->Isolate, PropertyMethod.c_str(), v8::NewStringType::kNormal).ToLocalChecked(),
                    v8::FunctionTemplate::New(this->Isolate, Callback)
                );
                return *this;
            }

            void Register(){
                v8::Local<v8::Object> Instance = this->ObjectInstance->NewInstance(
                    this->Isolate->GetCurrentContext()
                ).ToLocalChecked();
                this->Isolate->GetCurrentContext()->Global()->Set(
                    this->Isolate->GetCurrentContext(),
                    this->Name,
                    Instance
                ).FromJust();
            }
    };

    static inline void CreateMethod(const std::string MethodName, void(*Callback)(const v8::FunctionCallbackInfo<v8::Value>& Arguments)){
        Zenda::Definitions::Global->Set(
            Zenda::Shortcuts::V8Name(Zenda::Definitions::Isolate, std::string(MethodName)), 
            Zenda::Shortcuts::V8FunctionTemplate(Zenda::Definitions::Isolate, Callback));
    }

    static inline void Set(v8::Local<v8::Object> Object, std::string Key, size_t Value){
        v8::Maybe<bool> IntValue = Object->Set(v8::Isolate::GetCurrent()->GetCurrentContext(), V8String(v8::Isolate::GetCurrent(), Key), V8Number(v8::Isolate::GetCurrent(), Value));
    }

    static inline void Set(v8::Local<v8::Object> Object, std::string Key, std::string Value){
        v8::Maybe<bool> StrValue = Object->Set(v8::Isolate::GetCurrent()->GetCurrentContext(), V8String(v8::Isolate::GetCurrent(), Key), V8String(v8::Isolate::GetCurrent(), Value));
    }

    static inline void Set(v8::Local<v8::Object> Object, std::string Key, v8::Local<v8::Object> Value){
        v8::Maybe<bool> ObjValue = Object->Set(v8::Isolate::GetCurrent()->GetCurrentContext(), V8String(v8::Isolate::GetCurrent(), Key), Value);
    }

    static inline ObjectCreator CreateObject(const std::string ObjectName){
        ObjectCreator ObjectCreatorInstance(Zenda::Definitions::Isolate, ObjectName);
        return ObjectCreatorInstance;
    }
    
    std::string GetKeyValue(v8::Isolate* Isolate, v8::Local<v8::Object> Object, std::string Key, std::string Default = "undefined"){
        v8::Local<v8::Value> Value = Object->Get(Isolate->GetCurrentContext(), 
                Zenda::Shortcuts::V8String(Isolate, Key)).ToLocalChecked().As<v8::Value>();
        if(Value->IsUndefined())
            return Default;
        v8::String::Utf8Value StringValue(Isolate, Value);
        return std::string(*StringValue);
    }

    size_t GetKeyValueAsInteger(v8::Isolate* Isolate, v8::Local<v8::Object> Object, std::string Key, std::string Default){
        return std::atoi(GetKeyValue(Isolate, Object, Key, Default).c_str());
    }

    v8::Local<v8::Value> V8String(v8::Isolate* Isolate, const std::string String){
        return v8::String::NewFromUtf8(
            Isolate, String.c_str(), v8::NewStringType::kNormal,
            static_cast<int>(String.length())
        ).ToLocalChecked();
    }

    v8::Local<v8::Value> V8Number(v8::Isolate* Isolate, const int Integer){
        return v8::Number::New(Isolate, Integer);
    }

    v8::Local<v8::Name> V8Name(v8::Isolate* Isolate, const std::string String){
        return V8String(Isolate, String).As<v8::Name>();
    }

    v8::Local<v8::Value> V8Boolean(v8::Isolate* Isolate, const bool Bool){
        return v8::Boolean::New(Isolate, Bool);
    }

    static inline void V8Exception(v8::Isolate* Isolate, const std::string Message){
        Isolate->ThrowException(V8String(Isolate, Message));
    }

    v8::MaybeLocal<v8::Value> V8CallJSFunction(v8::Local<v8::Context> Context, v8::Local<v8::Function> LFunction, v8::Local<v8::Value> Recv, const unsigned short int Argc, v8::Local<v8::Value> Arguments[]){
        return LFunction->Call(Context, Recv, Argc, Arguments);
    }

    v8::Local<v8::Data> V8FunctionTemplate(v8::Isolate* Isolate, void(*Callback)(const v8::FunctionCallbackInfo<v8::Value>& Arguments)){
        return v8::FunctionTemplate::New(Isolate, Callback);
    }

    v8::Local<v8::Integer> V8Integer(v8::Isolate* Isolate, const int Integer){
        return v8::Integer::New(Isolate, Integer);
    }

    static void ReportException(v8::TryCatch* try_catch){
        v8::String::Utf8Value Exception(Zenda::Definitions::Isolate, try_catch->Exception());
        v8::Local<v8::Message> message = try_catch->Message();
        const std::string ExceptionString = std::string(*Exception);

        if(message.IsEmpty())
            std::cout << ExceptionString << std::endl;

        else{
            v8::String::Utf8Value Filename(
                Zenda::Definitions::Isolate, message->GetScriptOrigin().ResourceName());
            const std::string FilenameString = std::string(*Filename);
            unsigned int LineNumber = message->GetLineNumber(
                Zenda::Definitions::Isolate->GetCurrentContext()).FromJust();

            std::cout << std::endl << " ZendaJS Engine Runtime -> [Error in line " << std::to_string(LineNumber) << "] - [" << FilenameString << "]" << std::endl;
            std::cout << std::endl << " -> " << ExceptionString << std::endl << std::endl;
            v8::String::Utf8Value SourceLine(
                Zenda::Definitions::Isolate, message->GetSourceLine(
                    Zenda::Definitions::Isolate->GetCurrentContext()).ToLocalChecked());
            
            const std::string SourceLineString = std::string(*SourceLine);
            std::cout << " " << SourceLineString << std::endl;
            
            const unsigned int
                Start = message->GetStartColumn(
                    Zenda::Definitions::Isolate->GetCurrentContext()
                ).FromJust(),
                End = message->GetEndColumn(
                    Zenda::Definitions::Isolate->GetCurrentContext()
                ).FromJust();
            
            unsigned short int 
                Iterator = 0,
                Jterator = 0;
            
            for(Iterator; Iterator < Start; Iterator++) 
                fprintf(stderr, " ");
            
            for(Jterator; Jterator < End; Jterator++)
                fprintf(stderr, " ^");
            
            std::cout << std::endl;
        }
    }  
};
