# Week 1: Where in the Genome Does Replication Begin?
## 1.2 Hidden Messages in the Replication Origin
### Pattern Count
To compute Count(Text, Pattern), our plan is to “slide a window” down Text, checking whether each k-mer substring of Text matches Pattern. We will therefore refer to the k-mer starting at position i of Text as Text(i, k). Throughout this book, we will often use 0-based indexing, meaning that we count starting at 0 instead of 1. In this case, Text begins at position 0 and ends at position |Text| − 1 (|Text| denotes the number of symbols in Text). For example, if Text = GACCATACTG, then Text(4, 3) = ATA. Note that the last k-mer of Text begins at position |Text| − k, e.g., the last 3-mer of GACCATACTG starts at position 10 − 3 = 7. This discussion results in the following pseudocode for computing Count(Text, Pattern).

    PatternCount(Text, Pattern)
        count ← 0
        for i ← 0 to |Text| − |Pattern|
            if Text(i, |Pattern|) = Pattern
                count ← count + 1
        return count

### Frequent Words
A straightforward algorithm for finding the most frequent k-mers in a string Text checks all k-mers appearing in this string (there are |Text| − k + 1 such k-mers) and then computes how many times each k-mer appears in Text. To implement this algorithm, called FrequentWords, we will need to generate an array Count, where Count(i) stores Count(Text, Pattern) for Pattern = Text(i, k)

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

### The frequency array
Compute PatternToNumber(ATGCAA). (You can complete this exercise by hand.)

    input:
        pattern = ATGCAA
        k = 1
    
    lookup table:
        A = 0
        C = 1
        G = 2
        T = 3
    
    ATGCAA
    032100 value from lookup table
    543210 position (ie. 4^pos)
    
    A       T       G       C       A       A
    0*4^5 + 3*4^4 + 2*4^3 + 1*4^2 + 0*4^1 + 0*4^0= 912

    5437 / 4 = 1359 R 1
    1359 / 4 = 339 R 3
    339 / 4 = 84 R 3
    84 / 4 = 21 R 0
    21/4 = 5 R 1
    5/4 = 1 R 1
    1/4 = 0 R 1
    Take the remainders from the bottom up and you get:
    
    1110331, corresponding lexicographically to ﻿CCCAGGC
