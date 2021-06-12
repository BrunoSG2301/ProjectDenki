
//Bruno Sánchez García A01378960
//Carlos Antonio Buendia López A01379471 
#include <Keypad.h>

#include <Nextion.h>
#include <Arduino_FreeRTOS.h>
#include "Seguridad.h"
#include "Anticolisiones.h"
#include "varGlobales.h"
const byte rows = 4;
const byte cols = 4;
  const char keys[rows][cols]={
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
  };
byte pinrows[rows]={22,24,26,28};
byte pincols[cols]={30,32,34,36};

char BUTTON;
char pasword[9];
char masterpwd[9]="12345678";
byte index = 0; 
boolean tecladoMatricial;
Keypad Buttons = Keypad(makeKeymap(keys),pinrows,pincols,rows,cols);
#include <SPI.h>
#include <MFRC522.h>
#define RST_PIN         5          // Configurable, see typical pin layout above
#define SS_PIN          53         // Configurable, see typical pin layout above
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance
//Declaración de Funciones 
void loop_general();
void b1_preview(void *ptr);
void bt0_playPause(void *ptr);
void b3_next(void *ptr);
void b4_random(void *ptr);
void b5_rewind(void *ptr);
void b6_prevList(void *ptr);
void CSRPI();

int pasa=0;
int count1 = 1;
//-------------------------------------------------------------------------------------------------------------------------
//Bonones de la page 1 en Nextion
NexButton b1 = NexButton(1,3,"b1");//preview
NexDSButton bt0 = NexDSButton(1,6,"bt0");//play/pause
NexButton b3 = NexButton(1,4,"b3");//next
NexButton b4 = NexButton(1,5,"b4");//random
NexButton b5 = NexButton(1,8,"b5");//repetir 1 vez más
NexButton b6 = NexButton(1,10,"b6");//lista anterior
NexButton b7 = NexButton(1,11,"b7");//lista posterior
NexButton b9 = NexButton(1,13,"b9");//añadir lista
NexButton b10 = NexButton(1,14,"b10");//eliminar
NexButton b11 = NexButton(1,15,"b11");//Stop

NexSlider h0 = NexSlider(1,16,"h0");//Control de Volumen

NexScrolltext objSongName = NexScrolltext(1,2,"objSongName");// nombre de la cancion que se encuentra reproduciendo
NexScrolltext NameList = NexScrolltext(1,19,"NameList");// nombre de la cancion que se encuentra reproduciendo


//-------------------------------------------------------------------------------------------------------------------------


//registro al objetos a la lista de eventos touch
NexTouch *nex_listen_list[] = {&b1,&bt0,&b3,&b4,&b5,&b6,&b7,&b9,&b10,&b11,&h0,NULL};
//------------------------------------------------------SET-UP---------------------------------------------------------------
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(buttonIO, INPUT);
  pinMode(7,OUTPUT);
  //-------------------------------------------------------------------------------------------------------------------------
  setup_seguridad(); 
  setup_anticolisiones();
  //-------------------------------------------------------------------------------------------------------------------------
  nexInit();//Inicio comunicación entre el microcontrolador y la pantalla Nextion
  //-------------------------------------------------------------------------------------------------------------------------
  //Registro el llamado al la funcion del los respectivos eventos de cada boton o actuador touch
  b1.attachPop(b1_preview);
  bt0.attachPop(bt0_playPause);
  b3.attachPop(b3_next);
  b4.attachPop(b4_random);
  b5.attachPop(b5_rewind);
  b6.attachPop(b6_prevList);
  
  
  //-------------------------------------------------------------------------------------------------------------------------
  
}
//----------------------------------------------------VOID-LOOP--------------------------------------------------------------
void loop() {
  // put your main code here, to run repeatedly
  buttonState = digitalRead(buttonIO);
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

    Serial.print("UID: ");
    for (byte i = 0; i< mfrc522.uid.size;i++){
      if(mfrc522.uid.uidByte[i]<0x10){
        Serial.print(" 0");
      }else{
        Serial.print(" ");
      }
      Serial.print(mfrc522.uid.uidByte[i], HEX);
      readUID[i]= mfrc522.uid.uidByte[i];
    }
    Serial.print("\t\n");
    TecladoMatrix();
    
    if(compareUID(readUID,keyChain) or tecladoMatricial){
      Serial.println("Bienvenido Señor Buendia.");
      Serial.println("Iniciando los Sistemas, Reconfigurando los Servidores");
      Serial.println("¿Que es  lo que desea?");
      init_led(2,250);
      //nexLoop(nex_listen_list);//cada vez que el elemento sea llamado, se direccionara al correpondiente evento del componente
      //loop_anticolisiones();
      
      while(buttonState == LOW){
        nexLoop(nex_listen_list);//cada vez que el elemento sea llamado, se direccionara al correpondiente evento del componente
        loop_anticolisiones();
      }
     
      //Serial.println(count1,DEC);
    }
    
    else if(compareUID(readUID,card)){
      Serial.println("Bienvenido Señor Carlos Buendia esta usando la llave secundaria tiene un tiempo limitado(30 min)para encoantrar la principal.");
      Serial.println("Si necesita su reposición llave. Llame a la agencia más cercana(55-74-85-74-43).");
      init_led(1,300);
      nexLoop(nex_listen_list);//cada vez que el elemento sea llamado, se direccionara al correpondiente evento del componente
      //loop_anticolisiones();
      //delay(30000);
       while(buttonState == LOW){
        nexLoop(nex_listen_list);//cada vez que el elemento sea llamado, se direccionara al correpondiente evento del componente
        loop_anticolisiones();
      }
     
      //nexLoop(nex_listen_list);//cada vez que el elemento sea llamado, se direccionara al correpondiente evento del componente
      
      Serial.print(count1,DEC);
    }
    else{
      Serial.println("Un estraño!!!");
        switch(count1){
          case 1:
            Serial.println("No eres un usuario Bienvenido!");
            Serial.println("Retírate!");
            init_led(0,100);
            break;
          case 2:
            Serial.println("No eres un usuario Bienvenido!");
            Serial.println("Retírate!");
            Serial.println("Tomando Caprura!");
            Serial.println("Enviando a bases de datos de las autoridades correspondientes");
            init_led(0,100);
            break;
          case 3:
            Serial.println("No eres un usuario Bienvenido!");
            Serial.println("Retírate!");
            Serial.println("Bloqueando");
            init_led(0,100);
            digitalWrite(7,HIGH);
            //return false;
            break;
            Serial.print(count1,DEC);
        }
      }
      
    count1+=1;
    for(int i = 0; i<3;i++){
      digitalWrite(Led[i],LOW);
    }
    mfrc522.PICC_HaltA();
    count1 +=1;
}


