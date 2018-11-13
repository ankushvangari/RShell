#include "Base.h"
#include <vector>
#include <string>

using namespace std;

class User {
  vector<Base*> inputs;
  string userName;
  string input;

  User() {}
  User(string uN) : userName(uN) {}

  void run() {
    cout << "$";
    while (cin >> input) {
	if (input == "||")
	
	else if (input == "&&") {

	}
	else if (input == ";") {

	}
	else {
	  inputs.push_back(Base(input));
	}
    }
  }
}
