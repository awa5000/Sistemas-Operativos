#include<iostream>
#include<string>
#include<vector>
#include "command.h"
#include "parser.h"
#include "executor.h"
using namespace std;
void show_prompt(){
  cout<<"mi_shell";
  cout.flush();
}

int main(){
  string line;
  while(true){
    show_prompt();
    if(!getline(cin,line)){
      cout<<endl<<"Saliendo de mi_shell."<<endl;
      break;
    }
    if(line.empty()){
      continue;
    }
    if(line=="salir"){
      break;
    }
    Command command = parse_line(line);
    execute_command(command);
  }
  return 0;
}
