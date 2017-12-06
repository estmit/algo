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

vector <vector <int>> lcs_len_vect(const string &s1, const string &s2){
    int n = s1.length();
    vector <vector<int>> lcs_len(n+1, vector<int>(n+1, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++){
            if (s1[i-1] == s2[j-1])
              lcs_len[i][j] = lcs_len[i-1][j-1] + 1;
            else
              lcs_len[i][j] = max(lcs_len[i-1][j], lcs_len[i][j-1]);
        }
    }
    return lcs_len;
}

int num_distinct_lcs(const string &s1, const string &s2) {
    int n = s1.length();
    vector <vector<int>> num_distinct(n+1, vector<int>(n+1,0));
    vector <vector<int>> lcs_len(n+1, vector<int>(n+1, 0));

    lcs_len = lcs_len_vect(s1, s2);

    for (int i = 0; i <= n; i++) {  // using the ith character onwards of first string
        for (int j = 0; j <= n; j++) {   // using the jth character onwards of second string
            if (i==0 || j==0)
                num_distinct[i][j] = 1;   // empty string
            else {
      	        num_distinct[i][j] = 0;
                if (s1[i-1]==s2[j-1])
                    num_distinct[i][j] = num_distinct[i-1][j-1];
                else {
                    if (lcs_len[i-1][j] == lcs_len[i][j])
                        num_distinct[i][j] = (num_distinct[i][j] + num_distinct[i-1][j])%23102009;
                    if (lcs_len[i][j-1] == lcs_len[i][j])
                        num_distinct[i][j] = (num_distinct[i][j] + num_distinct[i][j-1])%23102009;
                    if (lcs_len[i-1][j-1] == lcs_len[i][j]) {
                        if (num_distinct[i][j] < num_distinct[i-1][j-1])
                            num_distinct[i][j] += 23102009;
                        num_distinct[i][j] = num_distinct[i][j] - num_distinct[i-1][j-1];
                    }
                }
            }
            //cout << "i: " << i << "\tj: " << j << "\tdistinct ij: " << num_distinct[i][j] << endl;
        }
    }
    return num_distinct[n][n];
}

pair<string, string> determined_strings(const vector<string> &bstr, vector<string> &lcs_res) {
    int longest_so_far = 0;
    pair<string, string> res;
    for (int i = 0; i < bstr.size(); i++) {
        for (int j = i + 1; j < bstr.size(); j++) {
            int longest_ending_here = num_distinct_lcs(bstr[i], bstr[j]);
            if (longest_ending_here > longest_so_far) {
                longest_so_far = longest_ending_here;
                res.first = bstr[i];
                res.second = bstr[j];
                //lcs_res = longest_ending_here;
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

    // n = 4
    auto set_1_strings = binary_string_set(4, 16);
    // assert(set_1_strings.size() == 16);
    vector<string> set_1_output = {};
    //start_timer();
    auto set_1_pair = determined_strings(set_1_strings, set_1_output);

    cout << "n = 4\n";
    cout << "A = " << set_1_pair.first << "\t B = " << set_1_pair.second << endl;
    cout << "number of distinct LCS’s = " << num_distinct_lcs(set_1_pair.first, set_1_pair.second) << endl;
    //print_strings(set_1_output);
    //cout << "Time elapsed: " << elapsed_time() << endl;
    cout << endl;

    // n = 7
    auto set_2_strings = binary_string_set(7, 128);
    vector<string> set_2_output = {};
    //start_timer();
    auto set_2_pair = determined_strings(set_2_strings, set_2_output);
    cout << "n = 7\n";
    cout << "A = " << set_2_pair.first << "\t B = " << set_2_pair.second << endl;
    cout << "number of distinct LCS’s = " << num_distinct_lcs(set_2_pair.first, set_2_pair.second) << endl;
    //print_strings(set_1_output);
    //cout << "Time elapsed: " << elapsed_time() << endl;
    cout << endl;
    //
    //
    // // n = 10
    auto set_3_strings = binary_string_set(10, 1024);
    vector<string> set_3_output = {};
    //start_timer();
    auto set_3_pair = determined_strings(set_3_strings, set_3_output);
    cout << "n = 10\n";
    cout << "A = " << set_3_pair.first << "\t B = " << set_3_pair.second << endl;
    cout << "number of distinct LCS’s = " << num_distinct_lcs(set_3_pair.first, set_3_pair.second) << endl;
    //print_strings(set_1_output);
    //cout << "Time elapsed: " << elapsed_time() << endl;
    cout << endl;
    //
    //
    // n = 12
    auto set_4_strings = binary_string_set(12, 4096);
    vector<string> set_4_output = {};
    //start_timer();
    auto set_4_pair = determined_strings(set_4_strings, set_4_output);
    cout << "n = 12\n";
    cout << "A = " << set_4_pair.first << "\t B = " << set_4_pair.second << endl;
    cout << "number of distinct LCS’s = " << num_distinct_lcs(set_4_pair.first, set_4_pair.second) << endl;
    //print_strings(set_1_output);
    //cout << "Time elapsed: " << elapsed_time() << endl;

    // string s1 = "100110001100";
    // string s2 = "010101010101";
    // cout << "number of distinct LCS’s = " << num_distinct_lcs(s1, s2) << endl;


}
