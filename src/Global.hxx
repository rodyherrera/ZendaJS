#include <iostream>
#include <v8.h>
using namespace std;
using namespace v8;

const char* ZendaVersion = "1.0.3";
const char* ZendaCreator = "Rodolfo Herrera Hernandez";

Isolate* ZendaIsolate;
Local<String> ZendaName;
Local<ObjectTemplate> ZendaGlobal;
unique_ptr<Platform> ZendaPlatform;
Isolate::CreateParams ZendaCreateParams;
vector<string> ZendaJavascriptCoreFiles;