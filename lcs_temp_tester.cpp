#include <vector>
#include <string>
#include <utility>
#include <algorithm>
#include <iostream>
#include <cassert>
#include <cmath> // remove after binary_string_set() has been impl'ed

extern "C"{
#include "timer.h"
}

using namespace std;

unsigned lcs_memoization(const string &s1, const string &s2) {
    //s1 and s2 should have same length, n
    //returns length of LCS first
    //redo with dynamic programming
    int n = s1.length();
    vector <vector<int>> common (n+1, vector<int>(n+1, 0));
    vector <vector<string>> lcstring(n+1, vector<string>(n+1, ""));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++){
            // cout << "i: " << i << "\t j: " << j << endl;
            // cout << "s1: " << s1[i-1] << "\t s2: " << s2[j-1] << endl;
            if (s1[i-1] == s2[j-1]) {
              common[i][j] = common[i-1][j-1] + 1;
              lcstring[i][j] = lcstring[i-1][j-1] + s1[i-1];
            }

            else{
              common[i][j] = max(common[i-1][j], common[i][j-1]);
              if(lcstring[i-1][j].length() > lcstring[i][j-1].length())
                lcstring[i][j] = lcstring[i-1][j];
              else
                lcstring[i][j] = lcstring[j][i-1];
            }
            // cout << "common: " << common[i][j] << endl;
        }
    }
    // cout << "lcstring: " << lcstring[n][n] << endl;
    return common[n][n];
}
// len lcs
// find lcs
// num lcs

int lcs(const string &s1, const string &s2) {

    int n = s1.length();
    vector <string> result; //distinct lcs

    vector <vector <int>> numlcs (n+1, vector<int>(n+1, 0));
    vector <vector <int>> lenlcs (n+1, vector<int>(n+1, 0));

    for (int i=n; i>=0; i--) {  // using the ith character onwards of first string
        for (int j=n; j>=0; j--) {   // using the jth character onwards of second string
              if(i==0 || j==0){
                  numlcs[i][j] = 1;
                  lenlcs[i][j] = 0;
              }
              else {
                  numlcs[i][j] = 0;
                  if (s1[i] == s2[j]) {
                    lenlcs[i][j] = lenlcs[i-1][j-1] + 1;
                    numlcs[i][j] = numlcs[i-1][j-1];
                    if (lenlcs[i-1][j] == lenlcs[i][j])
                        numlcs[i][j] += numlcs[i-1][j];
                    if (lenlcs[i][j-1] == lenlcs[i][j])
                        numlcs[i][j] += numlcs[i][j-1];
                   }
                   else{
                     lenlcs[i][j] = max(lenlcs[i-1][j], lenlcs[i][j-1]);
                   }
              }
              cout << "lcslen ij: " << lenlcs[i][j] << endl;
              cout << "numlcs ij: " << numlcs[i][j] << endl;
          }
    }
    return numlcs[0][0];
}

int main() {

    //testing LCS algorithm
    string s1 = "1001";
    string s2 = "0110";
    int result = lcs_memoization(s1,s2);
    cout << "lcs length: " << result << endl;

    int result2 = lcs(s1, s2);
    cout << "lcs num: " << result2 << endl;

}
