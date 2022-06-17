// Project include
#include "../commands/handler.h"
#include "../commands/ping.h"

// Dpp include
#include <dpp/fmt/format.h>

void info_h(dpp::cluster& client, const dpp::slashcommand_t& event)
{
	/* ------------------- I still making it, please wait ------------------- */

	// The info command will be used menu system, we have a lot of info!
	client.on_message_create([&client](const dpp::message_create_t& event) {
		
		dpp::message content("Please choose a category you'd like to know");

		// Add component
		content.add_component(
			dpp::component().add_component(
				dpp::component().set_type(dpp::cot_selectmenu)
					.set_placeholder("Information categories")
					.add_select_option(
						dpp::select_option(
							"About me", 
							"about", 
							"About this bot"
						))
					.add_select_option(
						dpp::select_option(
							"Avatar and Username", 
							"avatar_username",
							"Information about this bot avatar and username"
						))
					.set_id("information")
			)
		);

		// Create a message with the content
		event.reply(
			content.set_flags(dpp::m_ephemeral)
		);

		});

	/*		Seems like it will be deleted
	
	client.on_select_click([&client](const dpp::select_click_t& event) {
		event.reply("You clicked " + event.custom_id + " and chose: " + event.values[0]);
		});

	*/

	/* ---------------------------------------------------------------------- */

	// Interaction reply check
	fmt::print(
		"[running] info command replied from {}\n",
		event.command.usr.format_username()
	);
}