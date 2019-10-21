/*
 * Imprimir na porta serial apenas se em modo DEVMODE
*/

void startSerial(){
#ifdef DEVMODE
  Serial.begin(115200);
  Serial.println();
#endif
}

void myprint(String mensagem) {
#ifdef DEVMODE
  Serial.print(mensagem);
#endif
}

void myprintln(String mensagem) {
#ifdef DEVMODE
  Serial.println(mensagem);
#endif
}
