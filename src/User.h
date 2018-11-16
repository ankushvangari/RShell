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
 
  bool run(string line) {    
    string l, r, str;
    Base *t, *left;

    stringstream ss(line);
    inputs.clear();

    //Get first command
    while (ss >> str && !str.empty() && str.at(0) != '#' 
	    && str.at(str.size() - 1) != ';' && !isConnector(str))
      l += str + ' ';
    
    //Return if comment found
    if (str.empty() || str.at(0) == '#')
	return false;

    //Semicolon edge case (With/without space)
    if (!str.empty() && str.size() > 1 && str.at(str.size() - 1) == ';') {
        str.erase(str.size() - 1);
        l += str + ' ';
        str = ";";
    }

    if (!l.empty())
      l.erase(l.size() - 1);

    if (!isConnector(str) || !(ss >> r) || r.at(0) == '#') {
      Command *c = new Command(l);
      bool b  = c->execute();
   cout << b << endl; 
return b;
      return (new Command(l))->execute();
    }

    r += ' ';
    t = makeConnector(str);
    str = r; 
    //Get first command to the right of first connector
    while (ss >> str && str.at(0) != '#' &&str.at(str.size() - 1) != ';' && !isConnector(str))
        r += str + ' ';

    //Stop and run command up to comment if found
    if (!str.empty() && str.at(0) == '#') {
	return (new Command(r))->execute();
    }

    //Semicolon edge case
    if (!str.empty() && str.size() > 1 && str.at(str.size() - 1) == ';') {
        str.erase(str.size() - 1);
        r += str + ' ';
        str = ";";
    }

    if (!r.empty())
      r.erase(r.size()-1);

    //Create command with appropriate left/right and add to vector (Creating tree)
    t->left = new Command(l);
    t->right = new Command(r);
    inputs.push_back(t);

    //Continue process till end of input
     while (!ss.eof() && isConnector(str)) {
        r.clear();
          t = makeConnector(str);
          while (!ss.eof() && ss >> str && str.at(0) != '#' && str.at(str.size() - 1) != ';' && !isConnector(str)) {
            r += str + ' ';
          }
	  if (!str.empty() && str.at(0) == '#') {
	    if (!r.empty())
	      r.erase(r.size() - 1);
	    t->left = inputs.at(inputs.size() - 1);
	    t->right = new Command(r);
	    inputs.push_back(t);
	    break;
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
   
  return inputs.at(inputs.size() - 1)->execute();
  }
 
  void run() {
    char hostname[HOST_NAME_MAX];
    char username[LOGIN_NAME_MAX];
    gethostname(hostname, HOST_NAME_MAX);
    getlogin_r(username, LOGIN_NAME_MAX);

    cout << username << "@" << hostname << "$ " ;
    string line;
    
    while(getline(cin, line)) {
      if (!line.empty() && line.at(0) == '#') 
	return;

      if (!line.empty())
	run(line); 
      cout << username << "@" << hostname << "$ ";
    }
  }
};
#endif
