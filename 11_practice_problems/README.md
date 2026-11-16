# Practice Problems (1-14)

Standalone C++ programs following the existing assignments' console-based format,
with simple classes/functions and step-by-step comments explaining the algorithms.
Rotation uses repeated shifts, polynomial insertion uses ordinary previous/current
pointers, and scheduling uses a plain array ready queue. These choices favour
ease of understanding over maximum efficiency.
Compile and run each file separately (each has its own `main`):

```sh
c++ -std=c++11 -Wall -Wextra -pedantic 01_array_rotation.cpp -o /tmp/practice
/tmp/practice
```

| No. | File | Topic |
| --- | --- | --- |
| 1 | `01_array_rotation.cpp` | Left/right rotation by k |
| 2 | `02_matrix_operations.cpp` | 2-D array addition and multiplication |
| 3 | `03_polynomial_addition.cpp` | Linked-list polynomial addition |
| 4 | `04_alternate_doubly_linked_list.cpp` | Alternate merge, sort and reverse display |
| 5 | `05_railway_reservation.cpp` | Circular linked list, reserve/cancel/display |
| 6 | `06_eight_queens_stack.cpp` | Iterative stack backtracking, all 92 solutions counted |
| 7 | `07_tower_of_hanoi.cpp` | Recursive disk moves |
| 8 | `08_hospital_priority_queue.cpp` | Stable priority queue for appointments |
| 9 | `09_fcfs_sjf_scheduling.cpp` | Non-preemptive FCFS and SJF with arrival times |
| 10 | `10_palindrome_deque.cpp` | Compare both ends using a deque |
| 11 | `11_phone_book_sentinel.cpp` | Sentinel search and sorted insertion |
| 12 | `12_percentage_merge_sort.cpp` | Merge sort on floating-point percentages |
| 13 | `13_hash_chaining_replacement.cpp` | Given 12 scores, linked chaining with replacement |
| 14 | `14_medical_stock_linear_probing.cpp` | Medical stock, hash modulo 9 |

## Conventions

- Rotation changes the current array. Negative k reverses direction.
- Polynomials accept non-negative exponents and combine repeated powers.
- Alternate merging consumes both input lists and appends any leftover nodes.
- Railway reservation models one train with 10 seats and unique reservation IDs.
- Hospital priorities: 1 emergency, 2 urgent, 3 routine. Equal priorities use FIFO.
- Scheduling ties use arrival time, then process input order. Output includes
  start/finish, waiting/turnaround times, and averages.
- Palindrome checks and alphabetical name ordering are case-sensitive; spaces
  are significant. An empty string is a palindrome.
- Problem 13 mixes the terms "separate chaining" and "with replacement".
  This uses linked collision chains sharing the 12 slots (coalesced chaining),
  relocating foreign occupants so each chain starts at its home address.
- Problem 14 says "linear probing without changing with replacement" in the
  supplied PDF. Both with-replacement and without-replacement modes are provided
  so either interpretation can be practised. Choose the mode before inserting.
- Programs expect the prompted input types; failed input ends the program.
  Array sizes and relevant ranges are checked. Use values whose arithmetic fits
  the declared numeric types.
