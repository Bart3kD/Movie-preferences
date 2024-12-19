# Movie Preferences Management System

This program manages a hierarchical system of users and their movie preferences. Users are organized in a tree structure, where each user has a parent, and users can store a list of their favorite movies. The system allows adding and removing users, managing their movie lists, and printing combined movie lists of a user and their parent.

---

## Features and Functionalities

### User Management
1. **Adding a User**:  
   Command: `addUser <parentUserID> <userID>`  
   - Adds a new user (`userID`) to the system, assigning them to an existing parent (`parentUserID`).
   - Outputs `OK` if successful, or `ERROR` if:
     - The `parentUserID` does not exist.
     - The `userID` already exists.
   - Time Complexity: Linear with respect to the number of users.

2. **Deleting a User**:  
   Command: `delUser <userID>`  
   - Removes a user (`userID`) from the system.  
   - All children of the deleted user are reassigned to the parent of the deleted user.
   - The root user (`userID = 0`) cannot be deleted.
   - Outputs `OK` if successful, or `ERROR` if:
     - The `userID` does not exist.
   - Time Complexity: Linear with respect to the number of users.

---

### Movie Management
3. **Adding a Movie to a User**:  
   Command: `addMovie <userID> <movieID>`  
   - Adds a movie (`movieID`) to the list of movies for the specified user (`userID`).
   - Ensures movies are stored in ascending order and that duplicates are not added.
   - Outputs `OK` if successful, or `ERROR` if:
     - The `userID` does not exist.
     - The `movieID` is already on the user's list.
   - Time Complexity: Linear with respect to the number of users plus the number of movies in the user's list.

4. **Deleting a Movie from a User**:  
   Command: `delMovie <userID> <movieID>`  
   - Removes a movie (`movieID`) from the list of movies for the specified user (`userID`).
   - Outputs `OK` if successful, or `ERROR` if:
     - The `userID` does not exist.
     - The `movieID` is not on the user's list.
   - Time Complexity: Linear with respect to the number of users plus the number of movies in the user's list.

---

### Displaying Movies
5. **Print User Movies**:  
   Command: `printUserMovies <userID>`  
   - Prints all movies from the specified user (`userID`) and their parent in ascending order.
   - Outputs:
     - A single line of space-separated movie IDs.
     - An empty line if no movies exist for the user or their parent.
     - `ERROR` if the user does not exist.
   - Time Complexity: Linear with respect to the number of users plus the combined number of movies in the user's and parent's lists.

---

## Program Details

### Input and Commands
The program reads commands from standard input, one per line, and executes them immediately. Valid commands include:
- `addUser <parentUserID> <userID>`
- `delUser <userID>`
- `addMovie <userID> <movieID>`
- `delMovie <userID> <movieID>`
- `printUserMovies <userID>`

### Tree Structure
- **Root User**: The user with `userID = 0` is the root and always exists.
- **Parent-Child Relationship**: Users are linked via a parent pointer and a dynamic list of children.

### Dynamic Memory Allocation
- Users and their movie lists are managed using dynamically allocated structures. Memory is resized as necessary to accommodate growing lists.
- All allocated memory is freed at the end of the program.

---

## Usage

1. **Compilation**:  
   Compile the program using a C compiler, e.g., `gcc`:
   ```bash
   gcc main.c -o main
   ```

2. **Execution**:  
   Run the program and provide commands via standard input (or any input that you make):
   ```bash
   ./movie < test.in
   ```
   The program also works for manual inputs.

3. **Example Input**:
   ```
   addUser 0 1
   addMovie 1 101
   addMovie 0 102
   printUserMovies 1
   delMovie 1 101
   delUser 1
   ```

4. **Expected Output**:
   ```
   OK
   OK
   OK
   101 102
   OK
   OK
   ```

---

## Implementation Details

- **Dynamic Arrays**: Both user lists and movie lists use dynamically resizing arrays to efficiently manage elements.
- **Sorting**: Movies are stored in sorted order within each user's list.
- **Error Handling**: Commands validate user and movie existence, ensuring robustness.

---

## Memory Management
- The program ensures no memory leaks by freeing all allocated resources when exiting.
- Each user's children and movies are deallocated recursively during user deletion or program termination.

---

## Limitations and Assumptions
- The input is always valid, meaning commands conform to the expected format and structure.
- There is no limit on the number of users, movies, or operations, except for system memory constraints.
