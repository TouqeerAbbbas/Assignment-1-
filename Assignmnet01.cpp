#include <iostream>
#include <string>

using namespace std;

// Structure for each Task (node in the linked list)
struct Task {
    int taskID;              // Unique ID for each task
    string description;      // Description of the task
    int priority;            // Priority of the task
    Task* next;              // Pointer to the next task (next node in the list)
};

// Function to create a new task node
Task* createTask(int id, string desc, int priority) {
    return new Task{id, desc, priority, nullptr};  // Using aggregate initialization for simplicity
}

// Function to add a task to the list, sorted by priority
void addTask(Task*& head, int id, string desc, int priority) {
    Task* newTask = createTask(id, desc, priority);

    // Insert at the beginning if list is empty or new task has higher priority
    if (!head || head->priority < priority) {
        newTask->next = head;
        head = newTask;
    } else {
        Task* current = head;
        while (current->next && current->next->priority >= priority) {
            current = current->next;
        }
        newTask->next = current->next;
        current->next = newTask;
    }
    cout << "Task added successfully.\n";
}

// Function to view all tasks in the list
void viewTasks(Task* head) {
    if (!head) {
        cout << "No tasks available.\n";
        return;
    }

    for (Task* current = head; current; current = current->next) {
        cout << "Task ID: " << current->taskID
             << "\nDescription: " << current->description
             << "\nPriority: " << current->priority << "\n\n";
    }
}

// Helper function to delete a task and free memory
void deleteTask(Task*& task) {
    Task* temp = task;
    task = task->next;
    cout << "Task with ID " << temp->taskID << " removed.\n";
    delete temp;  // Free memory
}

// Function to remove the task with the highest priority (first task)
void removeHighestPriorityTask(Task*& head) {
    if (!head) {
        cout << "No tasks to remove.\n";
        return;
    }
    deleteTask(head);
}

// Function to remove a specific task by its task ID
void removeTaskByID(Task*& head, int id) {
    if (!head) {
        cout << "No tasks to remove.\n";
        return;
    }

    if (head->taskID == id) {
        deleteTask(head);  // Remove the first task if it matches the ID
        return;
    }

    Task* current = head;
    while (current->next && current->next->taskID != id) {
        current = current->next;
    }

    if (current->next) {
        deleteTask(current->next);  // Remove the task if found
    } else {
        cout << "Task with ID " << id << " not found.\n";
    }
}

// Main function to handle the menu-based interaction
int main() {
    Task* head = nullptr;  // Initialize the head of the list to nullptr
    int choice, id, priority;
    string description;

    do {
        // Display the menu
        cout << "\nTask Management System\n";
        cout << "1. Add New Task\n";
        cout << "2. View All Tasks\n";
        cout << "3. Remove Highest Priority Task\n";
        cout << "4. Remove Task by ID\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                // Add a new task
                cout << "Enter task ID: ";
                cin >> id;
                cin.ignore();  // Ignore newline character left by cin
                cout << "Enter task description: ";
                getline(cin, description);
                cout << "Enter task priority: ";
                cin >> priority;
                addTask(head, id, description, priority);
                break;

            case 2:
                // View all tasks
                viewTasks(head);
                break;

            case 3:
                // Remove the highest priority task
                removeHighestPriorityTask(head);
                break;

            case 4:
                // Remove a task by its ID
                cout << "Enter task ID to remove: ";
                cin >> id;
                removeTaskByID(head, id);
                break;

            case 5:
                // Exit the program
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice, please try again.\n";
        }
    } while (choice != 5);

    return 0;
}