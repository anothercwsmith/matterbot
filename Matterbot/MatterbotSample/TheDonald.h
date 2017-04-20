#pragma once
#include "Matterbot.h"
#include <chrono>
#include <thread>

namespace lospi
{
	struct TheDonald : ICommand {
		std::wstring get_name() override {
			return L"thedonald";
		}

		std::wstring get_help() override {
			return L"`thedonald [MESSAGE]`: `TheDonald` will respond with the last tweet of @realdonaldtrump. It's the best!";
		}

		std::wstring handle_command(const std::wstring &team, const std::wstring &channel,
			const std::wstring &user, const std::wstring &command_text) override {


			system("start C:\\Users\\DOTlaptop\\Documents\\GitHub\\matterbot\\Matterbot\\MatterbotSample\\gettweet.ps1\"");
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));


			return command_text;
		}
	};
}
#pragma once
