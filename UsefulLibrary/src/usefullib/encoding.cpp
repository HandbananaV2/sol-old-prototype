/*
 * encoding.cpp
 *
 *  Created on: Jun. 18, 2020
 *      Author: Michel
 */

#include "encoding.h"
#include <sstream>
#include <string>
#include <stdio.h>
/*
 *
 */
void UsefulLibrary::Encoding::explode(const std::string &allocator, char delimiter, std::vector<std::string> &out) {
	std::stringstream ss(allocator);
	std::string line = "";

	while (std::getline(ss, line, delimiter)) {
		out.push_back(line);
	}
}
/*
 *
 */
std::vector<std::string> UsefulLibrary::Encoding::explode_r(const std::string &allocator, char delimiter) {
	std::vector<std::string> tmp;

	UsefulLibrary::Encoding::explode(allocator, delimiter, tmp);

	return tmp;
}
/*
 *
 */
bool UsefulLibrary::Encoding::ends_with_c(const std::string &allocator, char code) {
	if (allocator.empty())
		return false;

	return (allocator.at(allocator.length() - 1) == code);
}
/*
 *
 */
bool UsefulLibrary::Encoding::ends_with_s(const std::string &allocator, const std::string allocator1) {
	if ((allocator.empty() || allocator1.empty()) || allocator1.length() >= allocator.length())
		return false;

	return (allocator.substr(allocator.length() - allocator1.length()) == allocator1);
}
/*
 *
 */
bool UsefulLibrary::Encoding::starts_with_c(const std::string &allocator, char code) {
	if (allocator.empty())
		return false;

	return allocator[0] == code;
}
/*
 *
 */
bool UsefulLibrary::Encoding::starts_with_s(const std::string &allocator, const std::string allocator1) {
	if ((allocator.empty() || allocator1.empty()) || allocator1.length() >= allocator.length())
		return false;

	return (allocator.substr(0, allocator1.length()) == allocator1);
}
/*
 *
 */
std::string UsefulLibrary::Encoding::append_if_not(const std::string &allocator, char char1, const std::string &allocator1) {
	if (!ends_with_c(allocator, char1))
		return allocator + allocator1;
	else
		return allocator;
}
/*
 *
 */
std::string UsefulLibrary::Encoding::prepend_if_not(const std::string &allocator, char char1, const std::string &allocator1) {
	if (!starts_with_c(allocator, char1))
		return allocator1 + allocator;
	else
		return allocator;
}
