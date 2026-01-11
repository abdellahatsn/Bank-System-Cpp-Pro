# Bank Management System (Enterprise v2.0) 🏦🔐

A robust, CLI-based financial management system built with **C++**. This project has evolved from a simple data handler into a **Secure Multi-User Environment**, featuring a custom-built permissions engine and advanced data integrity checks.

## 🚀 Key Features (v2.0 Update)
- **User Authentication:** Integrated login system to secure bank data and restrict unauthorized access.
- **Role-Based Access Control (RBAC):** Granular permission management (Show Client List, Add, Delete, Update, Transactions, and User Management) using bitwise-inspired logic.
- **Transaction System:** Secure Deposit and Withdraw operations with real-time balance validation.
- **Administrative Protection:** Built-in safeguards to prevent self-deletion and unauthorized modification of the 'Admin' account.
- **Data Persistence:** Automatic synchronization with dual flat-file databases (`ClientsFile.txt` and `UsersFile.txt`).

## 🛠️ Technical Implementation
- **Permissions Engine:** Efficient permission checking via logic operations, ensuring high-speed access validation (Complexity: O(1)).
- **In-Memory Management:** Optimized use of `std::vector` and **Pass-by-Reference** to minimize memory overhead and boost performance.
- **Robust Input Validation:** Implemented `std::numeric_limits` and stream clearing (`cin.clear/ignore`) to create a "crash-proof" CLI experience.
- **Custom Serialization:** Developed logic to convert complex struct records into flat-file formats and vice-versa.
- **Clean Code Architecture:** Organized logic using Enums and modular functions for scalability and maintainability.

## 📂 File Structure
- `main.cpp`: Core application logic, Security/Permissions engine, and UI screens.
- `ClientsFile.txt`: Persistent storage for client financial records (Separator: `#//#`).
- `UsersFile.txt`: Secure database for authorized personnel, passwords, and their permission bits.

## 💻 How to Run
1. Clone the repository.
2. Ensure you have a C++ compiler (GCC/Clang).
3. Compile: `g++ main.cpp -o BankSystem`
4. Run: `./BankSystem` (or `BankSystem.exe` on Windows).

---
*Developed by Abdellah Ait Sliman as part of a deep dive into C++, Software Security, and Low-Level Logic.*
