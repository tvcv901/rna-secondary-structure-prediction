# cs-f364-assignments<br><br>CS F364 (Design and Analysis of Algorithms) Assignments

## Assignment 1 - Sweep Line Algorithm (Bentley-Ottmann)

### Directory Structure

`headers` folder - contains implementation for Point, Line and Node data structures and Balanced BST class declarations

`EQBalancedBST.cpp` - contains implementation for event queue data structure

`SBalancedBST.cpp` - contains implementation for status data structure

`eventQueue.cpp` and `status.cpp` - for testing working of both data structures

`Makefile` - for creating object files and executable files

### Steps to run `eventQueue.cpp` and `status.cpp` (Works only in a Windows environment)

1. Open Command Prompt or Powershell and run `make` in the root directory of the project (make sure you have GNUMake installed on your machine)
2. Run `.\EQoutput.exe` to test the event queue data structure<br>
   Run `.\SBoutput.exe` to test the status data structure<br>
3. Run `make clean` to remove object files and executable files
