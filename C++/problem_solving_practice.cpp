#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <stack>
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

// merges two lists to one list
ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
    if ((list1 == nullptr) && (list2 != nullptr)) return list2;
    if ((list2 == nullptr) && (list1 != nullptr)) return list1;
    if ((list1 == nullptr) && (list2 == nullptr)) return nullptr;
    ListNode* dummyHead = new ListNode(0);
    ListNode* list = dummyHead;
    while (list1 && list2) {
        if (list1->val < list2->val) {
            list->next = list1;
            list1 = list1->next;
        }
        else {
            list->next = list2;
            list2 = list2->next;
        }
        list = list->next;
    }
    list->next = list1 ? list1 : list2;
    return dummyHead->next;
}

// Helper to print linked list
void printList(ListNode* head) {
    while (head) {
        std::cout << head->val;
        if (head->next) std::cout << " -> ";
        head = head->next;
    }
    std::cout << std::endl;
}

// Helper to build a linked list from an array
ListNode* buildList(std::initializer_list<int> vals) {
    ListNode* head = nullptr;
    ListNode* tail = nullptr;
    for (int v : vals) {
        if (!head) {
            head = new ListNode(v);
            tail = head;
        }
        else {
            tail->next = new ListNode(v);
            tail = tail->next;
        }
    }
    return head;
}

// Container With Most Water
int maxArea(std::vector<int>& height) {
    int left = 0;
    int right = static_cast<int>(height.size()) - 1;
    int maxArea = 0;

    while (left < right) {
        int width = right - left;
        int h = std::min(height[left], height[right]);
        maxArea = std::max(maxArea, width * h);

        if (height[left] < height[right]) ++left;
        else --right;
    }
    return maxArea;
}

// Remove Duplicates from Sorted Array
int removeDuplicates(std::vector<int>& nums) {
    if (nums.empty()) return 0; // If array is empty, return 0
    std::unordered_set<int> set; // contains numbers to check duplicates
    int k = 0;
    for (int n : nums) {
        // if value is unique
        if (set.count(n) == 0) {
            set.insert(n);
            nums[k++] = n;  //update the array and increase the counter
        }
    }
    return k;
}

// Reverses digits of an integer with overflow check
int reverse(int x) {
    long long y = 0;
    while (x != 0) {
        y = y * 10 + x % 10;
        x /= 10;
    }
    if (y > INT_MAX || y < INT_MIN) return 0;
    return static_cast<int>(y);
}

// Reverses bits of a 32-bit integer
int reverseBits(int n) {
    int x = 0;
    for (int i = 0; i < 32; i++) {
        x <<= 1;
        x |= (n & 1);
        n >>= 1;
    }
    return x;
}

//smallest number x greater than or equal to n, such that the binary representation of x contains only set bits
int smallestNumber(int n) {
    int y = 0;
    // Keep shifting n until all bits are processed
    while (n != 0) {
        n >>= 1;   // Right shift n (to count how many bits it has)
        y <<= 1;   // Make space for one more bit
        y |= 1;    // Set the new bit to 1
    }
    return y;  // y will be like 1, 3, 7, 15, 31, ...
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

// Converts a Roman numeral to an integer
int romanToInt(std::string s) {
    std::unordered_map<char, int> values = {
        {'I', 1}, {'V', 5}, {'X', 10},
        {'L', 50}, {'C', 100}, {'D', 500}, {'M', 1000}
    };

    int total = 0;
    for (int i = 0; i < static_cast<int>(s.size()); i++) {
        if (i + 1 < static_cast<int>(s.size()) && values[s[i]] < values[s[i + 1]])
            total -= values[s[i]];
        else
            total += values[s[i]];
    }
    return total;
}

// Converts a string to a 32-bit signed integer
int myAtoi(std::string s) {
    int i = 0, n = s.size(), result = 0, sign = 1;

    while (i < n && s[i] == ' ') i++;

    if (i < n && (s[i] == '+' || s[i] == '-')) {
        sign = (s[i] == '-') ? -1 : 1;
        i++;
    }

    while (i < n && isdigit(s[i])) {
        int digit = s[i] - '0';
        if (result > (INT_MAX - digit) / 10)
            return (sign == 1) ? INT_MAX : INT_MIN;
        result = result * 10 + digit;
        i++;
    }
    return result * sign;
}

// Finds median of two sorted arrays
double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2) {
    std::vector<int> merged;
    int i = 0, j = 0;

    while (i < nums1.size() && j < nums2.size()) {
        if (nums1[i] < nums2[j]) merged.push_back(nums1[i++]);
        else merged.push_back(nums2[j++]);
    }
    while (i < nums1.size()) merged.push_back(nums1[i++]);
    while (j < nums2.size()) merged.push_back(nums2[j++]);

    int n = merged.size();
    if (n % 2) return merged[n / 2];
    return (merged[n / 2] + merged[n / 2 - 1]) / 2.0;
}

// Checks if an integer is a palindrome
bool isPalindrome(int x) {
    if (x < 0) return false;
    long long y = 0, z = x;
    while (x != 0) {
        y = y * 10 + x % 10;
        x /= 10;
    }
    return z == y;
}

// Checks Valid Parentheses order
bool isValid(const std::string& s) {
    //create a stack to push and pop
    std::stack<char> st;

    for (char c : s) {
        // If it's an opening bracket, push onto stack
        if (c == '(' || c == '{' || c == '[') {
            st.push(c);
        }
        // If it's a closing bracket, check top of stack
        else {
            if (st.empty()) return false; // no matching opening
            char top = st.top();
            // Check if matching type
            if ((c == ')' && top != '(') ||
                (c == ']' && top != '[') ||
                (c == '}' && top != '{'))
                return false;

            st.pop();
        }

    }
    return st.empty();

}

