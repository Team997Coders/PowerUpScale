#include <Arduino.h>
#include "Scale.h"

Scale::Scale(int lhsSwitchPin, int rhsSwitchPin, int lhsLEDPin, int rhsLEDPin) : lhsPlate(Plate(lhsLEDPin)), rhsPlate(Plate(rhsLEDPin)) {
  // Set local variables for later use
  this->lhsSwitchPin = lhsSwitchPin;
  this->rhsSwitchPin = rhsSwitchPin;

  // Set up pins
  pinMode(lhsSwitchPin, INPUT_PULLUP);
  pinMode(rhsSwitchPin, INPUT_PULLUP);

  gameState = GameState::OFF;
  updateState();
  hasChanged = false;
}

void Scale::setFieldLeftAlliance(Alliance value) {
  fieldLeftAlliance = value;
}

bool Scale::stateChanged() {
  return hasChanged;
}

void Scale::acknowledgeStateChanged() {
  hasChanged = false;
}

bool Scale::isLHSOwned() {
  return lhsOwned;
}

bool Scale::isRHSOwned() {
  return rhsOwned;
}

void Scale::updateState() {
  // HIGH = switch is open
  // LOW = switch is closed (and owned)

  bool lhsWasOwned;
  bool rhsWasOwned;

  lhsWasOwned = lhsOwned;
  rhsWasOwned = rhsOwned;
  
  if (digitalRead(lhsSwitchPin) == LOW) {
    lhsOwned = true;
    rhsOwned = false;
  }

  if (digitalRead(rhsSwitchPin) == LOW) {
    rhsOwned = true;
    lhsOwned = false;  
  }

  // This should never happen and if it does, then no one owns the switch
  if (digitalRead(lhsSwitchPin) == LOW && digitalRead(rhsSwitchPin) == LOW) {
    rhsOwned = false;
    lhsOwned = false;
  }

  if (digitalRead(lhsSwitchPin) == HIGH) {
    lhsOwned = false;
  }

  if (digitalRead(rhsSwitchPin) == HIGH) {
    rhsOwned = false;
  }

  if (lhsWasOwned != lhsOwned || rhsWasOwned != rhsOwned) {
    hasChanged = true;
  }
}

void Scale::updatePlates() {
  if (hasChanged) {
    switch (gameState)
    {
      case GameState::OFF:
        lhsPlate.SolidFullBlack();
        rhsPlate.SolidFullBlack();
        break;
      case GameState::PLAY:
        if (!lhsOwned && !rhsOwned) {
          lhsPlate.SolidFullAllianceColor();
          rhsPlate.SolidFullAllianceColor();
        }
        if (lhsOwned) {
          lhsPlate.PulsingFullAllianceColor();
          rhsPlate.SolidFullAllianceColor();
        }
        if (rhsOwned) {
          lhsPlate.SolidFullAllianceColor();
          rhsPlate.PulsingFullAllianceColor();
        }
        break;
      case GameState::SAFE:
        lhsPlate.SolidFullGreen();
        rhsPlate.SolidFullGreen();
        break;
      case GameState::STAFFSAFE:
        lhsPlate.PulsingFullPurple();
        rhsPlate.PulsingFullPurple();
        break;
      case GameState::RANDOMIZE:
        lhsPlate.SolidFullAllianceColor();
        rhsPlate.SolidFullAllianceColor();
        break;
    }
  }
  lhsPlate.Update();
  rhsPlate.Update();
}

void Scale::randomize() {
  int randomizer;

  gameState = GameState::RANDOMIZE;
  hasChanged = true;

  randomizer = random(0, 2);
  if (randomizer == 1)
  {
    lhsPlate.SetAlliance(Alliance::RED);
    rhsPlate.SetAlliance(Alliance::BLUE);
  }
  else
  {
    rhsPlate.SetAlliance(Alliance::RED);
    lhsPlate.SetAlliance(Alliance::BLUE);
  }
  Serial.print(F("LHS = "));
  Serial.print(AllianceAsString::Is(lhsPlate.GetAlliance()));
  Serial.print(F("; RHS = "));
  Serial.println(AllianceAsString::Is(rhsPlate.GetAlliance()));
}

Alliance Scale::getFieldLeftAlliance() {
  return fieldLeftAlliance;
}

Alliance Scale::getLHSAlliance() {
  return lhsPlate.GetAlliance();
}

Alliance Scale::getRHSAlliance() {
  return rhsPlate.GetAlliance();
}

void Scale::play() {
  gameState = GameState::PLAY;
  hasChanged = true;
}

void Scale::off() {
  gameState = GameState::OFF;
  hasChanged = true;
}

void Scale::safe() {
  gameState = GameState::SAFE;
  hasChanged = true;
}

void Scale::staffsafe() {
  gameState = GameState::STAFFSAFE;
  hasChanged = true;
}

GameState Scale::getGameState() {
  return gameState;
}

