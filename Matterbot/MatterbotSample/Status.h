#pragma once
#include "Matterbot.h"
#include "Md5.h"
#include "Md5Utilities.h"
#include <string>
#include <sstream>

namespace lospi
{
	long unsigned int hashesBuiltTotal  = 0;
	long unsigned int toBuild;
	long unsigned int left;

	struct Status : ICommand {
		explicit Status(std::shared_ptr<Matterbot> bot) : bot{ bot } { }
		std::wstring get_name() override { return L"status"; }

		std::wstring get_help() override { return L"`status`: `status` gives the user a status update."; }

		std::wstring handle_command(const std::wstring& team, const std::wstring& channel,
			const std::wstring& user, const std::wstring& command_text) override {
			
			toBuild = calcHashTotal(level);

			left = toBuild - hashesBuiltTotal;
			double prct = ((double)hashesBuiltTotal / toBuild) * 100.00;
			std::string response = "```Hashes built: ";
			response += std::to_string(hashesBuiltTotal);
			response += "\nBuilding:     ";
			response += std::to_string(toBuild);
			response += "\nLeft:         ";
			response += std::to_string(left);
			response += "\nPercent:      ";
			response += std::to_string(prct);
			response += "%```";
			return string_to_wstring(response);
		}

		int calcHashTotal(int level = 1) {
			int total = 0;
			for (int i = level - 1; i < level + 10; i++) {
				total += (int)pow(4, i);
			}
			return total;
		}
	private:
		std::shared_ptr<Matterbot> bot;
	};
}