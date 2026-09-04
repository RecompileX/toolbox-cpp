#pragma once

#include <algorithm>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>

namespace toolbox {
namespace detail {

template <typename T>
inline bool parseLine(const std::string& line, T& value) {
    if constexpr (std::is_same_v<T, std::string>) {
        value = line;
        return true;
    } else {
        std::istringstream stream(line);
        stream >> value;
        stream >> std::ws;
        return !stream.fail() && stream.eof();
    }
}

template <typename T>
inline bool isWithinBounds(
    const T& value,
    const std::optional<T>& min,
    const std::optional<T>& max
) {
    return (!min || value >= *min) && (!max || value <= *max);
}

} // namespace detail

template <typename T = std::string>
inline T getln(
    std::string_view variableName,
    std::optional<T> min = std::nullopt,
    std::optional<T> max = std::nullopt
) {
    if (min && max && *min > *max) {
        std::swap(*min, *max);
    }

    for (;;) {
        std::cout << variableName << ": ";

        std::string line;
        if (!std::getline(std::cin, line)) {
            throw std::ios_base::failure("toolbox::getln could not read input");
        }

        T value{};
        if (!detail::parseLine(line, value)) {
            std::cout << "Invalid " << variableName << ". Try again.\n";
            continue;
        }

        if (!detail::isWithinBounds(value, min, max)) {
            std::cout << variableName << " must be";
            if (min) {
                std::cout << " at least " << *min;
            }
            if (min && max) {
                std::cout << " and";
            }
            if (max) {
                std::cout << " at most " << *max;
            }
            std::cout << ". Try again.\n";
            continue;
        }

        return value;
    }
}

template <typename T>
inline T getln(std::string_view variableName, T min) {
    return getln<T>(variableName, std::move(min), std::nullopt);
}

template <typename T>
inline T getln(std::string_view variableName, T min, T max) {
    return getln<T>(
        variableName,
        std::optional<T>(std::move(min)),
        std::optional<T>(std::move(max))
    );
}

// The last argument is a type tag, such as int{} or std::string{}.
template <typename Min, typename Max, typename T>
inline T getln(std::string_view variableName, Min min, Max max, T /*typeTag*/) {
    return getln<T>(
        variableName,
        static_cast<T>(std::move(min)),
        static_cast<T>(std::move(max))
    );
}

} // namespace toolbox
