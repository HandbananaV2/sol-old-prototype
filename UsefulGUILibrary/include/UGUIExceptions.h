/*
 * UGUIExceptions.h
 *
 *  Created on: Aug. 11, 2020
 *      Author: Michel
 */

#ifndef INCLUDE_UGUIEXCEPTIONS_H_
#define INCLUDE_UGUIEXCEPTIONS_H_

#include <stdexcept>
#include <exception>
#include <stdlib.h>

// Basic Exception
class UGUI_Exception: public std::logic_error {
	public:
		UGUI_Exception(const std::string &errMsg);
};
// Exception used when a function is not used or implemented
class UGUI_UnimplementedFunctionCall: public UGUI_Exception {
	public:
		UGUI_UnimplementedFunctionCall(const std::string&);
};

#endif /* INCLUDE_UGUIEXCEPTIONS_H_ */
