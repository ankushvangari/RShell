#ifndef COMMAND_H
#define COMMAND_H

class Command : public Base {

  public:
  Command() : Base() {}
  Command(std::string cmd) : Base(cmd) {}
  bool execute() {
    vector<char*> commands;
    stringstream ss(cmd);
    string str;
    char *ca;
    
    str = cmd.substr(0, cmd.find(' '));
    ca = new char[str.size()];
    strcpy(ca, str.c_str());
    commands.push_back(ca);
    
    if (cmd.find(' ') != string::npos) {
      str = cmd.substr(cmd.find(' ') + 1);
      ca = new char[str.size()];
      strcpy(ca, str.c_str());
      commands.push_back(ca);
    }
    commands.push_back(NULL);
    
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
      if (waitpid(pid, 0, 0) == -1) {
	perror("Child Wait Fail");
	return false;
      }
    }
    else {
	perror("Fork Failed");
	return false;
    }

    return true;
/*
    pid_t child = fork();
    
    if (child < 0) {
	perror("Internal Error: Cannot fork.");
	return false;
    }
    else if (child == 0) {
	char *argv = new char(cmd.size()-1);
	strcpy(argv, cmd.c_str());
	execvp(argv[0], argv);
	perror(cmd);
	return false;
    }
    else {
	if (waitpid(child, 0, 0) < 0) {
	  perror("Internal error: cannot wait for child");
	  return false;
	}
    }*/
  }

};
#endif
