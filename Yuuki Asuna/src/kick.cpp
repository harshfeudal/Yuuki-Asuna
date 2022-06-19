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

	// Check if we have reason or not
	if (std::holds_alternative<std::string>(target_reason)) 
	{
		std::string reason = std::get<std::string>(target_reason);
		client.set_audit_reason(reason);
	}
	else
	{
		std::string reason = "No reason provided";
		client.set_audit_reason(reason);
	}

	// Guild find and get the guild ID
	auto* guild_find = dpp::find_guild(event.command.guild_id);
	dpp::snowflake guild_target = event.command.guild_id;

	// Find the command.usr role
	// auto command_target_user_role = dpp::find_role();
	
	/*
		Note:
			- It's still under-construction!
			- Role check is still under process!
			- I decide to make button too, since we need to confirm that they want to kick,
			not a mistake.
		
		Thanks!
	*/

	/* ------------------- I still making it, please wait ------------------- */

	// Role check is making ...

	// Button is making

	// If the interaction location is not a guild
	if (!guild_find)
	{
		event.reply(
			dpp::message()
			.set_flags(dpp::m_ephemeral)
			.set_content("You cannot use this command outside the server")
		);
	}

	// Check permission: if they don't have KICK_MEMBERS permission
	if (!(guild_find->base_permissions(&event.command.usr).has(dpp::p_kick_members)))
	{
		event.reply(
			dpp::message()
			.set_flags(dpp::m_ephemeral)
			.set_content("You have lack of permission to kick :(")
		);
	}

	client.guild_member_kick(guild_target, user_targeted);

	// Remake the reply section

	// Reply when got kicked
	std::string kick_ephemeral_content = fmt::format("<@{}> has been kicked!", user_targeted);

	event.reply(
		dpp::message()
		.set_flags(dpp::m_ephemeral)
		.set_content(kick_ephemeral_content)
	);

	/* ---------------------------------------------------------------------- */	

	// Interaction reply check
	fmt::print(
		"[running] kick command replied from {}\n",
		event.command.usr.format_username()
	);
}