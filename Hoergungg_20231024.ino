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
#include "ButtonController.h"

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini player;
void printDetail(uint8_t type, int value);

const int nrButtons = 9;
ButtonController buttonControllers[nrButtons];

Input play;
Input back;
Input forward;
PersistanceState state;

int sensorValue;
int sensorPin;

void setup()
{
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
  mySoftwareSerial.begin(9600);
  Serial.begin(9600);

  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  delay(1000);

  // Try to establish a connection
  while (!player.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    delay(2000);
  }

  Serial.println(F("Player communication works."));

  state = PersistanceState();

  buttonControllers[0] = ButtonController(9, 1, state,  player);
  buttonControllers[1] = ButtonController(12, 2, state,  player);
  buttonControllers[2] = ButtonController(13, 3, state,  player);
  buttonControllers[3] = ButtonController(3, 4, state,  player);
  buttonControllers[4] = ButtonController(4, 5, state,  player);
  buttonControllers[5] = ButtonController(5, 6, state,  player);
  buttonControllers[6] = MediaController(6, state,  player, MediaControl::NEXT_TRACK);
  buttonControllers[7] = MediaController(7, state,  player, MediaControl::PREVIOUS_TRACK);
  buttonControllers[8] = MediaController(8, state,  player, MediaControl::PAUSE_PLAY);

  Serial.println(F("Input folders set"));

  Serial.println(F("Settings all set, ready to go."));

  Serial.println(F("Setting Timout"));
  player.setTimeOut(500); //Set serial communictaion time out 500ms

  Serial.println(F("Set EQ"));
  player.EQ(DFPLAYER_EQ_NORMAL);

  Serial.println(F("Set output Device"));
  player.outputDevice(DFPLAYER_DEVICE_SD);

  Serial.println(F("start playing current track"));
  player.playFolder(state.getFolder(), state.getTrack());

  Serial.println(F("Settings all set, ready to go."));
}

void loop()
{
  // loop over all buttons
  for (int i = 0; i < nrButtons; i++) {
        buttonControllers[i].loop();
    }

  if (player.available()) {
    uint8_t type = player.readType();
    int value =  player.read();

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
      player.playFolder(state.getFolder(), state.getTrack());  //play specific mp3 in SD:/15/004.mp3; Folder Name(1~99); File Name(1~255)
    }

    //play first song in folder, as the file is not found
    if (type == DFPlayerError && value == FileMismatch) {
      Serial.println("Cannot Find File and Folder (File, Folder)");
      Serial.println(state.getTrack());
      Serial.println(state.getFolder());
      state.setTrack(state.getFolder());
      state.setFolder(1);
      player.playFolder(state.getFolder(), state.getTrack());  //play specific mp3 in SD:/15/004.mp3; Folder Name(1~99); File Name(1~255)
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