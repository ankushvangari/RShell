#include <string>

class Base {
  protected:
  std::string cmd;
  Base *left, *right;
  char connector;
  bool isSuccessful;
  
  public:
    Base() {}
    Base(string c, 
    virtual bool execute() = 0;
};
