# CMSC-641
This repository contains code, scripts, and results for the CMSC 641 project, which involves integer factorization using Pollard's Rho and \(p-1\) algorithms.

## Project Overview

### Algorithms Implemented:
- **Pollard's Rho**
- **Pollard's \(p-1\)**

### Workflow:
1. **Data Chunking**: Split the data into smaller chunks for parallel processing.
2. **Parallel Execution**: Process the chunks using `tcsh` scripts.
3. **Result Consolidation**: Combine the outputs into a single results file.

---

## How to Run

### Requirements
- **C++ Compiler** with GMP library.
- **Python** for data preprocessing.
- **tcsh** shell for parallel execution.

### Steps
1. Build the factorizer:
   ```bash
   make
