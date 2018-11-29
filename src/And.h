#ifndef AND_H
#define AND_H
//#include "Connector.h"

class And : public Connector {
  public:
    And() : Connector("&&") {}
    And(string str) : Connector(str) {}

    bool execute() {
	return (right) ? (left->execute() && right->execute()) : (left->execute());
    }

};
#endif
