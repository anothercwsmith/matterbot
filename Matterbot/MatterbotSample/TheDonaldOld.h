#pragma once
#include "Matterbot.h"

#include <cpprest/http_client.h>
#include <cpprest/filestream.h>

#include <cpprest/http_listener.h>              // HTTP server
#include <cpprest/json.h>                       // JSON library
#include <cpprest/uri.h>                        // URI library

#include <cpprest/containerstream.h>            // Async streams backed by STL containers
#include <cpprest/interopstream.h>              // Bridges for integrating Async streams with STL and WinRT streams
#include <cpprest/rawptrstream.h>               // Async streams backed by raw pointer to memory
#include <cpprest/producerconsumerstream.h>     // Async streams for producer consumer scenarios

using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams
using namespace web::http::oauth2::experimental;

using namespace web::http::experimental::listener;          // HTTP server

using namespace web::json;                                  // JSON library

namespace lospi
{
	struct TheDonald : ICommand {
		std::wstring get_name() override {
			return L"thedonald";
		}

		std::wstring get_help() override {
			return L"`thedonald [MESSAGE]`: `TheDonald` will respond with the last tweet of @realdonaldtrump. It's the best!";
		}

		std::wstring handle_command(const std::wstring &team, const std::wstring &channel,
			const std::wstring &user, const std::wstring &command_text) override {
			utility::string_t redirect_uri(U("https://0acae3f2.ngrok.io:80"));
			utility::string_t listener_uri(U("https://0acae3f2.ngrok.io:9001"));
			oauth2_config m_oauth2_config(U("R0D0Uy7HDzk6MDnO6rhWnIp6C"), /* Your live App key*/
				U("4xf7uhmilW4Pm6sxMAsThchUbpKlJcAn4WTMlosBuDQvKNQeyV"), /* Your live App secret*/
				U("https://api.twitter.com/oauth/authorize"), /* Authorization endpoint*/
				U("https://api.twitter.com/oauth/access_token"), /* Token endpoint */
				redirect_uri); /* Redirect URI */

				auto auth_uri = m_oauth2_config.build_authorization_uri(false);  /* Get the authorization uri */

				http_listener m_listener(listener_uri);

				m_listener.support([&](http_request request) -> void
				{
					m_oauth2_config.token_from_redirected_uri(request.request_uri()).then([&]() -> void
					{
						auto token = m_oauth2_config.token().access_token(); // Get the access token
					});
					request.reply(status_codes::OK, U("Ok."));
				});
				m_listener.open().wait();

				http_client_config http_config;
				http_config.set_oauth2(m_oauth2_config);
				http_client client(U("https://api.twitter.com/1.1/"), http_config);
				client.request(methods::GET, U("search/tweets.json?q=%40realdonaldtrump")).wait();

				http_request request(methods::GET);
				
				request.body();
				
				auto response = client.request(request).get();
				std::wstringstream ss;

				ss << response.body();

				return ss.str();
		}
	};
}
#pragma once