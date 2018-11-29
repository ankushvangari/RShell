#ifndef COMMAND_H
#define COMMAND_H

class Command : public Base {

  public:
  Command() : Base() {}
  Command(std::string cmd) : Base(cmd) {}

  bool exists(const std::string& name) {
    struct stat buffer;
    return (stat (name.c_str(), &buffer) == 0);
  }

  bool fileExists(const std:: string &name) {
    struct stat buffer;
    if (stat(name.c_str(), &buffer) != 0)
      return false;
    return (buffer.st_mode & S_IFREG);
  }

  bool dirExists(const std::string &name) {
    struct stat buffer;
    if (stat(name.c_str(), &buffer) != 0)
      return false;
    return (buffer.st_mode & S_IFDIR);
  }

  bool testCommand() {
    cmd = cmd.substr(cmd.find(' ') + 1);
    bool b;

    boost::replace_all(cmd, " ]", "");

    if (cmd.at(0) != '-' || cmd.at(1) == 'e') {
      b = exists(cmd.substr(cmd.find(' ') + 1));
      cout  << ((b) ? "(True)" : "(False)");
      cout << endl;
      return b;
    } 
    else if (cmd.at(1) == 'f') {
      b = fileExists(cmd.substr(cmd.find(' ') + 1));
      cout << ((b) ? "(True)" : "(False)");
      cout << endl;
      return b;
    }
    else if (cmd.at(1) == 'd') {
      b = dirExists(cmd.substr(cmd.find(' ') + 1));
      cout << ((b) ? "(True)" : "(False)");
      cout << endl;
      return b;
    }
  }

  bool execute() {
    if (left)
      left->execute();

    int status;

    vector<char*> commands;
    stringstream ss(cmd);
    string str, str2;
    char *ca;
    
    //Break up command
    str = cmd.substr(0, cmd.find(' '));
    ca = new char[str.size()];
    strcpy(ca, str.c_str());
    commands.push_back(ca);
    if (str == "exit")
	exit(0);

    if (str == "test" || str == "[")
	return testCommand(); 
    //Break up command with arguments
    if (cmd.find(' ') != string::npos) {
      str2 = cmd.substr(cmd.find(' ') + 1);
      //boost::replace_all(str2, "briancrites ", "[");
     //if (str != "echo")
       // boost::replace_all(str2, " ]", "");
      //else
       // boost::replace_all(str2, "brian", "");

      ca = new char[str2.size()];
      strcpy(ca, str2.c_str());
      commands.push_back(ca);
    }
    commands.push_back(NULL);

    //Execute commands
    char **cmds	= &commands[0];
    pid_t pid = fork();
    if (pid == 0) {
	if (execvp(cmds[0], cmds) == -1) {
	 perror("Exec Fail");
	  exit(1);
	  return false;
	}
    }    
    else if (pid > 0) {
      do { waitpid(pid, &status, 0); }
      while (WIFEXITED(status) == -1);
/*
      if (waitpid(pid, 0, 0) == -1) {
	perror("Child Wait Fail");
	return false;
      }*/
    }
    else {
	perror("Fork Failed");
	return false;
    }
    
    if (right)
      right->execute();

    return !WEXITSTATUS(status);
  }

};
#endif
