# Practice Problems (1-14)

Standalone C++ programs with simple classes for data structures (stack, queue,
deque, linked lists, phone book and hash tables). Each class keeps its data and
operations together, using plain arrays or pointers inside. There are no STL
container classes, templates or inheritance. Basic array, matrix and sorting
exercises keep ordinary functions. Braces are on separate lines, with
step-by-step comments. Most programs read
input once and print the result, like the supplied array-rotation example.
Only railway reservation keeps a menu for repeated bookings and cancellations.
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
| 4 | `04_alternate_doubly_linked_list.cpp` | Alternate merge and sort |
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

- Rotation prints left and right rotations of the original array. Use k >= 0.
- Polynomials accept non-negative exponents and combine repeated powers.
- Alternate merging consumes both input lists and appends any leftover nodes.
- Railway reservation models one train with 10 seats and unique reservation IDs.
- Hospital priorities: 1 emergency, 2 urgent, 3 routine. Equal priorities use FIFO.
  Read appointments, display their order, serve one patient, then show the rest.
- Scheduling prints both FCFS and SJF for the same input.
  Scheduling ties use arrival time, then process input order. Output includes
  start/finish, waiting/turnaround times, and averages.
- Phone book reads the initial friends, shows sorted names, then searches once
  and inserts the missing friend if space is available.
- Palindrome checks and alphabetical name ordering are case-sensitive; spaces
  are significant. An empty string is a palindrome; maximum length is 100.
- Problem 13 mixes the terms "separate chaining" and "with replacement".
  This uses linked collision chains sharing the 12 slots (coalesced chaining),
  relocating foreign occupants so each chain starts at its home address.
- Problem 14 says "linear probing without changing with replacement" in the
  supplied PDF. Both with-replacement and without-replacement modes are provided
  so either interpretation can be practised. Choose the mode, enter up to nine
  records, view the table, then search for one medicine key.
- Programs expect the prompted input types; failed input ends the program.
  Array sizes and relevant ranges are checked. Use values whose arithmetic fits
  the declared numeric types.
