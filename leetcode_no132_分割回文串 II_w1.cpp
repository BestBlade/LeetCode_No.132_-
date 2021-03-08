/* ------------------------------------------------------------------|
给你一个字符串 s，请你将 s 分割成一些子串，使每个子串都是回文。

返回符合要求的 最少分割次数 。

 

示例 1：

输入：s = "aab"
输出：1
解释：只需一次分割就可将 s 分割成 ["aa","b"] 这样两个回文子串。
示例 2：

输入：s = "a"
输出：0
示例 3：

输入：s = "ab"
输出：1
 

提示：

1 <= s.length <= 2000
s 仅由小写英文字母组成

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/palindrome-partitioning-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。|
-------------------------------------------------------------------*/

/*  动态规划
*
*	执行用时：36 ms, 在所有 C++ 提交中击败了66.81%的用户
*	内存消耗：7.1 MB, 在所有 C++ 提交中击败了75.43%的用户
*/

#include <iostream>
#include <string> 
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <stack>
#include <queue>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(NULL) {}

};

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

int minCut(string s) {
    int n = s.size();
    vector<vector<bool>> isValid(n, vector<bool>(n, 1));
    //i不能从0开始，因为f(0,4)要用f(1,3)判断，但这时i还在0，因此f(1,3)是个错误值不能使用
    //因此只能从n-1开始遍历
    for (int i = n - 1; i >= 0; --i) {
        for (int j = i + 1; j < n; ++j) {
            isValid[i][j] = (s[i] == s[j]) && isValid[i + 1][j - 1];
        }
    }

    vector<int> cut(n, INT_MAX);
    //从第0个字符开始查找到最远的回文串尾i
    for (int i = 0; i < n; ++i) {
        if (isValid[0][i]) {
            cut[i] = 0;
        }
        else {
            //寻找从0开始到i的最少分割次数j
            for (int j = 0; j < i; ++j) {
                //如果[j+1,i]之间是回文，就找到cut[j]+1和cut[i]之间的最小值
                if (isValid[j + 1][i]) {
                    cut[i] = min(cut[i], cut[j] + 1);
                }
            }
        }
    }
    return cut[n - 1];
}

int main() {
    string s = "aabba";
    minCut(s);
}