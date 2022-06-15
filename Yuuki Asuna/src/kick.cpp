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

	/* ---------------- Under-construction ----------------
	
	// Set reply connect when kick
	std::string message_content = fmt::format(
		// I'll soon put the target_user, event.command.usr and reason here
		"Asuna has kicked `{}`, requested from `{}` :(\nFor reason: {}"
	);

	// Reply when kick
	event.reply(
		dpp::message()
		.set_content(message_content)
	);

	*/

	// Under-testing if this works (will deleted this command soon)
	event.reply(
		dpp::message()
		.set_flags(dpp::m_ephemeral)
		.set_content("Under-construction")
	);

	// Interaction reply check
	fmt::print(
		"[running] kick command replied from {}\n",
		event.command.usr.format_username()
	);
}