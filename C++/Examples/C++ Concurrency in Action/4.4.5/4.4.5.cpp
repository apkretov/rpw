#pragma region MINE

#include "../../stdafx.h"
#include "Listing 4.22.h"

using namespace std::chrono_literals;

/*
 Few enough chunks that the gathering task also gets a thread straight away: MSVC runs
 std::async on a pool that starts small (four tasks here) and only grows once the threads
 it has are all blocked, which would otherwise keep the gathering task off the CPU until
 the first chunk had already finished.
*/
static constexpr std::size_t item_count = 3 * whatever;

int main() {
	print_file_line();

	say("=== Listing 4.22: gathering results from futures using std::async ===");
	say("{} items, chunk size {} -> {} chunks; chunk k works for {} ms * (k + 1),",
		item_count, whatever, item_count / whatever, chunk_stagger_ms);
	say("so the results become ready one after another instead of all at once.");
	say("");

	std::vector<MyData> vec = make_data(item_count);

	auto pending = process_data(vec);
	gather_start_ms = elapsed_ms(); // when the gatherer was scheduled (≈ when it runs with a free pool slot)
	say("[T{} main] process_data returned at {} ms - the gathering task now owns the chunk futures.",
		thread_label(), elapsed_ms());

	while (pending.wait_for(100ms) != std::future_status::ready)
		say("[T{} main] main thread still free at {} ms", thread_label(), elapsed_ms());

	FinalResult const r = pending.get();

	say("");
	say("chunks = {}, items = {}, sum = {} (expected {})",
		r.chunks, r.items, r.sum, static_cast<long long>(item_count) * (item_count - 1) / 2);
	say("first chunk ready at {} ms, last chunk ready at {} ms, final result at {} ms",
		r.first_ready_ms, r.last_ready_ms, r.finished_ms);
	say("thread T{} ran the gathering task from {} ms to {} ms and blocked {} of {} times at f.get().",
		r.gatherer, gather_start_ms.load(), r.finished_ms, r.waits, r.chunks);
	say("");
	say("Textbook: that one thread is occupied for the whole run and is woken once per chunk,");
	say("so every result costs an extra context switch. std::experimental::when_all (Listing 4.23)");
	say("waits for the whole set at once and schedules the gathering with .then instead.");

	return 0;
}
#pragma endregion // MINE
