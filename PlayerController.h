#ifndef PLAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include "PersistanceState.h"


class PlayerController{
  public: 
      PlayerController();
      PlayerController(DFRobotDFPlayerMini player, PersistanceState state, int rxPin, int txPin);
      void setup();
      void loop();

  private:
      void printDetail(uint8_t type, int value);
      void handleError(uint8_t type, int value);

      DFRobotDFPlayerMini _player;
      PersistanceState _state;
      SoftwareSerial _mySoftwareSerial;



};

#endif