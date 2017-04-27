#pragma once
#include "Matterbot.h"
#include "Md5.h"
#include "Md5Utilities.h"

namespace lospi
{
	struct Pass : ICommand {
		explicit Pass(std::shared_ptr<Matterbot> bot) : bot{ bot } { }
		std::wstring get_name() override { return L"pass"; }

		std::wstring get_help() override { return L"`pass [MESSAGE]`: `pass` will request and recieve a password from rivestment."; }

		std::wstring handle_command(const std::wstring &team, const std::wstring &channel, const std::wstring &user, const std::wstring &command_text) override
		{
			bot->post_message(L"rivestment password");

			return L"";
		}
	private:
		std::shared_ptr<Matterbot> bot;
	};
}
