# 🚀 AlphaCompiler: Compiler and Virtual Machine for the Alpha Language

**AlphaCompiler** is a full-fledged compiler and virtual machine implementation for the **Alpha programming language**, developed as part of the CS-340 course at the **University of Crete**. The project showcases end-to-end compiler design, from lexical and syntax analysis to intermediate and target code generation, and execution via a virtual machine.

## 📁 Table of Contents

- [🌟 Features](#-features)
- [🛠️ Technologies Used](#-technologies-used)
- [🚀 Getting Started](#-getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
- [🧩 Usage](#-usage)
- [📄 Project Structure](#-project-structure)
- [👥 Contributors](#-contributors)
- [📜 License](#-license)

---

## 🌟 Features

- **Lexical Analysis** using **Flex**  
- **Syntax Analysis** with **Bison**  
- **Intermediate Code Generation** (quad generation)  
- **Target Code Generation** for binary output  
- **Alpha Virtual Machine (AVM)** for executing compiled binaries  

---

## 🛠️ Technologies Used

- **Flex**: For lexical analysis  
- **Bison**: For syntax parsing  
- **C**: For core compiler and VM implementation  

---

## 🚀 Getting Started

### Prerequisites

Ensure you have the following installed:

- **GCC** compiler
- **Flex** and **Bison**  
- **Make** utility  

Install dependencies on Ubuntu:

```bash
sudo apt-get install build-essential flex bison
```

### Installation

1. **Clone the repository**:

    ```bash
    git clone https://github.com/aangelakis/AlphaCompiler.git
    cd AlphaCompiler
    ```

2. **Build the compiler and virtual machine**:

    ```bash
    make
    ```

---

## 🧩 Usage

### Compile and Run the Compiler

Navigate to the correct directory and compile the project:

```bash
cd Paradoseis/phase_4_5
make
./a.out name_of_test_file
```

### Compile and Run the AVM

After compiling the compiler, compile and run the Alpha Virtual Machine (AVM):

```bash
cd avm
make
./avm.out
```

**Note**: The instructions are printed to the file `instructions_output.txt`.

---

## 📄 Project Structure

```plaintext
AlphaCompiler/
├── Paradoseis/
│   └── phase_4_5/
│       ├── avm/                # Alpha Virtual Machine
│       ├── libs/               # Libraries
│       ├── testMains/          # Test main files
│       ├── tests/Phase4-5/     # Test cases
│       ├── Makefile            # Build automation
│       ├── README.txt          # Additional documentation
│       ├── expression.c        # Expression handling code
│       ├── expression.h        # Expression handling header
│       ├── instruction.c       # Instruction handling code
│       ├── instruction.h       # Instruction handling header
│       ├── parser.y            # Syntax parser (Bison)
│       ├── quads.c             # Quad generation code
│       ├── quads.h             # Quad generation header
│       ├── scanner.l           # Lexical analyzer (Flex)
│       ├── syntaxanal.c        # Syntax analysis code
│       └── yacc_utilities.h    # YACC utility functions
└── README.md                   # Project documentation
```

---

## 👥 Contributors

- **Alexandros Angelakis, Christos Zarkos, Theodoros Chalkidis**

---

## 📜 License

This project is licensed under the **MIT License**. See the [LICENSE](LICENSE) file for details.

---
