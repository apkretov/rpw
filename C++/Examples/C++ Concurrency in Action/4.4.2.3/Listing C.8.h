#pragma once

#include "Listing C.2.h"
#include "Listing C.3.h"
#include "Listing C.4.h"
#include "Listing C.6.h"
#include "messaging_config.h"

class bank_machine {
	messaging::receiver incoming;
	unsigned balance;
public:
	bank_machine() : balance(199) {}
	void done() { get_sender().send(messaging::close_queue()); }

	void run() {
		try {
			for (;;) {
				incoming.wait()
					MSG_HANDLE(verify_pin, [&](verify_pin const& msg) {
						if (msg.pin == "1937") {
							msg.atm_queue.send(pin_verified());
						} else {
							msg.atm_queue.send(pin_incorrect());
						}
					})
					MSG_HANDLE(withdraw, [&](withdraw const& msg) {
						if (balance >= msg.amount) {
							msg.atm_queue.send(withdraw_ok()); balance -= msg.amount;
						} else {
							msg.atm_queue.send(withdraw_denied());
						}
					})
					MSG_HANDLE(get_balance, [&](get_balance const& msg) {
						msg.atm_queue.send(::balance(balance));
					})
					MSG_HANDLE(withdrawal_processed, [&](withdrawal_processed const& msg) {})
					MSG_HANDLE(cancel_withdrawal, [&](cancel_withdrawal const& msg) {});
			}
		}
		catch (messaging::close_queue const&) {}
	}

	messaging::sender get_sender() { return incoming; }
};
