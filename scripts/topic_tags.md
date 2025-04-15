## 1. [Array (1889)](https://leetcode.com/problem-list/array/)

## 2. [String (784)](https://leetcode.com/problem-list/string/)

## 3. [Hash Table (688)](https://leetcode.com/problem-list/hash-table/)

## 4. [Dynamic Programming (579)](https://leetcode.com/problem-list/dynamic-programming/)

## 5. [Math (573)](https://leetcode.com/problem-list/math/)

## 6. [Sorting (446)](https://leetcode.com/problem-list/sorting/)

## 7. [Greedy (409)](https://leetcode.com/problem-list/greedy/)

## 8. [Depth-First Search (316)](https://leetcode.com/problem-list/depth-first-search/)

## 9. [Binary Search (305)](https://leetcode.com/problem-list/binary-search/)

## 10. [Database (302)](https://leetcode.com/problem-list/database/)

## 11. [Matrix (252)](https://leetcode.com/problem-list/matrix/)

## 12. [Tree (242)](https://leetcode.com/problem-list/tree/)

## 13. [Breadth-First Search (241)](https://leetcode.com/problem-list/breadth-first-search/)

## 14. [Bit Manipulation (236)](https://leetcode.com/problem-list/bit-manipulation/)

## 15. [Two Pointers (218)](https://leetcode.com/problem-list/two-pointers/)

## 16. [Prefix Sum (200)](https://leetcode.com/problem-list/prefix-sum/)

## 17. [Heap (Priority Queue) (194)](https://leetcode.com/problem-list/heap-priority-queue/)

## 18. [Simulation (177)](https://leetcode.com/problem-list/simulation/)

## 19. [Binary Tree (176)](https://leetcode.com/problem-list/binary-tree/)

## 20. [Stack (167)](https://leetcode.com/problem-list/stack/)

## 21. [Counting (159)](https://leetcode.com/problem-list/counting/)

## 22. [Graph (159)](https://leetcode.com/problem-list/graph/)

## 23. [Sliding Window (149)](https://leetcode.com/problem-list/sliding-window/)

## 24. [Design (130)](https://leetcode.com/problem-list/design/)

## 25. [Enumeration (115)](https://leetcode.com/problem-list/enumeration/)

## 26. [Backtracking (108)](https://leetcode.com/problem-list/backtracking/)

## 27. [Union Find (87)](https://leetcode.com/problem-list/union-find/)

## 28. [Linked List (81)](https://leetcode.com/problem-list/linked-list/)

## 29. [Ordered Set (71)](https://leetcode.com/problem-list/ordered-set/)

## 30. [Number Theory (69)](https://leetcode.com/problem-list/number-theory/)

## 31. [Monotonic Stack (65)](https://leetcode.com/problem-list/monotonic-stack/)

A monotonic stack is a stack data structure that maintains its elements in either an increasing or decreasing order. Here are its key properties:

1. Order Maintenance:
    - In a **Monotonic Increasing Stack**, each new element pushed onto the stack is greater than or equal to the element at the top of the stack.
    - In a **Monotonic Decreasing Stack**, each new element pushed onto the stack is less than or equal to the element at the top of the stack.
2. Efficiency:
    - It allows for efficient retrieval of the next greater or next smaller element in a sequence, typically in linear time `O(n)`.
3. Dynamic Updates:
    - As elements are added or removed, the stack dynamically maintains its monotonic property, ensuring that the operations of pushing and popping elements are efficient.
4. Application:
    - Monotonic stacks are commonly used in problems involving the next greater element, next smaller element, stock span problems, and histogram problems.

## 32. [Segment Tree (61)](https://leetcode.com/problem-list/segment-tree/)

## 33. [Trie (57)](https://leetcode.com/problem-list/trie/)

## 34. [Combinatorics (53)](https://leetcode.com/problem-list/combinatorics/)

## 35. [Bitmask (49)](https://leetcode.com/problem-list/bitmask/)

## 36. [Queue (48)](https://leetcode.com/problem-list/queue/)

## 37. [Recursion (47)](https://leetcode.com/problem-list/recursion/)

