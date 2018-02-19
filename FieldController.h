#ifndef H_FIELDCONTROLLER
#define H_FIELDCONTROLLER

#include <Arduino.h>
#include <Ethernet.h>
#include "Alliance.h"
#include "HTTPClient.h"

class FieldController {
  IPAddress fieldControllerServer;
  HTTPClient httpClient;
  
  public:
  FieldController(char *ipAddress);
  void updateScale(bool lhsOwnsIt, bool rhsOwnsIt);
  void initializeScaleSettings(Alliance fieldLeftAlliance, Alliance lhs, Alliance rhs, IPAddress ip);
};

#endif // H_FIELDCONTROLLER
