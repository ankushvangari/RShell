#ifndef USER_H
#define USER_H

#include <boost/algorithm/string.hpp>
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
#include <algorithm>

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

  vector<Base*> makeTree(string line) {
    string l = "", r = "", str = "";
    Base *t, *left;
    vector<Base*> inpts;
    stringstream ss(line);

    size_t lP = count(line.begin(), line.end(), '(');
    size_t rP = count(line.begin(), line.end(), ')');

    if (lP != rP) {
      cout << "Error: Uneven parentheses" << endl;
      return vector<Base*>();
    }
    if (lP > 0) 
      return parentheses(line);

    //Get first command
    while (ss >> str && !str.empty() && str.at(0) != '#' 
	    && str.at(str.size() - 1) != ';' && !isConnector(str))
      l += str + ' ';
       //Return if comment found
    if (str.empty() || str.at(0) == '#') {
	if (l.empty())
	  return vector<Base*>();
	l.erase(l.size()-1);
	return vector<Base*>{new Command(l)};
    }

    //Semicolon edge case (With/without space)
    if (!str.empty() && str.size() > 1 && str.at(str.size() - 1) == ';') {
        str.erase(str.size() - 1);
        l += str + ' ';
        str = ";";
    }

    if (!l.empty())
      l.erase(l.size() - 1);

    if (!isConnector(str) || ((ss >> r) && r.at(0) == '#')) {
      return vector<Base*>{new Command(l)};
    }
   
    r += ' ';
    t = makeConnector(str);
    str = r; 

    //Get first command to the right of first connector
    while (ss >> str && str.at(0) != '#' && str.at(str.size() - 1) != ';' && !isConnector(str))
        r += str + ' ';

    //Stop and run command up to comment if found
    if (!str.empty() && str.at(0) == '#') {
	return vector<Base*>{(new Command(r))};
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
    if (!l.empty())
      t->left = new Command(l);
    if (!r.empty())
      t->right = new Command(r);
    inpts.push_back(t);

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
	    t->left = inpts.at(inpts.size() - 1);
            if (!r.empty())
	      t->right = new Command(r);
	    inpts.push_back(t);
	    break;
	  }

          if (!str.empty() && str.size() > 1 && str.at(str.size()-1) == ';') {
            str.erase(str.size() - 1);
            r += str + ' ';
            str = ";";
          }
          if (!r.empty())
            r.erase(r.size()-1);
          t->left = inpts.at(inpts.size()-1);
          t->right = new Command(r);
          inpts.push_back(t);
    }
   return inpts;
  }

  //Adapted from https://stackoverflow.com/questions/12752225/how-do-i-find-the-position-of-matching-parentheses-or-braces-in-a-given-piece-of 
  int findClosingParen(string line, int openPos) {
    int closePos = openPos;
    int counter = 1;
    while (counter > 0) {
        char c = line.at(++closePos);
        if (c == '(') {
            counter++;
        }
        else if (c == ')') {
            counter--;
        }
    }
    return closePos;
}

  vector<Base*> parentheses(string line) {
    vector<Base*> l, m, r;
    int closePos, openPos = line.find('(');
    Base *t, *t2;
   
    closePos = findClosingParen(line, openPos);
   
    l = makeTree(line.substr(0, openPos));
    m = makeTree(line.substr(openPos + 1, closePos - openPos - 1));
    r = makeTree(line.substr(closePos + 1));
    
    if (!l.empty() && !m.empty()) {
      t = l.at(l.size() - 1);
      while (t->right)
        t = t->right;
      t->right = m.at(m.size() - 1);
    }
   
    if (!r.empty() && (!m.empty() || !l.empty())) {
      t2 = r.at(r.size() - 1);
      while (t2->left)
        t2 = t2->left;
      t2->left = (m.empty()) ? l.at(l.size() - 1) : m.at(m.size() - 1);;
    }
  
    if (!r.empty())
      return r;

    if (!l.empty())
      return l;

    if (!m.empty())
      return m;
    return vector<Base*>();
  }

  bool run(string line) {    
    size_t lB = std::count(line.begin(), line.end(), '[');
    size_t rB = std::count(line.begin(), line.end(), ']');

    string str = "hi brian";
    
    if (lB != rB) {
      cout << "Uneven brackets" << endl;
      return false; 
    }

    inputs = makeTree(line);

    if (inputs.size() < 1)
      return false;
    return inputs.at(inputs.size() - 1)->execute();
  }
 
  //Keeps getting input and calls other run function with line of commands
  void run() {
    char hostname[HOST_NAME_MAX];
    char username[LOGIN_NAME_MAX];
    gethostname(hostname, HOST_NAME_MAX);
    getlogin_r(username, LOGIN_NAME_MAX);

    cout << username << "@" << hostname << "$ " ;
    string line;
    
    while(getline(cin, line)) {
      //if (!line.empty()) 
	//return;

      if (!line.empty())
	run(line); 
      cout << username << "@" << hostname << "$ ";
    }
  }
};
#endif
