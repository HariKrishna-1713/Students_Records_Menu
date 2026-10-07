# Student Record Management System

A menu-driven console application in **C** that manages student records with a **dynamically allocated singly linked list** and persists them to a plain-text file. It was built as a mini project to practise structures, pointers, dynamic memory, linked lists, file handling and modular programming.

---

## Table of Contents

1. [Overview](#overview)
2. [Features](#features)
3. [Project Structure](#project-structure)
4. [How the Program Works](#how-the-program-works)
5. [Data Structure](#data-structure)
6. [Module / Function Reference](#module--function-reference)
7. [Data File Format](#data-file-format)
8. [Requirements](#requirements)
9. [Setup and Build](#setup-and-build)
10. [Usage Guide](#usage-guide)
11. [Sample Session](#sample-session)
12. [Algorithms and Complexity](#algorithms-and-complexity)
13. [Memory Management](#memory-management)
14. [Specification Compliance](#specification-compliance)
15. [Known Limitations](#known-limitations)
16. [Troubleshooting](#troubleshooting)
17. [Test Checklist](#test-checklist)
18. [Future Enhancements](#future-enhancements)
19. [Concepts Demonstrated](#concepts-demonstrated)

---

## Overview

The program (`student`) is assembled from several source files, one per operation. When it starts it loads existing records from disk, then shows a menu in a loop until the user exits. All records live in memory as a linked list while the program runs; the user decides when to write them back to disk.

## Features

| Key | Option | Description |
|-----|--------|-------------|
| A/a | Add New Record | Creates a new node. Roll number is assigned automatically; user enters name and percentage |
| D/d | Delete a Record | Delete by roll number, or by name (matching records are listed, then a roll number is requested) |
| S/s | Show the List | Prints all records in a bordered table with colour-coded percentages |
| M/m | Modify a Record | Search by roll number / name / percentage, then edit name or percentage |
| V/v | Save | Writes all records to the data file |
| T/t | Sort the List | Sort by name, percentage, ascending roll number or descending roll number |
| E/e | Exit | Terminates the program |

Additional behaviour:
- Records are **loaded automatically at startup**.
- Menu choices are **case-insensitive** (`a` and `A` both work).
- The screen is cleared on every menu refresh and the program pauses with "Press Enter to continue..." after each action.
- Invalid menu input prints `Invalid input` and returns to the menu.
- Empty-list cases are handled with friendly messages (`Student DB is empty`).

## Project Structure

```
cProject/
├── student_record_menu.c   # main(): loads data, shows menu, dispatches to modules
├── stud_add.c              # global counter, student struct, stud_add()
├── stud_del.c              # stud_del()
├── stud_mod.c              # stud_mod()
├── stud_show.c             # stud_show() with ANSI colours
├── stud_sort.c             # stud_sort()
├── stud_save.c             # stud_save()
├── stud_load.c             # stud_load()
├── studentDB               # data file (plain text)
└── README.md
```

> **Single translation unit:** `student_record_menu.c` pulls in every other `.c` file using `#include "file.c"`, so **only `student_record_menu.c` is compiled**. The include order matters: `stud_add.c` comes first because it defines the `student` struct that every other module needs.

## How the Program Works

```
        ┌────────────────────┐
        │   program starts   │
        └─────────┬──────────┘
                  ▼
        ┌────────────────────┐
        │ DB = stud_load()   │  read studentDB -> build linked list
        └─────────┬──────────┘
                  ▼
        ┌────────────────────┐
   ┌───►│  clear + show menu │
   │    └─────────┬──────────┘
   │              ▼
   │    ┌────────────────────┐
   │    │ read choice (scanf)│
   │    └─────────┬──────────┘
   │              ▼
   │    A: stud_add   D: stud_del   S: stud_show   M: stud_mod
   │    V: stud_save  T: stud_sort  E: exit(0)
   │              │
   │              ▼
   │    "Press Enter to continue..."
   └──────────────┘
```

Functions that can change the head of the list (`stud_add`, `stud_del`, `stud_mod`) take the head pointer and **return the new head**, which `main` stores back in `DB`. Functions that never change the head (`stud_show`, `stud_sort`, `stud_save`) return `void`.

## Data Structure

```c
typedef struct student
{
    int   rollno;               // unique roll number
    char  student_name[50];     // single-word name (max 49 chars)
    float percentage;           // marks in percent
    struct student *link;       // pointer to the next node
} student;
```

```
 head
  │
  ▼
┌────┬───────┬──────┬──────┐   ┌────┬───────┬──────┬──────┐
│ 8  │ Arya  │87.65 │ link ├──►│ 1  │ Hari  │56.76 │ link ├──► ... ──► NULL
└────┴───────┴──────┴──────┘   └────┴───────┴──────┴──────┘
```

A global `int cnt` is declared in `stud_add.c` and updated by `stud_load()` (last loaded roll number + 1).

## Module / Function Reference

| File | Function | Signature | What it does |
|------|----------|-----------|--------------|
| `student_record_menu.c` | `main` | `int main()` | Loads DB, runs the menu loop, calls the other functions |
| `stud_add.c` | `stud_add` | `student *stud_add(student *head)` | Allocates a node, finds the highest existing roll number, assigns `max + 1`, reads name and percentage, appends to the **end** of the list |
| `stud_del.c` | `stud_del` | `student *stud_del(student *head)` | Submenu `R`/`N`. By roll: find, unlink, `free`. By name: list all matches in a table, ask for roll number, delete the node that matches **both** roll number and name |
| `stud_mod.c` | `stud_mod` | `student *stud_mod(student *head)` | Submenu `R`/`N`/`P` to locate a record, then modify its fields |
| `stud_show.c` | `stud_show` | `void stud_show(student *head)` | Prints the table. Percentage colour: green ≥ 90, yellow ≥ 60, red < 60 |
| `stud_sort.c` | `stud_sort` | `void stud_sort(student *head)` | Submenu `N`/`P`/`A`/`D`; sorts in place by swapping node data |
| `stud_save.c` | `stud_save` | `void stud_save(student *head)` | Opens the file in `"w"` mode and writes one record per line (`%d %s %.2f`) |
| `stud_load.c` | `stud_load` | `student *stud_load()` | Opens the file in `"r"` mode, reads records with `fscanf`, appends each to a new list; returns `NULL` if the file is missing |

## Data File Format

Plain text, one record per line, fields separated by a single space:

```
<rollno> <name> <percentage>
```

Sample `studentDB`:

```
8 Arya 87.65
1 Hari 56.76
3 Harsha 75.32
2 Loki 98.77
4 Luffy 67.99
6 Naruto 67.99
5 Zoro 56.74
7 bob 69.00
9 Ansi 65.78
10 Narayana 87.54
```

Notes:
- The order in the file is the order in the list at the time of saving (so a sorted list is saved sorted).
- Names must not contain spaces, otherwise the record cannot be re-read correctly.
- If the file does not exist at startup, the program prints `No previous student records found` and starts with an empty list. The file is created the first time you press `V`.

## Requirements

- **OS:** Linux / Unix-like (uses `system("clear")`, `<stdio_ext.h>` and `__fpurge`, which are not available on standard Windows compilers)
- **Compiler:** GCC (or Clang) with glibc
- **Terminal:** ANSI colour support for the coloured percentage column

## Setup and Build

1. **Fix the paths.** The source currently uses absolute paths under `/home/v25he11g2/cProject/`. Change them in:
   - `student_record_menu.c` – the seven `#include "...c"` lines
   - `stud_load.c` and `stud_save.c` – the `studentDB` path in `fopen`

   For portability use relative names instead:

   ```c
   #include "stud_add.c"
   ...
   fp = fopen("studentDB", "r");
   ```

2. **Compile**

   ```bash
   gcc student_record_menu.c -o student
   ```

   Optional, with warnings and debug info:

   ```bash
   gcc -Wall -Wextra -g student_record_menu.c -o student
   ```

3. **Run**

   ```bash
   ./student
   ```

   If you use relative paths, run the program from the project folder so it finds `studentDB`.

## Usage Guide

### Main menu

```
**** STUDENT RECORD MENU ****

A/a : Add New Record
D/d : Delete a Record
S/s : Show the List
M/m : Modify a Record
V/v : Save
T/t : Sort the List
E/e : Exit

Enter your choice
```

### A – Add
1. Enter the student name (one word).
2. Enter the percentage.
3. The new record is appended with an automatically assigned roll number.

### D – Delete
```
R/r : Delete using Roll Number
N/n : Delete using Name
```
- **R:** enter the roll number; the record is removed at once.
- **N:** enter the name; all records with that name are displayed, then you enter the roll number of the one to delete (useful when several students share a name).

### S – Show
```
+---------+------------------------------------------------+------------+
| Roll No | Student Name                                   | Percentage |
+---------+------------------------------------------------+------------+
| 8       | Arya                                           | 87.65      |
| 1       | Hari                                           | 56.76      |
| 2       | Loki                                           | 98.77      |
+---------+------------------------------------------------+------------+
```

| Percentage | Colour |
|-----------|--------|
| 90 and above | Green |
| 60 to 89.99 | Yellow |
| Below 60 | Red |

### M – Modify
1. **Search by:** `R` roll number, `N` name, or `P` percentage.
2. For name/percentage searches, matching records are shown and you choose a roll number.
3. **Modify field:** `N` name or `P` percentage.

### T – Sort
```
N/n : Sort by Name
P/p : Sort by Percentage            (highest first)
A/a : Sort by Ascending rollno
D/d : Sort by Descending rollno
```
Sorting affects the in-memory list only. Press `V` afterwards to store the new order in the file.

### V – Save
Writes all records to the data file and prints `Student records saved successfully`.

> **Important:** nothing is written to disk automatically. Press `V` before you exit, or your changes are lost.

## Sample Session

```
Enter your choice
a
Enter Student_name
Kiran
Enter percentage
92.5

Press Enter to continue...

Enter your choice
s
(table displays, Kiran appears in green)

Enter your choice
d
R/r : Delete using Roll Number
N/n : Delete using Name
Enter your choice: r
Enter the Student Rollno you want to delete: 5
Record deleted successfully

Enter your choice
v
Student records saved successfully
```

## Algorithms and Complexity

| Operation | Method | Time |
|-----------|--------|------|
| Add | Scan list for max roll number, then walk to tail and append | O(n) |
| Delete | Linear search with a `prev` pointer, unlink, `free` | O(n) |
| Show | Single traversal | O(n) |
| Modify (search) | Linear search | O(n) |
| Sort | Exchange sort: nested loops compare node `i` with every later node `j` and swap the data (`rollno`, `name`, `percentage`) when out of order | O(n²) |
| Save / Load | One pass over the list / file (load appends at the tail by walking the list each time) | O(n) save, O(n²) load |

Sorting swaps the **data inside nodes**, not the node pointers, so `head` never changes during a sort.

## Memory Management

- Each record is allocated with `malloc(sizeof(student))`, and the result is checked for `NULL`.
- A deleted node is released with `free()` after being unlinked.
- In `stud_load`, a node that fails to read is freed before the loop breaks.
- Nodes still in the list at program exit are not freed explicitly; the OS reclaims the memory. A cleanup function would make the program Valgrind-clean:

  ```bash
  valgrind --leak-check=full ./student
  ```

## Specification Compliance

| Requirement (from the mini-project brief) | Status |
|------------------------------------------|--------|
| Menu with A, D, S, M, V, T, E | Done |
| Singly linked list, dynamic nodes | Done |
| Roll number auto-assigned, no duplicates | Partly: no duplicates, but uses `max + 1` instead of the smallest free number |
| Delete by roll number / by name (+ roll number prompt) | Done |
| Tabular display | Done (with borders and colours) |
| Modify with search by R / N / P, then modify N / P | Implemented in `stud_mod.c` (verify the full file) |
| Save to file and load at startup | Done, file is named `studentDB` (spec says `student.dat`) |
| Sort by name and percentage | Done (plus roll number ascending/descending) |
| Exit submenu: `S` save and exit, `E` exit without saving | Not yet: `E` exits directly |

## Known Limitations

- **Smallest-available roll number:** deleting roll 3 of 1-5 leaves a gap that is never reused. The spec wants the smallest unused positive number.
- **Exit submenu** is missing, so unsaved changes can be lost without a warning.
- **Single-word names only:** `scanf("%49s")` stops at the first space, and the file format uses spaces as separators.
- **No input validation:** non-numeric percentage input or values outside 0-100 are not rejected, and a bad `scanf` can leave stray characters in the input buffer.
- **Hard-coded absolute paths** prevent the project from running on another machine without edits.
- **Platform-specific calls:** `system("clear")` and `__fpurge` limit portability to Linux.
- **Including `.c` files** works but is not standard practice (see enhancements).
- **No memory cleanup on exit.**
- **Duplicate names** are allowed (this is intended, which is why delete-by-name asks for a roll number).

## Troubleshooting

| Problem | Likely cause / fix |
|---------|--------------------|
| `fatal error: .../stud_add.c: No such file or directory` | Absolute include paths do not match your machine. Update them (see Setup) |
| `unknown type name 'student'` | `stud_add.c` must be included before the other modules |
| `fatal error: stdio_ext.h` / `__fpurge` undefined | You are on Windows or macOS. Use Linux/WSL, or replace `__fpurge(stdin)` with a loop that reads until `'\n'` |
| `No previous student records found` at start | `studentDB` does not exist at the configured path. Press `V` to create it, or create it manually using the format above |
| Records disappear after restarting | You did not press `V` (Save) before exiting |
| Garbled characters like `[38;5;46m` | Your terminal does not support ANSI colours |
| Table columns misaligned | Terminal window is too narrow (table is about 78 characters wide) |
| A record is skipped when loading | A line has a name containing spaces or an incorrectly formatted line; loading stops at the first bad line |

## Test Checklist

- [ ] Start with no `studentDB` file: message shown, menu works.
- [ ] Add 3+ students, show list, verify roll numbers 1, 2, 3.
- [ ] Add two students with the same name; delete by name and choose one roll number.
- [ ] Delete the first, a middle and the last node.
- [ ] Delete from an empty list: `Student DB is empty`.
- [ ] Delete a non-existent roll number and name: proper "not found" messages.
- [ ] Modify a record by roll number, name and percentage.
- [ ] Sort by each of the four options and verify with Show.
- [ ] Save, exit, restart: data and order are restored.
- [ ] Enter an invalid menu key: `Invalid input`.
- [ ] Percentages 95, 75 and 40 show green, yellow and red.

## Future Enhancements

- Implement smallest-available roll number allocation.
- Add the Save and Exit / Exit Without Saving submenu and an "unsaved changes" flag.
- Support names with spaces (`fgets` and a delimiter such as `,` or `|` in the file).
- Validate all input (range checks, buffer clearing).
- Split into proper modules: `.h` header for the struct and prototypes, separate `.c` files compiled and linked with a `Makefile`.
- Replace data-swapping sort with a pointer-relinking merge sort (O(n log n)).
- Add search/filter, statistics (average, topper) and CSV export.
- Free the entire list before exiting.
- Make the file path configurable (command-line argument or macro).

Example `Makefile` once the project is split into headers and sources:

```make
CC      = gcc
CFLAGS  = -Wall -Wextra -g
SRC     = student_record_menu.c stud_add.c stud_del.c stud_mod.c stud_show.c stud_sort.c stud_save.c stud_load.c
OUT     = student

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT)
```

## Concepts Demonstrated

- Structures and `typedef`
- Pointers and pointer-to-pointer-free list manipulation (head returned from functions)
- Dynamic memory allocation (`malloc`, `free`)
- Singly linked list: insert at tail, delete (head / middle / tail), traverse, sort
- File I/O (`fopen`, `fscanf`, `fprintf`, `fclose`)
- String handling (`strcmp`, `strcpy`)
- Menu-driven design with `switch` and modular code
- ANSI escape codes for terminal colours

## Author

Koteswar Rao Golgani
