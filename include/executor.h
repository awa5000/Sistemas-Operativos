#ifndef EXECUTOR_H
#define EXECUTOR_H
#include "command.h"
void execute_command(const Command& command);
void execute_simple_command(const SimpleCommand& command,bool is_background);
bool handle_builtin_command(const SimpleCommand& command);
void setup_redirections(const Command& command);
#endif
