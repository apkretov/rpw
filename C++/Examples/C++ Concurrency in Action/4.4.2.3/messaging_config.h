#pragma once

// Set via project preprocessor definitions, or override here:
//   USE_TEMPLATES=1  — original TemplateDispatcher chain (default)
//   USE_TEMPLATES=0  — concrete chain_dispatcher with explicit handle_* methods
#ifndef USE_TEMPLATES
#define USE_TEMPLATES 0
#endif

#if USE_TEMPLATES
#define MSG_HANDLE(Msg, body) .handle<Msg>(body)
#else
#define MSG_HANDLE(Msg, body) .handle_##Msg(body)
#endif

#include <mutex>

inline std::mutex& messaging_output_mutex() { // Serializes all console output (stdout and stderr) across threads.
	static std::mutex m;
	return m;
}

#ifndef NDEBUG
#include <cstdio>
#define DISPATCH_TRACE(link, where) \
	do { \
		std::lock_guard<std::mutex> _dispatch_trace_lk(messaging_output_mutex()); \
		std::fprintf(stderr, "[dispatch] %s %s chained=%d\n", link, where, chained ? 1 : 0); \
		std::fflush(stderr); \
	} while (0)
#else
#define DISPATCH_TRACE(link, where) ((void)0)
#endif
