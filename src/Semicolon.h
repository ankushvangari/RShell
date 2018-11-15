#ifndef SEMICOLON_H
#define SEMICOLON_H

class Semicolon :public Connector {
  public:
    Semicolon() : Connector() {}
    Semicolon(string str) : Connector(str) {}

    bool execute() {
	left->execute();
	return right->execute();
    }
};
#endif
