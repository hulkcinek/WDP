#include <iostream>
#include <vector>
#include <climits>
#include <ranges>
#include <algorithm>

class Interval {
private:
    int start;
    int end;
    bool isOverlapping(Interval other) {
        return start <= other.end && other.start <= end;
    }
public:
    Interval(int start, int end) : start(start), end(end) {}

    int minimalDistance(Interval other) {
        if (isOverlapping(other)) {
            return 0;
        }
        int a = std::abs(start - other.end);
        int b = std::abs(other.start - end);
        return std::min(a, b);
    }

    int getStart() const {
        return start;
    }
};

std::vector<Interval> intervals;

void readInputs() {
    int input_count;
    std::cin >> input_count;
    for (int i = 0; i < input_count; i++) {
        int start;
        std::cin >> start;
        int end;
        std::cin >> end;
        intervals.emplace_back(start, end);
    }
}

void findMinimumGap() {
    std::ranges::sort(intervals, [](Interval a, Interval b) {
        return a.getStart() < b.getStart();
    });
    int minimum_gap = INT_MAX;
    for (int i = 1; i < intervals.size(); ++i) {
        Interval interval1 = intervals[i];
        Interval interval2 = intervals[i - 1];

        int distance = interval1.minimalDistance(interval2);

        if (distance < minimum_gap) {
            minimum_gap = distance;
        }
    }
    std::cout << minimum_gap << std::endl;
}

int main() {
    readInputs();
    findMinimumGap();
    return 0;
}