## 38. [Divide and Conquer (47)](https://leetcode.com/problem-list/divide-and-conquer/)

## 39. [Memoization (42)](https://leetcode.com/problem-list/memoization/)

## 40. [Binary Indexed Tree (42)](https://leetcode.com/problem-list/binary-indexed-tree/)

## 41. [Geometry (40)](https://leetcode.com/problem-list/geometry/)

## 42. [Binary Search Tree (40)](https://leetcode.com/problem-list/binary-search-tree/)

## 43. [Hash Function (39)](https://leetcode.com/problem-list/hash-function/)

## 44. [String Matching (36)](https://leetcode.com/problem-list/string-matching/)

## 45. [Topological Sort (35)](https://leetcode.com/problem-list/topological-sort/)

## 46. [Shortest Path (34)](https://leetcode.com/problem-list/shortest-path/)

## 47. [Rolling Hash (30)](https://leetcode.com/problem-list/rolling-hash/)

## 48. [Game Theory (28)](https://leetcode.com/problem-list/game-theory/)

## 49. [Interactive (23)](https://leetcode.com/problem-list/interactive/)

## 50. [Data Stream (21)](https://leetcode.com/problem-list/data-stream/)

## 51. [Monotonic Queue (18)](https://leetcode.com/problem-list/monotonic-queue/)

A monotonic queue is a data structure that is used to maintain the elements in a specific order (either increasing or decreasing) to quickly find the minimum or maximum within a sliding window. The key property of a monotonic queue is that its elements are ordered in a way that facilitates constant-time retrieval of the minimum or maximum value.

### Key Features:

1. **Monotonic Increasing Queue**: Elements in the queue are arranged such that each successive element is greater than or equal to the previous one. This facilitates quick access to the maximum value within the current sliding window.
2. **Monotonic Decreasing Queue**: Elements in the queue are arranged such that each successive element is less than or equal to the previous one. This structure enables efficient retrieval of the minimum value within the current sliding window.

### Usage:

- Monotonic queues are particularly useful for problems where you need to find extreme values (maximum or minimum) over every possible contiguous subarray (sliding window) of a given size in an array.

### Implementation:

- Data Structure: Implemented typically using a deque (double-ended queue) in programming languages like C++ or Python, allowing efficient insertion and deletion operations from both ends.
- Algorithm:
    1. Iterate through the array while maintaining the monotonic property of the queue.
    2. Adjust the queue to ensure it reflects the monotonic nature as new elements are added or as the sliding window moves.
    3. Retrieve extreme values (maximum or minimum) from the queue as the sliding window moves across the array.

Monotonic queues offer a time-efficient solution (often O(n) complexity) to sliding window problems where maintaining the order of elements is crucial for quick retrieval of extreme values within each window.

## 52. [Brainteaser (17)](https://leetcode.com/problem-list/brainteaser/)

## 53. [Doubly-Linked List (13)](https://leetcode.com/problem-list/doubly-linked-list/)

## 54. [Randomized (12)](https://leetcode.com/problem-list/randomized/)

## 55. [Merge Sort (12)](https://leetcode.com/problem-list/merge-sort/)

## 56. [Counting Sort (11)](https://leetcode.com/problem-list/counting-sort/)

## 57. [Iterator (9)](https://leetcode.com/problem-list/iterator/)

## 58. [Concurrency (9)](https://leetcode.com/problem-list/concurrency/)

## 59. [Probability and Statistics (7)](https://leetcode.com/problem-list/probability-and-statistics/)

## 60. [Quickselect (7)](https://leetcode.com/problem-list/quickselect/)

## 61. [Suffix Array (7)](https://leetcode.com/problem-list/suffix-array/)

## 62. [Bucket Sort (6)](https://leetcode.com/problem-list/bucket-sort/)

## 63. [Line Sweep (6)](https://leetcode.com/problem-list/line-sweep/)

## 64. [Minimum Spanning Tree (5)](https://leetcode.com/problem-list/minimum-spanning-tree/)

## 65. [Shell (4)](https://leetcode.com/problem-list/shell/)

## 66. [Reservoir Sampling (4)](https://leetcode.com/problem-list/reservoir-sampling/)

