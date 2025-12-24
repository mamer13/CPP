#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
#include <climits>

// Definition of a singly-linked list node
struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

// Adds two numbers represented as linked lists
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    ListNode* dummyHead = new ListNode(0);
    ListNode* current = dummyHead;
    int carry = 0;

    while (l1 != nullptr || l2 != nullptr || carry != 0) {
        int sum = carry;
        if (l1) { sum += l1->val; l1 = l1->next; }
        if (l2) { sum += l2->val; l2 = l2->next; }

        carry = sum / 10;
        current->next = new ListNode(sum % 10);
        current = current->next;
    }
    return dummyHead->next;
}

// Container With Most Water
int maxArea(std::vector<int>& height) {
    int left = 0;
    int right = static_cast<int>(height.size()) - 1;
    int maxA = 0;

    while (left < right) {
        int width = right - left;
        int h = std::min(height[left], height[right]);
        maxA = std::max(maxA, width * h);

        if (height[left] < height[right]) ++left;
        else --right;
    }
    return maxA;
}

// Remove Duplicates from Sorted Array (your set-based approach)
int removeDuplicates(std::vector<int>& nums) {
    if (nums.empty()) return 0;
    std::unordered_set<int> set;
    int k = 0;
    for (int n : nums) {
        if (set.count(n) == 0) {
            set.insert(n);
            nums[k++] = n;
        }
    }
    return k;
}

// Returns the length of the longest substring without repeating characters
int lengthOfLongestSubstring(std::string s) {
    std::unordered_set<char> seen;
    int left = 0, maxLength = 0;

    for (int right = 0; right < static_cast<int>(s.size()); ++right) {
        while (seen.count(s[right])) {
            seen.erase(s[left]);
            left++;
        }
        seen.insert(s[right]);
        maxLength = std::max(maxLength, right - left + 1);
    }
    return maxLength;
}

// Converts a string to a 32-bit signed integer
int myAtoi(std::string s) {
    int i = 0, n = static_cast<int>(s.size()), result = 0, sign = 1;

    while (i < n && s[i] == ' ') i++;

    if (i < n && (s[i] == '+' || s[i] == '-')) {
        sign = (s[i] == '-') ? -1 : 1;
        i++;
    }

    while (i < n && isdigit(static_cast<unsigned char>(s[i]))) {
        int digit = s[i] - '0';
        if (result > (INT_MAX - digit) / 10)
            return (sign == 1) ? INT_MAX : INT_MIN;
        result = result * 10 + digit;
        i++;
    }
    return result * sign;
}

// Zigzag string conversion
std::string convert(std::string s, int numRows) {
    if (numRows == 1 || s.size() <= static_cast<size_t>(numRows)) return s;

    std::vector<std::string> rows(numRows);
    int currRow = 0;
    bool goingDown = false;

    for (char c : s) {
        rows[currRow] += c;
        if (currRow == 0 || currRow == static_cast<int>(rows.size()) - 1)
            goingDown = !goingDown;
        currRow += goingDown ? 1 : -1;
    }

    std::string result;
    for (std::string r : rows) result += r;
    return result;
}

// Finds two indices whose values sum up to target (brute force)
std::vector<int> twoSum(std::vector<int>& nums, int target) {
    for (int n = 0; n < static_cast<int>(nums.size()); n++) {
        for (int m = n + 1; m < static_cast<int>(nums.size()); m++) {
            if (nums[m] + nums[n] == target)
                return { n, m };
        }
    }
    return {};
}

int main() {
    // addTwoNumbers
    ListNode* l1 = new ListNode(2, new ListNode(4, new ListNode(3)));
    ListNode* l2 = new ListNode(5, new ListNode(6, new ListNode(4)));
    ListNode* sum = addTwoNumbers(l1, l2);

    std::cout << "Sum of two linked lists: ";
    for (ListNode* p = sum; p != nullptr; p = p->next) std::cout << p->val;
    std::cout << "\n---------------------------------------------------\n";

    // maxArea
    std::vector<int> heights = { 1,8,6,2,5,4,8,3,7 };
    std::cout << "Max water area: " << maxArea(heights) << std::endl;
    std::cout << "---------------------------------------------------\n";

    // removeDuplicates
    std::vector<int> numsDup = { 1, 1, 2, 3, 3, 4, 4, 5 };
    int newLength = removeDuplicates(numsDup);
    std::cout << "New length: " << newLength << "\nArray: ";
    for (int i = 0; i < newLength; i++) std::cout << numsDup[i] << " ";
    std::cout << "\n---------------------------------------------------\n";

    // lengthOfLongestSubstring
    std::cout << "Length of longest substring of 'abcabcbb': "
        << lengthOfLongestSubstring("abcabcbb") << std::endl;
    std::cout << "---------------------------------------------------\n";

    // myAtoi
    std::cout << "String '   -42' to int: " << myAtoi("   -42") << std::endl;
    std::cout << "---------------------------------------------------\n";

    // convert (Zigzag)
    std::cout << "Zigzag (PAYPALISHIRING, 3): " << convert("PAYPALISHIRING", 3) << std::endl;
    std::cout << "---------------------------------------------------\n";

    // twoSum
    std::vector<int> nums = { 2,7,11,15 };
    std::vector<int> indices = twoSum(nums, 9);
    std::cout << "TwoSum indices: ";
    for (int idx : indices) std::cout << idx << " ";
    std::cout << "\n---------------------------------------------------\n";

    return 0;
}
