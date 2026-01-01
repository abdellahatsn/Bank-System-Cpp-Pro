# Bank Management System (C++ Edition) 🏦

A high-performance, CLI-based Bank Management System built with **C++**. This project demonstrates advanced procedural programming techniques, efficient memory management, and data persistence.

## 🚀 Key Features
- **Client Management:** Add, Delete, Update, and Find clients with unique Account Numbers.
- **Transaction System:** Secure Deposit and Withdraw operations with balance validation.
- **Data Persistence:** Automatic synchronization with a flat-file database (`ClientsFile.txt`).
- **Input Validation:** Robust handling of user inputs to prevent buffer errors and duplicate records.
- **Formatted UI:** Clean table views for client lists and total balances using `iomanip`.

## 🛠️ Technical Implementation
- **Memory Efficiency:** Uses `std::vector` and **Pass-by-Reference** to minimize memory overhead.
- **String Manipulation:** Custom `split` logic for parsing data records.
- **Enums & Structs:** Clear logical separation of choices and data models.
- **Buffer Management:** Clean use of `cin.ignore` and `getline` for a seamless user experience.

## 📁 File Structure
- `main.cpp`: Core application logic.
- `ClientsFile.txt`: Data storage file (Semicolon-separated values).

## 💻 How to Run
1. Clone the repository.
2. Ensure you have a C++ compiler (GCC/Clang).
3. Compile: `g++ main.cpp -o BankSystem`
4. Run: `./BankSystem` (or `BankSystem.exe` on Windows).

---
*Created as part of my deep dive into C++ and Data Integrity.*
