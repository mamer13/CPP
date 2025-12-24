#include <iostream>
#include <vector>

// Finds median of two sorted arrays (merge-based solution)
double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2) {
    std::vector<int> merged;
    int i = 0, j = 0;

    while (i < static_cast<int>(nums1.size()) && j < static_cast<int>(nums2.size())) {
        if (nums1[i] < nums2[j]) merged.push_back(nums1[i++]);
        else merged.push_back(nums2[j++]);
    }
    while (i < static_cast<int>(nums1.size())) merged.push_back(nums1[i++]);
    while (j < static_cast<int>(nums2.size())) merged.push_back(nums2[j++]);

    int n = static_cast<int>(merged.size());
    if (n % 2) return merged[n / 2];
    return (merged[n / 2] + merged[n / 2 - 1]) / 2.0;
}

int main() {
    std::vector<int> a = { 1,3 }, b = { 2 };
    std::cout << "Median of [1,3] and [2]: " << findMedianSortedArrays(a, b) << std::endl;
    return 0;
}
