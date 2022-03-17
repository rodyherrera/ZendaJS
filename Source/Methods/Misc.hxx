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

#define WEBVIEW_IMPLEMENTATION
#include "WebView.hxx"

namespace Zenda::JavaScript::Methods::Misc{
    static inline void Version(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void Creator(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static void ExecuteScript(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void Sleep(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void UseWebView(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static void SendMail(const v8::FunctionCallbackInfo<v8::Value>& Arguments);

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
