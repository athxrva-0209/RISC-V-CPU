# RISC-V-CPU
A single cycle RISC-V 32 bit CPU in verilog HDL that can execute c codes compiled into binary instructions using RISC-V compiler.

## Introduction
RISC-V  is an instruction set architecture like ARM based on RISC (Reduced Instruction Set Architecture) principles. What sets RISC-V ISA different from others ISAs is its completely open source and free to use.

Due to being open-source in nature, RISC-V provides a vital step in designing, building and testing new hardware without paying any license fees or royalties.

## About the project
In this project, we shall implement Dijkstra's algorithm for shortest path to find out path from a given graph. 

To achieve this, a RISC-V 32-bit CPU is designed in verilog HDL which can run c codes compiled into binary instructions using RISC-V compiler.

For this, we need to know the basics of CPU architecture, and dijkstra's algorithm.

## Tech Stack
- Quartus Prime
- Modelsim Altera
- FPGA
- Verilog HDL
- Embedded C

## Architecture of RISC-V Implemented
![image](https://github.com/user-attachments/assets/ef7cd460-a875-45ea-99da-b50a6464e15b)

This is basic block diagram of the CPU.

## Implementation of Dijkstra's Algorithm on RISC-V CPU
The constraints for implementing the path planning algorithm must be optimized to ensure it fits within our RISC-V CPU data memory. If the path planner is not optimized enough, then it might not fit in our tightly packed RISC-V CPU data memory.

In the below image, node numbers are marked with blue color are used to make a graph for the path planner.

![image](https://github.com/user-attachments/assets/a59feb90-47c2-4b3b-96e9-58925bf29bfd)

The graph is stored in the data memory in the form of 1D array, which requires less space and hence consumes less data memory.

The path planning algorithm is written in C, which is first tested using a bash script.
After testing, the path planning source code is converted into binary instructions using RISC-V compiler and it is read by instruction memory of CPU.

For example, if start node is 26 and end node is 15, then shortest path given by algorithm, i.e output when source code is checked using bash script is as follows:

![image](https://github.com/user-attachments/assets/f8fd30f8-aacf-4542-bdf0-6fdfcf921070)

Path given by algorithm is [26, 10, 11, 12, 14, 15].
We can verify this path by looking at the graph provided above.

After generating a hex file for this algorithm's source code and loading it in the CPU's data memory, we can verify the output using testbench.
The transcript shows the expected node and the node calculated by CPU.

![image](https://github.com/user-attachments/assets/0580bb67-e5d3-4a0c-bf28-82f0e68609e4)







