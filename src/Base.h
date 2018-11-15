#ifndef BASE_H
#define BASE_H
#include <string>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdio.h>
#include <bits/stdc++.h>
#include <vector>
#include <sstream>

using namespace std;

class Base {
  public:
  std::string cmd;
  Base *left, *right;
  bool isSuccessful;
  
  public:
    Base() {}
    Base(std::string cmd) : cmd(cmd) {} 
    virtual bool execute() = 0;
};
#endif
