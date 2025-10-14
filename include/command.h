#ifndef COMMAND_H
#define COMMAND_H
#include<string>
#include<vector>
using namespace std;
enum class RedirectionType{
  NONE,
  TRUNCATE,
  APPEND
};
struct SimpleCommand{
  string executable;
  vector<string> arguments;
};
struct Command{
  vector<SimpleCommand> commands;
  string inputFile;
  string outputFile;
  RedirectionType redirection = RedirectionType::NONE;
  bool background = false;
};
#endif
