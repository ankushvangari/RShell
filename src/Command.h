#ifndef COMMAND_H
#define COMMAND_H

class Command : public Base {

  public:
  Command() : Base() {}
  Command(std::string cmd) : Base(cmd) {}
  bool execute() {
    int status;

    vector<char*> commands;
    stringstream ss(cmd);
    string str;
    char *ca;
    
    //Break up command
    str = cmd.substr(0, cmd.find(' '));
    ca = new char[str.size()];
    strcpy(ca, str.c_str());
    commands.push_back(ca);
    if (str == "exit")
	exit(0);

    //Break up command with arguments
    if (cmd.find(' ') != string::npos) {
      str = cmd.substr(cmd.find(' ') + 1);
      ca = new char[str.size()];
      strcpy(ca, str.c_str());
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

    return !WEXITSTATUS(status);
  }

};
#endif