void b1_preview(void *ptr){
  CSRPI();
  Serial.println("preview");
}


void bt0_playPause(void *ptr){
  uint32_t DualState;
  bt0.getValue(&DualState);
  CSRPI();
  if(DualState == true){
      Serial.println("play");
  }else if(DualState == false){
      Serial.println("pause");
  }else{
    return;
  }
  
}

void b3_next(void *ptr){
  CSRPI();
  Serial.println("next");
}

void b4_random(void *ptr){
  CSRPI();
  Serial.println("random");
}


void b5_rewind(void *ptr){
  CSRPI();
  Serial.println("rewind");
}

void b6_prevList(void *ptr){
  
  Serial.println("prv");
}

void CSRPI(){//Comunicación Serial con la Raspberry Pi
  if(Serial.available()>0){
      String dato = Serial.readStringUntil("\n");
      for(int index = 0;index<13;index++){
        if(dato == indexCharLS[index]){
          objSongName.setText(listSong[index]);
        }
        else{
          objSongName.setText("Tu lista Termino... deseas poner otra lista?");
          NameList.setText("Finalizó tu lista Main List");
        }
        NameList.setText(listFolder[0]);
      }
  }
}
void loop_general(){
  for(;;){
      nexLoop(nex_listen_list);//cada vez que el elemento sea llamado, se direccionara al correpondiente evento del componente
      //loop_anticolisiones();
//      buttonState = digitalRead(buttonIO);
//
//      // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
//      if (buttonState == HIGH) {
//      // turn LED on:
//         break;
//      }
//      else {
//        // turn LED off:
//        Serial.print("Boton_apagado");
//      }
  }
}

boolean compareUID(byte _read[], byte user[]){
  for(byte i=0;i<mfrc522.uid.size;i++){
    if(_read[i] != user[i])
        return(false);
  }
  return(true);
}
void init_led(int index,int tiempo){
  for(int i = 0;i<3 ;i++){
    digitalWrite(Led[index],HIGH);
    digitalWrite(buzzer,HIGH);
    delay(tiempo);
    digitalWrite(Led[index],LOW);
    digitalWrite(buzzer,LOW);
    delay(tiempo);
  }
}

void seguridad(){
  
}

void setup_seguridad(){
  //Serial.begin(9600);   // Initialize serial communications with the PC
  while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();      // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522 
  for(int i=0;i<3;i++){
    pinMode(Led[i],OUTPUT);
  }
  pinMode(buzzer,OUTPUT);
}


boolean TecladoMatrix(){
  BUTTON = Buttons.getKey();
  //Serial.print(BUTTON); 
  if(BUTTON){
    pasword[index] = BUTTON;
    index++;
    Serial.print(BUTTON);
  }
  if(index == 8){
    if(!strcmp(pasword,masterpwd)){
      tecladoMatricial = true;Serial.println("Correcto:");
    }else{
      tecladoMatricial = false;Serial.println("Incorrecto");
    }
    index = 0;    
    return tecladoMatricial;

  }
}
