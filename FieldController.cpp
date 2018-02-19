#include "FieldController.h"
#include "Utils.h"

FieldController::FieldController(char *ipAddress) {
  fieldControllerServer.fromString(ipAddress);
}

void FieldController::updateScale(bool lhsOwnsIt, bool rhsOwnsIt) {
  char outBuf[64];
  
  sprintf(outBuf, "lhsownsit=%s&rhsownsit=%s", BoolToString(lhsOwnsIt), BoolToString(rhsOwnsIt));

  httpClient.Post(
    fieldControllerServer,
    5000,
    "/api/scale",
    outBuf);
}

void FieldController::initializeScaleSettings(Alliance fieldLeftAlliance, Alliance lhs, Alliance rhs, IPAddress ip) {
  char outBuf[64];
  
  sprintf(outBuf, "FLAlliance=%s&LHSFL=%s&RHSFL=%s&IP=%d.%d.%d.%d", AllianceAsString::Is(fieldLeftAlliance), AllianceAsString::Is(lhs), AllianceAsString::Is(rhs), ip[0], ip[1], ip[2], ip[3]);

  httpClient.Post(
    fieldControllerServer,
    5000,
    "/api/ScaleSettings",
    outBuf);
}

