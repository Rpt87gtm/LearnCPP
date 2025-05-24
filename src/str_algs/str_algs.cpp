#include <str_alg/substr.hpp>

std::vector<int> rpt::prefix_function(const std::string &s) {
    int n = s.size();
    std::vector<int> pi(n);

    for (int i = 1; i < n; ++i) {
        int j = pi[i - 1];

        while (j > 0 && s[i] != s[j]) {
            j = pi[j - 1];
        }

        if (s[i] == s[j]) {
            ++j;
        }
        pi[i] = j;
    }

    return pi;
}

int rpt::substring_index(const std::string &text, const std::string &substring) {
    std::string s = substring + "#" + text;
    auto pi       = prefix_function(s);
    for (int i = substring.size() + 1; i < s.size(); ++i) {
        if (pi[i] == substring.size()) {
            return i - 2 * substring.size();
        }
    }

    return -1;
}