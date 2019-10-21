
void serverInit(){
  
  /* -------- HTTP SERVER ------------------------------ */

  server.begin();

  /* Spectre CSS - https://picturepan2.github.io/spectre */
  server.on("/spectre.min.css", css_);
  server.on("spectre.min.css", css_);
  server.on("/spectre-exp.min.css", exp_);
  server.on("spectre-exp.min.css", exp_);
  server.on("/spectre-icons.min.css", icons_);
  server.on("spectre-icons.min.css", icons_);

  /* Zepto.js (alternativa ao JQuery) - https://zeptojs.com */
  server.on("/zepto.min.js", zepto);
  server.on("zepto.min.js", zepto);

  /* User Files */
  server.on("/", fileindex);
  server.on("/index.html", fileindex);

  server.on("/user.js", userjs);
  server.on("user.js", userjs);

  server.on("/user.css", usercss);
  server.on("user.css", usercss);

  server.on("/logo.png", logo);
  server.on("logo.png", logo);

  server.on("/favicon.ico", favicon);
  server.on("favicon.ico", favicon);

  server.on("/parametros", HTTP_GET, []() {
    getParametros();
  });

}

void getParametros()
{

  String json;

  json = getJson(config);
  
  myprint("getParametros json = ");
  myprintln(json);

  server.send(200, "text/json", json);

}


void fileindex()
{
  File file = SPIFFS.open("/index.html.gz", "r");
  size_t sent = server.streamFile(file, "text/html");
}

void logo()
{
  File file = SPIFFS.open("/logo.png.gz", "r");
  size_t sent = server.streamFile(file, "image/png");
}

void favicon()
{
  File file = SPIFFS.open("/favicon.ico.gz", "r");
  size_t sent = server.streamFile(file, "image/x-icon");
}

void userjs()
{
  File file = SPIFFS.open("/user.js.gz", "r");
  size_t sent = server.streamFile(file, "application/javascript");
}

void usercss()
{
  File file = SPIFFS.open("/user.css.gz", "r");
  size_t sent = server.streamFile(file, "text/css");
}

void css_()
{
  File file = SPIFFS.open("/spectre.min.css.gz", "r");
  size_t sent = server.streamFile(file, "text/css");
}

void exp_()
{
  File file = SPIFFS.open("/spectre-exp.min.js.gz", "r");
  size_t sent = server.streamFile(file, "text/css");
}

void icons_()
{
  File file = SPIFFS.open("/spectre-icons.min.css.gz", "r");
  size_t sent = server.streamFile(file, "text/css");
}

void zepto()
{
  File file = SPIFFS.open("/zepto.min.js.gz", "r");
  size_t sent = server.streamFile(file, "application/javascript");
}
