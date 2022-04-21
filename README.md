# CS F364 (Design and Analysis of Algorithms) Assignments

## Assignment 1 - Sweep Line Algorithm (Bentley-Ottmann)

### Directory Structure

`headers` folder - contains implementation for Point, Line and Node data structures and Balanced BST class declarations

`plots` folder - contains plot for Timing Analysis

`resources` folder - contains resources for the assignment

`EQBalancedBST.cpp` - contains implementation for event queue data structure

`SBalancedBST.cpp` - contains implementation for status data structure

`eventQueue.cpp` and `status.cpp` - for testing working of both data structures

`Makefile` - for creating object files and executable files

### Steps to run `eventQueue.cpp` and `status.cpp` (Works only in a Windows environment)

1. Open Command Prompt or Powershell and run `make` in the `Assignment 1` folder of the project (make sure you have GNUMake installed on your machine)
2. Run `.\EQoutput.exe` to test the event queue data structure<br>
   Run `.\SBoutput.exe` to test the status data structure<br>
3. Run `make clean` to remove object files and executable files

## Assignment 2 - RNA Secondary Structure (Dynamic Programming Approach)

### Directory Structure

`data` folder - contains NDB Test Cases and Timing Analysis data

`plots` folder - contains plot for Timing Analysis

`resources` folder - contains resources for the assignment

`visualization` folder - contains `visualizer.py` python program to visualize the secondary structure

`Molecule.cpp` - contains implementation for the dynamic programming approach

### Steps to run `eventQueue.cpp` and `status.cpp` (Works only in a Windows environment)

1. Open Command Prompt or Powershell and run `.\molecule.bat` to input an RNA sequence.

2. To visualize the output,

   `cd visualization`

   `python visualizer.py`
