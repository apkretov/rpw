#include "events.h"
using std::string;
using namespace mtqc;
#include "constants.h"
using namespace mtqc::constants;

events::events() : cintOnSendTransaction_keyPressedOperationInt(gintOperationNull) {}

/*inline*/ bool events::getSrvMessageToQuik() const { 
	return cblnSrvMessageToQuik; 
} 

inline void events::setSrvMessageToQuik(bool blnSetSrvMessageToQuik) { 
	cblnSrvMessageToQuik = blnSetSrvMessageToQuik; 
}  

/*inline*/ string events::getSrvMessageToQuik_message() const { 
	return cstrSrvMessageToQuik_message; 
} 

//LESSON #5: MOVE SEMANTICS 
//Passing objects to functions efficiently @ https://mbevin.wordpress.com/2012/11/20/move-semantics/ 
inline void events::setSrvMessageToQuik_message(string strSrvMessageToQuik_strMessage) { 
	cstrSrvMessageToQuik_message = move(strSrvMessageToQuik_strMessage); 
} 

/*inline*/ bool events::getTableNotificationCallback() const { 
	return cblnTableNotificationCallback; 
} 

inline void events::setTableNotificationCallback(bool blnTableNotificationCallback) { 
	cblnTableNotificationCallback = blnTableNotificationCallback; 
} 

/*inline*/ int events::getTableNotificationCallback_msg() const { 
	return cintTableNotificationCallback_msg; 
} 

void events::setTableNotificationCallback_msg(int intTableNotificationCallback_msg) { 
	cintTableNotificationCallback_msg = intTableNotificationCallback_msg; 
} 

/*inline*/ int events::getTableNotificationCallback_par2() const { 
	return cintTableNotificationCallback_par2; 
} 

inline void events::setTableNotificationCallback_par2(int intTableNotificationCallback_par2) { 
	cintTableNotificationCallback_par2 = intTableNotificationCallback_par2; 
} 

/*inline*/ bool events::getOnAllTrade() const { 
	return cblnOnAllTrade; 
} 

/*inline*/ void events::setOnAllTrade(bool blnOnAllTrade) { 
	cblnOnAllTrade = blnOnAllTrade; 
} 

/*inline*/ bool events::getOnSendTransaction() const { 
	return cblnOnSendTransaction; 
} 

inline void events::setOnSendTransaction(bool blnOnSendTransaction) { 
	cblnOnSendTransaction = blnOnSendTransaction; 
} 

/*inline*/ bool events::getOnSendTransaction_opening() const { 
	return cblnOnSendTransaction_opening; 
} 

inline void events::setOnSendTransaction_opening(bool blnOnSendTransaction_opening) { 
	cblnOnSendTransaction_opening = blnOnSendTransaction_opening; 
} 

/*inline*/ bool events::getOnSendTransaction_closing() const { 
	return cblnOnSendTransaction_closing; 
} 

inline void events::setOnSendTransaction_closing(bool blnOnSendTransaction_closing) { 
	cblnOnSendTransaction_closing = blnOnSendTransaction_closing; 
} 

/*inline*/ bool events::getOnSendTransaction_keyPressedOperation() const { 
	return cblnOnSendTransaction_keyPressedOperation; 
} 

inline void events::setOnSendTransaction_keyPressedOperation(bool blnOnSendTransaction_keyPressedOperation) { 
	cblnOnSendTransaction_keyPressedOperation = blnOnSendTransaction_keyPressedOperation; 
} 

/*inline*/ int events::getOnSendTransaction_keyPressedOperationInt() const { 
	return cintOnSendTransaction_keyPressedOperationInt; 
} 

void events::setOnSendTransaction_keyPressedOperationInt(int intOnSendTransaction_keyPressedOperationInt) { 
	cintOnSendTransaction_keyPressedOperationInt = intOnSendTransaction_keyPressedOperationInt; 
} 

/*inline*/ bool events::getOnSendTransaction_keyPressedOperationResumed() const { 
	return cblnOnSendTransaction_keyPressedOperationResumed; 
} 

inline void events::setOnSendTransaction_keyPressedOperationResumed(bool blnOnSendTransaction_keyPressedOperationResumed) { 
	cblnOnSendTransaction_keyPressedOperationResumed = blnOnSendTransaction_keyPressedOperationResumed; 
} 

/*inline*/ bool events::getOnTransReply() const {
	return cblnOnTransReply; 
} 

/*inline*/ void events::setOnTransReply(bool blnOnTransReply) { 
	cblnOnTransReply = blnOnTransReply; 
} 

void events::srvMessageToQuik_reset() { 
	setSrvMessageToQuik_message("");
	setSrvMessageToQuik(false); //Reset the event parameters first and then the flag to prevent resetting those of a new event.
}

void events::tableNotificationCallback_reset() { 
	setTableNotificationCallback_msg(0);
	setTableNotificationCallback_par2(0);
	setOnSendTransaction_keyPressedOperationResumed(false);
	setTableNotificationCallback(false); //Reset the event parameters first and then the flag to prevent resetting those of a new event.
}

void events::OnSendTransaction_reset() { 
	setOnSendTransaction_opening(false);
	setOnSendTransaction_closing(false);
	setOnSendTransaction_keyPressedOperation(false);
	setOnSendTransaction_keyPressedOperationInt(gintOperationNull);
	setOnSendTransaction_keyPressedOperationResumed(false);
	setOnSendTransaction(false); //Reset the event parameters first and then the flag to prevent resetting those of a new event.
}
