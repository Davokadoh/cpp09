#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Split into pairs
vector<vector<int> > create_pairs(vector<int>& a) {
    vector<vector<int> > split_array;
    vector<int> temp_array;

    for (int i = 0; i < a.size(); i++) {
        int temp_length = temp_array.size();
        if (temp_length == 1) {
            temp_array.push_back(a[i]);
            split_array.push_back(temp_array);
            temp_array.clear();
        }
        else if (split_array.size() * 2 == a.size() - 1) {
            split_array.push_back(vector<int>(1, a[i]));
        }
        else if (temp_length == 0) {
            temp_array.push_back(a[i]);
        }
    }

    return split_array;
}

// Sort all the pairs
vector<vector<int> > sort_each_pair(vector<vector<int> >& split_array) {
    for (int i = 0; i < split_array.size(); i++) {
        if (split_array[i].size() != 1 && split_array[i][0] > split_array[i][1]) {
            swap(split_array[i][0], split_array[i][1]);
        }
    }

    return split_array;
}

// Build utility functions for recursive insertion sort by highest value in pair
void insert(vector<int>& A, int n, const vector<int>& element) {
    if (n < 0) {
        A[0] = element[0];
    }
    else if (element[1] >= A[n * 2 + 1]) {
        if (n == (A.size() - 1) / 2) {
            A.push_back(element[0]);
            A.push_back(element[1]);
        }
        else {
            A[(n + 1) * 2] = element[0];
            A[(n + 1) * 2 + 1] = element[1];
        }
    }
    else {
        if (n == (A.size() - 1) / 2) {
            A.push_back(A[n * 2]);
            A.push_back(A[n * 2 + 1]);
        }
        else {
            A[(n + 1) * 2] = A[n * 2];
            A[(n + 1) * 2 + 1] = A[n * 2 + 1];
            insert(A, n - 1, element);
        }
    }
}

// Entry function to recursively sort pairs by their higher value
void insertion_sort_pairs(vector<int>& A, int n) {
    if (n < 1) {
        return;
    }
    else {
        insertion_sort_pairs(A, n - 1);
        insert(A, n - 1, vector<int>(A.begin() + n * 2, A.begin() + n * 2 + 2));
    }
}

// Recursive function to generate nth Jacobsthal number
int jacobsthal(int n) {
    if (n == 0) {
        return 0;
    }
    else if (n == 1) {
        return 1;
    }
    else {
        return jacobsthal(n - 1) + 2 * jacobsthal(n - 2);
    }
}

// Build a sequence of valid Jacobsthal numbers, given an array length
vector<int> build_jacob_insertion_sequence(int array_len) {
    vector<int> end_sequence;
    int jacob_index = 3;

    while (jacobsthal(jacob_index) < array_len - 1) {
        end_sequence.push_back(jacobsthal(jacob_index));
        jacob_index++;
    }

    return end_sequence;
}

// Recursively sort the larger set of elements into sorted set
void sort_by_larger_value(vector<int>& sorted_split_array) {
    insertion_sort_pairs(sorted_split_array, sorted_split_array.size() / 2 - 1);
}

// Create sequence
vector<int> create_s(vector<vector<int> >& sorted_split_array, int straggler, bool print_comparison_estimation) {
    vector<int> S;
    vector<int> pend;
    int comparisons_made = 0;

    for (int i = 0; i < sorted_split_array.size(); i++) {
        S.push_back(sorted_split_array[i][1]);
        pend.push_back(sorted_split_array[i][0]);
    }

    S.insert(S.begin(), pend[0]);

    int iterator = 0;
    int jacobindex = 3;
    vector<int> indexSequence(1, 1);
    string last = "default";

    vector<int> jacob_insertion_sequence = build_jacob_insertion_sequence(pend.size());

    while (iterator <= pend.size()) {
        if (!jacob_insertion_sequence.empty() && last != "jacob") {
            indexSequence.push_back(jacob_insertion_sequence[0]);
            int item = pend[jacob_insertion_sequence[0] - 1];
            jacob_insertion_sequence.erase(jacob_insertion_sequence.begin());
            last = "jacob";
        }
        else {
            if (find(indexSequence.begin(), indexSequence.end(), iterator) != indexSequence.end()) {
                iterator++;
            }
            int item = pend[iterator - 1];
            indexSequence.push_back(iterator);
            last = "not-jacob";
        }

        int insertion_point = lower_bound(S.begin(), S.end(), item) - S.begin();
        S.insert(S.begin() + insertion_point, item);
        iterator++;
        jacobindex++;
        comparisons_made += 2;
    }

    if (straggler) {
        int insertion_point = lower_bound(S.begin(), S.end(), straggler) - S.begin();
        S.insert(S.begin() + insertion_point, straggler);
        comparisons_made += 2;
    }

    if (print_comparison_estimation) {
        cout << "Approximate Comparisons Made:" << endl;
        cout << comparisons_made << endl;
    }

    return S;
}

// Ford-Johnson Merge-Insertion Sort
vector<int> merge_insertion_sort(vector<int>& A) {
    cout << "Starting Array:" << endl;
    for (int i = 0; i < A.size(); i++) {
        cout << A[i] << " ";
    }
    cout << endl;

    bool hasStraggler = A.size() % 2 != 0;
    int straggler = 0;

    if (hasStraggler) {
        straggler = A[A.size() - 1];
        A.pop_back();
    }

    vector<vector<int> > split_array = create_pairs(A);
    vector<vector<int> > sorted_split_array = sort_each_pair(split_array);
    sort_by_larger_value(sorted_split_array);
    vector<int> S = create_s(sorted_split_array, straggler, true);

    cout << "Sorted Array:" << endl;
    for (int i = 0; i < S.size(); i++) {
        cout << S[i] << " ";
    }
    cout << endl;

    return S;
}

int main() {
    vector<int> A = {5, 8, 3, 2, 7, 1, 6, 4};
    vector<int> sorted_array = merge_insertion_sort(A);

    return 0;
}
