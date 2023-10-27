#ifndef BUTTONCONTROLLER_H
#define BUTTONCONTROLLER_H

#include "Input.h"
#include "PersistanceState.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

const int MAX_VOLUME = 30;

enum MediaControl {
    NEXT_TRACK,
    PREVIOUS_TRACK,
    PAUSE_PLAY
};



class ButtonController{
  public: 
      ButtonController();
      ButtonController(int pin, int folder, PersistanceState state, DFRobotDFPlayerMini player);
      virtual void loop();

  protected:
      PersistanceState _state;
      Input _input;
      int _folder;
      DFRobotDFPlayerMini _player;
};

class MediaController : public ButtonController{
  public: 
      MediaController();
      MediaController(int pin, PersistanceState state, DFRobotDFPlayerMini player, MediaControl action);
      void loop() override;  // Override the loop method to provide a new behavior
  private:
      void adjustVolume(int newVolume);
      MediaControl _action;
      bool _isPaused = false;
      int _volume;    
      

};

#endif