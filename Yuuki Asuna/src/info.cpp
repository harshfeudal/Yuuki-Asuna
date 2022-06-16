// Project include
#include "../commands/handler.h"
#include "../commands/ping.h"

// Dpp include
#include <dpp/fmt/format.h>

void info_h(dpp::cluster& client, const dpp::slashcommand_t& event)
{
	/* ------------------- I still making it, please wait ------------------- */
#pragma region constructing

	// The info command will be used menu system, we have a lot of info!
	client.on_message_create([&client](const dpp::message_create_t& event) {
		dpp::message content(event.msg.channel_id, "this text has a select menu");

		// Add component
		content.add_component(
			dpp::component().add_component(
				dpp::component().set_type(dpp::cot_selectmenu)
					.set_placeholder("Pick something")
					.add_select_option(dpp::select_option("label1", "value1", "description1"))
					.set_id("test")
			)
		);

		// Create a message with the content
		client.message_create(content);
		});

	client.on_select_click([&client](const dpp::select_click_t& event) {
		event.reply("You clicked " + event.custom_id + " and chose: " + event.values[0]);
		});

#pragma endregion
	/* ---------------------------------------------------------------------- */

	// Under-testing if this works (will deleted this command soon)
	event.reply(
		dpp::message()
		.set_flags(dpp::m_ephemeral)
		.set_content("Info is under-construction!")
	);

	// Interaction reply check
	fmt::print(
		"[running] info command replied from {}\n",
		event.command.usr.format_username()
	);
}