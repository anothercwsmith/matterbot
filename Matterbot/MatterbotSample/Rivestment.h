#pragma once
#include "Matterbot.h"
#include "Md5.h"
#include "Md5Utilities.h"

namespace lospi
{
	struct Rivestment : ICommand {
		std::wstring get_name() override {
			return L"rivestment";
		}

		std::wstring get_help() override {
			return L"`rivestment [MESSAGE]`: `rivestment` will start an epic battle in Cybersapce.";
		}

		//step 1 - Command handler command_text wstring
		std::wstring handle_command(const std::wstring &team, const std::wstring &channel,
			const std::wstring &user, const std::wstring &command_text) override {
			
			//declares and initialized variable to store size of string
			auto inputStringSize = 0;
			
			//step 2 - wstring_toString -> string
			auto modifiedString = wstring_to_string(command_text);
			
			//step 3 - c_str() -> char*, size() -> unsigned_int
			char* modifiedStringTwo = std::strcpy(modifiedStringTwo, modifiedString.c_str());

			inputStringSize = modifiedString.size();

			//step 4 - compute_Md5 (char*, unsinged_int -> Md5Digest
			auto stringDigest = compute_md5(modifiedStringTwo, inputStringSize);

			//step 5 - get_str_from_Md5 -> wstring
			auto returnString = get_str_from_md5(stringDigest);

			return command_text;
		}
	};
}