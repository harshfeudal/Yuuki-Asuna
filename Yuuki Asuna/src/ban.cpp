// Project include
#include "../commands/handler.h"
#include "../commands/ban.h"

// Dpp include
#include <dpp/fmt/format.h>

void ban_h(dpp::cluster& client, const dpp::slashcommand_t& event)
{
	// Target a user mentioned, make reason and prune day
	auto target_user = event.get_parameter("member");
	auto target_reason = event.get_parameter("reason");
	auto purgeDay = event.get_parameter("day");
	user_targeted = std::get<dpp::snowflake>(target_user);

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
		// Check permission: if they don't have BAN_MEMBERS permission
		if (!(guild_find->base_permissions(&event.command.usr).has(dpp::p_kick_members)))
		{
			event.reply(
				dpp::message()
				.set_flags(dpp::m_ephemeral)
				.set_content("You have lack of permission to kick :(")
			);
		}
	}

	// Check if we have reason or not
	if (std::holds_alternative<std::string>(target_reason))
	{
		reason = std::get<std::string>(target_reason);
	}
	else
	{
		reason = "No kick reason provided";
	}

	// Confirmation button
	dpp::message ban_confirm("Do you want to ban? Press the button below to confirm");

	ban_confirm.add_component(
		dpp::component()
		.add_component(
			dpp::component()
			.set_label("Ban")
			.set_type(dpp::cot_button)
			.set_style(dpp::cos_danger)
			.set_id("ban_id")
		).add_component(
			dpp::component()
			.set_label("Cancel")
			.set_type(dpp::cot_button)
			.set_style(dpp::cos_secondary)
			.set_id("cancel_id")
		)
	);

	event.reply(
		ban_confirm.set_flags(dpp::m_ephemeral)
	);

	client.on_button_click([&client](const dpp::button_click_t& event) {
		if (event.custom_id == "ban_id")
		{
			// Provide reason audit log
			client.set_audit_reason(reason);

			// Ban member
			// client.guild_ban_add();

			// Announce when banned
			std::string ban_content = fmt::format("<@{}> has been banned!", user_targeted);

			// Reply when got banned
			event.reply(
				dpp::interaction_response_type::ir_update_message,
				dpp::message()
				.set_flags(dpp::m_ephemeral)
				.set_content(ban_content)
			);

			// Interaction reply check
			fmt::print(
				"[running] ban command - ban button replied from {}\n",
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
				"[running] ban command - cancel button replied from {}\n",
				event.command.usr.format_username()
			);
		}
		});

	// Interaction reply check
	fmt::print(
		"[running] ban command replied from {}\n",
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