#pragma once

class token {

	static json getaccountarray() {

		ifstream accounts(workdir + "/accounts.json");
		string t((std::istreambuf_iterator<char>(accounts)),
			std::istreambuf_iterator<char>());
		json accountarray = json::parse(t);
		return accountarray;
	}

	static void writeaccountarray(json newarray) {

		ofstream accounts(workdir + "/accounts.json");
		accounts << newarray.dump();
	}

	static string createcode(int length = 32) {

		std::string temp;
		static const char alphanum[] =
			"0123456789"
			"abcdef";

		srand((unsigned)time(NULL) * getpid());

		temp.reserve(length);

		for (int i = 0; i < length; ++i)
			temp += alphanum[rand() % (sizeof(alphanum) - 1)];


		return temp;
	}

	static string codegen() {

		json accountarray = getaccountarray();
		string code = createcode();
		while (accountarray.contains(code))
			code = createcode();

		return code;
	}

public:
	static string associatename(string code) {

		json accountarray = getaccountarray();
		if (accountarray.contains(code))
			return accountarray[code];
		return string();
	}

	static string createlogin(string name) {

		json accountarray = getaccountarray();
		if (strstr(accountarray.dump().c_str(), name.c_str()))
			return string();

		string logincode = codegen();
		accountarray[logincode] = name;
		writeaccountarray(accountarray);

		return logincode;
	}
};
