// Project include
#include "../commands/handler.h"
#include "../commands/userinfo.h"

// Dpp include
#include <dpp/fmt/format.h>

void userinfo_h(dpp::cluster& client, const dpp::slashcommand_t& event)
{
	// Under-construction

	// Interaction reply check
	fmt::print(
		"[running] userinfo command replied from {}\n",
		event.command.usr.format_username()
	);
}