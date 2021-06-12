//Librerias de Nextion--------------------------------------------------------------------------------------------------------------
//#include <doxygen.h>
//#include <NexButton.h>
//#include <NexCheckbox.h>
//#include <NexConfig.h>
//#include <NexCrop.h>
//#include <NexDualStateButton.h>
//#include <NexGauge.h>
//#include <NexGpio.h>
//#include <NexHardware.h>
//#include <NexHotspot.h>
//#include <NexNumber.h>
//#include <NexObject.h>
//#include <NexPage.h>
//#include <NexPicture.h>
//#include <NexProgressBar.h>
//#include <NexRadio.h>
//#include <NexRtc.h>
//#include <NexScrolltext.h>
//#include <NexSlider.h>
//#include <NexText.h>
//#include <NexTimer.h>
//#include <Nextion.h>
//#include <NexTouch.h>
//#include <NexUpload.h>
//#include <NexVariable.h>
//#include <NexWaveform.h>
//Librerias de Nextion--------------------------------------------------------------------------------------------------------------
char *listSong[] = { "Aaron Smith - Dancin (KRONO Remix) (Español).mp3",
                     "Brooks _ KSHMR - Voices (feat. TZAR) [Official Lyric Video].mp3",
                     "Duvet.mp3",
                     "Fire Emblem Fates - Lost in Thoughts All Alone [Full English Version].mp3",
                     "I Left My Umbrella at Home.mp3",
                     "KSHMR & Lost Stories - Bombay Dreams [feat. Kavita Seth] (Official Music Video).mp3",
                     "KSHMR x Hard Lights - Over and Out (feat. Charlott Boss) [Official Audio].mp3",
                     "KSHMR, Jeremy Oceans - One More Round (Free Fire Booyah Day Theme Song) [Official Music Video].mp3",
                     "LMFAO ft. Lauren Bennett, GoonRock - Party Rock Anthem (Official Audio).mp3",
                     "Major Lazer & DJ Snake - Lean On (feat. MØ) (Official Music Video).mp3",
                     "Panic! At The Disco - House of Memories (Official Audio).mp3",
                     "Pharrell Williams - Happy (Official Music Video).mp3",
                     "Pitbull - Hey Baby (Drop It To The Floor) ft. T-Pain.mp3"};
char *indexCharLS[] = {"0","1","2","3","4","5","6","7","8","9","10","11","12"};
char *indexCharF[] = {"0","1","2","3"};
char *listFolder[] = {"mainlist",
                      "Hello World",
                      "Joy",
                      "Relax"};
String dato;
int buttonIO=2;
int buttonState = 0; 


byte readUID[4];
//Successful access for the following users
const byte card[4] = {0x70, 0x8C, 0x2E, 0x30};      // this is UID card dectect by sensor RFID-RC522
const byte keyChain[4] = {0xDA, 0x1E, 0x92, 0x80};  //this is UID Key Chain dectect by sensor RFID-RC522
int Led[3]={43,45,47};
const int buzzer = 49;
//inicializando las funciones que necesitamos para el codifgo 
boolean compareUID(byte _read[], byte user[]);
void init_led(int index,int tiempo);









//Variables de Matríz led
