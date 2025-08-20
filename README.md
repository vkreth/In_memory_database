# C In-Memory Database

A simple in-memory key-value store written in C.  
This project is inspired by Redis(Kachao) and is built to practice **low-level programming**, **data structures**, and **hash tables** in C.

## 🚀 Features
- Insert (SET) key-value pairs
- Retrieve (GET) values by key
- Delete (DEL) keys
- Check existence (EXISTS) of a key
- Simple hash function for indexing
- Handles collisions with small lists

## 🛠️ How It Works
- Keys and values are stored in a **hash table** of fixed size (`TABLE_SIZE`).
- Each slot in the table holds a small list of `struct member { key, value }`.
- Insertions and lookups use the hash function to find the correct slot.
- Supports basic Redis-like operations:
  - **SET** → insert or update a key
  - **GET** → retrieve value by key
  - **DEL** → delete a key
  - **EXISTS** → check if a key exists

## 📂 Project Structure
