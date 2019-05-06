// Projeto SmartLight
// Desenvolvido por: @gg_arduino

#include <SoftwareSerial.h>

#define rele 2
#define pinPalma A0

SoftwareSerial btSerial(8, 9); // RX, TX  ligar invertido

void executarAcao();

void setup() {
  pinMode(rele, OUTPUT);
  pinMode(pinPalma, INPUT); 
  
  btSerial.begin(9600);
  Serial.begin(9600);
}

void loop() {
  int sensorSom;
  static String btComando;
  static bool releStatus = HIGH; 

  while (btSerial.available()) {
     char comandoRec = btSerial.read();
     btComando += char( comandoRec );
     Serial.print(comandoRec);

     if (comandoRec == ';') {
        if (btComando == "B1;") {
            releStatus = !releStatus;
            digitalWrite(rele, releStatus);
        }
        btComando = ""; 
     }
  }
  
  long duracao = pulseIn(pinPalma,HIGH);
  Serial.println(duracao);
  if(duracao>0){
    executarAcao();
  }
  
  delay(5);
}

void executarAcao(){
  Serial.println("Palma!");
  digitalWrite(rele, !digitalRead(rele));
  delay(250);
}
