#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <cmath>
#include "input.hpp"
#include "e_coli_genome.hpp"

using namespace std;

/*
    PatternCount(Text, Pattern)
        count ← 0
        for i ← 0 to |Text| − |Pattern|
            if Text(i, |Pattern|) = Pattern
                count ← count + 1
        return count
*/

int patternCount(const string& text, const string& pattern, int cnt=0) {
    int n = text.size(),
        k = pattern.size();
    for (auto i=0; i <= n - k; ++i)
        if (text.substr(i, k) == pattern)
            ++cnt;
    return cnt;
}

// inefficient algorithm:
/*
    FrequentWords(Text, k)
        FrequentPatterns ← an empty set
        for i ← 0 to |Text| − k
            Pattern ← the k-mer Text(i, k)
            Count(i) ← PatternCount(Text, Pattern)
        maxCount ← maximum value in array Count
        for i ← 0 to |Text| − k
            if Count(i) = maxCount
                add Text(i, k) to FrequentPatterns
        remove duplicates from FrequentPatterns
        return FrequentPatterns
*/

// efficiently use a hash table as a counter find frequent words:
/*
    ComputingFrequencies(Text, k)
        for i ← 0 to 4k − 1
            FrequencyArray(i) ← 0
        for i ← 0 to |Text| − k
            Pattern ← Text(i, k)
            j ← PatternToNumber(Pattern)
            FrequencyArray(j) ← FrequencyArray(j) + 1
        return FrequencyArray
*/

using Counter = unordered_map<string, int>;
using Set = unordered_set<string>;
Set frequentWords(const string& text, int k, int t=0, Counter counter={}, int max_cnt=0, Set patterns={}) {
    int n = text.size();
    for (auto i=0; i <= n - k; ++i)
        max_cnt = max(max_cnt, ++counter[text.substr(i, k)]);
    if (max_cnt < t) // threshold t occurrences
        return {};
    for (auto& [pattern, count]: counter)
        if (count == max_cnt)
            patterns.insert(pattern);
    return patterns;
}

string reverseComplement(string s, string t={}) {
    transform(s.begin(), s.end(), back_inserter(t), [](auto c) {
        switch (c) {
            case 'A': return 'T';
            case 'C': return 'G';
            case 'G': return 'C';
            case 'T': return 'A';
            case 'N': return 'N';
        }
        return c; // invalid use-case for neucleotides
    });
    return {t.rbegin(), t.rend()};
}

using VI = vector<int>;
VI patternMatch(const string& text, const string& pattern, VI index={}) {
    int n = text.size(),
        k = pattern.size();
    for (auto i=0; i <= n - k; ++i)
        if (text.substr(i, k) == pattern)
            index.push_back(i);
    return index;
}

using VS = vector<string>;
Set findClumps(const string& text, int k, int L, int t, Set ans={}) {
    int n = text.size();
    for (auto i=0; i <= n - k; ++i) {
        auto chunk = text.substr(i, L);
        auto fw = frequentWords(chunk, k, t);
        ans.insert(fw.begin(), fw.end());
    }
    return ans;
}



