#ifndef OR_H
#define OR_H

class Or : public Connector {
  public:
    Or() : Connector("||") {}
    Or(string str) : Connector(str) {}
 
    bool execute() {
        if (!left && !right)
          return true;
        if (!left)
          return right->execute();

	return (right) ? (left->execute() || right->execute()) : (left->execute());
    }
};
#endif
