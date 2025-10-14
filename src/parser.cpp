#include "parser.h"
#include <sstream>
#include <vector>
#include <iostream>
using namespace std;
Command parse_line(const string& line){
  istringstream iss(line);
  vector<string> tokens;
  string token;

  while(iss >> token){
    tokens.push_back(token);
  }

  Command final_command;
  if(tokens.empty()){
    return final_command;
  }

  auto current_simple_cmd = SimpleCommand();

  for(size_t i=0;i<tokens.size();++i){
    const auto& current_token = tokens[i];
    if(current_token == ">"){
      final_command.redirection = RedirectionType::TRUNCATE;
      if(i + 1 <tokens.size()){
        final_command.outputFile = tokens[++i];
      }
    }else if(current_token == ">>"){
      final_command.redirection = RedirectionType::APPEND;
      if(i+1 < tokens.size()){
        final_command.outputFile = tokens[++i];
      }
    }else if(current_token == "<"){
      if(i + 1 <tokens.size()){
        final_command.inputFile = tokens[++i];
      }
    }else if(current_token == "&"){
      final_command.background = true;
    }else if(current_token == "|"){
      if(!current_simple_cmd.executable.empty()){
        final_command.commands.push_back(current_simple_cmd);
        current_simple_cmd = SimpleCommand();
      }
    }else{
      if(current_simple_cmd.executable.empty()){
        current_simple_cmd.executable = current_token;
      }
      current_simple_cmd.arguments.push_back(current_token);
    }
  }
if(!current_simple_cmd.executable.empty()){
  final_command.commands.push_back(current_simple_cmd);
}
return final_command;
}
