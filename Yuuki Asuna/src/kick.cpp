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
#pragma region constructing

	// ...

#pragma endregion
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