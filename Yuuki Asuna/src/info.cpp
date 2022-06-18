// Project include
#include "../commands/handler.h"
#include "../commands/ping.h"

// Dpp include
#include <dpp/fmt/format.h>

void info_h(dpp::cluster& client, const dpp::slashcommand_t& event)
{
	/* ------------------- I still making it, please wait ------------------- */

	// The info command will be used menu system, we have a lot of info!
	dpp::message content("Select a category you'd like to know");

	// Add component
	content.add_component(
		dpp::component().add_component(
			dpp::component().set_type(dpp::cot_selectmenu)
			.set_placeholder("Select one")
			.add_select_option(
				dpp::select_option(
					"About me",
					"about",
					"About Yuuki Asuna"
				))
			.add_select_option(
				dpp::select_option(
					"Avatar and Username",
					"avatar_username",
					"Information about Asuna avatar and username"
				))
			.add_select_option(
				dpp::select_option(
					"Asuna status",
					"status",
					"Show Asuna working status"
				))
			.add_select_option(
				dpp::select_option(
					"Commands",
					"commands",
					"Commands usage and permission from Asuna"
				))
			.add_select_option(
				dpp::select_option(
					"Invite & Support",
					"invite_support",
					"Invite link and support server"
				))
			.add_select_option(
				dpp::select_option(
					"Guilds & Shards",
					"guilds_shards",
					"Guilds and shards detail"
				))
			.add_select_option(
				dpp::select_option(
					"Source code",
					"source_code",
					"Github link for Asuna source code"
				))

			/* Vote is now not supported because haven't done
			
			.add_select_option(
				dpp::select_option(
					"Vote",
					"vote",
					"Vote for Asuna!"
				))
			.set_id("information")

			*/
		)
	);

	// Reply a message with the content
	event.reply(
		content.set_flags(dpp::m_ephemeral)
	);
	
	// Put while testing (delete soon)
	client.on_select_click([&client](const dpp::select_click_t& event) {
		event.reply(
			dpp::message()
			.set_flags(dpp::m_ephemeral)
			.set_content("You clicked " + event.custom_id + " and chose: " + event.values[0])
		);

		// Interaction reply check
		fmt::print(
			"[running] info command - selection replied from {}\n",
			event.command.usr.format_username()
		);
		});


	/* ---------------------------------------------------------------------- */

	// Interaction reply check
	fmt::print(
		"[running] info command replied from {}\n",
		event.command.usr.format_username()
	);
}