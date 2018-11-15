#ifndef OR_H
#define OR_H

class Or : public Connector {
  public:
    Or() : Connector() {}
    Or(string str) : Connector(str) {}
 
    bool execute() {
	return (left->execute() || right->execute());
    }
};
#endif
