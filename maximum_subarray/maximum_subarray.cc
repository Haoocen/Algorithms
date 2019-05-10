#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <math.h>
#include "maximum_subarray.h"

using namespace std;

////////////////////////////////////////////////////////////
// Solution 1
////////////////////////////////////////////////////////////
int MaximumSubarray::solutionOne(vector<int> &A) {
    int n = A.size();
    int max = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            int sum = 0;
            for (int k = i; k <= j; ++k) {
                sum = sum + A.at(k);
            }
            if (sum > max) max = sum;
        }
    }
    return max;
}

////////////////////////////////////////////////////////////
// Solution 2
////////////////////////////////////////////////////////////
int MaximumSubarray::solutionTwo(vector<int> &A) {
    int n = A.size();
    int max = 0;
    for (int i = 0; i < n; ++i) {
        int sum = 0;
        for (int j = i; j < n; ++j) {
            sum = sum + A.at(j);
            if (sum > max) max = sum;
        }
    }
    return max;
}

int MaximumSubarray::solutionTwoB(vector<int> &A) {
    int n = A.size();
    A.push_back(0);
    int max = 0;
    vector<int> B{0};
    for(int i = 0; i < n; ++i) {
        B.push_back(B.at(i) + A.at(i));
    }
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            // A[i..j] = B[j+1]-B[i]
            if (B.at(j+1) - B.at(i) > max) {
                max = B.at(j+1) - B.at(i);
            }
        }
    }
    A.pop_back();
    return max;
}
////////////////////////////////////////////////////////////
// Solution 3
////////////////////////////////////////////////////////////

int recur(vector<int> &A, int lo, int hi) {
    if (lo > hi) return 0;
    if (lo == hi)  return A[lo] > 0 ? A[lo] : 0;

    int sum, maxLeftEndsAtMid, maxRightStartsWithMid, mid = (lo + hi) / 2;

    maxLeftEndsAtMid = sum = 0;
    for (int i = mid; i >= lo; --i) {
        sum = sum + A[i];
        maxLeftEndsAtMid = sum > maxLeftEndsAtMid ? sum : maxLeftEndsAtMid;
    }

    maxRightStartsWithMid = sum = 0;
    for (int i = mid + 1; i <= hi; ++i) {
        sum = sum + A[i];
        maxRightStartsWithMid = max(sum, maxRightStartsWithMid);
    }

    return max({maxLeftEndsAtMid+maxRightStartsWithMid, recur(A,lo,mid), recur(A,mid+1,hi)} );
}

int MaximumSubarray::solutionThree(vector<int> &A) {
    int lo = 0;
    int hi = A.size() - 1;
    return recur(A, lo, hi);
}

////////////////////////////////////////////////////////////
// Solution 4
////////////////////////////////////////////////////////////

int MaximumSubarray::solutionFour(vector<int> &A) {
    int maxsol = 0;
    int tail = 0;
    for (int i = 0; i < A.size(); ++i) {
        tail = max(tail + A[i], 0);
        maxsol = max(maxsol, tail);
    }
    return maxsol;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void runCompare(vector<int> &A) {
        
        MaximumSubarray solution;

        int result;
        
        cout << "=================================== results ===================================" << endl;

        auto started = chrono::high_resolution_clock::now();
        result = solution.solutionFour(A);
        auto done = chrono::high_resolution_clock::now();
        cout << "Algorithm Four Gave A Result of " << result << ". It took " << chrono::duration_cast<chrono::milliseconds>(done-started).count() << "ms" << endl;
        
        started = chrono::high_resolution_clock::now();
        result = solution.solutionThree(A);
        done = chrono::high_resolution_clock::now();
        cout << "Algorithm Three Gave A Result of " << result << ". It took " << chrono::duration_cast<chrono::milliseconds>(done-started).count() << "ms" << endl;
        
        started = chrono::high_resolution_clock::now();
        result = solution.solutionTwoB(A);
        done = chrono::high_resolution_clock::now();
        cout << "Algorithm Two Gave A Result of " << result << ". It took " << chrono::duration_cast<chrono::milliseconds>(done-started).count() << "ms" << endl;
       
        started = chrono::high_resolution_clock::now();
        result = solution.solutionOne(A);
        done = chrono::high_resolution_clock::now();
        cout << "Algorithm One Gave A Result of " << result << ". It took " << chrono::duration_cast<chrono::milliseconds>(done-started).count() << "ms" << endl;

}

int main(void){
    cout << "Please enter an array or use random generator. E: enter. G: Generate." << endl;

    char c;

    cin >> c;

    vector<int> A;

    if (c == 'G') {
        cout << "Please enter how many elements fo you want in the array: Range up to 2000 since algorithm one is an Theta(n^3) algorithm" << endl;
        int i; cin >> i;
        
        if (i < 0 || i > 2000 ) return 1;

        for (; i > 0; --i) {
            A.push_back(rand() % 100 * pow(-1, rand()));
        }

        runCompare(A);

    } else if (c == 'E') {
        cout << "Please enter the elemnets you wanna put into the array in order. Enter any character to end." << endl;

        int i;

        cin >> i;

        do {
            if (cin) A.push_back(i);
        } while (cin >> i);
        
        for (int k = 0; k < A.size(); ++k ){
            cout << A.at(k);
        }

        runCompare(A);
    }

}