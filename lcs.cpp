#include <vector>
#include <string>
#include <utility>
#include <iostream>
#include <cassert>
#include <cmath> // remove after binary_string_set() has been impl'ed

//#include <timer.h>    // need for computing cpu time

using namespace std;

vector<string> binary_string_set(unsigned n) {
    int sz = pow(2.0, n);
    vector<string> res(sz, "");
    return res;
}

unsigned lcs(const string &s1, const string &s2) {
    return 0;
}

pair<string, string> distinct_lcs(const vector<string> &s, vector<string> &lcs) {
    return {};
}

void print_strings(const vector<string> &s) {
    return;
}

int main() {
    // n = 4
    auto set_1_strings = binary_string_set(4);
    assert(set_1_strings.size() == 16);
    vector<string> set_1_output = {};
    auto set_1_pair = distinct_lcs(set_1_strings, set_1_output);
    cout << "n = 4\n";
    cout << "A = " << set_1_pair.first << endl;
    cout << "B = " << set_1_pair.second << endl;
    cout << "number of distinct LCS’s = " << set_1_output.size() << endl;
    print_strings(set_1_output);

    // n = 7
    auto set_2_strings = binary_string_set(7);
    assert(set_2_strings.size() == 128);
    vector<string> set_2_output = {};
    auto set_2_pair = distinct_lcs(set_2_strings, set_2_output);
    cout << "n = 7\n";
    cout << "A = " << set_2_pair.first << endl;
    cout << "B = " << set_2_pair.second << endl;
    cout << "number of distinct LCS’s = " << set_2_output.size() << endl;
    print_strings(set_1_output);

    // n = 10
    auto set_3_strings = binary_string_set(10);
    assert(set_3_strings.size() == 1024);
    vector<string> set_3_output = {};
    auto set_3_pair = distinct_lcs(set_3_strings, set_3_output);
    cout << "n = 10\n";
    cout << "A = " << set_3_pair.first << endl;
    cout << "B = " << set_3_pair.second << endl;
    cout << "number of distinct LCS’s = " << set_3_output.size() << endl;
    print_strings(set_1_output);

    // n = 12
    auto set_4_strings = binary_string_set(12);
    assert(set_4_strings.size() == 4096);
    vector<string> set_4_output = {};
    auto set_4_pair = distinct_lcs(set_4_strings, set_4_output);
    cout << "n = 12\n";
    cout << "A = " << set_4_pair.first << endl;
    cout << "B = " << set_4_pair.second << endl;
    cout << "number of distinct LCS’s = " << set_4_output.size() << endl;
    print_strings(set_1_output);
}
