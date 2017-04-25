#pragma once
#include "Matterbot.h"
#include "Md5.h"
#include "Md5Utilities.h"
#include <string>
#include <sstream>

namespace lospi
{
	std::string alphabet = "hsoj"; //this is the alphabet
	std::map<std::string, std::string> mymap;

	struct Compute : ICommand {
		std::wstring get_name() override {
			return L"compute";
		}

		std::wstring get_help() override {
			return L"`compute [MESSAGE]`: `compute` will start an epic battle in Cybersapce.";
		}

		std::wstring handle_command(const std::wstring &team, const std::wstring &channel,
			const std::wstring &user, const std::wstring &command_text) override {
			
			int i = levelIntValue - 1;

			while (i < levelIntEndValue)
			{
				auto thing = Combinator(alphabet, i);
				while (thing.has_next())
				{
					auto next = thing.next();
					for (auto c : password)
					{
						next.emplace_back(c);
					}
					//next.emplace_back(password);

					auto digest = compute_md5(next.data(), next.size());
					auto hash = get_str_from_md5(digest);
					auto hashStr = wstring_to_string(hash);

					mymap.emplace(hashStr, next.data());
				}
				i++;
			}
			return 0;
		}
	};
}