#include <vector>
#include <string>
#include <utility>
#include <algorithm>
#include <iostream>
#include <cassert>
#include <cmath>

extern "C"{
#include "timer.h"
}

using namespace std;

void binary_string_permutation(vector<string> &set, string &s, unsigned n, unsigned k) {
    if (k <= 0) {
        set.emplace_back(s);
        return;
    }

    s[k - 1] = '0';
    binary_string_permutation(set, s, n, k - 1);
    s[k - 1] = '1';
    binary_string_permutation(set, s, n, k - 1);
}

vector<string> binary_string_set(unsigned n, unsigned sz) {
    string binary_string(n, '0');
    vector<string> res;
    res.reserve(sz);
    binary_string_permutation(res, binary_string, n, n);
    return res;
}

vector<string> lcs(const string &s1, const string &s2) {
    //s1 and s2 should have same length, n
    //returns length of LCS first
    //const int n = s1.length();

//    const int n = 4;
//    if (n < 1)
//      return 0;
//    int common[n+1][n+1] = {{0}};
//    for (int i = 1; i <= n; i++) {
//        for (int j = 1; j <= n; j++){
//            cout << "i: " << i << "\t j: " << j << endl;
//            cout << "s1: " << s1[i-1] << "\t s2: " << s2[j-1] << endl;
//            if (s1[i-1] == s2[j-1])
//                common[i][j] = common[i-1][j-1] + 1;
//            else
//                common[i][j] = max(common[i-1][j], common[i][j-1]);
//            cout << "common: " << common[i][j] << endl;
//        }
//    }
//    return common[n][n];
    return {};
}

pair<string, string> distinct_lcs(const vector<string> &bstr, vector<string> &lcs_res) {
    int longest_so_far = 0;
    pair<string, string> res;
    for (int i = 0; i < bstr.size(); i++) {
        for (int j = i + 1; j < bstr.size(); j++) {
            auto longest_ending_here = lcs(bstr[i], bstr[j]);
            if (longest_ending_here.size() > longest_so_far) {
                longest_so_far = longest_ending_here.size();
                res.first = bstr[i];
                res.second = bstr[j];
                lcs_res = longest_ending_here;
            }
        }
    }
    return res;
}

void print_strings(const vector<string> &s) {
    for (auto itr = s.begin(); itr != s.end(); itr++) {
        if (itr != s.begin()) cout << ", ";
        cout << *itr;
    }
    cout << endl;
}

int main() {

    //testing LCS algorithm
//    string s1 = "1001";
//    string s2 = "0100";
//    int result = lcs(s1,s2);
//    cout << "lcs length: " << result << endl;

    // n = 4
    auto set_1_strings = binary_string_set(4, 16);
    // assert(set_1_strings.size() == 16);
    vector<string> set_1_output = {};
    start_timer();
    auto set_1_pair = distinct_lcs(set_1_strings, set_1_output);
    cout << "n = 4\n";
    cout << "Time elapsed: " << elapsed_time() << endl;
    cout << "A = " << set_1_pair.first << endl;
    cout << "B = " << set_1_pair.second << endl;
    cout << "number of distinct LCS’s = " << set_1_output.size() << endl;
    print_strings(set_1_output);

    // n = 7
    auto set_2_strings = binary_string_set(7, 128);
    vector<string> set_2_output = {};
    start_timer();
    auto set_2_pair = distinct_lcs(set_2_strings, set_2_output);
    cout << "n = 7\n";
    cout << "Time elapsed: " << elapsed_time() << endl;
    cout << "A = " << set_2_pair.first << endl;
    cout << "B = " << set_2_pair.second << endl;
    cout << "number of distinct LCS’s = " << set_2_output.size() << endl;
    print_strings(set_1_output);


    // n = 10
    auto set_3_strings = binary_string_set(10, 1024);
    vector<string> set_3_output = {};
    start_timer();
    auto set_3_pair = distinct_lcs(set_3_strings, set_3_output);
    cout << "n = 1n\b";
    cout << "Time elapsed: " << elapsed_time() << endl;
    cout << "A = " << set_3_pair.first << endl;
    cout << "B = " << set_3_pair.second << endl;
    cout << "number of distinct LCS’s = " << set_3_output.size() << endl;
    print_strings(set_1_output);


    // n = 12
    auto set_4_strings = binary_string_set(12, 4096);
    vector<string> set_4_output = {};
    start_timer();
    auto set_4_pair = distinct_lcs(set_4_strings, set_4_output);
    cout << "n = 12\n";
    cout << "Time elapsed: " << elapsed_time() << endl;
    cout << "A = " << set_4_pair.first << endl;
    cout << "B = " << set_4_pair.second << endl;
    cout << "number of distinct LCS’s = " << set_4_output.size() << endl;
    print_strings(set_1_output);

}
