#ifndef USER_H
#define USER_H

#include <unistd.h>
#include <limits.h>
#include "Base.h"
#include "Connector.h"
#include "Command.h"
#include "And.h"
#include "Or.h"
#include "Semicolon.h"
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
  Connector * makeConnector(string str) {
    if (str == "&&") {
	return new And();
    }
    if (str == "||") {
        return new Or();
    }
    if (str == ";") {
        return new Semicolon();
    }
    return 0;
  }

  public:
  User() {}
  User(string uN) : userName(uN) {}
  
  void run() {
    char hostname[HOST_NAME_MAX];
    char username[LOGIN_NAME_MAX];
    gethostname(hostname, HOST_NAME_MAX);
    getlogin_r(username, LOGIN_NAME_MAX);
    
    cout << username << "@" << hostname << "$ " ;
    string line, l, r, str;
    Base *t, *left;
    getline(cin, line);
    stringstream ss(line);

    while (!ss.eof() && ss >> str && str.at(str.size() - 1) != ';' && !isConnector(str))
	l += str + ' ';
    if (!str.empty() && str.size() > 1 && str.at(str.size() - 1) == ';') {
	str.erase(str.size() - 1);
	l += str + ' ';
	str = ";";
    }
    
    if (!l.empty())
      l.erase(l.size() - 1);
    if (!isConnector(str)) {
      (new Command(l))->execute();
      return ;
    }
    t = makeConnector(str);

    while (!ss.eof() && ss >> str && str.at(str.size() - 1) != ';' && !isConnector(str))
	r += str + ' ';
    if (!str.empty() && str.size() > 1 && str.at(str.size() - 1) == ';') {
	str.erase(str.size() - 1);
	r += str + ' ';
	str = ";";
    }
    if (!r.empty())
      r.erase(r.size()-1);
    t->left = new Command(l);
    t->right = new Command(r);
    inputs.push_back(t);

    while (true) {
	r.clear();
	if (ss.eof()) break;
	if (isConnector(str)) {
	  t = makeConnector(str);
	  while (!ss.eof() && ss >> str && str.at(str.size() - 1) != ';' && !isConnector(str)) {
	    r += str + ' ';
	  }
	  if (!str.empty() && str.size() > 1 && str.at(str.size()-1) == ';') {
	    str.erase(str.size() - 1);
	    r += str + ' ';
	    str = ";";
	  }
          if (!r.empty())
	    r.erase(r.size()-1);
	  t->left = inputs.at(inputs.size()-1);
	  t->right = new Command(r);
	  inputs.push_back(t);
	}
    }

   //cout << inputs.size(); 
   inputs.at(inputs.size()-1)->execute();
  }
};
#endif
