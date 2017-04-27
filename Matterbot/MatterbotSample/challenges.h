#pragma once
#include "Matterbot.h"
#include "Md5.h"
#include "Md5Utilities.h"
#include <string>
#include <sstream>
#include <map>
#include <stdint.h>
#include <functional> 
#include <cctype>
#include <locale>
#include <algorithm>
#include <string>
#include <iostream>
#include <ostream>
#include <vector>
#include <thread>
#include <chrono>

namespace lospi
{
	std::string alphabet = "hsoj"; //this is the alphabet
	std::map<Md5Digest, std::string> mymap;
	std::vector<std::string> incomingStringValues;

	struct Challenges : ICommand {
		explicit Challenges(std::shared_ptr<Matterbot> bot) : bot{ bot } { }
		std::wstring get_name() override { return L"challenges"; }

		std::wstring get_help() override { return L"`challenges [MESSAGE]`: `challenge` will start an epic battle in Cybersapce."; }

		std::wstring handle_command(const std::wstring &team, const std::wstring &channel, const std::wstring &user, const std::wstring &command_text) override
		{	
			if (user != L"rivestment")
			{
				return L"Nope.";
			}

			if (mymap.empty() || levelChanged == true)
			{
				createHashMap(level);
				levelChanged = false;
			}

			recieveHashes(command_text);

			if (!mymap.empty())
			{
				bot->post_message(L"rivestment try " + compareHashes());
			}

			_sleep(2000);
			return (L"rivestment challenge " + std::to_wstring(challengeCount));
		}

		void createHashMap(int level)
		{
			int i = level - 1;
			
			std::this_thread::sleep_for(std::chrono::milliseconds(4000));

			for (int i = level - 1; i < level + 10; i++)
			{
				auto combing = Combinator(alphabet, i);
				while (combing.has_next())
				{
					auto next = combing.next();
					std::string salt(next.begin(), next.end());

					std::copy(password.begin(), password.end(), back_inserter(next));

					mymap.emplace(compute_md5(next.data(), next.size()), salt);
					
					hashesBuiltTotal++;
				}
			}
		}

		void recieveHashes(const std::wstring input)
		{
			incomingStringValues.clear();
			char delimiter = ' ';
			std::stringstream ss;
			std::string newInput = wstring_to_string(input);
			ss.str(newInput);
			std::string thing;
			while (std::getline(ss, thing, delimiter))
			{
				incomingStringValues.push_back(thing);
			}
		}

		std::wstring compareHashes()
		{
			std::wstring finalValue;

			for (int i = 0; i < incomingStringValues.size(); i++)
			{
				std::string salt = mymap[get_md5_from_str(string_to_wstring(incomingStringValues[i]))];
				finalValue += string_to_wstring(salt);
				finalValue += string_to_wstring(password);
				if (i < incomingStringValues.size() - 1)
				{
					finalValue += L" ";
				}
			}

			return finalValue;
		}

		private:
			std::shared_ptr<Matterbot> bot;
	};
}