#pragma once
#pragma once
#include "Matterbot.h"
#include "Md5.h"
#include "Md5Utilities.h"
#include <string>
#include <sstream>

namespace lospi
{
	struct Lvl : ICommand {
		explicit Lvl(std::shared_ptr<Matterbot> bot) : bot{ bot } { }
		std::wstring get_name() override { return L"lvl"; }

		std::wstring get_help() override { return L"`lvl [MESSAGE]`: `lvl` will request and set the rivestment level you want to play."; }

		std::wstring handle_command(const std::wstring &team, const std::wstring &channel, const std::wstring &user, const std::wstring &command_text) override
		{
			bot->post_message(L"rivestment level " + command_text);
			return L"";
		}
	private:
		std::shared_ptr<Matterbot> bot;
	};
}