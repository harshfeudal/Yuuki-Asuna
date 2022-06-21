#pragma once

// Project include
#include "../commands/handler.h"
#include "../commands/ping.h"
#include "../commands/info.h"
#include "../commands/kick.h"
#include "../commands/ban.h"

// Make a declaration
std::map<std::string, cmd_def> commands;