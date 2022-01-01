#pragma once
#include "../global.h"

namespace Other {

	void Init() {

		server.Get("/lightswitch/api/service/bulk/status", [](const auto& req, auto& res) {

			res.set_content(json::parse(R"(
[{
	"serviceInstanceId": "fortnite",
	"status": "UP",
	"message": "Fortnite is online",
	"maintenanceUri": null,
	"overrideCatalogIds": [],
	"allowedActions": ["PLAY", "DOWNLOAD"],
	"banned": false,
	"launcherInfoDTO": {
		"appName": "Fortnite",
		"catalogItemId": "4fe75bbc5a674f4f9b356b5c90567da5",
		"namespace": "fn"
	}
}])").dump(), "application/json");
			});

		server.Get("/socialban/api/public/v1/(.*)", [](const auto& req, auto& res) {

			res.set_content(json::parse(R"({"bans":[],"warnings":[]})").dump(), "application/json");
			});

		server.Get("/fortnite/api/v2/versioncheck/(.*)", [](const auto& req, auto& res) {

			res.set_content(json::parse(R"({"type":"NO_UPDATE"})").dump(), "application/json");
			});

		server.Get("/fortnite/api/storefront/v2/catalog", [](const auto& req, auto& res) {

			res.set_content(json::parse(R"({})").dump(), "application/json"); //item shop
			});

		server.Get("/fortnite/api/storefront/v2/keychain", [](const auto& req, auto& res) { //from 

			json response = json::parse("{}");

			httplib::Client client("");
			auto rawcontent = client.Get("/v1/epic/keychain");
			response = json::parse(rawcontent->body);

			res.set_content(response.dump(), "application/json");
			});

	}
}
