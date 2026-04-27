# Multiverse Tracker (JerryBoree)

A C-based system for managing and tracking "Jerry" entities across different planets, using custom-built generic data structures.

This project was developed as part of an Advanced Programming course and focuses on memory management, modular design, and generic Abstract Data Types (ADTs).

---

## 📌 Overview

The system reads data from a configuration file and manages a collection of "Jerries" (entities) and their associated physical characteristics.

Two main data structures are used:
- A linked list to store all Jerry objects
- A multi-value hash table that maps physical characteristics to Jerries

---

## 🏗️ Project Structure

### 🔹 Core Modules

#### Jerry Module
- `Jerry.c` – Implementation of all Jerry-related functions (creation, destruction, etc.)
- `Jerry.h` – Declarations of structs and public functions

> Note: Some internal helper functions are intentionally hidden and not exposed in the header file.

---

#### Generic Data Structures

##### Linked List
- `LinkedList.c` – Implementation of a generic linked list ADT
- `LinkedList.h` – Function declarations

##### Key-Value Pair
- `KeyValuePair.c` – Generic key-value pair implementation
- `KeyValuePair.h` – Function declarations

##### Hash Table
- `HashTable.c` – Generic hash table using chaining (array of linked lists)
- `HashTable.h` – Function declarations

##### Multi-Value Hash Table
- `MultiValueHashTable.c` – Extension of hash table allowing multiple values per key
- `MultiValueHashTable.h` – Function declarations

> Each key maps to a linked list of values.

---

#### Utilities
- `Defs.h` – General definitions (`bool`, `status`, etc.)

---

## 🚀 Main Program

### `JerryBoreeMain.c`

Responsible for:
- Reading input from a configuration file
- Initializing data structures
- Managing user interaction through a CLI menu

### Key Functionalities:
- Memory-safe creation and destruction of objects
- Shallow and deep copy handling
- Hashing based on physical characteristic names
- Input validation
- Error handling (especially memory allocation failures)

---

## 🧠 Key Functions

- `CopyJerry` – Shallow copy of a Jerry object  
- `FreeJerry` / `FreeShallowJerry` – Memory management  
- `PrintJerry` – Output representation  
- `TransformPCNameToNumber` – Hash function helper  
- `EqualPCName` – Key comparison  
- `read_configuration` – File parsing and initialization  
- `MemoryProblem` – Graceful handling of memory failures  

---

## 🛠️ Technologies & Concepts

- C Programming
- Manual Memory Management
- Abstract Data Types (ADT)
- Generic Programming using function pointers
- Hash Tables with Chaining
- Multi-value indexing
