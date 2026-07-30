#pragma once

#pragma region MINE
/*
Listing 4.22 is kept close to the book; everything it names but never defines lives here:
MyData, ChunkResult, FinalResult, whatever, process_chunk and gather_results.

The printed gathering lambda omits mutable; the listing adds it so all_results is non-const
and f.get() compiles. begin != end (vs. the book's beg) is the other local fix.

The data is rigged so the weakness the book complains about is visible: each chunk works a
little longer than the one before it, so the results become ready one at a time and the
gathering task has to wake up, take one result, and block again, once per chunk.
*/

#include <algorithm>
#include <atomic>
#include <chrono>
#include <format>
#include <mutex>
#include <print>
#include <thread>
#include <vector>

using Steady = std::chrono::steady_clock;

inline Steady::time_point const run_start = Steady::now();

inline long long elapsed_ms() {
	return std::chrono::duration_cast<std::chrono::milliseconds>(Steady::now() - run_start).count();
}

inline int thread_label() { // Short stable names (T0, T1, ...); thread ids are unwieldy to print.
	static std::atomic<int> next{0};
	thread_local int const label = next++;
	return label;
}

inline std::mutex io_mx;

template <typename... Args>
void say(std::format_string<Args...> fmt, Args&&... args) {
	std::lock_guard<std::mutex> lk(io_mx);
	std::println(fmt, std::forward<Args>(args)...);
}

inline constexpr std::size_t whatever = 125; // the book's placeholder for the chunk size
inline constexpr int chunk_stagger_ms = 150; // chunk k works chunk_stagger_ms * (k + 1)

struct MyData {
	int chunk;   // the chunk this item belongs to, so process_chunk can tell where it is
	int value;
	int work_ms; // how long the whole chunk pretends to work
};

inline std::vector<MyData> make_data(std::size_t items) {
	std::vector<MyData> vec;
	vec.reserve(items);
	for (std::size_t i = 0; i < items; ++i) {
		int const chunk = static_cast<int>(i / whatever);
		vec.push_back(MyData{chunk, static_cast<int>(i), chunk_stagger_ms * (chunk + 1)});
	}
	return vec;
}

inline std::atomic<long long> gather_start_ms{-1}; // when the gathering task was scheduled (set from main)

struct ChunkResult {
	int chunk = -1;
	std::size_t items = 0;
	long long sum = 0;
	int worker = -1;                // thread that ran process_chunk
	long long ready_at_ms = 0;      // when this chunk's future became ready
	long long collected_at_ms = -1; // when the gathering task pulled the value out of that future

	ChunkResult() = default;
	ChunkResult(int c, std::size_t n, long long s, int w, long long ready) : chunk(c), items(n), sum(s), worker(w), ready_at_ms(ready) {}

	ChunkResult(ChunkResult const&) = default;
	ChunkResult& operator=(ChunkResult const&) = default;
	ChunkResult& operator=(ChunkResult&&) = default;

	ChunkResult(ChunkResult&& other) noexcept // The result is move-assigned into the shared state when the chunk finishes, so the first move-construction is f.get() handing the value to the gathering task: the exact moment the book marks with 1 in the listing.
		: chunk(other.chunk), items(other.items), sum(other.sum), worker(other.worker),
		  ready_at_ms(other.ready_at_ms), collected_at_ms(other.collected_at_ms) {
		if (collected_at_ms < 0)
			collected_at_ms = elapsed_ms();
	}
};

inline ChunkResult process_chunk(std::vector<MyData>::iterator first, std::vector<MyData>::iterator last) { // Not a template and not overloaded, so std::async(process_chunk, ...) can deduce it.
	int const chunk = first->chunk;
	std::this_thread::sleep_for(std::chrono::milliseconds(first->work_ms)); // stand-in for real work
	long long sum = 0;
	for (auto it = first; it != last; ++it)
		sum += it->value;
	return ChunkResult(chunk, static_cast<std::size_t>(last - first), sum, thread_label(), elapsed_ms());
}

struct FinalResult {
	std::size_t chunks = 0;
	std::size_t items = 0;
	long long sum = 0;
	long long first_ready_ms = 0;
	long long last_ready_ms = 0;
	long long finished_ms = 0;
	int waits = 0;      // how many chunks were still unfinished when the gathering task reached them
	int gatherer = -1;  // thread that ran the gathering task
};

inline FinalResult gather_results(std::vector<ChunkResult> const& v) {
	FinalResult r;
	r.chunks = v.size();
	r.gatherer = thread_label();

	say("");
	say("  chunk | ran on | ready at | collected at | gathering task");
	say("  ------+--------+----------+--------------+------------------------------");

	long long collected_so_far = gather_start_ms.load(); // The task can only reach a chunk once it is done with the previous one, so it had to block whenever the next chunk was still unfinished at that point.
	for (auto const& c : v) {
		long long const collected = c.collected_at_ms < 0 ? c.ready_at_ms : c.collected_at_ms;
		bool const blocked = c.ready_at_ms > collected_so_far;
		if (blocked)
			++r.waits;

		say("  {:>5} | {:>6} | {:>5} ms | {:>9} ms | {}", c.chunk, std::format("T{}", c.worker),
			c.ready_at_ms, collected, blocked ? "woke up for it after sleeping" : "result was already waiting");

		collected_so_far = collected;
		r.items += c.items;
		r.sum += c.sum;
		r.first_ready_ms = r.first_ready_ms == 0 ? c.ready_at_ms : std::min(r.first_ready_ms, c.ready_at_ms);
		r.last_ready_ms = std::max(r.last_ready_ms, c.ready_at_ms);
	}

	r.finished_ms = elapsed_ms();
	return r;
}
#pragma endregion // MINE
