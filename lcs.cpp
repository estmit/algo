#include <vector>
#include <string>
#include <utility>
#include <algorithm>
#include <iostream>
#include <cassert>
#include <cmath>
#include <stdlib.h>

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

//returns 2d vector of lengths of lcs. Largest len is at [n][n]
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

vector <vector <string>> lcs_string_vect(const string &s1, const string &s2){
    int n = s1.length();
    vector <vector<string>> lcs_string(n+1, vector<string>(n+1, ""));
    vector <vector<int>> lcs_len(n+1, vector<int>(n+1, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++){
            if (s1[i-1] == s2[j-1]){
              lcs_len[i][j] = lcs_len[i-1][j-1] + 1;
              lcs_string[i][j] = lcs_string[i-1][j-1] + s1[i-1];
            }
            else {
              lcs_len[i][j] = max(lcs_len[i-1][j], lcs_len[i][j-1]);
              //what if equal?
              if (lcs_len[i-1][j] > lcs_len[i][j-1])
                  lcs_string[i][j] = lcs_string[i-1][j];
              else
                  lcs_string[i][j] = lcs_string[i][j-1];
            }
        }
    }
    return lcs_string;
}

vector <string> list_distinct_lcs(const string &s1, const string &s2) {
    int n = s1.length();
    vector <vector<int>> lcs_len(n+1, vector<int>(n+1, 0));
    vector <vector<string>> lcs_string(n+1, vector<string>(n+1, ""));
    vector <string> lcs_res;
    lcs_len = lcs_len_vect(s1, s2);
    lcs_string = lcs_string_vect(s1, s2);
    int lcs_length = lcs_len[n][n];

    for (int i = 0; i <= n; i++){
        for (int j = 0; j <= n; j++) {
            bool dup = false;
            if(lcs_string[i][j].length() == lcs_length){
                for (int n = 0; n < lcs_res.size(); n++) {
                    if(lcs_string[i][j] == lcs_res[n]){
                        dup = true;
                    }
                }
                if (dup == false) {
                    lcs_res.push_back(lcs_string[i][j]);
                    //cout << "lcs string: " << lcs_string[i][j] << endl;
                }
            }
        }
    }
    return lcs_res;
}
//
// int num_distinct_lcs2(const string &s1, const string &s2){
//     int n = s1.length();
//     vector <vector<int>> lcs_len(n+1, vector<int>(n+1, 0));
//     vector <vector<string>> lcs_string(n+1, vector<string>(n+1, ""));
//     vector <string> lcs_res;
//     lcs_len = lcs_len_vect(s1, s2);
//     lcs_string = lcs_string_vect(s1, s2);
//     int lcs_length = lcs_len[n][n];
//
//     for (int i = 0; i <= n; i++){
//         for (int j = 0; j <= n; j++) {
//             bool dup = false;
//             if(lcs_string[i][j].length() == lcs_length){
//                 for (int n = 0; n < lcs_res.size(); n++) {
//                     if(lcs_string[i][j] == lcs_res[n]){
//                         dup = true;
//                     }
//                 }
//                 if (dup == false) {
//                     lcs_res.push_back(lcs_string[i][j]);
//                     //cout << "lcs string: " << lcs_string[i][j] << endl;
//                 }
//             }
//         }
//     }
//     return lcs_res.size();
// }

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
                if (s1[i-1] == s2[j-1])
                    num_distinct[i][j] = num_distinct[i-1][j-1];
                else {
                    if (lcs_len[i-1][j] == lcs_len[i][j])
                        num_distinct[i][j] = (num_distinct[i][j] + num_distinct[i-1][j]);
                    if (lcs_len[i][j-1] == lcs_len[i][j])
                        num_distinct[i][j] = (num_distinct[i][j] + num_distinct[i][j-1]);
                    if (lcs_len[i-1][j-1] == lcs_len[i][j]) {
                        num_distinct[i][j] = abs(num_distinct[i][j] - num_distinct[i-1][j-1]);
                    }
                }
            }
        }
    }
    return num_distinct[n][n];
}

pair<string, string> determined_strings(const vector<string> &bstr, vector<string> &lcs_res) {
    int longest_so_far = 0;
    int n = bstr[1].length();
    pair<string, string> res;
    for (int i = 0; i < bstr.size(); i++) {
        for (int j = i + 1; j < bstr.size(); j++) {
            if ((bstr[i][1] != bstr[j][1]) && (bstr[i][n-1] != bstr[j][n-1])){
                int longest_ending_here = num_distinct_lcs(bstr[i], bstr[j]);
                if (longest_ending_here > longest_so_far) {
                    longest_so_far = longest_ending_here;
                    res.first = bstr[i];
                    res.second = bstr[j];
                    //lcs_res = longest_ending_here;
                }
            }
        }
    }
    return res;
}

void print_strings(const vector<string> &s) {
    cout << "list of lcs: " << endl;
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
    auto set_1_num_distinct = num_distinct_lcs(set_1_pair.first, set_1_pair.second);
    cout << "n = 4\n";
    cout << "A = " << set_1_pair.first << "\t B = " << set_1_pair.second << endl;
    cout << "number of distinct LCS’s = " << set_1_num_distinct << endl;
    vector <string> set_1_lcs = list_distinct_lcs(set_1_pair.first, set_1_pair.second);
    print_strings(set_1_lcs);
    //cout << "Time elapsed: " << elapsed_time() << endl;
    cout << endl;

    // n = 7
    auto set_2_strings = binary_string_set(7, 128);
    vector<string> set_2_output = {};
    //start_timer();
    auto set_2_pair = determined_strings(set_2_strings, set_2_output);
    auto set_2_num_distinct = num_distinct_lcs(set_2_pair.first, set_2_pair.second);
    vector <string> set_2_lcs = list_distinct_lcs(set_2_pair.first, set_2_pair.second);
    cout << "n = 7\n";
    cout << "A = " << set_2_pair.first << "\t B = " << set_2_pair.second << endl;
    cout << "number of distinct LCS’s = " << set_2_num_distinct << endl;
    print_strings(set_2_lcs);
    //cout << "Time elapsed: " << elapsed_time() << endl;
    cout << endl;


    // n = 10
    auto set_3_strings = binary_string_set(10, 1024);
    vector<string> set_3_output = {};
    //start_timer();
    auto set_3_pair = determined_strings(set_3_strings, set_3_output);
    auto set_3_num_distinct = num_distinct_lcs(set_3_pair.first, set_3_pair.second);
    vector <string> set_3_lcs = list_distinct_lcs(set_3_pair.first, set_3_pair.second);
    cout << "n = 10\n";
    cout << "A = " << set_3_pair.first << "\t B = " << set_3_pair.second << endl;
    cout << "number of distinct LCS’s = " << set_3_num_distinct << endl;
    print_strings(set_3_lcs);
    //cout << "Time elapsed: " << elapsed_time() << endl;
    cout << endl;


    // n = 12
    auto set_4_strings = binary_string_set(12, 4096);
    vector<string> set_4_output = {};
    //start_timer();
    auto set_4_pair = determined_strings(set_4_strings, set_4_output);
    auto set_4_num_distinct = num_distinct_lcs(set_4_pair.first, set_4_pair.second);
    vector <string> set_4_lcs = list_distinct_lcs(set_4_pair.first, set_4_pair.second);
    cout << "n = 12\n";
    cout << "A = " << set_4_pair.first << "\t B = " << set_4_pair.second << endl;
    cout << "number of distinct LCS’s = " << set_4_num_distinct << endl;
    print_strings(set_4_lcs);
    //cout << "Time elapsed: " << elapsed_time() << endl;
}
