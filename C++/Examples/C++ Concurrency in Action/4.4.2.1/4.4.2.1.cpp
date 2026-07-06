#pragma region MINE
#include "receiver.h"
#include "queue.h"
#include "sender.h"
#include "simulator_components.h"
#include "Listing 4.15.h"
#include "Listing 4.16.h"
#include "../../stdafx.h"
#include <print>
#include <thread>
#include <chrono>

int main() {
	print_file_line();

	using namespace messaging;
    receiver atm_receiver;
    queue bank_queue;
    queue hardware_queue;
    
    sender bank_sender(&bank_queue);
    sender hardware_sender(&hardware_queue);
    sender atm_sender = atm_receiver;

    atm atm_(&atm_receiver, &bank_sender, &hardware_sender);

    std::jthread atm_thread(&atm::run, &atm_);

	std::println("--- Simulating Actor Interaction ---");
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

	std::println("\n[Action] User inserts card...");
    atm_sender.send(card_inserted{"Acc-12345"});
    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    std::println("\n[Action] User presses digits...");
    atm_sender.send(digit_pressed{'1'});
    atm_sender.send(digit_pressed{'2'});
    atm_sender.send(digit_pressed{'3'});
    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    std::println("\n[Action] User clears last digit...");
    atm_sender.send(clear_last_pressed{});
    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    std::println("\n[Action] User inputs remaining digits to complete 4-digit PIN...");
    atm_sender.send(digit_pressed{'3'});
    atm_sender.send(digit_pressed{'4'});

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    atm_thread.detach(); 

    return 0;
}
#pragma endregion //MINE