#ifndef MOLECULE
#define MOLECULE

#include <iostream>
#include <iomanip>
#include <chrono>

/*! \mainpage RNA Secondary Sequence Prediction
 *
 * \section problem_statement_sec Problem Statement
 *
 * We are given a RNA sequence which is a string consisting of the characters in the set of nitrogenous bases \f$\{A, C, G, U\}\f$.
 * The task is to predict the secondary RNA structure for the given RNA sequence which also satifies the following constraints:
 * <ol>
 *  <li>\f$A\f$ can form a pair only with \f$U\f$, and \f$C\f$ can form a pair only with \f$G\f$
 *  <li>There should be no knots in the secondary structure (two base pairs cannot overlap or cross each other)
 *  <li>There should be no kinks in the secondary structure (two bases cannot form a pair if they are close to each other. In this problem, the bases cannot form a pair if there are less than 5 between them)
 *  <li>Each base can form a pair at most once (the same base cannot be a part of two different pairs)
 * </ol>
 *
 * \section algorithm_sec Algorithm
 *
 * The optimal solution to the above problem uses a dynamic programming approach. Let \f$dp(i, j)\f$ be the maximum number of base pairs that can be formed without violating the above constraints in the range \f$[i, j]\f$, where \f$1 \le i, j \le len(sequence)\f$. \n \n
 * The solution for \f$dp(i, j)\f$ is given as: \n
 * \f[dp(i, j) =
 * \begin{cases}
 * 0 & i \ge j - 4 \\
 * \max \begin{cases}
 * dp(i, j - 1), \\
 * \underset{\forall t \in [i, j - 1]}\max \{dp(i, t - 1) + dp(t + 1, j - 1) + 1\}
 * \end{cases} & otherwise
 * \end{cases}\f]
 * The solution to the overall problem is finding the maximum number of base pairs for the given RNA sequence, which is \f$dp(1, len(sequence))\f$.
 * \subsection understanding_the_equation Understanding the Equation
 * Suppose we are trying to find the maximum number of base pairs that can be formed in the interval \f$[i, j]\f$.
 * \image html "rna_secondary_structure_algo.png" width=750cm
 * From the figure, suppose the bases at positions \f$t (t \in [i, j - 1])\f$ and \f$j\f$ can be paired. The problem \f$[i, j]\f$ gets split into two subproblems because of the pairing. \n
 * The first subproblem (highlighted in orange) is for the interval \f$[i, t - 1]\f$, whose solution is \f$dp(i, t - 1)\f$, and \n
 * The second subproblem (highlighted in yellow) is for the interval \f$[t + 1, j - 1]\f$, whose solution is \f$dp(t + 1, j - 1)\f$. \n \n
 * Hence, \f$dp(i, j)\f$ will be the sum of (assuming that pairing \f$t\f$ and \f$j\f$ gives the maximum):
 * <ul>
 *  <li>\f$dp(i, t - 1)\f$ (the first subproblem)
 *  <li>\f$dp(t + 1, j - 1)\f$ (the second subproblem)
 *  <li>\f$1\f$ (for the pair \f$(t, j)\f$)
 * </ul>
 *
 * \section implementation_section Implementation
 * Each RNA sequence has a matrix and an array of base pairs associated with it.
 * We use a matrix \f$maxMatchings\f$ of size \f$n\f$ x \f$n\f$, where \f$n\f$ is the length of the RNA sequence. \f$maxMatchings[i][j]\f$ is the maximum number of base pairs that can be obtained in the interval \f$[i, j]\f$ without violating the constraints.
 * This matrix is used to get the array of base pairs of the secondary structure of RNA.
 *
 * \section Complexity
 * Let \f$T(n)\f$ be the running time to solve the problem whose RNA sequence is of length \f$n\f$. We have the recurrence relation: \n
 * \f$T(n > 5) = \sum_{t = 0}^{n - 2}T(n - 2 - t) * T(t)\f$, \n
 * \f$T(n \le 4) = c\f$ \n
 * On solving the recurrence relation, we get that \f$T(n)\f$ is exponential with \f$n\f$. \n \n
 * Notice that we solve the same subproblem multiple times if the recursive approach is used. To avoid this, we can store the answer to the subproblem once it has been solved. If we come across the same subproblem again, we can obtain it directly from the stored values, instead of solving the subproblem again.
 * This step is known as memoization. \n
 *
 * \subsection order_of_subproblems Order of Subproblems
 * Suppose we have the problem in the interval \f$[i, j]\f$. The solution for this problem depends on subproblem(s) of size(s) smaller than the interval \f$[i, j]\f$. \n
 * Hence, in order to solve a bigger problem, we need to solve the problems of smaller sizes first. Therefore, we need to solve the subproblems of smallest size first (starting with size \f$6\f$ for this problem).
 * Following the above ordering to solve the subproblems and using memoization, the time complexity of the solution becomes \f$O(n^3)\f$.
 * \n \n
 * For memoization, we are storing the answer for each subproblem \f$[i, j]\f$ \f$1 \le i \le j \le n\f$. The total number of subproblems can be calculated as \f$\sum_{i = 1}^{n} \sum_{j = i}^{n} 1\f$, which is \f$O(n^2)\f$. Hence, the space complexity for the solution is \f$O(n^2)\f$.
 */

