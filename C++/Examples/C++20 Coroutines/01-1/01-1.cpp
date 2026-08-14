#if 1

#include "connection.h"
#include "database.h"
#include "parsed_request.h"
#include "../../stdafx.h"

Database database;

void handle_request(connection& conn) {
	LogDuration ld("handle_request"); //MINE
	std::string request = conn.read();      // blocks until data arrives
	auto parsed = parse_request(request);
	auto data = database.query(parsed.id);  // blocks until database responds
	auto response = compute_response(data);
	conn.write(response);                   // blocks until write completes
}

int main() {
	print_file_line();

	connection conn;
	handle_request(conn);

	return 0;
}
#endif //1
