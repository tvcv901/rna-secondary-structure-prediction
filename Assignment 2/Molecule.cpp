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
    int ans;                                   // stores the maximum number of base pairs
    int **maxMatchings;                        // table where maxMatchings[i][j] = maximum number of bonds that can be formed between indices i and j where i < j
    Match *matches;                            // stores the base pairs
    int curMatches;                            // number of base pairs found so far
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
                    if (isValidPairing(sequence[t], sequence[j]) && !isKink(t, j))
                    {
                        if (t == i)
                            maxMatchings[i][j] = max(maxMatchings[i][j], 1 + maxMatchings[t + 1][j - 1]);
                        else
                            maxMatchings[i][j] = max(maxMatchings[i][j], 1 + maxMatchings[i][t - 1] + maxMatchings[t + 1][j - 1]);
                    }
                }
            }
        }
        ans = maxMatchings[0][len - 1];
    }

    void calculateMatchings(int l, int r)
    {
        if (curMatches == ans || maxMatchings[l][r] == 0)
            return;

        if (isValidPairing(sequence[l], sequence[r]) && !isKink(l, r))
        {
            if (maxMatchings[l + 1][r - 1] + 1 == maxMatchings[l][r])
            {
                matches[curMatches].i = l;
                matches[curMatches].j = r;
                curMatches++;
                calculateMatchings(l + 1, r - 1);
                return;
            }
        }

        for (int t = l + 1; t <= r; t++)
        {
            if (isValidPairing(sequence[t], sequence[r]) && !isKink(t, r))
            {
                if (maxMatchings[l][t - 1] + maxMatchings[t + 1][r - 1] + 1 == maxMatchings[l][r])
                {
                    matches[curMatches].i = t;
                    matches[curMatches].j = r;
                    curMatches++;
                    calculateMatchings(l, t - 1);
                    calculateMatchings(t + 1, r - 1);
                    return;
                }
            }
        }

        calculateMatchings(l, r - 1);
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

        maxMatchings = new int *[len];
        for (int i = 0; i < len; i++)
            maxMatchings[i] = new int[len];

        for (int i = 0; i < len; i++)
            for (int j = 0; j < len; j++)
                maxMatchings[i][j] = 0;

        auto start = chrono::high_resolution_clock::now();
        calculateMaxMatchings();
        auto stop = chrono::high_resolution_clock::now();
        exec_time = chrono::duration_cast<chrono::microseconds>(stop - start);

        matches = new Match[ans];
        curMatches = 0;
        calculateMatchings(0, len - 1);
    }

    int getSequenceLength()
    {
        return len;
    }

    string getSequence()
    {
        return sequence;
    }

    int getMaxMatchings()
    {
        return ans;
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

    void printPairs()
    {
        for (int i = 0; i < ans; i++)
            cout << sequence[matches[i].i] << "---" << sequence[matches[i].j] << "  (" << matches[i].i << ", " << matches[i].j << ")\n";
    }

    double getExecutionTime()
    {
        return exec_time.count();
    }
};

int main()
{
    // freopen(".\\data\\timing_input.txt", "r", stdin);
    // freopen("timing_output.txt", "w", stdout);

    string seq;
    cin >> seq;

    cout << "------------------------------------------------------------------------------------------------------------------------\n\n";
    Molecule rnaSequence(seq);
    cout << "RNA sequence:                      " << rnaSequence.getSequence() << '\n';
    cout << "Length of the RNA sequence:        " << rnaSequence.getSequenceLength() << '\n';
    cout << "Maximum number of base pairs:      " << rnaSequence.getMaxMatchings() << '\n';
    cout << "Time taken to calculate max pairs: " << fixed << setprecision(3) << rnaSequence.getExecutionTime() << "ms\n";
    cout << "The base pairs are:\n";
    rnaSequence.printPairs();
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