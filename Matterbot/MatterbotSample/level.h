#pragma once
#include "Matterbot.h"
#include "Md5.h"
#include "Md5Utilities.h"
#include <string>
#include <sstream>

namespace lospi
{
	std::string level = { NULL };
	int levelIntValue = 0;
	std::string levelEnd = { NULL };
	int levelIntEndValue = 0;

	struct Level : ICommand {
		std::wstring get_name() override {
			return L"level";
		}

		std::wstring get_help() override {
			return L"`level [MESSAGE]`: `level` will request and set the rivestment level you want to play.";
		}

		std::wstring handle_command(const std::wstring &team, const std::wstring &channel,
			const std::wstring &user, const std::wstring &command_text) override {
			
			level = wstring_to_string(command_text);

			levelIntValue = std::stoi(level);

			levelIntEndValue = levelIntValue + 10;

			levelEnd = std::to_string(levelIntEndValue);

			auto levelEndWString = string_to_wstring(levelEnd);
			
			return levelEndWString;
		}
	};
}