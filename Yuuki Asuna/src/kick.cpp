// Project include
#include "../commands/handler.h"
#include "../commands/kick.h"

// Dpp include
#include <dpp/fmt/format.h>

void kick_h(dpp::cluster& client, const dpp::slashcommand_t& event)
{
	// Target a user mentioned
	auto target_user = event.get_parameter("member");

	// Making reason
	auto reason = event.get_parameter("reason");
	
	/*
		Note:
		- Permission will be checked using Dpp system,
		I no need to make a single check like Discord.js
		- It's still under-construction!
		
		Thanks!
	*/

	/* ------------------- I still making it, please wait ------------------- */

	// .has() permission is planning ...

	auto* guild_find = dpp::find_guild(event.command.guild_id);
	if (guild_find->base_permissions(&event.command.usr).has(dpp::p_kick_members))
	{
		// client.guild_member_kick(guild_find, target_user);
		// client.set_audit_reason(reason);
	}

	/*
	Advise code:

	Type 1:
	std::accumulate(guild_member.roles.cbegin(), guild_member.roles.cend(), false, [](bool ret, dpp::role const& role) -> bool {
		return ret || role.has_ban_members();
		}));
	
	Type 2:
	auto* guild = dpp::find_guild(event.command.guild_id);
	if (!guild) { handle uncached guild case }
	if (guild->base_permissions(&event.command.usr).has(dpp::p_ban_members)) {
		
	}
	*/

	/* ---------------------------------------------------------------------- */

	// Under-testing if this works (will deleted this command soon)
	event.reply(
		dpp::message()
		.set_flags(dpp::m_ephemeral)
		.set_content("Under-construction kick command")
	);

	// Interaction reply check
	fmt::print(
		"[running] kick command replied from {}\n",
		event.command.usr.format_username()
	);
}