int main() {
//    auto ans1 = patternCount(text1, pattern1);
//    cout << ans1 << endl << endl; // 40
//
//    auto ans2 = frequentWords(text2, 12);
//    copy(ans2.begin(), ans2.end(), ostream_iterator<string>(cout, " ")); cout << endl << endl;
//
//    auto ans3 = reverseComplement(text3);
//    cout << ans3 << endl << endl;
//
//    auto ans4 = patternMatch(text4, pattern4);
//    copy(ans4.begin(), ans4.end(), ostream_iterator<int>(cout, " ")); cout << endl << endl;
//
//    auto ans5 = patternMatch(text5, pattern5);
//    copy(ans5.begin(), ans5.end(), ostream_iterator<int>(cout, " ")); cout << endl << endl;
//
//    string ans6;
//    for (auto val6=5437, i=0; i <= 6; val6 /= 4, ++i) {
//        auto mod = val6 % 4;
//        ans6.push_back(
//            mod == 0 ? 'A' :
//            mod == 1 ? 'C' :
//            mod == 2 ? 'G' :
//            mod == 3 ? 'T' : 'N'
//        );
//    }
//    reverse(ans6.begin(), ans6.end());
//    cout << ans6 << endl << endl;
//
//    string ans7;
//    for (auto val7=5437, i=0; i <= 7; val7 /= 4, ++i) {
//        auto mod = val7 % 4;
//        ans7.push_back(
//            mod == 0 ? 'A' :
//            mod == 1 ? 'C' :
//            mod == 2 ? 'G' :
//            mod == 3 ? 'T' : 'N'
//        );
//    }
//    reverse(ans7.begin(), ans7.end());
//    cout << ans7 << endl << endl;
//
//    auto ans8 = findClumps("TGTAAAAGACTGTGTGGCTTCTCATCAGGCGCCATCGTTCAGTCACAACGACCCTTACTTGGTCGCACACAGTACATTGAATACAGGAAACCTCCTCCTATCCGCTCTGTTGAACCTTAACCCGTTACAGCCTGCAGCAACCCGATACAAGAAACGGAATGAACATTACGACGATAGCAGATGAGATTGTCAATTGTCATTGTATTGTCAAAGACGTCGACGGACGTCGAACAATACTGCAGCTATAGCGGTGGTTTGGAAAAGTGTCACGCCCCCGAAAGCACCGCTAATCTTTCTACATTGTCTTGGTACGGTCGGTAACCGAATAGATTATATATGTCTTGAATGTCCGGCGCGCGGAAGGCGCGGGCGCGCGGTCACCACAACCTGTCTGTGCTAGCTTACCAGCTAGCTTACCCCCCCACGCCCACGGATCTAGCCGTCGTGCAAAAGAAGCGTACATACATCTGATTCTCCGTCCCGTTGTCGGACGCTGCGGACGTACGTATGTGACACTTTTTTTCCTGACCTGACTCCCGTTATAGCATTCGTTGCACATTGTTGTCGTCAATTTGCTTTGCGCGAATTGTCGCTGCATTTCCATTTCATTTCCATTTCGCCCCGACTGTCCCCTCGCGGTTCACACTTCCCAAGACAGTCCAGAACAAAGCACAAATCTATAGTTTAAGCGACATTCATTAATCGCCCACAGCTAGAGCGGAATGAGCGGAATAAAGTTATTAACGAGCAATGGAATGGGCAATGGAATGCCAATGGGCTACGATAACGAGTGCCCTGTTTAGTCGGGGGCTTAGTGGTAGTGCTAGAGGTATGCAACTTTGAGAGGCAACTTGCAACTTTTGAAACCAGTTCACGAGCGCTTAGTCTGTACCAGCGATAGGGTATCACTCACATCATTCACATCAAAAACTTCAGACTTCAATTCAAACGCCAGGCTGAGAAGCGCGCGTTGGTCAGTTGCGAGGTCTTCTTCGTTGACTCCCGCTCCAGTTAGAAATTGTCGTCACGCCAGTTGAGGCTCTCTTTTCGTACAGCGAGTGGCCAGCTAGCCCTCGAAATCTGATATTGTCGTGTGTTGTCGTGTGCGATCCCAGACATGGCGCGACCAATTGGCGCGCTGGGCTGATTGTAGATCGCGGGTAGTGGTATGGCGTGACGGCACATTGTTGGCGTAAGCGCGTAAGCGTAAGCGGGGACATACTTATCCTTAATCCTTCATGTCGTCGTGTCGTTCGTGCAAAATCGATTGAGATTGAGACGGTCGTTCAGCTTCTAAGCATTCTCCAGACGCCGCTGTGTCCCCCTAGATACTGCTCCGACGTCATCGCGCATAAGAGGCAAACCGGTGCCACCATGCAAACGACCGTTTAATTGCGTCTAGAGGCCAGCCCAATGCCGGGTTATTACGGCGGTTTGTAAAAGGTGGATTACTACAACCTACTAGTACAAACTACGAAGCATTGAGACGACTTAGAACAGAGCGTGCGTCACGAGAAGAGTGACACGCCATTCTCCTACATAGTGGGTGCCGTTCCGCATTCGCATTCGCATTTCCGCAACATGCAGCAACATCTGCAACTCAGCTCCTCCGGCAGGTAACATCCTCGTGCGCTATAGGTGTCTACACCTCTTCACTTCTACCCTCCACGTGCAAGCGCTCCTGCGGATTAACTCGGTGCATGAAACGGAAATACGACCGATCGGTCAATATCGACAAAGCGACAAAGCGACAAAGCGACAAAGCGACAAAGCGACAAAG",
//        8, 28, 3);
//    copy(ans8.begin(), ans8.end(), ostream_iterator<string>(cout, " ")); cout << endl << endl; // AGCGACAA AAGCGACA AAAGCGAC GCGACAAA CAAAGCGA ACAAAGCG GCGTAAGC CGACAAAG GACAAAGC CGTAAGCG

    auto ans9 = findClumps(e_coli_genome, 9, 500, 3);
    copy(ans9.begin(), ans9.end(), ostream_iterator<string>(cout, " ")); cout << endl << endl; //

    return 0;
}
