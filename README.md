# 🔐 Multithreaded Cipher Encryption System

A multithreaded encryption program in C implementing **Caesar** and **RSA** ciphers using **POSIX threads**, **semaphores**, and modular design. Built for demonstrating **concurrency** and **synchronization** in Operating Systems.

---

## 🚀 Features

- 🔁 Encrypts words in parallel using multiple threads
- 🔐 Supports Caesar and RSA encryption schemes
- 🧵 Uses POSIX Threads (pthreads) for concurrent processing
- 🛑 Thread-safe encryption via semaphores
- 📂 Modular structure using header and implementation files
- 📄 Command-line interface for interactive testing

---

## 🧠 Concepts Demonstrated

- **Multithreading (pthreads)**
- **Thread synchronization (semaphores)**
- **Modular programming in C**
- **Caesar Cipher logic**
- **RSA public key encryption**
- **Critical sections & race condition avoidance**

---

## 🏗️ Project Structure

Cipher-Encryption-System/
│
├── .git/                   # Git repository folder (automatically created)
├── cipher.c               # Contains Caesar and RSA encryption thread functions
├── cipher.h               # Header file with declarations and shared structures
├── main.c                 # Main program logic, user interface, thread creation
├── pthreadGC2.dll         # Required Windows DLL for pthread support (if on Windows)
│
├── README.md              # Project overview, build instructions, usage, etc.
├── LICENSE                # (Optional) License file if you choose to open-source
└── Makefile               # (Optional but recommended) Build automation script

