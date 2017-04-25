#pragma once
#include "Matterbot.h"
#include "Md5.h"
#include "Md5Utilities.h"
#include <sstream>

namespace lospi
{
	struct Challenges : ICommand {
		explicit Challenges(std::shared_ptr<Matterbot> bot) : bot{ bot } { }
		std::wstring get_name() override { return L"challenges"; }

		std::wstring get_help() override { return L"`challenges [MESSAGE]`: `challenge` will start an epic battle in Cybersapce."; }

		std::wstring handle_command(const std::wstring &team, const std::wstring &channel, const std::wstring &user, const std::wstring &command_text) override
		{
			bot->post_message(L"rivestment password");
			bot->post_message(L"rivestment level");
			bot->post_message(L"rivestment challenge 1");

			return 0;
		}
	private:
		std::shared_ptr<Matterbot> bot;
	};
}