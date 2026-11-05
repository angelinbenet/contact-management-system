# Contact Management System in C

A simple, menu-driven **Contact Management System** implemented in standard C. It allows users to add, search, modify, delete, sort, and count contacts, with automatic data persistence using binary file handling.

---

## Features

* **Add Contacts:** Create new contact entries with a unique auto-generated ID, name, phone number, email, and address.
* **Display Contacts:** View all stored contacts neatly formatted in a tabular layout.
* **Search Contacts:** Search for specific contacts instantly either by their **Contact ID** or **Name**.
* **Modify Contacts:** Update individual fields (Name, Phone, Email, Address) or all details of an existing contact.
* **Delete Contacts:** Remove a contact by ID with automatic list reorganization.
* **Sort Contacts:** Alphabetically sort your entire contact list by name.
* **Data Persistence:** Automatically saves and loads contacts to/from a local binary file (`contacts.dat`) so your data isn't lost when you exit.

---

## Code Structure

```text
├── main.c           # Source code containing all system logic and menu
└── contacts.dat     # Binary data file generated automatically at runtime
