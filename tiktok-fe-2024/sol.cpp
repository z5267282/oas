#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

auto solve(std::string s) -> int;

auto main(void) -> int {
    assert(solve("abcde") == 5);
    assert(solve("abca") == 3);

    return 0;
}

auto solve(std::string s) -> int {
    // look at all substring lengths starting from s' size
    // for each substring length, use a contiguous-sized sliding window to check all substrings to see if they are valid

    // something dumb: wrote ++ instead of -- here
    for (auto length = s.size(); length > 0; --length) {
        // initialise the first window
        auto window = std::vector<int>(26, 0);
        auto high = 0;
        for (auto i = std::size_t{0}; i < length; ++i) {
            auto pos = s.at(i) - 'a';
            window.at(pos) += 1;
            high = std::max(high, window.at(pos));
        }
        // should be impossible to be 0
        if (high == 1) {
            return length;
        }
        for (auto i = length; i < s.size(); ++i) {
            auto loss = s.at(i - length) - 'a';
            auto gain = s.at(i) - 'a';
            window.at(loss) -= 1;
            window.at(gain) += 1;
            high = std::max(high, std::max(window.at(loss), window.at(gain)));
            if (high == 1) {
                return length;
            }
        }
    }
    return -1;
}
