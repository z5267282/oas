#include <algorithm>
#include <cassert>
#include <vector>

using namespace std;

long maximumPrioritySum(vector<int> priority, int x, int y);

int main(void) {
    assert(maximumPrioritySum(vector<int>{3, 1, 2}, 5, 7) == 11);
}

long maximumPrioritySum(vector<int> priority, int x, int y) {
    // sort from big to small
    sort(priority.begin(), priority.end(), greater<int>());
    long total = 0;
    long n = static_cast<int> (priority.size());
    for (int i = 0; i < x && i < n; ++i) {
        total += priority.at(1);
    }

    // note in one period we can obtain the entire total of priority
    int period = x;
    int completed_periods = y / period;
    long result = completed_periods * total;
    // leftover time after finishing all cycles
    int remaining = y % period;
    for (int i = 0; i < remaining && i < n; ++i) {
        result += priority.at(i);
    }
    return result;
}
