/*Código para detectar objetos con los sensores HC-SRO4 y MH con Arduino MEGA
 * Bruno Sánchez García A01378960
 * Carlos Antonio Buendia Lopez 
 * 11/05/2021 1.1v
 */
 //Se Incluye librearía para controlar Matriz de LED
#include <LedControl.h>
//La matriz se conecta al arduino de la siguiente manera
/*
 * VCC -> 5V
 * GND -> GND
 * DIN -> Pin Digital 22
 * CS -> Pin Digital 23
 * CLK -> Pin Digital 24
 */
//Pines de la matriz LED
int DIN = 31;
int CS =  33;
int CLK = 35;
//Valores de los sensores frontales y laterales
float sf = 0;
float sb = 0;
bool sl;
bool sr;
byte car[8]=   {0x00,0x00,0x38,0x3C,0x3C,0x38,0x00,0x00,};
byte slt[8]=   {0x3C,0x42,0x38,0x3C,0x3C,0x38,0x00,0x00,};
byte srt[8]=   {0x00,0x00,0x38,0x3C,0x3C,0x38,0x42,0x3C,};
byte sft[8]=   {0x00,0x02,0x39,0x3D,0x3D,0x39,0x02,0x00,};
byte sbk[8]=   {0x00,0x40,0xB8,0xBC,0xBC,0xB8,0x40,0x00,};
LedControl lc=LedControl(DIN,CLK,CS,0);
//Declaramos que usaremos las funciones en este lugar
void setup_anticolisiones();
void loop_anticolisiones();

void det_ft();
void det_bk();
void det_lf();
void det_rt();
void printByte(byte character []);
long readUltrasonicDistance(int triggerPin, int echoPin);

void setup_anticolisiones(){
  Serial.begin(9600);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
 lc.shutdown(0,false);       //The MAX72XX is in power-saving mode on startup
 lc.setIntensity(0,15);      // Set the brightness to maximum value
 lc.clearDisplay(0);         // and clear the display
}

void loop_anticolisiones(){ 
      
      sf = 0.0001723 * readUltrasonicDistance(40,38);
      sb = 0.0001723 * readUltrasonicDistance(44,42);
      sl = digitalRead(A8);
      sr = digitalRead(A9);
      
      if (sf < 0.10){
        det_ft();
      }
      if (sb < 0.10){
        det_bk();
      }
      if (sl ==0){
        det_lf();
      }
      if (sr ==0){
        det_rt();
      }
      else{
        printByte(car);
      
      }
      
      //lc.clearDisplay(0);
      //delay(1000);

    
}

void det_ft(){
  printByte(sft);
  delay(400);
  printByte(car);
  delay(400);
}

void det_bk(){
  printByte(sbk); 
  delay(400);
  printByte(car);
  delay(400);
}
void det_lf(){
  printByte(slt); 
  delay(400);
  printByte(car);
  delay(400);
}
void det_rt(){
  printByte(srt); 
  delay(400);
  printByte(car);
  delay(400);
}

void printByte(byte character [])
{
  int i = 0;
  for(i=0;i<8;i++)
  {
    lc.setRow(0,i,character[i]);
  }
}

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  //Manda la señal uktra sonica por 10 milisegundos
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  //Lee el pin de echo y regresa la lectura de tiempo en microsegundos
  return pulseIn(echoPin, HIGH);
}
