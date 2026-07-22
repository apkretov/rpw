#pragma once

#pragma region MINE

struct message_base {
	virtual ~message_base() = default;
};

template<typename Msg>
struct wrapped_message : message_base {
	explicit wrapped_message(Msg const& c) : contents(c) {}
	Msg contents;
};
#pragma endregion //MINE