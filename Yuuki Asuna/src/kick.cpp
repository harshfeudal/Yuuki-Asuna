// Project include
#include "../commands/handler.h"
#include "../commands/kick.h"

// Dpp include
#include <dpp/fmt/format.h>

void kick_h(dpp::cluster& client, const dpp::slashcommand_t& event)
{
	// Guild find and get the guild ID
	auto* guild_find = dpp::find_guild(event.command.guild_id);

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

	event.reply(
		kick_confirm.set_flags(dpp::m_ephemeral)
	);

	// Interaction reply check
	fmt::print(
		"[running] kick command replied from {}\n",
		event.command.usr.format_username()
	);
}

/*--------------------------------------------------------*/

// This function will put in main.cpp file
void kick_button_function_h(dpp::cluster& client, const dpp::slashcommand_t& event)
{
	// Guild find and get the guild ID
	dpp::snowflake guild_target = event.command.guild_id;

	// Target a user mentioned
	auto target_user = event.get_parameter("member");
	dpp::snowflake user_targeted = std::get<dpp::snowflake>(target_user);

	// Making reason
	auto target_reason = event.get_parameter("reason");
	std::string reason;

	// Find the bot position role

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

	

	// Role check is making ...

	// Check if we have reason or not
	if (std::holds_alternative<std::string>(target_reason))
	{
		reason = std::get<std::string>(target_reason);
	}
	else
	{
		reason = "No kick reason provided";
	}

	client.on_button_click([&client, reason, user_targeted, guild_target](const dpp::button_click_t& event) {
		if (event.custom_id == "kick_id")
		{
			// Provide reason audit log
			client.set_audit_reason(reason);

			// Kick member
			client.guild_member_kick(guild_target, user_targeted);

			// Announce when kicked
			std::string kick_content = fmt::format("<@{}> has been kicked!", user_targeted);

			// Reply when got kicked
			event.reply(
				dpp::interaction_response_type::ir_update_message,
				dpp::message()
				.set_flags(dpp::m_ephemeral)
				.set_content(kick_content)
			);

			// Interaction reply check
			fmt::print(
				"[running] kick command - kick button replied from {}\n",
				event.command.usr.format_username()
			);
		}
		else if (event.custom_id == "cancel_id")
		{
			// Announce when cancelled
			std::string cancel_content("Cancelled request!");

			// Reply when cancelled
			event.reply(
				dpp::interaction_response_type::ir_update_message,
				dpp::message()
				.set_flags(dpp::m_ephemeral)
				.set_content(cancel_content)
			);

			// Interaction reply check
			fmt::print(
				"[running] kick command - cancel button replied from {}\n",
				event.command.usr.format_username()
			);
		}
		});
}