using namespace std;

/**
 * @brief Checks if two bases can form a bond between them.
 *
 * @param base1 The first nitrogenous base
 * @param base2 The second nitrogenous base
 * @return true For the base pairs - (A, U), (U, A), (C, G), (G, C)
 * @return false Otherwise
 */
bool isValidPairing(char base1, char base2);

/**
 * @brief Given two base positions, the function checks if forming a bond between them results in a kink.
 * A kink is said to be formed if the positions of the bases differ by less than 5
 * @param idx1 The position of the first nitrogenous base
 * @param idx2 The position of the second nitrogenous base (idx2 must be greater than idx1)
 * @return true If idx2 - idx1 <= 4
 * @return false Otherwise
 */
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

    /**
     * @brief Given the RNA sequence, the function fills the memoization table using a dynamic programming algorithm.
     * The table is a 2D matrix, where, table[i][j] represents the maximum number of base pairs that can be obtained in the interval [i, j].
     */
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

    /**
     * @brief For a given RNA sequence, the function computes one of the possible secondary structures for the RNA sequence.
     * It makes use of the memoization table to get the base pairs by backtracking.
     * @param l
     * @param r
     */
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
    /**
     * @brief Set the RNA sequence for the object.
     *
     * @param seq The RNA sequence
     */
    void setSequence(string seq)
    {
        sequence = seq;
    }

    /**
     * @brief Construct a new Molecule object
     *
     * @param seq The RNA sequence
     */
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

    /**
     * @brief Get the length of the RNA sequence.
     *
     * @return int The length of the RNA sequence
     */
    int getSequenceLength()
    {
        return len;
    }

    /**
     * @brief Get the RNA sequence.
     *
     * @return string The RNA sequence
     */
    string getSequence()
    {
        return sequence;
    }

    /**
     * @brief Get the maximum number of base pairs that can be formed from the RNA sequence.
     *
     * @return int The maximum number of base pairs for the RNA sequence
     */
    int getMaxMatchings()
    {
        return ans;
    }

    /**
     * @brief Prints the memoization table.
     * table[i][j] represents the maximum number of base pairs that can be formed in the interval [i, j].
     */
    void printTable()
    {
        for (int i = 0; i < len; i++)
        {
            for (int j = 0; j < len; j++)
                cout << maxMatchings[i][j] << " ";
            cout << '\n';
        }
    }

    /**
     * @brief Prints the base pairs.
     * Each line of the output is of the format:
     * first nitrogenous base --- second nitrogenous base, (position of first base, position of second base)
     */
    void printPairs()
    {
        for (int i = 0; i < ans; i++)
            cout << sequence[matches[i].i] << "---" << sequence[matches[i].j] << "  (" << matches[i].i << ", " << matches[i].j << ")\n";
    }

    /**
     * @brief Prints the base pairs.
     * Each line of the output is of the format:
     * position of first base, position of second base, first nitrogenous base, second nitrogenous base.
     * The output consists of k lines, where k is the maximum number of base pairs that can be formed for the RNA sequence.
     */
    void printBases()
    {
        for (int i = 0; i < ans; i++)
            cout << matches[i].i << " " << matches[i].j << " " << sequence[matches[i].i] << " " << sequence[matches[i].j] << '\n';
    }

    /**
     * @brief Get the time taken to calculate the maximum number of base pairs (filling the memoization table).
     *
     * @return double The time taken to calculate the maximum number of base pairs that can be formed from the RNA sequence
     */
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
    cout << "Enter the RNA sequence: ";
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

    freopen("rna_secondary_structure.txt", "w", stdout);
    cout << rnaSequence.getSequence() << '\n';
    cout << rnaSequence.getMaxMatchings() << '\n';
    rnaSequence.printBases();

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