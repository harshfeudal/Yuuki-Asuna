// Project include
#include "../commands/handler.h"
#include "../commands/kick.h"

// Dpp include
#include <dpp/fmt/format.h>

void kick_h(dpp::cluster& client, const dpp::slashcommand_t& event)
{
	// Target a user mentioned and make a reason
	auto target_user = event.get_parameter("member");
	auto target_reason = event.get_parameter("reason");

	// Guild find and get the guild ID
	auto* guild_find = dpp::find_guild(event.command.guild_id);

	// If the interaction location is not a guild
	if (!guild_find)
	{
		event.reply(
			dpp::message()
			.set_flags(dpp::m_ephemeral)
			.set_content("You cannot use this command outside the server")
		);
	}
	else if (guild_find)
	{
		// Check permission: if they don't have KICK_MEMBERS permission
		if (!(guild_find->base_permissions(&event.command.usr).has(dpp::p_kick_members)))
		{
			event.reply(
				dpp::message()
				.set_flags(dpp::m_ephemeral)
				.set_content("You have lack of permission to kick :(")
			);
		}
	}

	// Confirmation button
	dpp::message kick_confirm("Do you want to kick? Press the button below to confirm");

	kick_confirm.add_component(
		dpp::component()
		.add_component(
			dpp::component()
			.set_label("Kick")
			.set_type(dpp::cot_button)
			.set_style(dpp::cos_danger)
			.set_id("kick_id")
		).add_component(
			dpp::component()
			.set_label("Cancel")
			.set_type(dpp::cot_button)
			.set_style(dpp::cos_secondary)
			.set_id("cancel_id")
		)
	);

	// Check if we have reason or not
	if (std::holds_alternative<std::string>(target_reason))
	{
		reason = std::get<std::string>(target_reason);
	}
	else
	{
		reason = "No kick reason provided";
	}

	event.reply(
		kick_confirm.set_flags(dpp::m_ephemeral)
	);

	// Interaction reply check
	fmt::print(
		"[running] kick command replied from {}\n",
		event.command.usr.format_username()
	);
}

/*
		Note:
			- It's still under-construction!
			- Role check is still under process!
			- I decide to make button too, since we need to confirm that they want to kick,
			not a mistake.
			- To avoid NULL pointer, I have make `if (guild_find) to prevent
			NULL pointer warning.
			- For more information about this way, please head up to:
			https://docs.microsoft.com/en-us/cpp/code-quality/c6011?view=msvc-170

		Thanks!
*/

/*
		- I got an error:
			1. ] ERROR: Error 40060 [Interaction has already been acknowledged.] on API request, 
			returned content was: {"message": "Interaction has already been acknowledged.", "code": 40060}
*/