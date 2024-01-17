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
    Euclidean distance (i.e., √(x1 - x2)2 + (y1 - y2)2).

    You may return the answer in any order.
    The answer is guaranteed to be unique (except for the order that it is in).

    Constraints:

        * 1 <= k <= points.length <= 10**4
        * -10**4 <= xi, yi <= 10**4
*/
class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {

//
//!\todo TODO: >>> Under Construction <<<
//
return {};

    }
};

// [----------------(120 columns)---------------> Module Code Delimiter <---------------(120 columns)----------------]

TEST_CASE("Case 1")
{
    cerr << "Case 1" << '\n';
    vector<vector<int>> points{{1, 3}, {-2, 2}};
    auto const k = 1;
    auto const expected = vector<vector<int>>{{3, 3}, {-2, 4}};
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
