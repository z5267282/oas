#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

class solution {
public:
    virtual auto solve(std::string s) -> int = 0;

    auto run_tests(void) -> void {
        assert(this->solve(std::string{"1011"}) == 4);
        assert(this->solve(std::string{""}) == 1);

        auto file = std::ifstream{"q3-long.txt"};
        auto large = std::string{};
        file >> large;
        auto big = this->solve(large);
        file.close();

        assert(big == 692);
    }
};

/**
    Use a set to store all unique differences encountered so far.
    This is at worst quadratic if the size of the differences is linear with respect to |s| early on.
 */
class set : public solution {
public:
    auto solve(std::string s) -> int override {
        auto diffs = std::unordered_set<int>{};
        auto powers = std::unordered_set<int>{0};
        auto prefix = std::vector<int>{0};

        for (auto chr : s) {
            auto d = (chr == '0' ? 1 : -1) + prefix.back();
            prefix.push_back(d);
            diffs.insert(d);
            for (auto diff : diffs) {
                powers.insert(d - diff);
            }
        }

        return static_cast<int>(powers.size());
    }
};

/**
    This is a quadratic algorithm, but it is definitely correct.
    It was too slow in the OA.
 */
class certain : public solution {
    public:
    auto solve(std::string s) -> int override {
        if (s.empty()) {
            return 1;
        }

        auto prefix = std::vector<int>{0};
        for (auto chr : s) {
            prefix.push_back((chr == '0' ? 1 : -1) + prefix.back());
        }

        auto powers = std::unordered_set<int>{};
        // prefix will be of length |s| + 1, with last index |s|
        for (auto i = std::size_t{1}; i <= s.size(); ++i) {
            auto r = prefix.at(i);
            for (auto j = std::size_t{0}; j < i; ++j) {
                powers.insert(r - prefix.at(j));
            }
        }

        return static_cast<int>(powers.size());
    }
};

auto main(void) -> int {
    // change the class to test a different implementation
    auto sol = set{};
    sol.run_tests();
}
