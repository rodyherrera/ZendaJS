const char* ZendaVersion = "1.0.4";
const char* ZendaCreator = "Rodolfo Herrera Hernandez";

vector<string> CallArguments;

Isolate* ZendaIsolate;
Local<String> ZendaName;
Local<ObjectTemplate> ZendaGlobal;
unique_ptr<Platform> ZendaPlatform;
Isolate::CreateParams ZendaCreateParams;
vector<string> ZendaJavascriptCoreFiles;