/*
 * UGUIExceptions.cpp
 *
 *  Created on: Aug. 11, 2020
 *      Author: Michel
 */

#include "UGUIExceptions.h"

/*
* Basic Exception
*/
UGUI_Exception::UGUI_Exception(const std::string &errMsg) :
		std::logic_error((errMsg.empty()) ? "An exception of type UGUI_Exception has been raised" : errMsg) {
}
/*
* Unimplemented function exception
*/
UGUI_UnimplementedFunctionCall::UGUI_UnimplementedFunctionCall(const std::string &errMsg) :
		UGUI_Exception(errMsg) {

}
