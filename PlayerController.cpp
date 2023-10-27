#include "PlayerController.h"

#define DEFAULT_RX_PIN 10
#define DEFAULT_TX_PIN 11


PlayerController::PlayerController()
: _mySoftwareSerial(DEFAULT_RX_PIN, DEFAULT_TX_PIN) {}

PlayerController::PlayerController(DFRobotDFPlayerMini player, PersistanceState state, int rxPin, int txPin)
: _mySoftwareSerial(rxPin, txPin , false) {
  _player = player;
  _state = state;
  _mySoftwareSerial.begin(9600);
  

}

void PlayerController::setup(){

  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  delay(1000);

  // Try to establish a connection
  while (!_player.begin(_mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    delay(2000);
  }

  Serial.println(F("Player communication works."));
  

  Serial.println(F("Setting Timout"));
  _player.setTimeOut(500); //Set serial communictaion time out 500ms

  Serial.println(F("Set EQ"));
  _player.EQ(DFPLAYER_EQ_NORMAL);

  Serial.println(F("Set output Device"));
  _player.outputDevice(DFPLAYER_DEVICE_SD);

  Serial.println(F("start playing current track"));
  _player.playFolder(_state.getFolder(), _state.getTrack());

  Serial.println(F("Settings all set, ready to go."));

}
void PlayerController::loop() {
   
  if (_player.available()) {
    uint8_t type = _player.readType();
    int value =  _player.read();

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
      _state.nextTrack();
      _player.playFolder(_state.getFolder(), _state.getTrack());  //play specific mp3 in SD:/15/004.mp3; Folder Name(1~99); File Name(1~255)
    }

    //play first song in folder, as the file is not found
    if (type == DFPlayerError && value == FileMismatch) {
      Serial.println("Cannot Find File and Folder (File, Folder)");
      Serial.println(_state.getTrack());
      Serial.println(_state.getFolder());
      _state.setTrack(_state.getFolder());
      _state.setFolder(1);
      _player.playFolder(_state.getFolder(), _state.getTrack());  //play specific mp3 in SD:/15/004.mp3; Folder Name(1~99); File Name(1~255)
    }
  }

}

void PlayerController::handleError(uint8_t type, int value) {
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


void PlayerController::printDetail(uint8_t type, int value) {
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