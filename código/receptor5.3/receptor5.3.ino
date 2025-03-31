#include <SoftwareSerial.h>

#define VCC 6
#define GND 5
#define RX  4
#define TX  3
#define PRG 2

const int M1D=A0, M1I=A1, EN1=12; //pin motor 1
const int M2D=A4, M2I=A5, EN2=11; //pin motor 2

SoftwareSerial HC12(TX, RX); // HC-12 TX Pin, HC-12 RX Pin

  String mensaje = "";
  String mensajeA = "";
  String mensajeB = "";
  bool variable=false;
  int Val_1;
  int Val_2;
  int Valmap_1;
  int Valmap_2;
  int Valabs_1;
  int Valabs_2;

void setup() 
{
  pinMode(M1D, OUTPUT);
  digitalWrite(M1D, LOW);
  pinMode(M1I, OUTPUT);
  digitalWrite(M1I, LOW);
  
  Serial.begin(9600);  
  HC12.begin(9600); 
  
  pinMode(VCC, OUTPUT);
  digitalWrite(VCC, HIGH);
  
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
  
  Serial.println("receptor");
  delay(2000);
}


void loop() {
  HC12.flush();
  while (HC12.available()){
    char c = HC12.read();
    mensaje += c;
    delay(10);
  }
  

  mensaje.trim(); //elimina los espacios en blanco al principio y al final del mensaje
  int longitud = mensaje.length();

  //Serial.println(mensaje);

  if (longitud > 0 && longitud < 10) {
    boolean variable = false;  // Indica si ya se encontró el separador "_"
    mensajeA = "";  // Limpiamos las variables antes de procesar
    mensajeB = "";
    
    for (int i = 0; i < longitud; i++) {
        String separador = mensaje.substring(i, i + 1);  // Obtenemos el carácter actual

        // Si encontramos el separador "_", cambiamos el estado de variable
        if (separador == "_") {
            variable = true;
        } else if (!variable) {
            // Antes del primer "_", los caracteres se agregan a mensajeA
            mensajeA += separador;
        } else {
            // Después del primer "_", los caracteres se agregan a mensajeB
            mensajeB += separador;
        }
    }

    // Imprimimos los resultados para verificar la separación
    Serial.println("Mensaje: " + mensaje);  // Mensaje completo original
    /**
    Serial.println("MensajeA: " + mensajeA);  // Contenido antes del "_"
    Serial.println("MensajeB: " + mensajeB);  // Contenido después del "_"
    Serial.println("Longitud: " + String(longitud));  // Longitud del mensaje
    **/
}

    if(longitud>0){
      Val_1 = mensajeA.toInt();
      Val_2 = mensajeB.toInt();
      Valmap_1 = map(Val_1, 0, 1023, -255, 255);
      Valmap_2 = map(Val_2, 0, 1023, -255, 255);
      Valabs_1 = abs(Valmap_1);
      Valabs_2 = abs(Valmap_2);
    }
    //Serial.println(Val_1 + " _ " + Val_2);
    
    //control motor 1
      if(Val_1>(550)){
        digitalWrite(EN1, HIGH);
        analogWrite(M1D, Valabs_1);
        //Serial.println("M1 DERECHA");
      } else if(Val_1<550 && Val_1>500){
        digitalWrite(M1D, LOW);
        analogWrite(M1I, LOW);
        //Serial.println("STOP M1");
      } else{
        digitalWrite(EN1, HIGH);
        analogWrite(M1I, Valabs_1);
        //Serial.println("M1 IZQUIERDA");
      }

    //Control M2
      if(Val_2>(550)){
        digitalWrite(EN2, HIGH);
        analogWrite(M2D, Valabs_2);
        //Serial.println("M2 DERECHA");
      } else if(Val_2<550 && Val_2>500){
        digitalWrite(M2D, LOW);
        analogWrite(M2I, LOW);
        //Serial.println("STOP M2");
      } else{
        digitalWrite(EN2, HIGH);
        analogWrite(M2I, Valabs_2);
        //Serial.println("M2 IZQUIERDA");
      }

  mensaje = "";
  mensajeA = "";
  mensajeB = "";

  HC12.flush();
  
}
