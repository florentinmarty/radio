// Vector - Version: Latest
//#include <Vector.h>

/***************************************************
  DFPlayer - A Mini MP3 Player For Arduino
  <https://www.dfrobot.com/index.php?route=product/product&product_id=1121>

 ***************************************************
  This example shows the all the function of library for DFPlayer.

  Created 2016-12-07
  By [Angelo qiao](Angelo.qiao@dfrobot.com)

  GNU Lesser General Public License.
  See <http://www.gnu.org/licenses/> for details.
  All above must be included in any redistribution
 ****************************************************/

/***********Notice and Trouble shooting***************
  1.Connection and Diagram can be found here
  <https://www.dfrobot.com/wiki/index.php/DFPlayer_Mini_SKU:DFR0299#Connection_Diagram>
  2.This code is tested on Arduino Uno, Leonardo, Mega boards.
 ****************************************************/

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include "Input.h"
#include "PersistanceState.h"


SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);

Input inputFolder1;
Input inputFolder2;
Input inputFolder3;
Input inputFolder4;
Input inputFolder5;
Input inputFolder6;
Input play;
Input back;
Input forward;
PersistanceState state;

int sensorValue;
int sensorPin;
int volume;
int MAX_VOLUME;

void setup()
{
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
  //delay(1000);
  mySoftwareSerial.begin(9600);
  Serial.begin(9600);

  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  delay(1000);

  // Try to establish a connection
  while (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    delay(2000);
  }

  Serial.println(F("Player communication works."));

  Serial.println(F("Load current Tracks"));
  state = PersistanceState();
  
  volume = state.getVolume();
  
  MAX_VOLUME = 20;
  if (volume > MAX_VOLUME){
    state.setVolume(MAX_VOLUME);
  }

  inputFolder1 =  Input(9);
  inputFolder2 =  Input(12);
  inputFolder3 =  Input(13);
  inputFolder4 =  Input(3);
  inputFolder5 =  Input(4);
  inputFolder6 =  Input(5);
  Serial.println(F("Input folders set"));

  back =  Input(6);
  play =  Input(7);
  forward =  Input(8);
  Serial.println(F("Settings all set, ready to go."));


  Serial.println(F("Setting Timout"));
  myDFPlayer.setTimeOut(500); //Set serial communictaion time out 500ms

  Serial.println(F("Set Volume"));
  myDFPlayer.volume(volume);  //Set volume value (0~30).

  Serial.println(F("Set EQ"));
  myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);

  Serial.println(F("Set output Device"));
  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);



  Serial.println(F("start playing current track"));
  myDFPlayer.playFolder(state.getFolder(), state.getTrack());

  Serial.println(F("Settings all set, ready to go."));
}

