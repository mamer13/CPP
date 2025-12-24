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

// smallest number x greater than or equal to n,
// such that the binary representation of x contains only set bits
int smallestNumber(int n) {
    int y = 0;
    while (n != 0) {
        n >>= 1;
        y <<= 1;
        y |= 1;
    }
    return y;
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
    std::stack<char> st;

    for (char c : s) {
        if (c == '(' || c == '{' || c == '[') {
            st.push(c);
        }
        else {
            if (st.empty()) return false;
            char top = st.top();
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
    // mergeTwoLists
    ListNode* list1 = new ListNode(1, new ListNode(3, new ListNode(5)));
    ListNode* list2 = new ListNode(2, new ListNode(4, new ListNode(6)));

    ListNode* merged = mergeTwoLists(list1, list2);

    std::cout << "Merged list: ";
    for (ListNode* p = merged; p != nullptr; p = p->next) {
        std::cout << p->val;
        if (p->next) std::cout << " -> ";
    }
    std::cout << "\n---------------------------------------------------\n";

    // reverse (digits)
    std::cout << "Reversed digits of 12345: " << reverse(12345) << std::endl;
    std::cout << "---------------------------------------------------\n";

    // reverseBits
    std::cout << "Reversed bits of 5: " << reverseBits(5) << std::endl;
    std::cout << "---------------------------------------------------\n";

    // smallestNumber
    int n = 5;
    std::cout << "smallestNumber(5): " << smallestNumber(n) << std::endl;
    std::cout << "---------------------------------------------------\n";

    // romanToInt
    std::cout << "Roman MCMXCIV to int: " << romanToInt("MCMXCIV") << std::endl;
    std::cout << "---------------------------------------------------\n";

    // isPalindrome
    std::cout << "Is 121 palindrome? " << (isPalindrome(121) ? "Yes" : "No") << std::endl;
    std::cout << "---------------------------------------------------\n";

    // isValid
    std::string tests[] = { "()", "()[]{}", "(]", "([)]", "{[]}", "((((((", "{[()()]}" };
    for (const auto& s : tests) {
        std::cout << "Input: " << s
            << " -> " << (isValid(s) ? "Valid" : "Invalid")
            << std::endl;
    }
    std::cout << "---------------------------------------------------\n";

    // longestCommonPrefix
    std::vector<std::string> words = { "flower", "flow", "flight" };
    std::cout << "Longest common prefix: " << longestCommonPrefix(words) << std::endl;
    std::cout << "---------------------------------------------------\n";

    // reverseArray + getSize
    int arr[] = { 1,2,3,4,5 };
    reverseArray(arr, static_cast<int>(getSize(arr)));
    std::cout << "Reversed array: ";
    for (int v : arr) std::cout << v << " ";
    std::cout << "\nSize of arr: " << getSize(arr) << std::endl;
    std::cout << "---------------------------------------------------\n";

    return 0;
}