// Finds the longest common prefix in a vector of strings
std::string longestCommonPrefix(std::vector<std::string>& strs) {
    if (strs.empty()) return "";
    std::string prefix = strs[0];

    for (int i = 1; i < static_cast<int>(strs.size()); i++) {
        while (strs[i].find(prefix) != 0) {
            prefix = prefix.substr(0, prefix.size() - 1);
            if (prefix.empty()) return "";
        }
    }
    return prefix;
}

// Zigzag string conversion
std::string convert(std::string s, int numRows) {
    if (numRows == 1 || s.size() <= numRows) return s;

    std::vector<std::string> rows(numRows);
    int currRow = 0;
    bool goingDown = false;

    for (char c : s) {
        rows[currRow] += c;
        if (currRow == 0 || currRow == rows.size() - 1)
            goingDown = !goingDown;
        currRow += goingDown ? 1 : -1;
    }

    std::string result;
    for (std::string r : rows) result += r;
    return result;
}

// Finds two indices whose values sum up to target
std::vector<int> twoSum(std::vector<int>& nums, int target) {
    for (int n = 0; n < static_cast<int>(nums.size()); n++) {
        for (int m = n + 1; m < static_cast<int>(nums.size()); m++) {
            if (nums[m] + nums[n] == target)
                return { n, m };
        }
    }
    return {};
}

// Reverses an array in place
void reverseArray(int* arr, int size) {
    int* start = &arr[0];
    int* end = &arr[size - 1];
    int temp;

    while (start < end) {
        temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}

// Computes size of a raw array at compile time
template <typename T, size_t N>
constexpr size_t getSize(T(&)[N]) {
    return N;
}

int main() {
    // addTwoNumbers
    ListNode* l1 = new ListNode(2, new ListNode(4, new ListNode(3)));
    ListNode* l2 = new ListNode(5, new ListNode(6, new ListNode(4)));
    ListNode* result = addTwoNumbers(l1, l2);
    std::cout << "Sum of two linked lists: ";
    for (ListNode* p = result; p != nullptr; p = p->next)
        std::cout << p->val;
    std::cout << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;

    //mergeTwoLists
    // Create two sorted lists
    ListNode* list1 = buildList({ 1, 3, 5 });
    ListNode* list2 = buildList({ 2, 4, 6 });

    std::cout << "List 1: ";
    printList(list1);
    std::cout << "List 2: ";
    printList(list2);

    // Merge them
    ListNode* merged = mergeTwoLists(list1, list2);

    std::cout << "Merged list: ";
    printList(merged);
    std::cout << "---------------------------------------------------" << std::endl;

    // maxArea
    std::vector<int> heights = { 1,8,6,2,5,4,8,3,7 };
    std::cout << "Max water area: " << maxArea(heights) << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;

    // removeDuplicates
    std::vector<int> numsDup = { 1, 1, 2, 3, 3, 4, 4, 5 };

    int newLength = removeDuplicates(numsDup);

    std::cout << "New length: " << newLength << std::endl;
    std::cout << "Array after removing duplicates: ";
    for (int i = 0; i < newLength; i++) {
        std::cout << numsDup[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;

    // reverse (digits)
    std::cout << "Reversed digits of 12345: " << reverse(12345) << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;

    // reverseBits
    std::cout << "Reversed bits of 5: " << reverseBits(5) << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;

    //smallestNumber
    int n = 5;  // small example
    std::cout << smallestNumber(n) << std::endl;  // Output: 7
    std::cout << "---------------------------------------------------" << std::endl;

    // lengthOfLongestSubstring
    std::cout << "Length of longest substring of 'abcabcbb': "
        << lengthOfLongestSubstring("abcabcbb") << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;

    // romanToInt
    std::cout << "Roman MCMXCIV to int: " << romanToInt("MCMXCIV") << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;

    // myAtoi
    std::cout << "String '   -42' to int: " << myAtoi("   -42") << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;

    // findMedianSortedArrays
    std::vector<int> a = { 1,3 }, b = { 2 };
    std::cout << "Median of [1,3] and [2]: " << findMedianSortedArrays(a, b) << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;

    // isPalindrome
    std::cout << "Is 121 palindrome? " << (isPalindrome(121) ? "Yes" : "No") << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;

    // isValid
    std::string tests[] = { "()", "()[]{}", "(]", "([)]", "{[]}", "((((((", "{[()()]}" };

    for (const auto& s : tests) {
        std::cout << "Input: " << s
            << " -> " << (isValid(s) ? "Valid" : "Invalid")
            << std::endl;
    }
    std::cout << "---------------------------------------------------" << std::endl;

    // longestCommonPrefix
    std::vector<std::string> words = { "flower", "flow", "flight" };
    std::cout << "Longest common prefix: " << longestCommonPrefix(words) << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;

    // convert (Zigzag)
    std::cout << "Zigzag (PAYPALISHIRING, 3): " << convert("PAYPALISHIRING", 3) << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;

    // twoSum
    std::vector<int> nums = { 2,7,11,15 };
    std::vector<int> indices = twoSum(nums, 9);
    std::cout << "TwoSum indices: ";
    for (int idx : indices) std::cout << idx << " ";
    std::cout << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;

    // reverseArray
    int arr[] = { 1,2,3,4,5 };
    reverseArray(arr, getSize(arr));
    std::cout << "Reversed array: ";
    for (int n : arr) std::cout << n << " ";
    std::cout << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;

    // getSize
    std::cout << "Size of arr: " << getSize(arr) << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;

    return 0;
}
