#pragma once
#include "../mcp.h"
#include "../../global.h"
#include "../../tools.h"
#include "tokensys.h"

namespace api {

	void Init() {

		server.Get("/party/api/v1/Fortnite/user/(.*)", [](const auto& req, auto& res) {

			res.set_content(R"({"current":[],"pending":[],"invites":[],"pings":[]})", "application/json");
			});


		server.Get("/account/create/(.*)", [](const auto& req, auto& res) {

			json response = json::parse("{}");
			string code = token::createlogin(req.matches[1]);
			response["loginCode"] = code;
			response["msgVars"] = "Account created!";
			if (code.empty())
				response["msgVars"] = "An account with this username already exists";

			res.set_content(response.dump(), "application/json");
			});

		server.Post("/account/api/oauth/token", [](const auto& req, auto& res) {

			json response = json::parse("{}");

			if (req.get_param_value("grant_type") == "exchange_code") {
				string exchange = req.get_param_value("exchange_code");
				string name = token::associatename(exchange);

				if (!name.empty()) {
					response["access_token"] = "access_token";
					response["account_id"] = exchange;
					response["app"] = "fortnite";
					response["client_id"] = "ec684b56687f493fadea3cb2fe83f5c6";
					response["client_service"] = "fortnite";
					response["displayName"] = name;
					response["expires_at"] = "2030-01-01T23:59:59.999Z";
					response["expires_in"] = 300000;
					response["in_app_id"] = exchange;
					response["internal_client"] = true;
					response["refresh_expires_at"] = "2030-01-01T23:59:59.999Z";
					response["refresh_expires"] = 300000;
					response["refresh_token"] = exchange;
					response["token_type"] = "bearer";
				} else
					response = tools::throwerror("Invalid login, user does not exist.", 404, "fortnite | api", "User not found");
			}
			if (req.get_param_value("grant_type") == "client_credentials") {

				response["access_token"] = "access_token";
				response["client_id"] = "ec684b56687f493fadea3cb2fe83f5c6";
				response["client_service"] = "fortnite";
				response["expires_at"] = "2030-01-01T23:59:59.999Z";
				response["expires_in"] = 300000;
				response["internal_client"] = true;
				response["token_type"] = "bearer";
			}

			res.set_content(response.dump(), "application/json");
			});
	}
}