## 67. [Strongly Connected Component (3)](https://leetcode.com/problem-list/strongly-connected-component/)

## 68. [Eulerian Circuit (3)](https://leetcode.com/problem-list/eulerian-circuit/)

## 69. [Radix Sort (3)](https://leetcode.com/problem-list/radix-sort/)

## 70. [Rejection Sampling (2)](https://leetcode.com/problem-list/rejection-sampling/)

## 71. [Biconnected Component (1)](https://leetcode.com/problem-list/biconnected-component/)

---

- Date: 2025.03.28 17:12
- Code:
    ```js
    // 1. open 'https://leetcode.com/problemset/' in Google Chome;
    // 2. After the page is fully loaded, open the JavaScript Console, then copy
    //    and run the following JavaScript script:
    (function() {
      // Legacy method to copy to clipboard (works in Chrome)
      function copyToClipboardLegacy(text) {
        try {
          // Create temporary textarea element
          const textarea = document.createElement('textarea');
          textarea.value = text;
          textarea.setAttribute('readonly', '');
          textarea.style.cssText = 'position:absolute;left:-9999px;';
          document.body.appendChild(textarea);

          // Select and copy text
          textarea.select();
          const success = document.execCommand('copy');

          // Remove temporary element
          document.body.removeChild(textarea);

          if (success) {
            console.log('✅ Data successfully copied to clipboard');
            return true;
          } else {
            console.warn('⚠️ Copy command was unsuccessful');
            return false;
          }
        } catch (err) {
          console.error('❌ Error copying to clipboard:', err);
          return false;
        }
      }

      // Modern Clipboard API method (requires user interaction)
      async function copyToClipboardModern(text) {
        try {
          await navigator.clipboard.writeText(text);
          console.log('✅ Successfully copied data using Clipboard API');
          return true;
        } catch (err) {
          console.error('❌ Failed to copy using Clipboard API:', err);
          return false;
        }
      }

      try {
        const nextDataElement = document.getElementById('__NEXT_DATA__');
        if (!nextDataElement) {
          console.error('🔍 Could not find __NEXT_DATA__ element');
          return;
        }

        const jsonContent = nextDataElement.textContent;
        const parsedData = JSON.parse(jsonContent);

        const lines = parsedData.props.pageProps.topicTags.map(({name, questionCount, slug}, index) => {
          return `## ${index + 1}. [${name} (${questionCount})](https://leetcode.com/problem-list/${slug}/)`;
        });
        const markdownContent = lines.join('\n\n');
        console.log('📋 Data preview:\n', markdownContent);

        // First try using legacy method (works in Chrome)
        const legacySuccess = copyToClipboardLegacy(markdownContent);
        if (legacySuccess) {
          console.log('🎉 Data copied to clipboard, ready to paste');
        } else {
          // If legacy method fails, create interactive button
          console.log('🔄 Automatic copy failed, creating interactive button...');

          const overlay = document.createElement('div');
          overlay.style.cssText = 'position:fixed;top:0;left:0;width:100%;height:100%;background:rgba(0,0,0,0.7);backdrop-filter:blur(3px);z-index:99999;display:flex;justify-content:center;align-items:center;cursor:pointer;';

          const message = document.createElement('div');
          message.textContent = '👆 Click anywhere to copy data to clipboard';
          message.style.cssText = 'color:white;font-size:20px;';

          overlay.appendChild(message);

          overlay.addEventListener('click', async () => {
            // Try modern API (should work after user interaction)
            const modernSuccess = await copyToClipboardModern(markdownContent);
            if (modernSuccess) {
              message.textContent = '✅ Copy successful!';
            } else {
              // If modern API fails, fall back to legacy method
              const fallbackSuccess = copyToClipboardLegacy(markdownContent);
              message.textContent = fallbackSuccess ? '✅ Copy successful!' : '❌ Copy failed, please try again';
            }

            setTimeout(() => { document.body.removeChild(overlay); }, 1500);
          });

          document.body.appendChild(overlay);
        }
      } catch (error) {
        console.error('❌ Error processing data:', error);
      }
    })();
    ```
