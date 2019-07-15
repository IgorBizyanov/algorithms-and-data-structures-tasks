/*
    You are given an array with n integers and intger x. 
    Try to find two elements with sum = x.
    Time should be Theta(n*log(n)).
*/

#include <iostream>
#include <vector>
using namespace std;

vector<int> mergeSort(vector<int>& nums);
void merge(vector<int>& Left, vector<int>& Right, vector<int>& A);
bool areHereSuchElements(vector<int>& nums, int sum);
int binSearch(vector<int>& nums, int l, int r, int target);


int main() {
    int x, n;
    cout << "Enter x: ";
    cin >> x;
    cout << "Enter n: ";
    cin >> n;

    if (n <= 0) {
        cout << "Error. Number of elements cannot be negative.\nTry again." << endl;
        exit(0);
    }
    std::vector<int> nums(n);

    for (int i = 0; i < n; ++i) 
        cin >> nums[i];
    
    /*
        The main idea is to sort the array and use 
        Binary Search for each element after current element.
    */
    areHereSuchElements(nums, x);

    return 0;
}


/*
    This function finds out are here two elements with certain sum in an input array;
    Arguments:
        -   nums: input array
        -   sum:  sum for two elements from array

    Returns:
        -   bool: there are two elements in an array

*/
bool areHereSuchElements(vector<int>& nums, int sum) {
    mergeSort(nums);

    for (int i = 0; i < nums.size(); ++i) {
        int idx = -1;
        if ((idx = binSearch(nums, i+1, nums.size()-1, sum - nums[i])) > -1) {
            cout << "YES, they are " << nums[i] << " and " << nums[idx] << endl;
            return true;
        }
    }

    cout << "NO" << endl;
    return false;
}

/*
    Merge sort is a classical sorting algorithm.
    Includes mergeSort and merge functions.
*/

vector<int> mergeSort(vector<int>& nums) {
    int n = nums.size();

    if (n < 2) //if there is only one element in our vector or if it is empty
        return nums;

    int mid = n/2; //mid element is in the right subarray
    
    vector<int> left(mid);
    vector<int> right(n - mid);

    for (int i = 0; i < mid; i++)
        left[i] = nums[i];
    for (int i = mid; i < n; i++)
        right[i-mid] = nums[i];

    mergeSort(left);
    mergeSort(right);
    merge(left, right, nums);

    return nums;
}


void merge(vector<int>& Left, vector<int>& Right, vector<int>& A) {
    int nl = Left.size();
    int nr = Right.size();

    int i = 0; //for Left
    int j = 0; //for Right
    int k = 0; //for A

    while (i < nl && j < nr) {

        if (Left[i] <= Right[j])
            A[k++] = Left[i++];
        else
            A[k++] = Right[j++];
    }

    while (i < nl)
        A[k++] = Left[i++];
    while (j < nr)
        A[k++] = Right[j++];
}

/*
    Binary search is a classical search algorithm.
    Arguments:
        -   nums:   input array
        -   l:      left index of search
        -   r:      right index of search
        -   target: number to find in an input array

    Returns:
        -   int:    index (>-1) of found element (-1: if there is no such element) 
*/

int binSearch(vector<int>& nums, int l, int r, int target) {

    while (l <= r) {
        int mid = (l+r)/2;
        if (nums[mid] == target)
            return mid;
        else if (nums[mid] > target) 
            r = mid-1;
        else
            l = mid+1;
    }
    return -1;
}
