# Embedded & Real-Time Systems Development Portfolio
**Google & Reichman University AI Tech School**

[![C Standard](https://img.shields.io/badge/Standard-C90%20(ANSI)-blue.svg)](https://en.wikipedia.org/wiki/ANSI_C)
[![OS](https://img.shields.io/badge/OS-Linux-orange.svg)](https://www.linux.org/)
[![Memory](https://img.shields.io/badge/Memory-Valgrind_Tested-success.svg)](https://valgrind.org/)

---

## 👨‍💻 Collaborators
This repository is a collaborative technical portfolio actively developed and maintained by:
* **Osama Najjar**
* **Mostafa Taha**

## 🎯 Overview
Welcome to our technical portfolio. This repository serves as a centralized archive of our academic projects and assignments from the **Embedded and Real-Time Systems Development** course at Reichman University, in collaboration with the Google AI Tech School.

Our work focuses on building robust, high-performance systems from the ground up. We emphasize low-level C programming, manual memory management, generic data structure design, and operating system concepts. This repository is a "living document" and is updated as we progress through the course modules.

---

## 📂 Project Structure

Our assignments are organized into three core pillars:

### 1. C Foundations & Basics
The building blocks of our development journey.
* Focuses on: Pointer arithmetic, manual memory management, custom struct implementation, and macro-based performance optimization.

### 2. Generic Data Structures Library (`libds`)
A comprehensive, reusable library built from scratch, adhering to strict C90 standards. 
* Key implementations include: 
  * `Dyn_vec` (Dynamic Array)
  * `genHeap` (Max-Heap/Priority Queue)
  * `HashMap` (Separate chaining)
  * `DoubleLinkList` & `Single_link_list`
  * `Queue` & `Stack` implementations
* *Architecture:* These structures are modular and compiled into a shared dynamic library (`libds.so`) for easy integration.

### 3. Systems & OS Engineering
Low-level Linux system programming, focusing on concurrency and process management.
* **LibsIPC:** An Inter-Process Communication suite featuring:
  * Pipes for bidirectional communication.
  * POSIX Message Queues (`/mq_ping`, `/mq_pong`).
  * Signal handling (`sigaction`).
* **Shell:** A custom Linux shell implementation utilizing process creation and execution APIs.
* **Files & Bits:** Exercises in binary file I/O and low-level bit manipulation.

---

## 🛠️ Quality & Compilation Standards
We maintain high standards for portability and reliability. All projects are compiled with the following flags to ensure strict adherence to safety and standards:

```bash
gcc -ansi -pedantic -Wall -Werror -Wextra -D_POSIX_C_SOURCE=200809L
