//#include <SPI.h>
//#include <MFRC522.h>
//#define RST_PIN         5          // Configurable, see typical pin layout above
//#define SS_PIN          53         // Configurable, see typical pin layout above
//MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance
//byte readUID[4];
////Successful access for the following users
//const byte card[4] = {0x70, 0x8C, 0x2E, 0x30};      // this is UID card dectect by sensor RFID-RC522
//const byte keyChain[4] = {0xDA, 0x1E, 0x92, 0x80};  //this is UID Key Chain dectect by sensor RFID-RC522
//int Led[3]={43,45,47};
//const int buzzer = 49;
////inicializando las funciones que necesitamos para el codifgo 
//boolean compareUID(byte _read[], byte user[]);
//void init_led(int index,int tiempo);

//void setup_seguridad(){
//  //Serial.begin(9600);   // Initialize serial communications with the PC
//  while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
//  SPI.begin();      // Init SPI bus
//  mfrc522.PCD_Init();   // Init MFRC522 
//  for(int i=0;i<3;i++){
//    pinMode(Led[i],OUTPUT);
//  }
//  pinMode(buzzer,OUTPUT);
//}
//
//void seguridad(){
//   if ( ! mfrc522.PICC_IsNewCardPresent()) {
//    return;
//  }
//  // Select one of the cards
//  if ( ! mfrc522.PICC_ReadCardSerial()) {
//    return;
//  }
//  Serial.print("UID: ");
//    for (byte i = 0; i< mfrc522.uid.size;i++){
//      if(mfrc522.uid.uidByte[i]<0x10){
//        Serial.print(" 0");
//      }else{
//        Serial.print(" ");
//      }
//      Serial.print(mfrc522.uid.uidByte[i], HEX);
//      readUID[i]= mfrc522.uid.uidByte[i];
//    }
//    Serial.print("\t\n");
    
//    if(compareUID(readUID,keyChain)){
//      Serial.println("Bienvenido Señor Buendia.");
//      Serial.println("Iniciando los Sistemas, Reconfigurando los Servidores");
//      Serial.println("¿Que es  lo que desea?");
//      init_led(0,500);
//      return true;
//    }
//    
//    else if(compareUID(readUID,card)){
//      Serial.println("Bienvenido Señor Carlos Buendia esta usando la llave secundaria tiene un tiempo limitado(30 min)para encoantrar la principal.");
//      Serial.println("Si necesita su reposición llave. Llame a la agencia más cercana(55-74-85-74-43).");
//      init_led(0,500);
//      return true;
//      delay(30000);
//      return;
//    }
//    else{
//      Serial.println("Un estraño!!!");
//      for(int count =0;count < 3;count){
//        switch(count){
//          case 0:
//            Serial.println("No eres un usuario Bienvenido!");
//            Serial.println("Retírate!");
//            init_led(0,100);
//            break;
//          case 1:
//            Serial.println("No eres un usuario Bienvenido!");
//            Serial.println("Retírate!");
//            Serial.println("Tomando Caprura!");
//            Serial.println("Enviando a bases de datos de las autoridades correspondientes");
//            init_led(0,100);
//            break;
//          case 2:
//            Serial.println("No eres un usuario Bienvenido!");
//            Serial.println("Retírate!");
//            Serial.println("Bloqueando");
//            init_led(0,100);
//            return false;
//            break;
//        }
//      }
//      
//    }
//    for(int i = 0; i<3;i++){
//      digitalWrite(Led[i],LOW);
//    }
//    mfrc522.PICC_HaltA();
//}

//------------------------------------------------------------------------------------------------------------------
//boolean compareUID(byte _read[], byte user[]){
//  for(byte i=0;i<mfrc522.uid.size;i++){
//    if(_read[i] != user[i])
//        return(false);
//  }
//  return(true);
//}
//void init_led(int index,int tiempo){
//  for(int i = 0;i<3 ;i++){
//    digitalWrite(Led[index],HIGH);
//    digitalWrite(buzzer,HIGH);
//    delay(tiempo);
//    digitalWrite(Led[index],LOW);
//    digitalWrite(buzzer,LOW);
//    delay(tiempo);
//  }
//  digitalWrite(Led[index],HIGH);
//  digitalWrite(buzzer,HIGH);
//  delay(tiempo);
//  digitalWrite(Led[index],LOW);
//  digitalWrite(buzzer,LOW);
//  delay(tiempo);
//  digitalWrite(Led[index],HIGH);
//  digitalWrite(buzzer,HIGH);
//  delay(tiempo);
//}
  
