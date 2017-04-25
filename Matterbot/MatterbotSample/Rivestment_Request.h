#pragma once
#include "Matterbot.h"
#include "Md5.h"
#include "Md5Utilities.h"

namespace lospi
{

	struct Request : ICommand {
		std::wstring get_name() override {
			return L"request";
		}

		std::wstring get_help() override {
			return L"`request [MESSAGE]`: `password` will request and recieve a password from rivestment.";
		}

		std::wstring handle_command(const std::wstring &team, const std::wstring &channel,
			const std::wstring &user, const std::wstring &command_text) override {

			return 0;
		}
	};
}