void loop()
{

  inputFolder1.updateState();
  inputFolder2.updateState();
  inputFolder3.updateState();
  inputFolder4.updateState();
  inputFolder5.updateState();
  inputFolder6.updateState();
  back.updateState();
  play.updateState();
  forward.updateState();


  delay(20);


  if (inputFolder1.getFallingEdge())
  {
    Serial.println(F("1 gedrückt"));
    state.setFolder(1);
    myDFPlayer.playFolder(state.getFolder(), state.getTrack());  //play specific mp3 in SD:/15/004.mp3; Folder Name(1~99); File Name(1~255)
  }

    if (inputFolder1.isPressed())
  {
    Serial.println(F("1 lang gedrückt"));
    state.setFolder(1);
    state.setTrack(1);
    myDFPlayer.playFolder(state.getFolder(), state.getTrack());  //play specific mp3 in SD:/15/004.mp3; Folder Name(1~99); File Name(1~255)
  }

  if (inputFolder2.getFallingEdge())
  {
    Serial.println(F("2 gedrückt"));
    state.setFolder(2);
    myDFPlayer.playFolder(state.getFolder(), state.getTrack());  //play specific mp3 in SD:/15/004.mp3; Folder Name(1~99); File Name(1~255)
  }

    if (inputFolder2.isPressed())
  {
    Serial.println(F("2 lang gedrückt"));
    state.setFolder(2);
    state.setTrack(1);
    myDFPlayer.playFolder(state.getFolder(), state.getTrack());  //play specific mp3 in SD:/15/004.mp3; Folder Name(1~99); File Name(1~255)
  }

  if (inputFolder3.getFallingEdge())
  {
    Serial.println(F("3 gedrückt"));
    state.setFolder(3);
    state.setTrack(1);
    myDFPlayer.playFolder(state.getFolder(), state.getTrack());  //play specific mp3 in SD:/15/004.mp3; Folder Name(1~99); File Name(1~255)
  }

   if (inputFolder3.isPressed())
  {
    Serial.println(F("3 lang gedrückt"));
    state.setFolder(3);
    myDFPlayer.playFolder(state.getFolder(), state.getTrack());  //play specific mp3 in SD:/15/004.mp3; Folder Name(1~99); File Name(1~255)
  }

  if (inputFolder4.getFallingEdge())
  {
    Serial.println(F("4 gedrückt"));
    state.setFolder(4);
    myDFPlayer.playFolder(state.getFolder(), state.getTrack());  //play specific mp3 in SD:/15/004.mp3; Folder Name(1~99); File Name(1~255)
  }

  if (inputFolder4.isPressed())
  {
    Serial.println(F("4 lang gedrückt"));
    state.setFolder(4);
    state.setTrack(1);
    myDFPlayer.playFolder(state.getFolder(), state.getTrack());  //play specific mp3 in SD:/15/004.mp3; Folder Name(1~99); File Name(1~255)
  }
  if (inputFolder5.getFallingEdge())
  {
    Serial.println(F("5 gedrückt"));
    state.setFolder(5);
    myDFPlayer.playFolder(state.getFolder(), state.getTrack());  //play specific mp3 in SD:/15/004.mp3; Folder Name(1~99); File Name(1~255)
  }

  if (inputFolder5.isPressed())
  {
    Serial.println(F("5 lang gedrückt"));
    state.setFolder(5);
    state.setTrack(1);
    myDFPlayer.playFolder(state.getFolder(), state.getTrack());  //play specific mp3 in SD:/15/004.mp3; Folder Name(1~99); File Name(1~255)
  }
  if (inputFolder6.getFallingEdge())
  {
    Serial.println(F("6 gedrückt"));
    state.setFolder(6);
    myDFPlayer.playFolder(state.getFolder(), state.getTrack());  //play specific mp3 in SD:/15/004.mp3; Folder Name(1~99); File Name(1~255)
  }

 if (inputFolder6.isPressed())
  {
    Serial.println(F("6 lang gedrückt"));
    state.setFolder(6);
    state.setTrack(1);
    myDFPlayer.playFolder(state.getFolder(), state.getTrack());  //play specific mp3 in SD:/15/004.mp3; Folder Name(1~99); File Name(1~255)
  }
  if (back.getRisingEdge())
  {

    Serial.println("back");
    int nextTrack = 1;
    int currentTrack = state.getTrack();
    if (currentTrack > 2) {
      nextTrack = currentTrack - 1;
    }
    state.setTrack(nextTrack);


    myDFPlayer.playFolder(state.getFolder(), state.getTrack());  //play specific mp3 in SD:/15/004.mp3; Folder Name(1~99); File Name(1~255)
    // Strangely,this is needed,oterwise the risingedge detection does not work properly
    delay(200);


  }
  if (forward.getRisingEdge())
  {

    Serial.println("forward");
    state.nextTrack();

    myDFPlayer.playFolder(state.getFolder(), state.getTrack());  //play specific mp3 in SD:/15/004.mp3; Folder Name(1~99); File Name(1~255)
    // this is needed,oterwise the risingedge detection does not work properly
    delay(200);

  }

  // Volume
  if (back.isPressed())
  {
    volume--;
    if (volume < 1)
    {
      volume = 1;
    }
    
    myDFPlayer.volume(volume);
    

    Serial.println("Leiser: volume");
    Serial.println(volume);
    state.setVolume(volume);
    delay(200);

  }
  if (forward.isPressed())
  {
    Serial.println("Lauter: volume");
    Serial.println(volume);
    volume++;
    if (volume > MAX_VOLUME)
    {
      volume = MAX_VOLUME;
    }
    myDFPlayer.volume(volume);
    state.setVolume(volume);
    delay(200);

  }

  if (myDFPlayer.available()) {
    uint8_t type = myDFPlayer.readType();
    int value =  myDFPlayer.read();

    Serial.println("___________________________");
    printDetail(type, value); //Print the detail message from DFPlayer to handle different errors and states.
    Serial.println("___________________________");
    Serial.println("Playing somehow Stopped. the reason is:");
    Serial.println(type);
    Serial.println(DFPlayerPlayFinished);
    Serial.println("___________________________");

    //play next song
    if (type == DFPlayerPlayFinished) {
      Serial.println("playNext");
      state.nextTrack();
      myDFPlayer.playFolder(state.getFolder(), state.getTrack());  //play specific mp3 in SD:/15/004.mp3; Folder Name(1~99); File Name(1~255)
    }

    //play first song in folder, as the file is not found
    if (type == DFPlayerError && value == FileMismatch) {
      Serial.println("Cannot Find File and Folder (File, Folder)");
      Serial.println(state.getTrack());
      Serial.println(state.getFolder());
      state.setTrack(state.getFolder());
      state.setFolder(1);
      myDFPlayer.playFolder(state.getFolder(), state.getTrack());  //play specific mp3 in SD:/15/004.mp3; Folder Name(1~99); File Name(1~255)
    }
  }

}




void handleError(uint8_t type, int value) {
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}


void printDetail(uint8_t type, int value) {
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}