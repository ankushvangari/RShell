#ifndef USER_H
#define USER_H

#include "Base.h"
#include "Connector.h"
#include "Command.h"
#include <vector>
#include <string>
#include <bits/stdc++.h>
#include <sstream>

using namespace std;

class User {
  vector<Base*> inputs;
  string userName;
  string input;
  
  private:
  bool isConnector(string c) { return (c == ";" || c == "&&" || c == "||");}

  public:
  User() {}
  User(string uN) : userName(uN) {}
  
  void run() {
    cout << "$ " ;
    //char *cmds = getInput();
    string line, l, r, str;
    getline(cin, line);
    stringstream ss(line);
    Base *t, *left;

    while (!ss.eof() && ss >> str && !isConnector(str))
	l += str;
    t = new Connector(str);
    while (!ss.eof() && ss >> str && !isConnector(str))
	r += str;
    
    t->left = new Command(l);
    t->right = new Command(r);
    inputs.push_back(t);
    while (true) {
	r.clear();
	if (ss.eof()) break;
	if (isConnector(str)) {
	  t = new Connector(str);
	  while (!ss.eof() && ss >> str && !isConnector(str)) {
	    r += str;
	  }
	  t->left = inputs.at(inputs.size()-1);
	  t->right = new Command(r);
	  inputs.push_back(t);
	}
    }

   cout << inputs.size(); 
   //for (int j = 0; j < inputs.size(); j++)
	inputs.at(inputs.size()-1)->execute();
  }

  char * getInput() {
      string line;
      getline(cin, line);
      char *cmds = new char[line.size()-1];
      strcpy(cmds, line.c_str());
      return cmds;
  }
};
#endif
