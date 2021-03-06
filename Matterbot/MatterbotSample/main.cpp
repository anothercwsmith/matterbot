#include "Matterbot.h"
#include <iostream>
#include <sstream>
#include <unordered_map>
#include "ConsoleLogger.h"
#include "EchoCommand.h"
#include "WeatherCommand.h"
#include "ReverseCommand.h"
#include "TheDonald.h"
#include "level.h"
#include "Status.h"
#include "pass.h"
#include "password.h"
#include "chal.h"
#include "challenges.h"
#include "Rivestment_Request.h"

#define ERROR_SUCCESS 0
#define ERROR_FAILURE -1

using namespace std;
using namespace lospi;

int main() {
  wstring mattermost_url = L"https://hooks.slack.com",
    incoming_hook_route = L"services/T4Z1QAKSS/B4ZBTV7HP/Zzk6zaWMGRJdvTb6IyfUfGaU",
    outgoing_hook_route = L"http://127.0.0.1:9005/",
    outgoing_hook_token = L"7mcke6WANSlZrv4Jpdy5vHYo",
    welcome_message = L"Hello Dave.";

  try {
    auto bot = make_shared<Matterbot>(mattermost_url, incoming_hook_route, outgoing_hook_route, outgoing_hook_token);
    bot->set_logger(make_unique<ConsoleLogger>());
    bot->register_command(make_shared<EchoCommand>());
	bot->register_command(make_shared<WeatherCommand>());
	bot->register_command(make_shared<TheDonald>());
	bot->register_command(make_shared<Status>(bot));
	bot->register_command(make_shared<Chal>(bot));
	bot->register_command(make_shared<Challenges>(bot));
	bot->register_command(make_shared<Password>(bot));
	bot->register_command(make_shared<Level>(bot));
	bot->register_command(make_shared<Pass>(bot));
	bot->register_command(make_shared<Request>());
    bot->register_command(make_shared<ReverseCommand>(bot));
    bot->post_message(welcome_message);

    wstring console;
    wclog << ">> Type \'quit\' to quit. Any other input will be sent to the bot." << endl;
    while (getline(wcin, console)) {
      if (L"quit" == console) {
        wclog << ">> Quitting." << endl;
        return ERROR_SUCCESS;
      }
      if (L"" != console) { bot->post_message(console); }
    }
  }

  catch (exception e) {
    wcerr << "[-] Unhandled exception:" << e.what() << endl;
    return ERROR_FAILURE;
  }
}
