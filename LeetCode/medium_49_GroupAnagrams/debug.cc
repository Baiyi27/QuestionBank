/*
 * @lc app=leetcode.cn id=49 lang=cpp
 *
 * [49] Group Anagrams
 *
 * https://leetcode.cn/problems/group-anagrams/description/
 *
 * algorithms
 * Medium (68.30%)
 * Likes:    1931
 * Dislikes: 0
 * Total Accepted:    751.8K
 * Total Submissions: 1.1M
 * Testcase Example:  '["eat","tea","tan","ate","nat","bat"]'
 *
 * Given an array of strs strs, group the anagrams together. You can return
 * the answer in any order.
 *
 * An Anagram is a word or phrase formed by rearranging the letters of a
 * different word or phrase, typically using all the original letters exactly
 * once.
 *
 *
 * Example 1:
 * Input: strs = ["eat","tea","tan","ate","nat","bat"]
 * Output: [["bat"],["nat","tan"],["ate","eat","tea"]]
 * Example 2:
 * Input: strs = [""]
 * Output: [[""]]
 * Example 3:
 * Input: strs = ["a"]
 * Output: [["a"]]
 *
 *
 * Constraints:
 *
 *
 * 1 <= strs.length <= 10^4
 * 0 <= strs[i].length <= 100
 * strs[i] consists of lowercase English letters.
 *
 *
 */
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <numeric>
using namespace std;

// @lc code=start
class Solution {
public:
    vector<vector<string>> groupStrings(vector<string> &strs)
    {

        unordered_map<string, vector<string>> intUmapVec;
        for(const auto &str: strs) {
            string key= str;
            sort(key.begin(), key.end());
            intUmapVec[key].emplace_back(str);
        }
        return updateResult(intUmapVec);
    }

    vector<vector<string>> groupAnagrams(vector<string> &strs)
    {
        auto arrayHash= [fn= hash<int> {}](const array<int, 26> &arr) -> size_t {
            return accumulate(arr.begin(), arr.end(), 0u, [&](size_t acc, int num) {
                return (acc << 1) ^ fn(num);
            });
        };

        unordered_map<array<int, 26>, vector<string>, decltype(arrayHash)> arrUmapVec(0, arrayHash);
        for(string &str: strs) {
            array<int, 26> counts {};
            int length= str.length();
            for(int i= 0; i < length; ++i) {
                counts[str[i] - 'a']++;
            }
            arrUmapVec[counts].emplace_back(str);
        }

        return updateResult(arrUmapVec);
    }

private:
    vector<vector<string>> Res_;

    template <typename T>
    vector<vector<string>> updateResult(T &map)
    {
        Res_.clear();
        for(const auto &[k, v]: map) {
            Res_.emplace_back(move(v));
        }

        return Res_;
    }
};

void PrintResult(const vector<vector<string>> &res)
{
    for(const auto &v: res) {
        for(const auto &s: v) {
            cout << s << " ";
        }
        cout << endl;
    }
    putchar('\n');
}

int main()
{
    vector<string> inputStrs { "eat", "tea", "tan", "ate", "nat", "bat" };
    Solution s;
    auto output= s.groupStrings(inputStrs);
    PrintResult(output);

    auto output2= s.groupAnagrams(inputStrs);
    PrintResult(output2);

    return 0;
}

// @lc code=end
