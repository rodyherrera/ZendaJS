/***
 * Copyright (C) Rodolfo Herrera Hernandez. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root 
 * for full license information.
 *
 * =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
 *
 * Global.hxx: Initialization of variables for the execution of Zenda.
 *
 * This file initializes variables which are global, so that anywhere 
 * in the file branch of the Zenda base code they can be accessed, here 
 * there are only variables required to avoid loading garbage in the ram memory.

 *
 * For related information - https://github.com/rodiihernandezz/ZendaJS/
 *
 * =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
 ****/

#define ZendaVersion "1.0.7"
#define ZendaCreator "Rodolfo Herrera Hernandez"

string WorkingDirectory = "", PackagesFolder = "Packages/";
vector<string> CallArguments;

Isolate* ZendaIsolate;
Local<String> ZendaName;
Local<ObjectTemplate> ZendaGlobal;
unique_ptr<Platform> ZendaPlatform;
Isolate::CreateParams ZendaCreateParams;