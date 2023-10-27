#include "PersistanceState.h"
#include <EEPROM.h>
#define FOLDER_ADRESS 0
#define VOLUME_ADRESS 100

PersistanceState::PersistanceState(){
  
  // The folder number is the adress of the track number. This to save the read and write cycle of the EEPROM
  Serial.println("Ordner aus Speicher: ");
  Serial.println(getFolder());
  
  if(getFolder() > 20){
     Serial.println("WARNUNG, Ordner grösser als es ordner auf der SD Karte hat.Aktueller Ordner wird auf 1 gesetzt. ");
     EEPROM.update(FOLDER_ADRESS, 1);
  } 
  
    Serial.println("Lied für vorhergehenden Ordner aus Speicher: ");
    Serial.println(getTrack());
  
    if(getTrack()> 100) {//_folderAndTrackCount[_folder]){
      Serial.println("WARNUNG, Aktueller Track grösser als es Tracks im Ordner auf der SD Karte hat. Aktueller Track wird auf 1 gesetzt.");
      EEPROM.update(getFolder(), 1);
    
  }
}

PersistanceState::PersistanceState(int folderCount, int folderAndTrackCount[]){

}


void PersistanceState::setFolder(int folder){
    if(folder > 100){
      Serial.println("WARNUNG, Ordner grösser als 100");
    }else{
  
      Serial.println("Set Folder to ");Serial.println(folder );
      EEPROM.update(FOLDER_ADRESS, folder);
      delay(100);
      Serial.println("___________________\n" );
    }
}


void PersistanceState::setTrack(int track){
    if(track > 100){
      Serial.println("WARNUNG, tracknr grösser als 100");
    }else{

      Serial.println("Set track to ");Serial.println(track );Serial.println("___________________\n" );
      EEPROM.update(getFolder(), track);
    }
}

void PersistanceState::nextTrack(){
   
   Serial.println("Next track clicked");
   Serial.println("Current Folder:"); Serial.println(getFolder());
   Serial.println("next track played:"); Serial.println(getTrack()+1);
   EEPROM.update(getFolder(), getTrack() +1);
  
}


int PersistanceState::getFolder(){
    return EEPROM.read(FOLDER_ADRESS);
}


int PersistanceState::getTrack(){
  return EEPROM.read(getFolder());
}

int PersistanceState::getVolume(){
  return EEPROM.read(VOLUME_ADRESS);
}

void PersistanceState::setVolume(int volume){
  Serial.println("set Volume to");
  Serial.println(volume);

  return EEPROM.update(VOLUME_ADRESS, volume);
}

