#pragma once

// Dpp include
#include <dpp/dpp.h>

// Guild find and get the guild ID
dpp::snowflake guild_target;

// Target a user mentioned
dpp::snowflake user_targeted;

// Making reason
std::string reason;

// Forward declaration
void kick_h(dpp::cluster& client, const dpp::slashcommand_t& event);