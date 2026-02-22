# 🔧 AVR Two-Pass Assembler (System Software Project)

## 📘 Project Title
**Design and Implementation of a Two-Pass Assembler for AVR Instruction Set**

---

## 📖 Abstract
This project implements a complete **Two-Pass Assembler for AVR microcontrollers** that translates assembly language programs into machine code. The assembler improves translation accuracy and error handling by dividing the process into two distinct passes:

- **Pass 1 → Tokenization, Symbol Table Generation, Address Assignment**
- **Pass 2 → Instruction Encoding, Symbol Resolution, Machine Code Generation**

The assembler supports AVR instruction formats and uses structured tables such as opcode tables and symbol tables to ensure efficient translation and validation.

---

## 🎯 Problem Statement
Develop an AVR assembler capable of processing assembly programs and generating corresponding machine code using a two-pass mechanism while ensuring accuracy, efficiency, and complete instruction handling.

---

## 🎯 Objectives

### Pass 1 Objectives
- Tokenize input assembly program
- Generate symbol table with label addresses
- Process directives like `.ORG`, `.DB`, `.DW`
- Validate opcodes
- Maintain location counter

### Pass 2 Objectives
- Identify instruction formats
- Resolve symbols (forward/backward references)
- Encode instructions into machine code
- Produce final object code

---

## 🧠 Concept of Two-Pass Assembler

### ✔ Why Two Passes?
A single-pass assembler cannot resolve forward references.  
The two-pass approach solves this limitation.

| Pass | Responsibility |
|------|----------------|
| Pass 1 | Build symbol table and assign addresses |
| Pass 2 | Generate final machine code |

---

## 🏗 Architecture Overview

```
Assembly Program
      ↓
    Pass 1
      ↓
| symtab | intermediate | length |
             ↓
           Pass 2
             ↓
        Object Code
```

---

## 📂 Repository Structure

```
AVR-2PASS-ASSEMBLER/
│
├── pass1.c
├── pass2.c
├── optab.txt
├── optab2.txt
├── input3.txt
│
├── symtab.txt
├── intermediate.txt
├── length.txt
├── output.txt
│
└── README.md
```

---

## 📄 File Description

| File | Purpose |
|------|---------|
| pass1.c | First pass implementation |
| pass2.c | Second pass implementation |
| optab.txt | List of valid mnemonics |
| optab2.txt | Mnemonic + format + opcode mapping |
| input3.txt | Input assembly program |
| symtab.txt | Symbol table (generated) |
| intermediate.txt | Intermediate representation |
| length.txt | Program length |
| output.txt | Final object code |

---

## ⚙️ Requirements
- GCC Compiler
- Terminal / Command Prompt
- Basic C knowledge
- Any Operating System (Linux / Windows / Mac)

---

## ▶️ Execution Steps

### Step 1 — Compile Pass 1
```bash
gcc pass1.c -o pass1
```

### Step 2 — Run Pass 1
```bash
./pass1
```

Generated files:
```
symtab.txt
intermediate.txt
length.txt
```

---

### Step 3 — Compile Pass 2
```bash
gcc pass2.c -o pass2
```

### Step 4 — Run Pass 2
```bash
./pass2
```

Generated file:
```
output.txt
```

---

## 📊 Instruction Format Support

The assembler supports six AVR instruction formats:

| Format | Size | Description |
|--------|------|-------------|
| Format 0 | 16-bit | Single register instructions |
| Format 1 | 16-bit | Register-to-register |
| Format 2 | 16-bit | Register pair + constant |
| Format 3 | 16-bit | Immediate instructions |
| Format 4 | 16-bit | Branch instructions |
| Format 5 | 32-bit | Data direct instructions |

Each instruction may be either **16-bit (2 bytes)** or **32-bit (4 bytes)**.

---

## 🧩 Core Data Structures

### 1️⃣ Symbol Table (symtab)
Stores mapping of labels → memory addresses.

Example:
```
CONST 18
```

Used to resolve variables, jumps, and branch targets.

---

### 2️⃣ Opcode Tables

#### optab.txt
Contains valid mnemonics used for validation during Pass 1.

#### optab2.txt
Contains:
- mnemonic
- instruction format
- machine opcode value

Example entry:
```
LDS 5 91F0FFFF
```

---

## 🔍 Pass 1 Working

Pass 1 scans the source program line by line and:

- Separates label, opcode, operands
- Writes parsed instructions to intermediate file
- Adds labels to symbol table
- Updates location counter
- Detects duplicate symbols
- Calculates program length

---

## ⚙ Pass 2 Working

Pass 2 reads intermediate data and generates machine code:

- Reads intermediate file
- Finds opcode format
- Converts registers to binary
- Resolves symbols using symbol table
- Calculates branch displacement
- Encodes instruction bits
- Writes final machine code

---

## 🧪 Sample Outputs Included

The repository contains generated sample files:

- symtab.txt → symbol table
- intermediate.txt → parsed instructions
- length.txt → program size
- output.txt → final machine code

These are included for demonstration so users can verify output correctness.

---

## 🛠 Directives Supported

| Directive | Function |
|-----------|----------|
| .ORG | Set starting address |
| .DB | Define byte |
| .DW | Define word |
| BYTE. | Reserve memory space |

---

## ❗ Important Execution Notes
- Always run **Pass 1 before Pass 2**
- Do not rename files
- Keep all files in same directory
- Ensure opcode tables exist before execution

---

## 🎓 Educational Value

This project demonstrates core **System Software and Compiler Design concepts**:

- Assembler design
- Symbol resolution
- Instruction encoding
- Machine code generation
- Address calculation
- File handling
- Pass-based compilation logic

---

## 🚀 Key Features
✔ Supports multiple AVR instruction formats  
✔ Detects duplicate labels  
✔ Handles assembler directives  
✔ Resolves forward references  
✔ Generates machine code output  
✔ Modular architecture  

---

## 📚 References
- AVR Instruction Set Documentation
- Embedded Systems Programming References
- System Software Textbooks

---

## 🏁 Conclusion
This project implements a functional AVR assembler that translates human-readable assembly instructions into machine-executable code using a structured two-pass design. The approach ensures accurate symbol resolution, efficient opcode translation, and reliable object code generation.

---

⭐ **Clone → Compile → Run → Understand → Modify → Learn**
