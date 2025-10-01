# EduOS

A C++ educational operating system simulator that demonstrates fundamental OS concepts including process scheduling, memory management, and page replacement algorithms.

## Overview

EduOS is designed as a simulating tool for understanding core operating system mechanisms. The simulator implements:

- **Process Scheduling**: FIFO (First-In-First-Out) and SJF (Shortest Job First) algorithms
- **Memory Management**: Paged virtual memory with demand paging
- **Page Replacement**: FIFO and LRU (Least Recently Used) policies

The system simulates a simple computer with 16KB of physical RAM divided into 4KB pages, resulting in 4 physical frames. Processes make memory accesses that trigger page faults when pages are not resident in memory, demonstrating the dynamic behavior of virtual memory systems.

## Architecture

### Core Components

- **Simulation**: Main simulation engine that coordinates all components and manages the clock
- **Scheduler**: Implements process scheduling policies (FIFO, SJF)
- **CPU**: Executes processes and handles memory access requests
- **MMU (Memory Management Unit)**: Translates virtual addresses to physical addresses and handles page faults
- **PageReplacement**: Implements page replacement algorithms when memory is full
- **Process**: Represents a process with its page table and execution state

### Key Features

- Non-preemptive scheduling
- Demand paging with configurable page replacement policies
- Detailed logging of all system events
- Scenario-based testing with customizable workloads

## Prerequisites

- CMake 3.10 or higher
- C++ compiler with C++17 support (GCC, Clang, or MSVC)
- Make

## Installation and Build

1. Clone the repository:
```bash
git clone https://github.com/arpitkumar0007/EduOS---Operating-System-Virtualization-Simulator.git
cd EduOS---Operating-System-Virtualization-Simulator
```

2. Create a build directory:
```bash
mkdir build
cd build
```

3. Generate build files:
```bash
cmake ..
```

4. Compile the project:
```bash
make
```

5. Return to the root directory:
```bash
cd ..
```

## Usage

Run the simulator with a scenario file:

```bash
./build/EduOS scenarios/<filename>.txt
```

### Example

```bash
./build/EduOS scenarios/demo_1_fifo_fifo.txt
```

## Scenarios

The `scenarios` directory contains seven demonstration scenarios that illustrate different aspects of the simulator:

### Basic Demonstrations

**demo_1_fifo_fifo.txt**  
Basic FIFO scheduling with FIFO page replacement. Processes execute in arrival order with simple page replacement. Ideal for understanding fundamental scheduling concepts.

**demo_2_sjf_fifo.txt**  
Shortest Job First scheduling with FIFO page replacement. Demonstrates how shorter jobs are prioritized over longer ones that arrive first.

**demo_3_fifo_lru.txt**  
FIFO scheduling with LRU page replacement. Shows how LRU prevents unnecessary page faults through intelligent replacement decisions based on access patterns.

**demo_4_sjf_lru.txt**  
Combines SJF scheduling and LRU page replacement for optimized system performance. Demonstrates the most efficient configuration for minimizing turnaround time.

### Stress Tests

**demo_5_lru_stress_test.txt**  
Intentionally causes high page fault rates to demonstrate LRU behavior under memory pressure. Two processes require six pages with only four frames available.

**demo_6_sjf_contention.txt**  
Demonstrates process contention for both CPU and memory resources under SJF scheduling. Shows non-preemptive behavior when shorter jobs must wait.

**demo_7_final_stress_test.txt**  
Ultimate stress test with five processes competing for limited resources, simulating a heavily-loaded system. Requires ten unique pages across all processes with constant swapping.

## Scenario File Format

Scenario files use a simple text format:

```
# Comments start with #
scheduler: FIFO | SJF
page_replacement: FIFO | LRU

process: <pid> <name> <arrival_time> <burst_time> <priority> [memory_addresses...]
```

### Example

```
scheduler: SJF
page_replacement: LRU

process: 1 P1 0 6 10 4100 8200 12300
process: 2 P2 2 5 5 16400 20500 4100
```

## Output

The simulator provides detailed logging of all system events:

- Process arrivals and terminations
- Scheduling decisions
- Memory address translations
- Page faults and page replacements
- CPU execution cycles

Each log entry is tagged with the component that generated it (OS, CPU, MMU, SCHEDULER, etc.).

## Project Structure

```
EduOS/
├── main.cpp              # Entry point
├── Simulation.h/cpp      # Main simulation engine
├── Scheduler.h           # Scheduling algorithms
├── CPU.h                 # CPU execution logic
├── MMU.h/cpp             # Memory management unit
├── PageReplacement.h     # Page replacement policies
├── Process.h             # Process representation
├── Logger.h              # Logging utility
├── CMakeLists.txt        # Build configuration
├── scenarios/            # Test scenarios
│   ├── demo_*.txt        # Various demonstration scenarios
│   └── guide.txt         # Detailed scenario descriptions
└── .gitignore
```

## Educational Goals

This simulator is designed to help learners understand:

1. How process scheduling affects system throughput and response time
2. The relationship between virtual and physical memory
3. How page faults occur and are resolved
4. The trade-offs between different page replacement algorithms
5. Resource contention in multi-process systems

## License

This project is intended for educational purposes.
