#ifndef H_SCALE
#define H_SCALE

#include "Alliance.h"
#include "Plate.h"

enum class GameState { OFF = 0, SETUP = 1, PLAY = 2, STAFFSAFE = 3, SAFE = 4, RANDOMIZE = 5 };

class Scale
{
  // State variables identifying the current state of the switch's switches
  bool lhsOwned;
  bool rhsOwned;
  bool hasChanged;
  
  // State variables identifying which side of the switch is associated to an alliance
  Plate lhsPlate;
  Plate rhsPlate;

  // Hold the alliance of this switch
  Alliance fieldLeftAlliance;

  // Hold the pin locations of the interface hardware
  int lhsSwitchPin;
  int rhsSwitchPin;

  // What is the state of the game?
  GameState gameState;
  
  public:
  Scale(int lhsSwitchPin, int rhsSwitchPin, int lhsLEDPin, int rhsLEDPin);
  void setFieldLeftAlliance(Alliance value);
  Alliance getFieldLeftAlliance();
  Alliance getLHSAlliance();
  Alliance getRHSAlliance();
  void updateState();
  void updatePlates();
  bool stateChanged();
  void acknowledgeStateChanged();
  void randomize();
  GameState getGameState();
  void play();
  void off();
  void safe();
  void staffsafe();
  bool isLHSOwned();
  bool isRHSOwned();
};

#endif // H_SCALE
