#include <string>

using namespace std;

int getVulnerability(string password, int max_ops) {
    // for all letters, try and see if it is possible to achieve a substring length of max_ops
    int n = static_cast<int>(password.size());
    int ans = 0;
    for (char c = 'a'; c <= 'z'; ++c) {
        int left = 0;
        int count = 0;
        for (int right = 0; right < n; ++right) {
            if (password.at(right) != c) {
                ++count;
            }

            while (count > max_ops) {
                if (password.at(left)) {
                    --count;
                }
                ++left;
            }
            ans = max(ans, right - left + 1);
        }
    }
    return ans;
}
