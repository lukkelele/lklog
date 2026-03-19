#pragma once

#include <string>
#include <filesystem>

#include "core.h"

template<>
struct lklog::internal::fmt::formatter<std::filesystem::path> : lklog::internal::fmt::formatter<std::string>
{
    template<typename FormatContext>
    auto format(const std::filesystem::path& input, FormatContext& ctx) const
    {
        return lklog::internal::fmt::format_to(ctx.out(), "{}", input.generic_string());
    }
};

