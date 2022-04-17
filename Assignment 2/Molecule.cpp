#ifndef MOLECULE
#define MOLECULE

#include <iostream>
#include <iomanip>
#include <chrono>

using namespace std;

bool isValidPairing(char base1, char base2);
bool isKink(int idx1, int idx2);

class Molecule
{
private:
    struct Match
    {
        int i; // position of first base
        int j; // position of second base
    };

    string sequence;                           // stores the RNA sequence
    int len;                                   // stores the length of the RNA sequence
    long long **maxMatchings;                  // table where maxMatchings[i][j] = maximum number of bonds that can be formed between indices i and j where i < j
    Match **matches;                           // stores the base pairs
    chrono::duration<double, milli> exec_time; // stores the time (in ms) taken to calulcate the maximum number of bonds

    void calculateMaxMatchings()
    {
        // substrings of length <= 5 cannot have any matches
        // check substrings of length 6 and above

        // substring length can be at most length len
        for (int sz = 6; sz <= len; sz++)
        {
            for (int i = 0; i + sz - 1 < len; i++)
            {
                int j = i + sz - 1;
                maxMatchings[i][j] = maxMatchings[i][j - 1];
                for (int t = i; t <= j; t++)
                {
                    if (isValidPairing(sequence[i], sequence[j]) && !isKink(i, t))
                    {
                        if (t == j)
                            maxMatchings[i][j] = max(maxMatchings[i][j], 1 + maxMatchings[i + 1][t - 1]);
                        else
                            maxMatchings[i][j] = max(maxMatchings[i][j], 1 + maxMatchings[i + 1][t - 1] + maxMatchings[t + 1][j]);
                    }
                }
            }
        }
    }

public:
    void setSequence(string seq)
    {
        sequence = seq;
    }

    Molecule(string seq)
    {
        setSequence(seq);
        len = seq.length();

        maxMatchings = new long long *[len];
        for (int i = 0; i < len; i++)
            maxMatchings[i] = new long long[len];

        for (int i = 0; i < len; i++)
            for (int j = 0; j < len; j++)
                maxMatchings[i][j] = 0;

        auto start = chrono::high_resolution_clock::now();
        calculateMaxMatchings();
        auto stop = chrono::high_resolution_clock::now();
        exec_time = chrono::duration_cast<chrono::microseconds>(stop - start);

        matches = new Match *[len];
        for (int i = 0; i < len; i++)
            matches[i] = new Match[len];
    }

    int getSequenceLength()
    {
        return len;
    }

    string getSequence()
    {
        return sequence;
    }

    long long getMaxMatchings()
    {
        return maxMatchings[0][len - 1];
    }

    void printTable()
    {
        for (int i = 0; i < len; i++)
        {
            for (int j = 0; j < len; j++)
                cout << maxMatchings[i][j] << " ";
            cout << '\n';
        }
    }

    double getExecutionTime()
    {
        return exec_time.count();
    }
};

int main()
{
    // freopen(".\\data\\ndb_test_cases\\unique_rna_sequences.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    string seq;
    cin >> seq;

    cout << "------------------------------------------------------------------------------------------------------------------------\n\n";
    Molecule rnaSequence(seq);
    cout << "RNA sequence:                      " << rnaSequence.getSequence() << '\n';
    cout << "Length of the RNA sequence:        " << rnaSequence.getSequenceLength() << '\n';
    cout << "Maximum number of base pairs:      " << rnaSequence.getMaxMatchings() << '\n';
    cout << "Time taken to calculate max pairs: " << fixed << setprecision(3) << rnaSequence.getExecutionTime() << "ms\n";
    cout << "------------------------------------------------------------------------------------------------------------------------\n\n";

    return 0;
}

bool isValidPairing(char base1, char base2)
{
    return (base1 == 'A' && base2 == 'U') || (base1 == 'U' && base2 == 'A') || (base1 == 'C' && base2 == 'G') || (base1 == 'G' && base2 == 'C');
}

bool isKink(int idx1, int idx2)
{
    return (idx1 >= idx2 - 4);
}

#endif