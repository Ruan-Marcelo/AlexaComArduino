#include <Arduino.h>
#include <Espalexa.h>
#include <WiFi.h>

int const pinLedVM = 5;
int const pinLedAM = 17;
int const pinLedVD = 16;

const char* ssid =  "LOVE QUINN"; //"SALA_605";
const char* password = "ruanzin1"; //"sen@i602";

//WebServer server(80);
Espalexa espalexa;
//------------------------------------------
//Comando processados = "Led vermelho"
//------------------------------------------
String Dispositivo01 = "Led vermelho";


//PROTÓTIPOS DE FUNÇÕES
void limparTerminal();
void inicializarWiFi();
void inicializarAlexa();
void ligarLedVM(uint8_t brilho);



//------------------------------------------
//------------------------------------------
void setup() {
  Serial.begin(921600);

  pinMode(pinLedVM, OUTPUT);
  pinMode(pinLedAM, OUTPUT);
  pinMode(pinLedVD, OUTPUT);

  //digitalWrite(pinLedVM, HIGH);
  //digitalWrite(pinLedAM, HIGH);
  //digitalWrite(pinLedVD, HIGH);

  // Tempo para que eu possa abrir a janela do Monitor
  delay(2000); 

  limparTerminal();

  // Conecta-se ao WI-FI
  inicializarWiFi();  

//Conecta a Alexa
  inicializarAlexa();
}

//------------------------------------------
//------------------------------------------
void loop() {
  espalexa.loop();
  delay(1);
}

//------------------------------------------
//------------------------------------------
void limparTerminal(){
  Serial.write(27);       // Comando ESC 
  Serial.print("[2J");    // Comando clear screen 
  Serial.write(27);
  Serial.print("[H");     // Comando cursor to home 
}

//------------------------------------------
//------------------------------------------
void inicializarWiFi(){
  // Configurando como "Modo Estação"
  WiFi.mode(WIFI_STA);

  // Conecta o ESP32 à rede WI-FI
  WiFi.begin(ssid, password);

   // A conexão pode levar algum tempo
  Serial.print("Conectando-se ao WiFi: ");

  while (WiFi.status() != WL_CONNECTED) {    
    Serial.print('.');  
    delay(500);    
  }

  Serial.println("WiFi conectado.");
  Serial.print("Endereço IP: http://");
  Serial.println(WiFi.localIP()); // Obtem o IP para o ESP32
}

//----------------------------------------------------
//----------------------------------------------------
void inicializarAlexa(){
 //O parâmetro brilho contém  estado do dispositivo
 // (0: desligado, 255; ligado, 1-254: esmaecido)
 // que será enviado pela Alexa quando a função
 // callbacl() for chamada.

 espalexa.addDevice(Dispositivo01, ligarLedVM);




 espalexa.begin();

}

//----------------------------------------------------
// callback()
//----------------------------------------------------

void ligarLedVM(uint8_t brilho){
  if (brilho ==255)
  {
   digitalWrite(pinLedVM, HIGH);
   Serial.println("Led vermelho: ligado");
  }
  else 
  {
   digitalWrite(pinLedVM, LOW);
   Serial.println("Led vermelho: Desligado");
  }
}

