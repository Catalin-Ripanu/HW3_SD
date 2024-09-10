# HW3_SD

## Timeline and Overview
- The project was completed in 2 weeks and 2 days.
- Implementation ideas came successively.

## Week 1: Foundations and First Requirement
1. Implemented necessary structures, processing functions, and writing functions.
2. Used a 'for' loop and `fscanf` function to obtain data from the input file.
3. Completed requirement 1:
   - Found the connected component with the most nodes.
   - Saved this component in a binary tree.
   - Ascending order obtained by in-order traversal.
4. Encountered numerous Valgrind errors in the 'Productions' function.
   - Spent 2-3 days resolving errors caused by the binary tree vector.

## Week 2: Second Requirement and Debugging
1. Implemented requirement 2 using the `Degree` function.
2. Major obstacles encountered (SIGSEGV -> GDB).
3. 2-3 days spent on debugging:
   - Used Valgrind and GDB.
   - Valgrind reported most errors.
4. Implemented degree of kinship:
   - Represented minimum distance between nodes.
   - Used Breadth-First Search (BFS).
   - Called additional functions to ensure actors' presence in the tree.
5. Memory management: freed memory and returned results at function end.

## Main Program Structure
- Actor representation:
  - `actor->name`: Actor's name
  - `actor->code`: Associated code to prevent duplicates
- Tree structure:
  - Actors added to left or right of the tree for correct ordering.
  - Used `Compare_Names` function for proper ordering.
- No duplicates in the tree.

### Key Fields
- `Object`: Generic object storing node order number or actor name.
- `Number_of_nodes`: Node count
- `Adjency_List`: Vector of adjacency lists
- `Next`: Pointer to next node
- `Actor_Compare`: Function to compare actors

Example: `(char *)Graph->Adjency_List[1]->head->Object` stores the first actor's name in the graph.

## Final Stage: Third Requirement and Completion
1. Completed requirement 3 in 2 days.
2. Researched Tarjan's algorithm.
3. Complex implementation in `CriticalEdges` function:
   - Checked conditions (1-14) for actor ordering.
   - Conditions verified relationships between letters in actor names.
4. `main` function: Initialized graph and tree.
5. Writing function:
   - Used in-order traversal and '\n' for correct output format.
6. Used variables like `char *Name_Movie, **Names_Actors, *Name_Actor1, *Name_Actor2` for tree/graph construction and memory deallocation.

## Conclusion
This project presented significant challenges and was not trivial to implement.
