#include "Matterbot.h"
#include <chrono>
#include <thread>
#include <json/json.h>
#include <fstream>
#include "Md5Utilities.h"

using namespace lospi;

std::wstring TheDonald::handle_command(const std::wstring &team, const std::wstring &channel,
	const std::wstring &user, const std::wstring &command_text) {


	system("start C:\\Users\\DOTlaptop\\Documents\\GitHub\\matterbot\\Matterbot\\MatterbotSample\\gettweet.ps1\"");
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	std::ifstream twitter_file("tweet.json", std::ifstream::binary);
	Json::Value message;
	twitter_file >> message;
	auto msg = message["text"];
	auto messageText = string_to_wstring(msg.asString());

	return messageText;
}