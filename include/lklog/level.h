#pragma once

#include <cstddef>
#include <cstdint>

namespace lklog {
    enum class level : std::uint8_t
    {
        trace,
        debug,
        info,
        warn,
        error,
        fatal
    };

}