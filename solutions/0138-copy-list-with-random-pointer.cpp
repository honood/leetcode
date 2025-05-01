// HoNooD <honood@gmail.com>
// 2025.04.29 23:20
//
// 138. Copy List with Random Pointer
// https://leetcode.com/problems/copy-list-with-random-pointer/?envType=study-plan-v2&envId=top-interview-150
// https://leetcode.com/problems/copy-list-with-random-pointer/?envType=study-plan-v2&envId=top-100-liked

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);

// // Definition for a Node.
// class Node {
// public:
//   int val;
//   Node* next;
//   Node* random;
//
//   Node(int _val) {
//     val = _val;
//     next = nullptr;
//     random = nullptr;
//   }
// };

class Solution {
public:
  Node* copyRandomList(Node* head) {
    return copy_random_list_v4(head);
  }

private:
  // - Time complexity: O(n)
  // - Space complexity: O(n)
  Node* copy_random_list_v1(Node* head) {
    if (head == nullptr) {
      return nullptr;
    }

    unordered_map<Node*, Node*> node_map{{nullptr, nullptr}};

    Node* curr = head;
    while (curr != nullptr) {
      node_map.emplace(curr, new Node{curr->val});
      curr = curr->next;
    }

    curr = head;
    while (curr != nullptr) {
      Node* copy = node_map[curr];
      copy->next = node_map[curr->next];
      copy->random = node_map[curr->random];
      curr = curr->next;
    }

    return node_map[head];
  }

  // - Time complexity: O(n)
  // - Space complexity: O(n)
  Node* copy_random_list_v2(Node* head) {
    if (head == nullptr) {
      return nullptr;
    }

    unordered_map<Node*, Node*> node_map{{head, new Node{head->val}}};

    Node* curr = head;
    while (curr != nullptr) {
      if (curr->next != nullptr && !node_map.contains(curr->next)) {
        node_map.emplace(curr->next, new Node{curr->next->val});
      }

      if (curr->random != nullptr && !node_map.contains(curr->random)) {
        node_map.emplace(curr->random, new Node{curr->random->val});
      }

      if (curr->next != nullptr) {
        node_map[curr]->next = node_map[curr->next];
      }

      if (curr->random != nullptr) {
        node_map[curr]->random = node_map[curr->random];
      }

      curr = curr->next;
    }

    return node_map[head];
  }

  // clang-format off
  /*
  * Approach Description (Flawed):
  * This approach attempts an O(1) space deep copy by repurposing the 'random' pointers
  * of both original and copied nodes for temporary storage during the process.
  *
  * Pass 1:
  * 1. Iterate through the original list (node `curr`).
  * 2. For each `curr`, create a corresponding `copy` node.
  * 3. Link the `next` pointers of the `copy` nodes sequentially to form the basic copied list structure.
  * 4. Store the original random target of `curr` into `copy->random` for temporary storage.
  *    ( `copy->random = curr->random;` )
  * 5. Overwrite `curr->random` to point to its corresponding `copy` node, establishing a
  *    mapping from original to copy.
  *    ( `curr->random = copy;` )
  *
  * Pass 2:
  * 1. Iterate through the original list again (`curr`).
  * 2. For each `curr`:
  *    a. Retrieve the `copy` node using the mapping: `copy = curr->random;`
  *    b. Retrieve the `original_target` node from temporary storage: `original_target = copy->random;`
  *    c. Set the `copy` node's final `random` pointer: If `original_target` is not null,
  *       find its corresponding copy (`target_copy`) using the mapping stored in
  *       `original_target->random` (which should point to `target_copy`). Set
  *       `copy->random = target_copy;`. Otherwise, set `copy->random = nullptr;`.
  *    d. Restore the original node's `random` pointer: `curr->random = original_target;`.
  *
  * Note: This approach is flawed due to information collision and dependency issues
  *       during Pass 2, where setting the copy's random pointer and restoring the
  *       original's random pointer interfere with the required mappings.
  *
  *
  * Counter-Example Demonstrating the Flaw:
  * Consider a list with two nodes A and B, where A->random = B and B->random = A.
  *
  * After Pass 1:
  * - A->random points to A_copy (mapping)
  * - A_copy->random points to B (original target temp storage)
  * - B->random points to B_copy (mapping)
  * - B_copy->random points to A (original target temp storage)
  *
  * During Pass 2, processing node A:
  * 1. `copy_A` is found via `A->random`.
  * 2. `original_target_A` (which is B) is found via `copy_A->random`.
  * 3. To set `copy_A->random`, we need `original_target_A->random` (i.e., `B->random`),
  *    which correctly points to `B_copy`. So, `copy_A->random` is set to `B_copy`.
  * 4. `A->random` is restored to point back to `original_target_A` (which is B).
  *    -> A->random now points to B.
  *
  * During Pass 2, processing node B:
  * 1. `copy_B` is found via `B->random`.
  * 2. `original_target_B` (which is A) is found via `copy_B->random`.
  * 3. To set `copy_B->random`, we need `original_target_B->random` (i.e., `A->random`).
  *    ***FAILURE:*** Because `A->random` was restored in the previous step, it now points
  *    to B, *not* to `A_copy`. The required mapping (`A->random == A_copy`) has been
  *    destroyed prematurely, making it impossible to find `A_copy` (the `target_copy` for B).
  *
  * This demonstrates the inherent timing and dependency conflict in this approach.
  */
  // clang-format on
  Node* copy_random_list_v3(Node* head) {
    throw std::logic_error(
      "The attempted O(1) space approach by repurposing 'random' pointers "
      "for both mapping and temporary storage is fundamentally flawed and "
      "not implementable correctly due to information conflicts and "
      "dependency issues.");
  }

  // Interweaving Nodes
  //
  // - Time complexity: O(n)
  // - Space complexity: O(1)
  Node* copy_random_list_v4(Node* head) {
    if (head == nullptr) {
      return nullptr;
    }

    // Step 1: Create and interweave copied nodes
    // Original: A -> B -> C
    // After   : A -> A' -> B -> B' -> C -> C'
    Node* curr = head;
    while (curr != nullptr) {
      Node* copy = new Node{curr->val};
      copy->next = curr->next;
      curr->next = copy;
      curr = copy->next;
    }

    // Step 2: Assign random pointers for the copied nodes
    curr = head;
    while (curr != nullptr) {
      Node* copy = curr->next;
      if (curr->random != nullptr) {
        copy->random = curr->random->next;
      }
      curr = copy->next;
    }

    // Step 3: Decouple the intertwined lists
    Node dummy_head{0};
    Node* copied_tail = &dummy_head;
    curr = head;
    while (curr != nullptr) {
      assert(curr->next != nullptr);
      copied_tail->next = curr->next;
      copied_tail = copied_tail->next;

      curr->next = curr->next->next;
      curr = curr->next;
    }

    return dummy_head.next;
  }
};
