#pragma once
#include "Matterbot.h"
#include "Md5.h"
#include "Md5Utilities.h"

namespace lospi
{
	std::string password = { NULL };

	struct Password : ICommand {
		explicit Password(std::shared_ptr<Matterbot> bot) : bot{ bot } { }
		std::wstring get_name() override { return L"password"; }

		std::wstring get_help() override { return L"";}

		std::wstring handle_command(const std::wstring &team, const std::wstring &channel, const std::wstring &user, const std::wstring &command_text) override
		{
			password = wstring_to_string(command_text);
			auto returnPassword = string_to_wstring(password);

			return L"Confirmation Message: Your password has been set to: " + returnPassword;
		}
	private:
		std::shared_ptr<Matterbot> bot;
	};
}