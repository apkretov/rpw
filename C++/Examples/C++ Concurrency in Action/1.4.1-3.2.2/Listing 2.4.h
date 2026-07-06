#pragma once

#include <atomic>
#include <print>
#include <string>
#include <thread>

#pragma region MINE
enum command_type { open_new_document, process_some_input };

struct user_command {
	command_type type;
};

std::atomic<bool> new_document_requested(true); 
std::atomic<int> commands_done(0);

user_command get_user_input() { 
	if (new_document_requested.exchange(false)) // On the first call, simulate opening a new document
		return {open_new_document};
	return {process_some_input}; // Otherwise, simulate a generic command
}

std::string get_filename_from_user() { return "new_doc.txt"; } 

void process_user_input(user_command const& cmd) { std::print("Thread {}: Processing input\n", std::this_thread::get_id()); }

void open_document_and_display_gui(std::string const& filename) { std::print("Thread {}: Opening '{}'\n", std::this_thread::get_id(), filename); }

bool done_editing() { return commands_done.fetch_add(1) > 3; }
#pragma endregion //MINE


void edit_document(std::string const& filename) { 
    open_document_and_display_gui(filename);
    while (!done_editing()) {
        user_command cmd = get_user_input();
        if (cmd.type == open_new_document) {
            std::string const new_name = get_filename_from_user();
            std::thread t(edit_document, new_name);
            t.detach();
        } else {
            process_user_input(cmd);
        }
    }
}
