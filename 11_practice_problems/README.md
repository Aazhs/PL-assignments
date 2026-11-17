# Practice Problems (1-14)

Standalone C++ programs with simple classes for data structures (stack, queue,
deque, linked lists, phone book and hash tables). Each class keeps its data and
operations together, using plain arrays or pointers inside. There are no STL
container classes, templates or inheritance. Basic array, matrix and sorting
exercises keep ordinary functions. Constructors, method names and pointer/index
operations follow the matching original PL programs, with step-by-step comments.
Most programs read input once and print the result, like the supplied array-rotation example.
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
| 13 | `13_hash_chaining_replacement.cpp` | Given 12 scores, array-based chains with replacement |
| 14 | `14_medical_stock_linear_probing.cpp` | Medical stock, hash modulo 9 |

## Conventions

- Rotation prints left and right rotations of the original array. Use k >= 0.
- Polynomials accept non-negative exponents. Addition combines repeated powers
  in first-appearance order, matching the original addToResult() approach.
- Alternate merging consumes both input lists and appends any leftover nodes.
- Railway reservation models one train with 10 seats and unique reservation IDs.
- Hospital priorities: 1 emergency, 2 urgent, 3 routine. Equal priorities use FIFO.
  Read appointments, display their order, serve one patient, then show the rest.
- Scheduling prints both FCFS and SJF for the same input.
  Scheduling ties use arrival time, then process input order. Output includes
  start/finish, waiting/turnaround times, and averages.
- Phone book reads the initial friends, shows sorted names, then searches once
  and inserts the missing friend if space is available.
- Names, medicine names, and palindrome text are read with `cin >>`, so enter
  one word (use underscores for multiword names). Name sorting and palindrome
  comparisons are case-sensitive. Palindrome text has a maximum length of 100.
- Problem 13 mixes the terms "separate chaining" and "with replacement".
  This uses an index-based linked list: `table[]` stores scores and `next[]`
  stores links between slots. Replacement repairs indices rather than pointers.
  There is no separate Node class or dynamic memory.
- Medical stock uses three plain arrays in one class: `key[]`, `name[]`,
  and `quantity[]`. There is no separate Medicine class.
- Problem 14 says "linear probing without changing with replacement" in the
  supplied PDF. Both with-replacement and without-replacement modes are provided
  so either interpretation can be practised. Choose the mode, enter up to nine
  records, view the table, then search for one medicine key.
- Enter values of the prompted type. Input uses plain `cin >>` statements
  and basic range checks. Use values whose arithmetic fits the declared types.

## Original PL code used

These paths are relative to the parent `PL` folder:

| Practice | Original source | Reused pattern |
| --- | --- | --- |
| 3 | `linked/polynomial.cpp` | `addTerm`, `addToResult`, `add`, head/tail traversal |
| 4 | `linked/doubly.cpp` | `Node`, `Dll`, `create`, node-swapping `sort` |
| 5 | `linked/pizza.cpp` | Circular `Queue`, tail/size/capacity, `add`, `show` |
| 6 | `stack/stack.cpp` | Array stack, `push`, returning `pop`, `peek`, `isEmpty` |
| 8 | `queue.cpp` | front/rear, constructor, `enqueue`, `dequeue`, `display` |
| 9 | `queue.cpp`, `round_robin.cpp` | Queue operations and ready-process index approach |
| 10 | `stack/deque.cpp` | Circular front/rear/count, all four end operations |
| 11 | `assignment10_class.cpp` | Shift-right insertion loop from `insertionSortByName` |

Application-specific changes include patient priority ordering, selecting FCFS/SJF,
comparing deque characters, cancelling a reservation by ID, and alternate merging.
The original polynomial file mixes `Term` and `Node`; the adapted version consistently
uses `Node`. The original doubly linked sort also needs an empty-list check.
No matching implementations were found for rotation, matrix arithmetic, Hanoi,
merge sort or the two hash exercises; those use the same basic function/class style.
The original files outside `assignments` are unchanged.
