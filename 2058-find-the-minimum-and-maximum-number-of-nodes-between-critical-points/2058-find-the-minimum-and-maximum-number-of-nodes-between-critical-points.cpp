/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        // If there are less than 3 nodes, there can't be any critical points
        if (!head || !head->next || !head->next->next) {
            return {-1, -1};
        }

        int first_critical = -1;
        int last_critical = -1;
        int min_dist = INT_MAX;

        ListNode* prev = head;
        ListNode* curr = head->next;
        int index = 1; // 0-based index for head, 1-based for the first potential critical point

        while (curr->next != nullptr) {
            ListNode* next_node = curr->next;
            
            // Check if current node is a local maxima or local minima
            if ((curr->val > prev->val && curr->val > next_node->val) ||
                (curr->val < prev->val && curr->val < next_node->val)) {
                
                // If it's the very first critical point we've found
                if (first_critical == -1) {
                    first_critical = index;
                } else {
                    // Calculate the distance from the last seen critical point
                    min_dist = min(min_dist, index - last_critical);
                }
                
                // Update the last_critical to the current index
                last_critical = index;
            }
            
            // Move the pointers forward
            prev = curr;
            curr = next_node;
            index++;
        }

        // If we found less than two critical points, min_dist remains INT_MAX
        if (min_dist == INT_MAX) {
            return {-1, -1};
        }

        // max_dist is the difference between the first and the last critical point
        return {min_dist, last_critical - first_critical};
    }
};