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
#include <sys/stat.h>
#include <boost/algorithm/string.hpp>
#include <fcntl.h>

using namespace std;

class Base {
  public:
  std::string cmd;
  Base *left, *right;
  bool isSuccessful;
  
  public:
    Base() : left(0), right(0) {}
    Base(std::string cmd) : cmd(cmd), left(0), right(0) {} 
    virtual bool execute() = 0;
};
#endif
