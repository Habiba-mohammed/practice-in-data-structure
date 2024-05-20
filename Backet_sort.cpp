#include <iostream>
#include <vector>
#include <algorithm>

#define ll long long
 using namespace std;
#include  <bits/stdc++.h>











#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// Function to perform bucket sort on strings


void bucketSortFloat(vector<float>& arr, int numBuckets) {
    // Create buckets
    vector<vector<float>> buckets(numBuckets);


    for (int i = 0; i < arr.size(); i++) {
        int index = numBuckets * arr[i];
        buckets[index].push_back(arr[i]);
    }

    // Sort each bucket
    for (vector<float>& bucket : buckets) {
        sort(bucket.begin(), bucket.end());
    }

    // Concatenate sorted strings from buckets
    int index = 0;
    for (const vector<float>& bucket : buckets) {
        for (const float& element : bucket) {
            arr[index++] = element;
        }
    }
}

void bucketSortInt(vector<int>& arr, int numBuckets) {
    // Create buckets
    vector<vector<int>> buckets(numBuckets);

    // Find the range of values
    int maxx = *max_element(arr.begin(), arr.end());
    int minn = *min_element(arr.begin(), arr.end());
    double range = (maxx - minn + 1) / (double)(numBuckets);
    range=ceil(range);

    // Place each element in its corresponding bucket
    for (int i = 0; i < arr.size(); ++i) {
        int index = (arr[i] - minn) / range;
        if (index >= numBuckets)
            index = numBuckets - 1;
        buckets[index].push_back(arr[i]);
    }

    // Sort each bucket
    for (vector<int>& bucket : buckets) {
        sort(bucket.begin(), bucket.end());
    }

    // Concatenate sorted buckets
    int index = 0;
    for (const vector<int>& bucket : buckets) {
        for (const int& element : bucket) {
            arr[index++] = element;
        }
    }
}


int main() {


    vector<float> arrr={0.0003,0.005,1.7,10.888};
    bucketSortFloat(arrr, 2);

    cout << "Sorted floats:" << endl;
    for (const float& element : arrr) {
        cout << element << " ";
    }

    cout<<endl;

    vector<int> arrrr={4,122,5,8,9,10,10000000,122};
    bucketSortInt(arrrr, 2);

    cout << "Sorted integers:" << endl;
    for (const int& element : arrrr) {
        cout << element << " ";
    }

    return 0;
}
