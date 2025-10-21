#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <limits> // Required for numeric_limits

using namespace std;

// Helper function to read a valid number of a specific type
template <typename T>
bool read_valid_number(T& value, const string& prompt, const string& error_message) {
    while (true) {
        cout << prompt;
        if (cin >> value) {
            return true; // Input successful
        } else {
            // Input failed (e.g., character instead of number)
            cout << error_message << " Please try again.\n";
            cin.clear(); // Clear the error flags
            // Ignore the rest of the line to prevent infinite loop
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        }
    }
}

// ----------------------------------------------------------------------

int main() {
    // I. Reading DFA Definition
    size_t numStates; 
    size_t numSymbols;

    // 1. Validate number of states (must be > 0)
    do {
        if (!read_valid_number(numStates, "Enter number of states (must be > 0): ", "Invalid input type for number of states.")) return 1;
        if (numStates > 0) break;
        cout << "Error: Number of states must be greater than zero. Please try again.\n";
    } while (true);

    // 2. Validate number of symbols (must be > 0)
    do {
        if (!read_valid_number(numSymbols, "Enter number of symbols (must be > 0): ", "Invalid input type for number of symbols.")) return 1;
        if (numSymbols > 0) break;
        cout << "Error: Number of symbols must be greater than zero. Please try again.\n";
    } while (true);

    vector<char> symbols(numSymbols); 
    cout << "Enter symbols (e.g. a b): ";
    // This loop relies on spaces between symbols
    for (size_t i = 0; i < numSymbols; i++)
        cin >> symbols[i];

    // Transition table: Next State is stored as size_t
    vector<map<char, size_t>> transitions(numStates);
    cout << "\n--- Enter Transition Table ---\n";
    
    for (size_t s = 0; s < numStates; s++) { 
        cout << "From state " << s << ":\n";
        for (char sym : symbols) {
            size_t next;
            // 3. Validate Next State (must be < numStates)
            do {
                if (!read_valid_number(next, "  On '" + string(1, sym) + "' go to: ", "Invalid input type.")) return 1;
                if (next < numStates) break;
                cout << "Error: Next state " << next << " is out of range [0, " << numStates - 1 << "]. Please re-enter.\n";
            } while (true);
            
            transitions[s][sym] = next; 
        }
    }

    // 4. Validate Start State (must be < numStates)
    size_t startState;
    do {
        if (!read_valid_number(startState, "\nEnter start state: ", "Invalid input type.")) return 1;
        if (startState < numStates) break;
        cout << "Error: Start state " << startState << " is out of range [0, " << numStates - 1 << "]. Please re-enter.\n";
    } while (true);

    int numFinal_int; // Read count as int temporarily
    if (!read_valid_number(numFinal_int, "Enter number of final states: ", "Invalid input type.")) return 1;

    // Final states
    set<size_t> finalStates;
    cout << "Enter final states: ";
    for (size_t i = 0; i < (size_t)numFinal_int; i++) { 
        size_t f;
        // 5. Validate Final States (must be < numStates)
        do {
            if (!read_valid_number(f, "  Final state #" + to_string(i + 1) + ": ", "Invalid input type.")) return 1;
            if (f < numStates) break;
            cout << "Error: Final state " << f << " is out of range [0, " << numStates - 1 << "]. Please re-enter.\n";
        } while (true);
        finalStates.insert(f);
    }
    
    // --- II. Simulation Loop ---
    cout << "\n--- DFA Simulation Starts ---\n";
    while (true) {
        string input;
        cout << "\nEnter input string (or type 'exit' to quit): ";
        cin >> input;

        if (input == "exit")
            break;

        size_t currentState = startState;
        bool invalid = false;

        cout << "Processing path: State " << currentState; 

        for (char ch : input) {
            // Check for undefined transition (invalid symbol or incomplete DFA definition)
            if (transitions[currentState].find(ch) == transitions[currentState].end()) {
                cout << "\nError: Invalid symbol '" << ch << "' encountered or undefined transition.\n";
                invalid = true;
                break;
            }
            
            // Move to the next state
            size_t nextState = transitions[currentState][ch];
            cout << " -> (" << ch << ") -> State " << nextState;
            currentState = nextState;
        }
        
        cout << endl;

        if (invalid)
            continue;

        // III. Final Decision
        if (finalStates.count(currentState))
            cout << "Result: String Accepted! (ended in state " << currentState << ")\n";
        else
            cout << "Result: String Rejected! (ended in state " << currentState << ")\n";

        cout << "Final State reached: " << currentState << endl;
    }

    cout << "\nProgram terminated.\n";
    return 0;
}