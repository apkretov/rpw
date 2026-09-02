#pragma region MINE
#pragma once

#include <print>

enum class trace_mode { native, simple };

inline const char* trace_mode_label(trace_mode mode) { return mode == trace_mode::native ? "[Native]" : "[Simple]"; }

inline void trace_log(trace_mode mode, const char* tag, const char* detail = nullptr) {
	if (detail != nullptr && detail[0] != '\0')
		std::println("{} {} {}", trace_mode_label(mode), tag, detail);
	else
		std::println("{} {}", trace_mode_label(mode), tag);
}

inline void trace_frame_case(trace_mode mode, int case_num) { std::println("{} [Frame:case-{}]", trace_mode_label(mode), case_num); }

inline void trace_main(trace_mode mode, const char* detail) { trace_log(mode, "[Main]", detail); }

inline void trace_ramp(trace_mode mode, const char* detail) { trace_log(mode, "[Ramp]", detail); }

inline void trace_frame_state_index(trace_mode mode, int resume_state) {
	std::println("{} [Frame:state_index] save resume point -> {}", trace_mode_label(mode), resume_state);
}
#pragma endregion //MINE
