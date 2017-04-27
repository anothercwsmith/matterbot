#pragma once
#include "Matterbot.h"
#include "Md5.h"
#include "Md5Utilities.h"
#include <string>
#include <sstream>

namespace lospi
{
	int level = 1;
	bool levelChanged = false;
	long unsigned int hashesBuiltTotal = 0;
	

	struct Level : ICommand {
		explicit Level(std::shared_ptr<Matterbot> bot) : bot{ bot } { }
		std::wstring get_name() override { return L"level"; }

		std::wstring get_help() override { return L"`level [MESSAGE]`: `level` will request and set the rivestment level you want to play."; }

		std::wstring handle_command(const std::wstring &team, const std::wstring &channel, const std::wstring &user, const std::wstring &command_text) override
		{	
			if (user != L"anothercwsmith") {
				return L"I am sorry Dave. I must kill you now.";
			}

			bot->post_message(L"rivestment level " + command_text);

			level = std::stoi(command_text);
			hashesBuiltTotal = 0;
			levelChanged = true;
			return L"Confirmation Message: Your current level is now " + std::to_wstring(level);
		}
	private:
		std::shared_ptr<Matterbot> bot;
	};
}