#pragma once

#pragma region MINE
#include "message_base.h"

namespace messaging {
template<typename Msg> 
struct wrapped_message : message_base {
    explicit wrapped_message(Msg const& contents_) : contents(contents_) {}
    Msg contents;
};
}
#pragma endregion //MINE