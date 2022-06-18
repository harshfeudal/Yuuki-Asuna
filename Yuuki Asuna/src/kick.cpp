// Project include
#include "../commands/handler.h"
#include "../commands/kick.h"

// Dpp include
#include <dpp/fmt/format.h>

void kick_h(dpp::cluster& client, const dpp::slashcommand_t& event)
{
	// Target a user mentioned
	auto target_user = event.get_parameter("member");
	dpp::snowflake user_targeted = std::get<dpp::snowflake>(target_user);

	// Making reason
	auto target_reason = event.get_parameter("reason");
	std::string reason = std::get<std::string>(target_reason);

	// Guild find and get the guild ID
	auto guild_find = dpp::find_guild(event.command.guild_id);
	dpp::snowflake guild_target = event.command.guild_id;
	
	/*
		Note:
		- Permission will be checked using Dpp system,
		I no need to make a single check like Discord.js
		- It's still under-construction!
		
		Thanks!
	*/

	/* ------------------- I still making it, please wait ------------------- */

	if (guild_find->base_permissions(&event.command.usr).has(dpp::p_kick_members))
	{
		client.set_audit_reason(reason);
		client.guild_member_kick(guild_target, user_targeted);

		// Remake the reply section

		// Reply when got kicked
		event.reply(
			dpp::message()
			.set_flags(dpp::m_ephemeral)
			.set_content("kicked!")
		);
	}

	/* ---------------------------------------------------------------------- */	

	// Interaction reply check
	fmt::print(
		"[running] kick command replied from {}\n",
		event.command.usr.format_username()
	);
}