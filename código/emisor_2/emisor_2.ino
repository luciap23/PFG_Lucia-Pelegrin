#include <SoftwareSerial.h>

#define VCC1 13
#define VCC2 12
#define GND 11
#define RX 10
#define TX 9
#define PRG 8

const int M1 = A1;
int Val_M1;

const int M2 = A0;
int Val_M2;

SoftwareSerial HC12(TX, RX);

void setup() {
  
  pinMode(M1, INPUT);
  pinMode(M2, INPUT);

  Serial.begin(9600);
  HC12.begin(9600);

  pinMode(VCC1, OUTPUT);
  digitalWrite(VCC1, HIGH);

  pinMode(VCC2, OUTPUT);
  digitalWrite(VCC2, HIGH);

  pinMode(GND, OUTPUT);
  digitalWrite(GND, LOW);

  pinMode(PRG, OUTPUT);
  digitalWrite(PRG, LOW); 

  delay(500);
  HC12.write("AT+B9600");
  delay(500);
  HC12.write("AT+C001");
  delay(500);         
  HC12.write("AT+P4");
  delay(500); 
  HC12.write("AT+FU1");
  delay(500);  

  digitalWrite(PRG, HIGH);

  Serial.println("emisor");
  delay(3000);  
}

void loop() {

  Val_M1 = analogRead(M1);
  Val_M2 = analogRead(M2);
  Serial.print(Val_M1);
  Serial.print(" / ");
  Serial.println(Val_M2);

  HC12.print(Val_M1);
  HC12.print("_");
  HC12.println(Val_M2);  
  HC12.print("");
  delay(200);
  
}
