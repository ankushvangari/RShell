#ifndef CONNECTOR_H
#define CONNECTOR_H
#include "Base.h"

class Connector : public Base {
  public:
  Connector() : Base() {}
  Connector(std::string cmd) : Base(cmd) {}
  virtual bool execute() = 0
#endif
