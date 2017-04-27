#pragma once
#include "Matterbot.h"
#include "Md5.h"
#include "Md5Utilities.h"
#include <string>
#include <sstream>

namespace lospi
{
	int challengeCount = 0;


	struct Chal : ICommand {
		explicit Chal(std::shared_ptr<Matterbot> bot) : bot{ bot } { }
		std::wstring get_name() override { return L"chal"; }

		std::wstring get_help() override { return L"`chal [MESSAGE]`: `chal` will do \"Huge\" things."; }

		std::wstring handle_command(const std::wstring &team, const std::wstring &channel, const std::wstring &user, const std::wstring &command_text) override
		{
			if (user != L"anothercwsmith") {
				return L"I am sorry Dave. I must kill you now.";
			}

			bot->post_message(L"rivestment challenge " + command_text);

			challengeCount = std::stoi(command_text);
			
			return L"Confirmation Message: Your current challenge number is " + std::to_wstring(challengeCount);
		}
	private:
		std::shared_ptr<Matterbot> bot;
	};
}