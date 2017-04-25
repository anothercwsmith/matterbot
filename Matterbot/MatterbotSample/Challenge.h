#pragma once
#include "Matterbot.h"
#include "Md5.h"
#include "Md5Utilities.h"
#include <sstream>

namespace lospi
{
	struct Challenge : ICommand {
		std::wstring get_name() override {
			return L"challenge";
		}

		std::wstring get_help() override {
			return L"`challenge [MESSAGE]`: `challenge` will start an epic battle in Cybersapce.";
		}

		std::wstring handle_command(const std::wstring &team, const std::wstring &channel,
			const std::wstring &user, const std::wstring &command_text) override {

			return 0;
		}
	};
}