// Project include
#include "../commands/deploy_commands.h"

// Building slash commands
std::map<std::string, cmd_def> commands
{
	// Inspired JSON style, remember the name is lowercase
	{
		"ping", { "Check Asuna latecy", ping_h }
	},
	{
		"info", { "Show more information about Asuna bot :>", info_h }
	},
	{
		"kick",
			{
				"Asuna will kick a member you mentioned", kick_h,
				{
					dpp::command_option(
						dpp::co_mentionable,
						"member",
						"Mention a member to kick",
						true
					),
					dpp::command_option(
						dpp::co_string,
						"reason",
						"Reason why they got kick",
						false
					)
				}
			}
	},
	{
		"ban",
			{
				"Asuna will ban a member you mentioned", ban_h,
				{
					dpp::command_option(
						dpp::co_mentionable,
						"member",
						"Mention a member to ban",
						true
					),
					dpp::command_option(
						dpp::co_string,
						"reason",
						"Reason why they got ban",
						false
					)
	/*
		dpp::command_option(
			dpp::co_integer,
			"day",
			"Purge their messages within 7 days",
			false
		)
	*/
				}
			}
	}
};