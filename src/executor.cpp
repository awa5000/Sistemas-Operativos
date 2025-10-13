#include "executor.h"
#include<iostream>
#include<vector>
#include<string>
#include<unistd.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<cstring>
using namespace std;
static void execute_pipe_command(const Command& command);
static char* const* convert_to_c_array(const vector<string>& args);

void execute_command(const Command& command){
  if(command.commands.empty()){
    return;
  }
  if(command.commands.size()>1){
    execute_pipe_command(command);
  else{
    const auto& simple_cmd = command.commands[0];
    if(handle_builtin_command(simple_cmd)){
      return;
    }
    pid_t pid = fork();
    if(pid<0){
      perror("Error en fork()");
      return;
    }
    else if(pid==0){
      setup_redirections(command);
      auto args = convert_to_c_array(simple_cmd.arguments);
      execvp(simple_cmd.executable.c_str(),args);
      perror("Error en execvp()");
      exit(EXIT_FAILURE);
    }else{
      if(!command.background){
        int status;
        waitpid(pid,&status,0);
      }else{
        cout<<"[+] Proceso en segundo plano, PID: "<<pid<<endl;
      }
    }
  }
}
static void execute_pipe_command(const Command& command){
  int num_pipes = command.commands.size() -1;
  vector<int> pipefds(2*num_pipes);

  for(int i=0;i<num_pipes;++i){
    if(pipe(pipefds.data()+i*2)<0){
      perror("Error creando pipe");
      exit(EXIT_FAILURE);
    }
  }
  int cmd_index = 0;
  for(const auto& simple_cmd : command.commands){
    pid_t pid = fork();
    if(pid==0){
      if(cmd_index > 0){
        dup2(pipefds[(cmd_index - 1)*2],STDIN_FILENO);
      }else{
        setup_redirections(command);
      }
      if(cmd_index < num_pipes){
        dup2(pipefds[cmd_index*2+1],STDOUT_FILENO);
      }else{
        setup_redirections(command);
      }
      for(size_t i=0; i<(size_t)(2*num_pipes);++i){
        close(pipefds[i]);
      }
      auto args = convert_to_c_array(simple_cmd.arguments);
      execvp(simple_cmd.executable.c_str(),args);
      perror("Error en execvp() dentro de pipe");
      exit(EXIT_FAILURE);
    }else if(pid < 0){
      perror("Error en fork() para pipe");
      exit(EXIT_FAILURE);
    }
    cmd_index++;
  }
  for(size_t i=0;i<(size_t)(2*num_pipes);++i){
    close(pipefds[i]);
  }
  if(!command.background){
    for(size_t i=0;i<command.commands.size();++i){
      wait(NULL);
    }
  }
}
bool handle_builtin_command(const SimpleCommand& command){
  if(command.executable=="cd"){
    if(command.arguments.size()<2){
      cerr<<"cd: se esperaba un argumento"<<endl;
    }else{
      if(chdir(command.arguments[1].c_str())!=0){
        perror("cd");
      }
    }
    return true;
  }
  if(command.executable == "pwd"){
    char cwd[1024];
    if(getcwd(cwd,sizeof(cwd))!=NULL){
      cout<<cwd<<endl;
    }else{
      perror("pwd");
    }
    return true;
  }
  return false;
}
void setup_redirections(const Command& command){
  if(command.redirection != RedirectionType::NONE){
    int flags = O_WRONLY | O_CREAT;
    flags |= (command.redirection == RedirectionType::TRUNCATE) ? O_TRUNC : O_APPEND;
    int fd_out = open(command.outputFile.c_str(), flags,0666);
    if(fd_out<0){
      perror("Error abriendo archivo de salida");
      exit(EXIT_FAILURE);
    }
    dup2(fd_out,STDOUT_FILENO);
    close(fd_out);
  }
  if(!command.inputFile.empty()){
    int fd_in = open (command.inputFile.c_str(), O_RDONLY);
    if(fd_in<0){
      perror("Error abriendo archivo de entrada");
      exit(EXIT_FAILURE);
    }
    dup2(fd_in,STDIN_FILENO);
    close(fd_in);
  }
}
static char* const* convert_to_c_array(const vector<string>& args){
  char** c_args = new char*[args.size() + 1];
  for(size_t i=0; i<args.size();++i){
    c_args[i] = const_cast<char*>(args[i].c_str());
  }
  c_args[args.size()] = nullptr;
  return c_args;
}
}
