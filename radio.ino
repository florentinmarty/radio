#include "Arduino.h"

#include "DFRobotDFPlayerMini.h"
#include "ButtonController.h"
#include "PlayerController.h"

DFRobotDFPlayerMini player;

const int nrButtons = 9;
ButtonController buttonControllers[nrButtons];

PersistanceState state = PersistanceState();
PlayerController playerController = PlayerController(player, state, 10, 11);

void setup()
{
  // Pin 2 is used to power the mosfet for the DFPlayer. Probably not necessary. Could only be always on. 
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);

  Serial.begin(9600);


  playerController.setup();

  // Configruatation of the buttons.
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

}

void loop()
{
  // loop over all buttons
  for (int i = 0; i < nrButtons; i++) {
        buttonControllers[i].loop();
    }

  playerController.loop();

}
