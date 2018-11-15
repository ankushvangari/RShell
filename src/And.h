#ifndef AND_H
#define AND_H

class And : public Connector {
  public:
    And() : Connector() {}
    And(string str) : Connector(str) {}

    bool evaluate() {
	return (left->evaluate() && right->evaluate());
    }

};
