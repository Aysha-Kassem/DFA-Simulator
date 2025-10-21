# Deterministic Finite Automaton (DFA) Simulator

This C++ program implements a robust simulator for a Deterministic Finite Automaton (DFA). It allows the user to define the DFA structure (states, alphabet, transitions, start state, and final states) and then tests user-provided strings against the defined machine, printing the full processing path.

---

## 🚀 Features

* **Complete DFA Definition:** Reads the number of states, input alphabet, transition table, start state, and final states.
* **Robust Input Validation:** Ensures all numerical inputs (states, symbols, transitions) are valid integers and fall within the correct logical range (e.g., states are not out of bounds). Provides retry opportunities on failure.
* **Step-by-Step Path Tracing:** For every input string, the program prints the full path taken through the DFA (e.g., `State 0 -> (a) -> State 1`).
* **Rejection Handling:** Clearly rejects strings that end in a non-final state or encounter an undefined transition/invalid symbol.

---

## 🛠️ Requirements

* A C++ compiler that supports C++11 or later (e.g., `g++`, `clang++`).
* Standard C++ libraries (`iostream`, `vector`, `map`, `set`, `string`).

---

## 💻 Usage Example
**When you run the program, it will prompt you for the DFA definition first:**

DFA Setup Input
```bash
Prompt,Example Input,Notes
Enter number of states:,3,"Defines states 0, 1, and 2."
Enter number of symbols:,2,
Enter symbols (e.g. a b):,a b,"The alphabet is {a, b}."
From state 0: On 'a' go to:,1,"Transition δ(0,a)=1"
Enter start state:,0,
Enter number of final states:,1,
Final state #1:,2,State 2 is the only accepting state.
```


---

## Simulation
**After setup, the program enters a loop to test strings:**

```bash
--- DFA Simulation Starts ---

Enter input string (or type 'exit' to quit): aba
Processing path: State 0 -> (a) -> State 1 -> (b) -> State 2 -> (a) -> State 1
Result: String Rejected! (ended in state 1)
Final State reached: 1

Enter input string (or type 'exit' to quit): ab
Processing path: State 0 -> (a) -> State 1 -> (b) -> State 2
Result: String Accepted! (ended in state 2)
Final State reached: 2

Enter input string (or type 'exit' to quit): exit

Program terminated.
```

---

## 💡 Code Structure Details
```bash
| Component | C++ Implementation | Purpose |
| :--- | :--- | :--- |
| **DFA States** | `size_t numStates` | Total count of states. |
| **Transition Table** | `vector<map<char, size_t>> transitions` | Indexed by `transitions[current_state][symbol]`. This is the core logic. |
| **Start State** | `size_t startState` | The index where processing begins. |
| **Final States** | `set<size_t> finalStates` | A set is used for O(log N) or average O(1) lookups to determine if the final state is accepting. |
| **Validation** | `template <typename T> read_valid_number(...)` | Custom function using `cin.clear()` and `cin.ignore()` to robustly handle invalid input types and prevent runtime crashes. |
```

