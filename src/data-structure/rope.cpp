#include<ext/rope>
using namespace __gnu_cxx;
crope arr; string str; // or rope<T> arr; vector<T> str;
arr.insert(i, str); // Insert at position i with O(log n)
arr.erase(i, n);// Delete n characters from position i with O(log n)
arr.replace(i, n, str); // Replace n characters from position i with str with O(log n)
crope sub = arr.substr(i, n); // Get substring of length n starting from position i with O(log n)