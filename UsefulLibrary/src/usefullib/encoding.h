/*
 * encoding.h
 *
 *  Created on: Jun. 18, 2020
 *      Author: Michel
 */

#ifndef USELIB_ENCODING_H_
#define USELIB_ENCODING_H_

#include <string>
#include <vector>

namespace UsefulLibrary {
    /**
    * @namespace Encoding
    *
    *
    */
	namespace Encoding {
		/**
		 * Accepts a string as the first argument, then splits it by the delimiter.
		 *
		 * @param const std::string& - The string to split
		 * @param char delimiter - The char that is used to split the string
		 * @param std::vector<std::string>& - The list to store the elems in.
		 *
		 * @return void
		 */
		void explode(const std::string&, char delimiter, std::vector<std::string> &out);
        /**
		 * Accepts a string as the first argument, then splits it by the delimiter. The only difference
		 * between this function and the non-`r` version: This one returns the vector instead.
		 *
		 * @param const std::string& - The string to split
		 * @param char delimiter - The char that is used to split the string
		 *
		 * @return std::vector<std::string> - The list of split strings.
		 */
		std::vector<std::string> explode_r(const std::string&, char delimiter = ';');
        /**
		 * Returns true if the given string ends with the char.
		 *
		 * @param const std::string&
		 * @param char comparator
		 *
		 * @return bool
		 */
		bool ends_with_c(const std::string&, char code);
		/**
		 * Returns true if the given string ends with the string.
		 *
		 * @param const std::string&
		 * @param const std::string&
		 *
		 * @return bool
		 */
		bool ends_with_s(const std::string&, const std::string);
        /**
		 * Returns true if the given string begins with the char.
		 *
		 * @param const std::string&
		 * @param char comparator
		 *
		 * @return bool
		 */
		bool starts_with_c(const std::string&, char code);
		/**
		 * Returns true if the given string begins with the string.
		 *
		 * @param const std::string&
		 * @param const std::string&
		 *
		 * @return bool
		 */
		bool starts_with_s(const std::string&, const std::string);
        /**
		 * Appends a string to another string only if the input string does not end with the char.
		 *
		 * @param const std::string& - The string
		 * @param char comparator - The char to check
		 * @param const std::string& - The string to append
		 *
		 * @return std::string - The new string
		 */
		std::string append_if_not(const std::string&, char, const std::string&);
        /**
		 * Prepends a string in front of the input string only if the input does not begin with the char.
		 *
		 * @param const std::string& - The string
		 * @param char comparator - The char to check
		 * @param const std::string& - The string to append
		 *
		 * @return std::string - The new string
		 */
		std::string prepend_if_not(const std::string&, char, const std::string&);
	}
}

#endif /* USELIB_ENCODING_H_ */
