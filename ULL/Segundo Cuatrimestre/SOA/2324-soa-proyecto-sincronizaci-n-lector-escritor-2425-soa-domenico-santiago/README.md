# Reader-Writer Problem

This project implements a basic solution to the classic Reader-Writer problem using thread synchronization. The goal is to ensure consistent data access when multiple reader threads and a single writer thread operate on shared resources.

## Features

- One writer thread that updates a shared vector.
- Three reader threads:
  - **Reader 1:** Calculates the mode of the updated vector.
  - **Reader 2:** Calculates the standard deviation.
  - **Reader 3:** Calculates the sum of all elements multiplied by the last read value.
- Uses mutexes and condition variables for synchronization.
- Each reader maintains its own copy of data for calculation.




