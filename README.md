# 🧮 Arbitrary Precision Calculator

A **C-based Arbitrary Precision Calculator (APC)** that performs arithmetic operations on numbers of *any size*, overcoming the limitations of standard data types like `int`, `float`, or `double`.

---

## 🚀 Features

- Handles **very large integers** accurately using **doubly linked lists**.
- Supports:
  - ➕ Addition
  - ➖ Subtraction
  - ✖️ Multiplication
  - ➗ Division
- **Dynamic memory allocation** for efficient number storage.
- **Leading zero removal** for clean output.
- Modular design with header and source separation.

---

## 🧩 File Structure

```
📂 Arbitrary-Precision-Calculator
 ├── addition.c        # Addition logic using doubly linked lists
 ├── apc.h             # Header file with structures, macros, and function prototypes
 ├── main.c            # Main file to parse input and call arithmetic functions
 ├── subtraction.c     # (Optional) Subtraction implementation
 ├── multiplication.c  # (Optional) Multiplication implementation
 ├── division.c        # (Optional) Division implementation
 ├── Makefile          # For easy compilation
 └── README.md         # Project documentation
```

---

## ⚙️ How It Works

Numbers are stored as **doubly linked lists**, where each node holds one digit.  
For example, the number `1234` is stored as:

```
1 ⇄ 2 ⇄ 3 ⇄ 4
```

Arithmetic is performed **digit by digit**, starting from the least significant digit, similar to how humans perform manual calculations.

Example snippet from `addition.c`:
```c
while (t1 != NULL || t2 != NULL || carry != 0)
{
    int d1 = (t1 != NULL) ? t1->data : 0;
    int d2 = (t2 != NULL) ? t2->data : 0;
    int sum = d1 + d2 + carry;

    insert_at_begin(&res_head, &res_tail, sum % 10);
    carry = sum / 10;

    if (t1) t1 = t1->prev;
    if (t2) t2 = t2->prev;
}
```

---

## 🛠️ Compilation & Usage

### **Compile**
```bash
gcc main.c addition.c subtraction.c multiplication.c division.c -o apc
```

### **Run**
```bash
./apc
```

### **Example**
```
Enter first number : 999999999999999999
Operation (+, -, *, /): +
Enter second number: 1

Result: 1000000000000000000
```

---

## 📚 Concepts Used

- Doubly Linked Lists  
- Dynamic Memory Allocation  
- Pointers and Structures  
- Modular Programming in C

---

## 🔮 Future Enhancements

- Support for **negative numbers** and **decimal arithmetic**  
- Add **expression parsing** (e.g., `12+345*67`)  
- Implement **exponentiation** and **modulus operations**  
- Interactive or GUI-based interface  

---

K.BHAVANI SANKAR
📧 kottapallibhavanisankar@gmail.com


---

> “Accuracy matters more than speed — especially when numbers grow infinitely large.”
