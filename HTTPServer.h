#ifndef H_HTTPSERVER
#define H_HTTPSERVER

#include <Arduino.h>
#include <Ethernet.h>
#include "Scale.h"
#include "FieldController.h"

class HTTPServer
{
  EthernetServer server = EthernetServer(80);
  
  public:
  void SetGameState(Scale *myScale, FieldController *fieldController);
};

#endif // H_HTTPSERVER
