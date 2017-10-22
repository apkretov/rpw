#pragma once

namespace mtqc {
	
	class events { 
		bool		cblnSrvMessageToQuik{}; //The event flags.
		std::string	cstrSrvMessageToQuik_message;

		bool		cblnTableNotificationCallback{};
		int		cintTableNotificationCallback_msg{};
		int		cintTableNotificationCallback_par2{};

		bool		cblnOnAllTrade{};
	
		bool		cblnOnSendTransaction{};

		bool		cblnOnSendTransaction_opening{};
		bool		cblnOnSendTransaction_closing{};

		bool		cblnOnSendTransaction_keyPressedOperation{};
		int		cintOnSendTransaction_keyPressedOperationInt;
		bool		cblnOnSendTransaction_keyPressedOperationResumed{};

		bool		cblnOnTransReply{};

	public:
		events();
	
		bool getSrvMessageToQuik() const;
		void setSrvMessageToQuik(bool blnSetSrvMessageToQuik); 
	
		std::string getSrvMessageToQuik_message() const;
		void setSrvMessageToQuik_message(/*const std::string&*/std::string strSrvMessageToQuik_strMessage);
	
		bool getTableNotificationCallback() const;
		void setTableNotificationCallback(bool blnTableNotificationCallback);
	
		int getTableNotificationCallback_msg() const;
		void setTableNotificationCallback_msg(int intTableNotificationCallback_msg);
	
		int getTableNotificationCallback_par2() const;
		void setTableNotificationCallback_par2(int intTableNotificationCallback_par2);
	
		bool getOnAllTrade() const;
		void setOnAllTrade(bool blnOnAllTrade);
	
		bool getOnSendTransaction() const;
		void setOnSendTransaction(bool blnOnSendTransaction);
	
		bool getOnSendTransaction_opening() const;
		void setOnSendTransaction_opening(bool blnOnSendTransaction_opening);
	
		bool getOnSendTransaction_closing() const;
		void setOnSendTransaction_closing(bool blnOnSendTransaction_closing);
	
		bool getOnSendTransaction_keyPressedOperation() const;
		void setOnSendTransaction_keyPressedOperation(bool blnOnSendTransaction_keyPressedOperation);
	
		int getOnSendTransaction_keyPressedOperationInt() const;
		void setOnSendTransaction_keyPressedOperationInt(int intOnSendTransaction_keyPressedOperationInt);
	
		bool getOnSendTransaction_keyPressedOperationResumed() const;
		void setOnSendTransaction_keyPressedOperationResumed(bool blnOnSendTransaction_keyPressedOperationResumed);
	
		bool getOnTransReply() const;
		void setOnTransReply(bool blnOnTransReply);
	
		void srvMessageToQuik_reset();
		void tableNotificationCallback_reset();
		void OnSendTransaction_reset();
	};	
}
