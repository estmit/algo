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

int dp[12][12];
vector <string> dlcs;

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

int lcs_len(const string &s1, const string &s2){
    int n = s1.length();
    return lcs_len_vect(s1, s2)[n][n];
}

// code simulating algorithm from online source
// http://www.geeksforgeeks.org/print-longest-common-sub-sequences-lexicographical-order/

int lcs(string s1, string s2, int i, int j) {
  	int &ret = dp[i][j];
    int n = s1.length();

  	// base condition
  	if (i==n || j==n)
  		return ret = 0;

  	// if lcs has been computed
  	if (ret != -1)
  		return ret;

  	ret = 0;

  	// if characters are same return previous + 1 else
  	// max of two sequences after removing i'th and j'th
  	// char one by one
  	if (s1[i] == s2[j])
  		ret = 1 + lcs(s1, s2, i+1, j+1);
  	else
  		ret = max(lcs(s1, s2, i+1, j), lcs(s1, s2, i, j+1));
  	return ret;
}

void make_distinct_list(string s1, string s2, char data[], int indx1, int indx2, int currlcs, int lcslen) {
	   // if currlcs is equal to lcslen then store the unique lcs
    int n = s1.length();
  	if (currlcs == lcslen) {
        dlcs.push_back(data);
    		return;
  	}

  	// if we are done with all the characters of both string
  	if (indx1 == n || indx2 == n) {
        return;
    }

  	for (char ch='0'; ch<='1'; ch++) {
    		// done is a flag to tell that we have printed all the
    		// subsequences corresponding to current character
    		bool done = false;

    		for (int i=indx1; i<n; i++) {
      			// if character ch is present in str1 then check if
      			// it is present in str2
      			if (ch==s1[i]) {
          			for (int j=indx2; j<n; j++) {
            				// if ch is present in both of them and
            				// remaining length is equal to remaining
            				// lcs length then add ch in sub-sequenece
                    if (ch==s2[j]) {
                				data[currlcs] = ch;
                				make_distinct_list(s1, s2, data, i+1, j+1, currlcs+1, lcslen);
                				done = true;
                				break;
            			  }
        		    }
            }
      			// If we found LCS beginning with current character.
      			if (done)
      			     break;
    		}
	   }
}

// adopted and modified num distinct lcs algorithm from:
// https://comeoncodeon.wordpress.com/2009/11/13/number-of-distinct-lcs/
// https://www.codechef.com/wiki/tutorial-lcs-problem-revisited
// https://arxiv.org/pdf/cs/0301034.pdf
int num_distinct_lcs(const string &s1, const string &s2) {
    int n = s1.length();
    vector <vector<int>> num_distinct(n+1, vector<int>(n+1,0));
    vector <vector<int>> lcs_len(n+1, vector<int>(n+1, 0));

    lcs_len = lcs_len_vect(s1, s2);

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            if (i==0 || j==0)
                num_distinct[i][j] = 1;
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

pair<string, string> determined_strings(const vector<string> &bstr) {
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
    dlcs.clear();
    auto set_1_strings = binary_string_set(4, 16);
    // assert(set_1_strings.size() == 16);
    start_timer();
    auto set_1_pair = determined_strings(set_1_strings);
    auto set_1_num_distinct = num_distinct_lcs(set_1_pair.first, set_1_pair.second);
    cout << "n = 4\n";
    cout << "A = " << set_1_pair.first << "\t B = " << set_1_pair.second << endl;
    cout << "number of distinct LCS’s = " << set_1_num_distinct << endl;
    char data1[10];
    make_distinct_list(set_1_pair.first, set_1_pair.second, data1, 0, 0, 0, lcs_len(set_1_pair.first, set_1_pair.second));
    print_strings(dlcs);
    cout << "Time elapsed: " << elapsed_time() << endl;
    cout << endl;

    // n = 7
    dlcs.clear();
    auto set_2_strings = binary_string_set(7, 128);
    start_timer();
    auto set_2_pair = determined_strings(set_2_strings);
    auto set_2_num_distinct = num_distinct_lcs(set_2_pair.first, set_2_pair.second);
    cout << "n = 7\n";
    cout << "A = " << set_2_pair.first << "\t B = " << set_2_pair.second << endl;
    cout << "number of distinct LCS’s = " << set_2_num_distinct << endl;
    char data2[10];
    make_distinct_list(set_2_pair.first, set_2_pair.second, data2, 0, 0, 0, lcs_len(set_2_pair.first, set_2_pair.second));
    print_strings(dlcs);
    cout << "Time elapsed: " << elapsed_time() << endl;
    cout << endl;


    // n = 10
    dlcs.clear();
    auto set_3_strings = binary_string_set(10, 1024);
    start_timer();
    auto set_3_pair = determined_strings(set_3_strings);
    auto set_3_num_distinct = num_distinct_lcs(set_3_pair.first, set_3_pair.second);
    cout << "n = 10\n";
    cout << "A = " << set_3_pair.first << "\t B = " << set_3_pair.second << endl;
    cout << "number of distinct LCS’s = " << set_3_num_distinct << endl;
    char data3[30];
    make_distinct_list(set_3_pair.first, set_3_pair.second, data3, 0, 0, 0, lcs_len(set_3_pair.first, set_3_pair.second));
    print_strings(dlcs);
    cout << "Time elapsed: " << elapsed_time() << endl;
    cout << endl;


    // n = 12
    dlcs.clear();
    auto set_4_strings = binary_string_set(12, 4096);
    start_timer();
    auto set_4_pair = determined_strings(set_4_strings);
    auto set_4_num_distinct = num_distinct_lcs(set_4_pair.first, set_4_pair.second);
    cout << "n = 12\n";
    cout << "A = " << set_4_pair.first << "\t B = " << set_4_pair.second << endl;
    cout << "number of distinct LCS’s = " << set_4_num_distinct << endl;
    char data4[30];
    make_distinct_list(set_4_pair.first, set_4_pair.second, data4, 0, 0, 0, lcs_len(set_4_pair.first, set_4_pair.second));
    print_strings(dlcs);
    cout << "Time elapsed: " << elapsed_time() << endl;
    cout << endl;

    dlcs.clear();
}
