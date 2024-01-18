/*!
    \file "main.cpp"

    Author: Matt Ervin <matt@impsoftware.org>
    Formatting: 4 spaces/tab (spaces only; no tabs), 120 columns.
    Doc-tool: Doxygen (http://www.doxygen.com/)

    https://leetcode.com/problems/k-closest-points-to-origin/
*/

//!\sa https://github.com/doctest/doctest/blob/master/doc/markdown/main.md
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "utils.hpp"

/*
    Given an array of points where points[i] = [xi, yi] represents a 
    point on the X-Y plane and an integer k, return the k closest 
    points to the origin (0, 0).

    The distance between two points on the X-Y plane is the 
    Euclidean distance (i.e., √(x1 - x2)**2 + (y1 - y2)**2).

    You may return the answer in any order.
    The answer is guaranteed to be unique (except for the order that it is in).

    Constraints:

        * 1 <= k <= points.length <= 10**4
        * -10**4 <= xi, yi <= 10**4

    Solution #1:

    Use a max heap to track the k smallest vector magnitudes.
    If the top (largest) value on the heap is greater than m, 
    pop the value off the heap and push m on to the heap.
    Calculate the relative vector magnitude of each point pair as:
    m = (x - 0)**2 + (y - 0)**2 = x**2 + y**2
    Store the vector magnitude and the corresponding point data in
    a structure in the heap.
    Pop and return all (up to k) heap elements.

    Solution #2:

    Use std::nth_element(), which has an average time complexity of Θ(n),
    to [partially] sort an array of indexes into the supplied points.
    Then create the result from the first k indexes.
*/
class Solution {
public:
    /*
        Solution #1

        Time = O(n*log2(k))
                n = number of points (points.size())
                k = number of closest points to origin.

        Space = O(k)
    */
    vector<vector<int>> kClosest_maxHeap(vector<vector<int>>& points, int k) {
        struct heap_element_t {
            int x{};
            int y{};
            int_least32_t m{};
            heap_element_t() = default;
            heap_element_t(int x, int y)
                : x{std::move(x)}, y{std::move(y)}, m{x*x+y*y} {}
            bool operator==(heap_element_t const& rhs) const noexcept {
                return m == rhs.m;
            }
            bool operator<(heap_element_t const& rhs) const noexcept {
                return m < rhs.m;
            }
        };
        auto heap = std::priority_queue<heap_element_t>{};
        for (auto const& point : points) {
            assert(2 == point.size());
            if (2 <= point.size()) {
                auto const element = heap_element_t{point[0], point[1]};
                if (heap.size() >= k) {
                    if (element < heap.top()) {
                        heap.pop();
                        heap.push(std::move(element));
                    }
                } else {
                    heap.push(std::move(element));
                }
            }
        }

        auto result = vector<vector<int>>{};
        while (!heap.empty()) {
            result.emplace_back(vector<int>{heap.top().x, heap.top().y});
            heap.pop();
        }
        return result;
    }

    /*
        Solution #2

        Time = Θ(n+n+n+k) => Θ(3n+k) => Θ(n)
               O(n+n+n*log2(n)+k) => O(2n+n*log2(n)+k) => O(n*log2(n))
               'k' is dropped because k <= n.

        Space = O(n+n) => O(2n) => O(n)
    */
    vector<vector<int>> kClosest_sort(vector<vector<int>>& points, int k) {
        assert(points.size() >= k);
        if (points.size() < k) {
            return {};
        }

        // Create array of [vector] magnitudes, one for each point.
        auto const magnitudesSize = points.size();
        int_fast32_t magnitudes[magnitudesSize];
        std::transform(
            points.begin()
            , points.end()
            , magnitudes
            , [&](auto const& p) {
                return p[0] * p[0] + p[1] * p[1];
            }
        );
        
        // Create array of indexes into points (this array will be sorted).
        auto const pointsIndexesSize = points.size();
        size_t pointsIndexes[pointsIndexesSize];
        std::generate_n(
            pointsIndexes
            , pointsIndexesSize
            , [i=0]() mutable {
                return i++;
            }
        );
        
        // Sort the points indexes based on their corresponding magnitudes.
        // Using std::nth_element() to do a partial sort that has an 
        // average time complexity of Θ(n) and is O(n*log2(n)), which is
        // typically much faster than a full sort such as std::sort().
        std::nth_element(
            pointsIndexes
            , pointsIndexes + k - 1
            , pointsIndexes + pointsIndexesSize
            , [&magnitudes](auto const& lhs, auto const& rhs) {
                return magnitudes[lhs] < magnitudes[rhs];
            }
        );

        // Generate the result from the sorted indexes.
        vector<vector<int>> result{};
        while (k--) {
            result.emplace_back(std::move(points[pointsIndexes[k]]));
        }
        return result;
    }

    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
//        return kClosest_maxHeap(points, k);
        return kClosest_sort(points, k);
    }
};

// [----------------(120 columns)---------------> Module Code Delimiter <---------------(120 columns)----------------]

TEST_CASE("Case 1")
{
    cerr << "Case 1" << '\n';
    vector<vector<int>> points{{1, 3}, {-2, 2}};
    auto const k = 1;
    auto const expected = [&]{
        auto expected = vector<vector<int>>{{-2, 2}};
        for (auto& val : expected) { sort(val.begin(), val.end()); }
        sort(expected.begin(), expected.end());
        return expected;
    }();
    { // New scope.
        auto const start = std::chrono::steady_clock::now();
        auto result =  Solution{}.kClosest(points, k);
        for (auto& val : result) { sort(val.begin(), val.end()); }
        sort(result.begin(), result.end());
        CHECK(expected == result);
        cerr << "Elapsed time: " << elapsed_time_t{start} << '\n';
    }
    cerr << '\n';
}

TEST_CASE("Case 2")
{
    cerr << "Case 2" << '\n';
    vector<vector<int>> points{{3, 3}, {5, -1}, {-2, 4}};
    auto const k = 2;
    auto const expected = [&]{
        auto expected = vector<vector<int>>{{3, 3}, {-2, 4}};
        for (auto& val : expected) { sort(val.begin(), val.end()); }
        sort(expected.begin(), expected.end());
        return expected;
    }();
    { // New scope.
        auto const start = std::chrono::steady_clock::now();
        auto result =  Solution{}.kClosest(points, k);
        for (auto& val : result) { sort(val.begin(), val.end()); }
        sort(result.begin(), result.end());
        CHECK(expected == result);
        cerr << "Elapsed time: " << elapsed_time_t{start} << '\n';
    }
    cerr << '\n';
}

/*
    End of "main.cpp"
*/
