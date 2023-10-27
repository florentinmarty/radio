#include "Arduino.h"
#include "SoftwareSerial.h"
#include <Vector.h>

class PersistanceState{
  public: 
      PersistanceState();
      PersistanceState(int folderCount, int folderAndTrackCount[]);
      
      // when setting the folder, the current track is set to 1.
      void setFolder(int folder);
      
      // when there is an error (eg. file not found), then the first track in the folder can be played.
      void setTrack(int track);
      
      // goes to the next track in the current folder. if it is pressed when playing the last track, then it will play the first track.
      void nextTrack();
      
     // goes to the previous track in the current folder. if it is pressed when playing the first track, then it will play the last track in the folder.
      void previousTrack();
      
      // returns the current folder
      int getFolder();
      
      // returns the current track
      int getTrack();
      
      //read the volume
      int getVolume();
      
      // write the volume
      void setVolume(int volume);

  private:
      int _folderCount;
      int _volume;
      int* _folderAndTrackCount;
};