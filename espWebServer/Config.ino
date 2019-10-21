void setInitialConfigValues(bool isToFormat){

  /* Variaveis para pegar o Mac Address do modulo */
  uint8_t MAC_array[6];
  char MAC_char[12]; // Ex.: 5ccf7f11d904
  
  startSerial(); // Util.ino

  //Pega MAC_ADDRESS
  String mac_address = String(WiFi.macAddress());

  for (int i = 0; i < mac_address.length() -1; ++i){
    char c = mac_address.charAt(i);
    if (c == ':'){
      mac_address.remove(i,1);
    }
  }

  

  // Inicia o FileSystem do esp8266
  if (!SPIFFS.begin()) {
    myprintln("Erro ao carregar diretorio SPIFFS");
  }else{
    myprintln("Diretorio SPIFFS carregado!");
  }

  if (isToFormat){
    SPIFFS.format();
  }
 
  myprintln(listaDiretorio());

  if (! SPIFFS.exists(filename)){
    myprint("Arquivo ");
    myprint(filename);
    myprintln(" nao existe, criando o arquivo default.");
    String jsonAux = "{ \"vazao\" : \"0\", \"volume\" : \"0\"}";
    myprint("Valores defaul: ");
    myprintln(jsonAux);
    if (setJson (jsonAux, config) != 0){
      myprintln("DEU RUIM NO PARSE DO JSON");
    }else{
      if(!saveConfiguration(filename, config)){
        myprint("Arquivo criado ");
        myprint(filename);
        myprintln(" com sucesso");
      }
    }
    
  }

  setJson(loadConfiguration(filename), config);


}


String getJson (const Config &config){
  
  String json;
    
  // Allocate the memory pool on the stack
  // Don't forget to change the capacity to match your JSON document.
  // Use https://arduinojson.org/assistant/ to compute the capacity.
  StaticJsonBuffer<1024> jsonBuffer;

  // Parse the root object
  JsonObject &root = jsonBuffer.createObject();

  // Set the values
  root["vazao"]      = config.vazao;
  root["volume"]     = config.volume;       
;
  

  // Serialize to JSON var
  if (root.prettyPrintTo(json) == 0) {
    myprintln("Failed to write to file");
  }
    
  return json;
}


String loadConfiguration(const char* filename) {

  // Open file for reading
  File file = SPIFFS.open(filename, "r");

  if (!file) {
    myprint("Erro ao ler arquivo de configuracao = ");
    myprintln(filename);
    file.close();
    return String("");
   
  } else {
    myprint("Arquivo ");
    myprint(filename);
    myprintln(" carregado com sucesso.");
  }

  String json = file.readString();

  // Close the file (File's destructor doesn't close the file)
  file.close();

  return json;
}


bool setJson (String json, Config &config){

  // Allocate the memory pool on the stack.
  // Don't forget to change the capacity to match your JSON document.
  // Use arduinojson.org/assistant to compute the capacity.
  StaticJsonBuffer<1024> jsonBuffer;

  // Parse the root object
  JsonObject &root = jsonBuffer.parseObject(json);

  if (!root.success()){
    myprintln("Falha ao fazer o parse do json!");
    myprintln(json);
    return 1;
  }else{
    String jsonPretty = String();
    root.prettyPrintTo(jsonPretty);
    myprintln("Config in Json format:");
    myprintln(jsonPretty);
  }

  // Copy values from the JsonObject to the Config
  
  strlcpy(config.vazao,             
          root["vazao"] | "0",
          sizeof(config.vazao));

  strlcpy(config.volume,             
          root["volume"] | "0",
          sizeof(config.volume));

  return 0;
 
}


// Saves the configuration to a file
bool saveConfiguration(const char *filename, Config &config) {

  // Open file for writing
  File file = SPIFFS.open(filename, "w");
  if (!file) {
    myprintln(F("Failed to create file"));
    return 1;
  }

  String json;

  json = getJson(config);

  file.print(json);
  myprintln(json);

  file.close();

  return 0;
}


String listaDiretorio(){
  
  String str = "SPIFSS directory:\n";
  Dir dir = SPIFFS.openDir("/");
  while (dir.next()) {
    str += dir.fileName();
    str += " / ";
    str += dir.fileSize();
    str += "\r\n";
  }

  return str;
}
