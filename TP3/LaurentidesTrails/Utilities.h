#pragma once

#include <iostream>
#include <vector>

using namespace std;

void splitByWhitespace(string s, vector<string>& ss) {
	size_t pos = 0;
	string token, delimiter = " ";
	while ((pos = s.find(delimiter)) != std::string::npos) {
		token = s.substr(0, pos);
		ss.push_back(token);
		s.erase(0, pos + delimiter.length());
	}
	if (s != "") {
		ss.push_back(s);
	}
}