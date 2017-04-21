#pragma once
#include "Matterbot.h"
#include <chrono>
#include <thread>
#include "json.hpp"
#include <fstream>
#include "Md5Utilities.h"

namespace lospi
{
	struct TheDonald : ICommand {
		std::wstring get_name() override {
			return L"thedonald";
		}

		std::wstring get_help() override {
			return L"`thedonald [MESSAGE]`: `TheDonald` will respond with the last tweet of @realdonaldtrump. It's the best!";
		}

		std::string remove_html(std::string buf) {
			// assuming 'buf' contains your to-be-stripped html
			char *newbuf = new char[buf.size()];
			int len = buf.size();
			int j = 0;
			// scan string
			for (int i = 0; i<len; i++)
			{
				// found an open '<', scan for its close
				if (buf[i] == '<')
				{
					// charge ahead in the string until it runs out or we find what we're looking for
					for (; i<len && buf[i] != '>'; i++);
				}
				else
				{
					newbuf[j++] = buf[i];
				}
			}
			newbuf[j] = 0;
			buf = newbuf;
			delete[] newbuf;
			return buf;
		}

		std::wstring handle_command(const std::wstring &team, const std::wstring &channel,
			const std::wstring &user, const std::wstring &command_text) override {


			system("python C:\\Users\\DOTlaptop\\Documents\\GitHub\\matterbot\\Matterbot\\MatterbotSample\\tweet.py\"");
			std::this_thread::sleep_for(std::chrono::milliseconds(3000));

			std::ifstream twitter_file("tweet.json", std::ifstream::binary);
			
			std::string JSON(std::istreambuf_iterator<char>(twitter_file), {});

			using json = nlohmann::json;
			
			auto text = json::parse(JSON);
			//std::string handle = text["screen_name"];
			std::string quote = text["text"];
			std::string time = text["created_at"];
			std::string device = text["source"];

			device = remove_html(device);

			//auto screenameString = string_to_wstring(handle);
			auto quoteString = string_to_wstring(quote);
			auto timeString = string_to_wstring(time);
			auto deviceString = string_to_wstring(device);

			auto finalString = L"@realDonaldTrump: \"" + quoteString + L"\"" + L"\nTweeted at: " + timeString +L" \tUsing: " + deviceString;

			return finalString;
		}
	};
}
#pragma once
