# ESP8266 - Web Server - Dados Vazão de Fluídos

## Estrutura dos diretórios do projeto 

``` text
espWebServer
  |
  '- espWebServer
      |
      |- espWebServer.ino (projeto principal)
      |- Config.ino       (salva config no file system do esp8266)
      |- Util.ino         (Utilidades - Ex.: Gravacao Serial condicional em modo DEBUG)
      |- WebServer.ino    (Cria o web server que mostrará os dados - atualiza de 5 x 5 segundos)
      '- data             (Conteudo HTML, CSS etc para ser usado pelo Webserver.ino)
          |
          '-> Tudo que estiver nesse
              diretorio vai para a
              o File System do ESP8266
              usando o menu:
              Ferramentas
              -> ESP8266 Sketch Data Upload
          
            Obs: Nas IDEs mais novas, nao esta funcionando...
            -----------------------------------------------------------------
            link -> https://www.esp8266.com/viewtopic.php?f=32&t=19791

          Comandos:    
            wget https://github.com/esp8266/arduino-esp8266fs-plugin/releases/download/0.4.0/ESP8266FS-0.4.0.zip
            unzip ESP8266*
            cp -r ESP8266FS/ ~/arduino-1.8.9/tools/
            sudo apt install esptool
    
          Reiniciar o Arduino IDE

```

### NOTA IMPORTANTE

O ESP8266 utilizado possui Memoria = 512Kb e SPIFFS = 64Kb (se usar diferente, nao funciona)

### Pesquisas na internet

* [Conectar Arduino com ESP8266 com CD4050 (buffer nao inversor)](https://www.embarcados.com.br/esp8266-com-arduino/)  
* [Site Infortrônica Para Zumbis - Usando ESP8266 + MQTT](https://bitbucket.org/MarcoRabelo/esp8266/src/)  
* [How to Connect to an API with JavaScript](https://www.taniarascia.com/how-to-connect-to-an-api-with-javascript/)  
  
## Exemplo Esp8266 com Bootstrap embed

[Acessar link Esp8266 com Bootstrap](http://www.techtinker.co.za/2018/08/28/fully-embed-bootstrap-into-an-esp8266-web-server/)
