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

#include <Poco/Net/MailMessage.h>
#include <Poco/Net/MailRecipient.h>
#include <Poco/Net/SMTPClientSession.h>
#include <Poco/Net/NetException.h>
#include <Poco/Net/SecureSMTPClientSession.h>
#include <Poco/Net/InvalidCertificateHandler.h>
#include <Poco/Net/AcceptCertificateHandler.h>
#include <Poco/Net/SSLManager.h>
#include <Poco/Net/SecureStreamSocket.h>
#include <Poco/Net/MailRecipient.h>
#include "restclient-cpp/connection.h"
#include "restclient-cpp/restclient.h"

#define WEBVIEW_IMPLEMENTATION
#include "WebView.hxx"

namespace Zenda::JavaScript::Methods::Misc{
    static void Fetch(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void Version(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void Creator(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static void ExecuteScript(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void Sleep(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void UseWebView(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static void SendMail(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static void Timeout(const v8::FunctionCallbackInfo<v8::Value> &Arguments);

    struct ZTimer{
        uv_timer_t Request;
        v8::Isolate *Isolate;
        v8::Global<v8::Function> Callback;
    };

    uv_loop_t *Loop = DEFAULT_LOOP;

    static void OnTimerCallback(uv_timer_t *Handle){
        ZTimer *TimerWrap = (ZTimer *)Handle->data;
        v8::Isolate *Isolate = TimerWrap->Isolate;
        v8::Local<v8::Context> Context = Isolate->GetCurrentContext();
        if(Isolate->IsDead()){
            std::cout << "Isolate is dead" << std::endl;
            return;
        }
        v8::Handle<v8::Value> Resultr[] = {
            v8::Undefined(Isolate),
            v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), "Hello world").ToLocalChecked()};
        v8::Local<v8::Function> Callback = v8::Local<v8::Function>::New(Isolate, TimerWrap->Callback);
        v8::MaybeLocal<v8::Value> CallbackResolve = Callback->Call(Context, v8::Undefined(Isolate), 2, Resultr).ToLocalChecked();
    }

    static void Timeout(const v8::FunctionCallbackInfo<v8::Value> &Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        v8::Local<v8::Context> Context = Arguments.GetIsolate()->GetCurrentContext();
        int64_t Delay = Arguments[0]->IntegerValue(Context).ToChecked();
        int64_t Repeat = Arguments[1]->IntegerValue(Context).ToChecked();
        v8::Local<v8::Value> Callback = Arguments[2];
        if(!Callback->IsFunction()){
            std::cout << "Callback not declared!" << std::endl;
            return;
        }        
        ZTimer *TimerWrap = new ZTimer();
        TimerWrap->Isolate = Arguments.GetIsolate();
        TimerWrap->Callback.Reset(Arguments.GetIsolate(), Callback.As<v8::Function>());
        TimerWrap->Request.data = (void *) TimerWrap;
        uv_timer_init(Loop, &TimerWrap->Request);
        uv_timer_start(&TimerWrap->Request, OnTimerCallback, Delay, Repeat);
    }

    static void Fetch(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        v8::Local<v8::Promise::Resolver> Resolver = 
            v8::Promise::Resolver::New(Arguments.GetIsolate()->GetCurrentContext()).ToLocalChecked();
        v8::MaybeLocal<v8::Promise> Promise(Resolver->GetPromise());
        v8::String::Utf8Value Server(Arguments.GetIsolate(), Arguments[0]);
        v8::Local<v8::Object> Options = Arguments[1].As<v8::Object>();
        std::string Method = "GET";
        std::string Body = "";
        std::string UserAgent = "ZendaJS/Fetch";
        std::string BSAUsername = "";
        std::string BSAPassword = "";
        std::string CertPath = "";
        std::string CertType = "";
        std::string KeyPath = "";
        std::string KeyPassword = "";
        std::string Proxy = "";
        unsigned short int Timeout = 5;
        RestClient::HeaderFields RequestHeaders;
        if(!Options->IsUndefined()){
            v8::String::Utf8Value CustomMethod(Arguments.GetIsolate(), Zenda::Shortcuts::Get(Options, "Method"));
            v8::String::Utf8Value CustomBody(Arguments.GetIsolate(), Zenda::Shortcuts::Get(Options, "Body"));
            v8::String::Utf8Value CustomUserAgent(Arguments.GetIsolate(), Zenda::Shortcuts::Get(Options, "UserAgent"));
            v8::String::Utf8Value CustomCaFilePath(Arguments.GetIsolate(), Zenda::Shortcuts::Get(Options, "CaFilePath"));
            v8::Local<v8::Object> BasicAuth = Zenda::Shortcuts::Get(Options, "BasicAuth").As<v8::Object>();
            if(!BasicAuth->IsUndefined()){
                v8::String::Utf8Value CustomBSAUsername(Arguments.GetIsolate(), Zenda::Shortcuts::Get(BasicAuth, "Username"));
                v8::String::Utf8Value CustomBSAPassword(Arguments.GetIsolate(), Zenda::Shortcuts::Get(Options, "Password"));
                if(*CustomBSAUsername)
                    BSAUsername = std::string(*CustomBSAUsername);
                if(*CustomBSAPassword)
                    BSAPassword = std::string(*CustomBSAPassword);
            }
            v8::String::Utf8Value CustomCertPath(Arguments.GetIsolate(), Zenda::Shortcuts::Get(Options, "CertPath"));
            v8::String::Utf8Value CustomCertType(Arguments.GetIsolate(), Zenda::Shortcuts::Get(Options, "CertType"));
            v8::String::Utf8Value CustomKeyPath(Arguments.GetIsolate(), Zenda::Shortcuts::Get(Options, "KeyPath"));
            v8::String::Utf8Value CustomKeyPassword(Arguments.GetIsolate(), Zenda::Shortcuts::Get(Options, "KeyPassword"));
            v8::String::Utf8Value CustomProxy(Arguments.GetIsolate(), Zenda::Shortcuts::Get(Options, "Proxy"));
            v8::Local<v8::Value> CustomTimeout = Zenda::Shortcuts::Get(Options, "Timeout");
            v8::Local<v8::Object> CustomHeaders = Zenda::Shortcuts::Get(Options, "Headers").As<v8::Object>();
            if(!CustomHeaders->IsUndefined()){
                v8::Local<v8::Array> PropertyNames = CustomHeaders->GetPropertyNames(Arguments.GetIsolate()->GetCurrentContext()).ToLocalChecked().As<v8::Array>();
                for(unsigned short int PropertyNameIterator = 0; PropertyNameIterator < PropertyNames->Length(); PropertyNameIterator++){
                    v8::String::Utf8Value HeaderName(Arguments.GetIsolate(), 
                        PropertyNames->Get(Arguments.GetIsolate()->GetCurrentContext(), PropertyNameIterator).ToLocalChecked());
                    v8::String::Utf8Value HeaderValue(Arguments.GetIsolate(), Zenda::Shortcuts::Get(CustomHeaders, std::string(*HeaderName)));
                    RequestHeaders[*HeaderName] = *HeaderValue;
                }
            }
            if(!CustomTimeout->IsUndefined())
                Timeout = CustomTimeout->NumberValue(Arguments.GetIsolate()->GetCurrentContext()).FromJust();
            if(std::string(*CustomProxy) != "undefined")
                Proxy = std::string(*CustomProxy);
            if(std::string(*CustomKeyPassword) != "undefined")
                KeyPassword = std::string(*CustomKeyPassword);
            if(std::string(*CustomKeyPath) != "undefined")
                KeyPath = std::string(*CustomKeyPath);
            if(std::string(*CustomCertType) != "undefined")
                CertType = std::string(*CustomCertType);
            if(std::string(*CustomCertPath) != "undefined")
                CertPath = std::string(*CustomCertPath);
            if(std::string(*CustomUserAgent) != "undefined")
                UserAgent = std::string(*CustomUserAgent);
            if(std::string(*CustomMethod) != "undefined")
                Method = std::string(*CustomMethod);
            if(std::string(*CustomBody) != "undefined")
                Body = std::string(*CustomBody);
        }
        RestClient::init();
        RestClient::Connection* Connection = new RestClient::Connection(*Server);
        Connection->SetHeaders(RequestHeaders);
        if(CertPath.length())
            Connection->SetCertPath(CertPath);
        if(CertType.length())
            Connection->SetCertType(CertType);
        if(KeyPath.length())
            Connection->SetKeyPath(KeyPath);
        if(KeyPassword.length())
            Connection->SetKeyPassword(KeyPassword);
        if(Proxy.length())
            Connection->SetProxy(Proxy);
        if(BSAUsername.length() && BSAPassword.length())
            Connection->SetBasicAuth(BSAUsername, BSAPassword);
        Connection->SetUserAgent(UserAgent);
        Connection->SetTimeout(Timeout);
        RestClient::Response Response = Connection->get("");
        if(Method == "POST")
            Response = Connection->post("", Body);
        else if(Method == "PATCH")
            Response = Connection->patch("", Body);
        else if(Method == "HEAD")
            Response = Connection->head("");
        else if(Method == "DELETE")
            Response = Connection->del("");
        else if(Method == "OPTIONS")
            Response = Connection->options("");
        else if(Method == "PUT")
            Response = Connection->put("", Body);
        v8::Local<v8::Object> ReturnValue = v8::Object::New(Arguments.GetIsolate());
        v8::Local<v8::Object> Headers = v8::Object::New(Arguments.GetIsolate());
        v8::Local<v8::Object> LastRequest = v8::Object::New(Arguments.GetIsolate());
        v8::Local<v8::Object> BasicAuth = v8::Object::New(Arguments.GetIsolate());
        RestClient::Connection::Info ConnectionInfo = Connection->GetInfo();
        RestClient::Connection::RequestInfo LastRequestInfo = ConnectionInfo.lastRequest;
        std::map<std::string, std::string>::iterator HttpHeadersIterator;
        for(HttpHeadersIterator = Response.headers.begin(); HttpHeadersIterator != Response.headers.end(); HttpHeadersIterator++)
            Zenda::Shortcuts::Set(Headers, HttpHeadersIterator->first, HttpHeadersIterator->second);
        Zenda::Shortcuts::Set(BasicAuth, "Username", ConnectionInfo.basicAuth.username);
        Zenda::Shortcuts::Set(BasicAuth, "Password", ConnectionInfo.basicAuth.password);
        Zenda::Shortcuts::Set(LastRequest, "TotalTime", LastRequestInfo.totalTime);
        Zenda::Shortcuts::Set(LastRequest, "Code", LastRequestInfo.curlCode);
        Zenda::Shortcuts::Set(LastRequest, "Error", LastRequestInfo.curlError);
        Zenda::Shortcuts::Set(LastRequest, "NameLookupTime", LastRequestInfo.nameLookupTime);
        Zenda::Shortcuts::Set(LastRequest, "ConnectTime", LastRequestInfo.connectTime);
        Zenda::Shortcuts::Set(LastRequest, "AppConnectTime", LastRequestInfo.appConnectTime);
        Zenda::Shortcuts::Set(LastRequest, "PreTransferTime", LastRequestInfo.preTransferTime);
        Zenda::Shortcuts::Set(LastRequest, "StartTransferTime", LastRequestInfo.startTransferTime);
        Zenda::Shortcuts::Set(LastRequest, "RedirectTime", LastRequestInfo.redirectTime);
        Zenda::Shortcuts::Set(LastRequest, "RedirectCount", LastRequestInfo.redirectCount);
        Zenda::Shortcuts::Set(ReturnValue, "LastRequest", LastRequest);
        Zenda::Shortcuts::Set(ReturnValue, "StatusCode", Response.code);
        Zenda::Shortcuts::Set(ReturnValue, "Headers", Headers);
        Zenda::Shortcuts::Set(ReturnValue, "Body", Response.body);
        Zenda::Shortcuts::Set(ReturnValue, "BaseURL", ConnectionInfo.baseUrl);
        Zenda::Shortcuts::Set(ReturnValue, "CertPath", ConnectionInfo.certPath);
        Zenda::Shortcuts::Set(ReturnValue, "CertType", ConnectionInfo.certType);
        Zenda::Shortcuts::Set(ReturnValue, "UserAgent", ConnectionInfo.customUserAgent);
        Zenda::Shortcuts::Set(ReturnValue, "FollowRedirects", ConnectionInfo.followRedirects);
        Zenda::Shortcuts::Set(ReturnValue, "KeyPassword", ConnectionInfo.keyPassword);
        Zenda::Shortcuts::Set(ReturnValue, "KeyPath", ConnectionInfo.keyPath);
        Zenda::Shortcuts::Set(ReturnValue, "MaxRedirects", ConnectionInfo.maxRedirects);
        Zenda::Shortcuts::Set(ReturnValue, "NoSignal", ConnectionInfo.noSignal);
        Zenda::Shortcuts::Set(ReturnValue, "Timeout", ConnectionInfo.timeout);
        Zenda::Shortcuts::Set(ReturnValue, "UriProxy", ConnectionInfo.uriProxy);
        RestClient::disable();
        v8::Maybe<bool> PromiseResolve = Resolver->Resolve(Arguments.GetIsolate()->GetCurrentContext(), ReturnValue);
        Arguments.GetReturnValue().Set(Promise.ToLocalChecked());
    }

    static void SendMail(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        //TODO: Initial version of the method, it is necessary to apply 
        //TODO: customization to the sending of messages, not all SMTP 
        //TODO: servers share the same logging systems, it applies one by 
        //TODO: default, in future versions it will be fixed.
        v8::HandleScope Scope(Arguments.GetIsolate());
        try{
            v8::Local<v8::Object> Data = Arguments[0].As<v8::Object>();
            v8::String::Utf8Value To(Arguments.GetIsolate(), Zenda::Shortcuts::Get(Data, "To",
                "The parameter 'To' was not found, you must specify the email where you want to send."));
            v8::String::Utf8Value From(Arguments.GetIsolate(),Zenda::Shortcuts::Get(Data, "From",
                "The 'From' parameter was not found, the email from where it will be sent must be specified."));
            v8::String::Utf8Value Subject(Arguments.GetIsolate(), Zenda::Shortcuts::Get(Data, "Subject",
                "The parameter 'Subject' was not found, you must specify it."));
            v8::String::Utf8Value Content(Arguments.GetIsolate(), Zenda::Shortcuts::Get(Data, "Content",
                "The parameter 'Content' was not found, you must specify the content of the email."));
            v8::String::Utf8Value ContentType(Arguments.GetIsolate(), Zenda::Shortcuts::Get(Data, "ContentType",
                "The parameter 'ContentType' was not found, you must specify it."));
            v8::Local<v8::Object> SmtpConfig = Zenda::Shortcuts::Get(Data, "SMTP",
                "The parameter 'SMTP' was not found, you must provide the object that will contain information about the server.").As<v8::Object>();
            v8::String::Utf8Value SmtpHostname(Arguments.GetIsolate(), Zenda::Shortcuts::Get(SmtpConfig, "Hostname", 
                "The 'Hostname' parameter of the 'SMTP' parameter was not found, you must specify the hostname of the SMTP server."));
            v8::String::Utf8Value SmtpUsername(Arguments.GetIsolate(), Zenda::Shortcuts::Get(SmtpConfig, "Username", 
                "The 'Username' parameter of the 'SMTP' object was not found, you must specify the user to log in."));
            v8::String::Utf8Value SmtpPassword(Arguments.GetIsolate(), Zenda::Shortcuts::Get(SmtpConfig, "Password",
                "The 'Password' parameter of the 'SMTP' object was not found, you must specify the password to log in."));
            unsigned short int SmtpPort = v8::Local<v8::Integer>::Cast(Zenda::Shortcuts::Get(SmtpConfig, "Port",
                "The 'Port' parameter was not found in the 'SMTP' parameter, you must specify the port the server is using."))->Value();
            Poco::Net::Context::Ptr MailContext = new Poco::Net::Context(
                Poco::Net::Context::CLIENT_USE, "", "", "", Poco::Net::Context::VERIFY_NONE, 9, false, "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH");
            Poco::SharedPtr<Poco::Net::InvalidCertificateHandler> MailCertificate = new Poco::Net::AcceptCertificateHandler(false);
            Poco::Net::SSLManager::instance().initializeClient(0, MailCertificate, MailContext);
            Poco::Net::SecureSMTPClientSession* MailSecureSession = 
                new Poco::Net::SecureSMTPClientSession(std::string(*SmtpHostname), SmtpPort);
            Poco::Net::SecureSMTPClientSession* MailSession = 
                new Poco::Net::SecureSMTPClientSession(std::string(*SmtpHostname), SmtpPort);
            Poco::Net::SecureStreamSocket* MailSSLSocket = 
                new Poco::Net::SecureStreamSocket(MailContext);
            MailSSLSocket->connect(Poco::Net::SocketAddress(std::string(*SmtpHostname), SmtpPort));
            MailSecureSession = new Poco::Net::SecureSMTPClientSession(*MailSSLSocket);
            MailSession = MailSecureSession;
            MailSecureSession->login();
            MailSecureSession->startTLS(MailContext);
            MailSession->login(Poco::Net::SMTPClientSession::AUTH_LOGIN, std::string(*SmtpUsername), std::string(*SmtpPassword));
            std::string SubjectString = Poco::Net::MailMessage::encodeWord(std::string(*Subject), "UTF-8");
            Poco::Net::MailMessage Message;
            Message.setSender(std::string(*From));
            Message.addRecipient(Poco::Net::MailRecipient(Poco::Net::MailRecipient::PRIMARY_RECIPIENT, std::string(*To)));
            Message.setSubject(SubjectString);
            Message.setContentType(std::string(*ContentType));
            Message.setContent(std::string(*Content), Poco::Net::MailMessage::ENCODING_8BIT);
            try{
                MailSession->sendMessage(Message);
                MailSession->close();
                Arguments.GetReturnValue().Set(Zenda::Shortcuts::V8Boolean(Arguments.GetIsolate(), false));
            }catch(Poco::Net::SMTPException &RuntimeError){
                Arguments.GetReturnValue().Set(
                    Zenda::Shortcuts::V8String(Arguments.GetIsolate(), RuntimeError.displayText()));
            }catch(Poco::Net::NetException &RuntimeError){
                Arguments.GetReturnValue().Set(
                    Zenda::Shortcuts::V8String(Arguments.GetIsolate(), RuntimeError.displayText()));
            }
        }catch(std::exception &RuntimeError){
            Arguments.GetReturnValue().Set(
                Zenda::Shortcuts::V8String(Arguments.GetIsolate(), std::string(RuntimeError.what())));
        }
    }

    static inline void UseWebView(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        v8::Local<v8::Object> Configuration = Arguments[0].As<v8::Object>();
        std::string Title = Zenda::Shortcuts::GetKeyValue(Arguments.GetIsolate(), Configuration, "Title", "ZendaJS - Default WebView Window Title");
        std::string Website = Zenda::Shortcuts::GetKeyValue(Arguments.GetIsolate(), Configuration, "Website", "https://github.com/codewithrodi/ZendaJS/");
        std::string Evaluate = Zenda::Shortcuts::GetKeyValue(Arguments.GetIsolate(), Configuration, "Evaluate", "");
        std::string Hint = Zenda::Algorithms::StringToUpper(
                Zenda::Shortcuts::GetKeyValue(Arguments.GetIsolate(), Configuration, "Hint", ""));
        unsigned short int Width = Zenda::Shortcuts::GetKeyValueAsInteger(Arguments.GetIsolate(), Configuration, "Width", "800");
        unsigned short int Height = Zenda::Shortcuts::GetKeyValueAsInteger(Arguments.GetIsolate(), Configuration, "Height", "600");
        unsigned short int SizeMode = WEBVIEW_HINT_NONE;
        if(Hint == "STATIC")
            SizeMode = WEBVIEW_HINT_FIXED;
        else if(Hint == "MAXIMUM")
            SizeMode = WEBVIEW_HINT_MAX;
        else if(Hint == "MINIMUM")
            SizeMode = WEBVIEW_HINT_MIN;
        webview::webview WebView(true, nullptr);
        WebView.set_title(Title);
        WebView.eval(Evaluate);
        WebView.set_size(Width, Height, SizeMode);
        WebView.navigate(Website);
        WebView.run();
    }

    static inline void Version(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        std::cout << ZENDA_VERSION << std::endl;
    }

    static inline void Creator(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        std::cout << ZENDA_CREATOR << std::endl;
    }

    static void ExecuteScript(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        if(Arguments[0]->IsUndefined())
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "To be able to execute one or more files you must first indicate them as a parameter, we are not guessers.");
        else
            for(unsigned short int Iterator = 0; Iterator < Arguments.Length(); Iterator++){
                v8::HandleScope Scope(Arguments.GetIsolate());
                v8::String::Utf8Value RequestedFile(Arguments.GetIsolate(), Arguments[Iterator]);
                std::string CharFile = std::string(*RequestedFile);
                std::string Contents = Zenda::FileSystem::ReadFile(CharFile);
                v8::Local<v8::Module> LModule = Zenda::JavaScript::Modules::Check(Zenda::JavaScript::Modules::Load(
                    Contents, CharFile, Arguments.GetIsolate()->GetCurrentContext()), Arguments.GetIsolate()->GetCurrentContext());
                v8::Local<v8::Value> Returned = Zenda::JavaScript::Modules::Execute(LModule, Arguments.GetIsolate()->GetCurrentContext());
            }
    }

    static inline void Sleep(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if(Arguments[0]->IsUndefined())
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "In order to sleep you need to indicate the time in milliseconds.");
        else
            sleep(Arguments[0]->NumberValue(Arguments.GetIsolate()->GetCurrentContext()).FromJust() / 1000);
    }
};
