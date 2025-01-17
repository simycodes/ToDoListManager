#include <iostream>
#include <list> 
#include <string> 
using namespace std;

// TASK CLASS TO HOLD TASK INFORMATION
class Task {
    public:
        int taskId;
        string taskDetails;

        Task(int id, string incomingTaskDetails) {
            taskId = id; 
            taskDetails = incomingTaskDetails;
        }
            
};

// FUNCTION PROTOTYPES (FUNCTION DEFINATIONS DONE AFTER THE main() FUNCTION)

// FUNCTION(PROTOTYPE) TO DISPLAY THE MENU
void displayMenu(list<Task*> &taskList);

// FUNCTION(PROTOTYPE) TO DISPLAY TO-DO-LIST TASKS
void displayTasks(list<Task*> &taskList);

// FUNCTION(PROTOTYPE) TO ADD A TASK TO THE TO-DO LIST
void addTask(list<Task*>& taskList, int& nextId);

// FUNCTION(PROTOTYPE) TO REMOVE A TASK FROM TO-DO LIST
void removeTask(list<Task*>& taskList);

int main() {
    // LIST THAT WILL HOLD POINTERS (LIST OF POINTERS OF TASK DATA TYPE) TO THE TASK 
    // OBJECTS TO BE CREATED. 
    list<Task*> taskList;
    // list<Task> *taskList;

    // FIRST TASK ID - HELP IN CREATING UNIQUE TASK IDS IN SEQUENTIAL FOR ALL NEW TASKS
    int taskId = 1; 
    // VARIABLE TO HOLD USERS SELECTED OPTION FROM THE MAIN MENU
    int selectedOption;

    // APP WELCOME MESSAGE
    cout << "\n####--- WELCOME TO THE TO-DO LIST TASK APP MANAGER ---#####:\n";

    // DO-WHILE LOOP TO ATLEAST DISPLAY THE MENU ONCE BEFORE ANY USER INPUT
    do {
        // CALL FUNCTION TO DISPLAY THE TO-DO MENU
        displayMenu(taskList);
        // GET USER INPUT
        cin >> selectedOption;
        // CHECK TYPE OF INCOMING DATA IF ITS A STRING
        if (cin.fail()) {
            cout << "\n-| Invalid Text Input For Option: Run App Again To Add New Tasks  -|\n\n";
            exit(1);
        }
        // IGNORE NEWLINE CHARACTER AFTER AN INTEGER INPUT
        cin.ignore(); 

        // VERIFY INCOMING DATA FOR OPTIONS RANGES
        if(selectedOption <= 0) {
            selectedOption = 4;
        }
        if(selectedOption > 4) {
            selectedOption = 4;
        }

        // ADD TASK, DELETE TASK OR EXIT PROGRAM DEPENDING ON USER INPUT
        switch (selectedOption) {
        case 1:
            addTask(taskList, taskId);
            break;
        case 2:
            removeTask(taskList);
            break;
        case 3:
            cout << "Exiting.....\n";
            cout << "App Exited! Run App Again To Add New Tasks\n";
            break;
        case 4:
            cout << "-| Invalid Option: Select a Valid Option Between 1 and 3 -|\n";
            break;
        default:
            cout << "####--- Invalid Option - Select a Valid Option Between 1 and 3, Thanks - Try Again.\n ---####";
            break;  
        }
    } while (selectedOption != 3);


    // REMOVING(CLEANING UP) DYNAMICALL ALLOCATED MEMORY/STORAGE FOR THE TASK OBJECTS
    for (Task*& task : taskList) {
        delete task; // - ADDITIONAL REQ.3 USE delete OPERATOR
    }

    // NOTE: THE LIST OF OBJECTS IS A POINTER OF MEMORY/STORAGE ADDRESSES OF TASK/OBJECT
    // ELEMENTS
    // THE TASK OBJECTS WILL PERSIST IN MEMORY/STORAGE UNTIL EXPLICITLY DELETED, EVEN IF 
    // THE LIST GOES OUT OF SCOPE, HENCE delete task FOR EACH TASK INSIDE taskList
    // DYNAMICALLY ALLOCATED OBJECTS (USING NEW) MUST BE EXPLICITLY DELETED TO AVOID 
    // MEMORY LEAKS.
    
    return 0;
}

// FUNCTION TO DISPLAY THE TO-DO LIST MANAGER
void displayMenu(list<Task*> &taskList) {
    cout << "\n#--|   THE TO-DO LIST APP MENU:  |--#\n";
    cout << "-| Please Select An Option: |-\n";
    cout << "1. To Add Task\n";
    cout << "2. To Remove Task\n";
    cout << "3. To Exit\n";

    // DISPLAY TASKS IF USER HAS INSERTED SOME
    if (taskList.empty()) {
        cout << "\n-| Your Tasks Will Be Displayed Here! Enter 1 To Add a New Task. |-\n\n";
    } 
    else {
        cout << "\nAvailable Tasks:\n";
        for (Task*& task : taskList) {
            cout << "Task ID: " << task->taskId << " | Task Details: " << task->taskDetails << endl;
            // THE -> OPERATOR IS USED TO ACCESS THE OBJECT'S METHODS/FIELDS VIA THE POINTER.
        }
        cout << "\n";
    }

    // NOTE: IN for (Task*& task : taskList) {}
    // task IS A POINTER TO A Task OBJECT. EACH ELEMENT IN taskList IS OF TYPE TASK*, SO 
    // task REPRESENTS ONE OF THOSE POINTERS DURING EACH ITERATION OF THE LOOP.

    // THE & MAKES task A REFERENCE TO THE POINTER IN THE LIST. THIS MEANS task IS NOT A 
    // COPY OF THE POINTER BUT A DIRECT REFERENCE TO THE ACTUAL POINTER STORED IN TASKLIST.

    // BY MAKING TASK A REFERENCE TO THE POINTER, ANY CHANGES TO TASK (SUCH AS DELETING 
    // IT OR SETTING IT TO NULLPTR) DIRECTLY AFFECT THE ORIGINAL POINTER STORED IN 
    // TASKLIST. WITHOUT THE &, MODIFICATIONS TO TASK WOULD NOT AFFECT THE ORIGINAL LIST
    // ELEMENTS.

}

// FUNCTION TO DISPLAY TO-DO-LIST TASKS
// taskList IS PASSED AS A REFERENCE
// ANY /CHANGES/MODIFICATIONS TO TASKLIST INSIDE THE FUNCTION WILL DIRECTLY AFFECT THE 
// ORIGINAL LIST IN THE CALLING CODE.
// list<Task*>& MEANS THE FUNCTION OPERATES ON THE ORIGINAL LIST, NOT A COPY.
void displayTasks(list<Task*> &taskList) {
    if (taskList.empty()) {
        cout << "No Tasks Available. Add a new Task.\n";
        return;
    }

    cout << "\nAvailable Tasks To Delete:\n";
    for (Task*& task : taskList)  {
        cout << "Task ID: " << task->taskId << " | Task Name: " << task->taskDetails << endl;
    }
}

// FUNCTION TO ADD A TASK TO THE TO-DO LIST
// PASSING taskList AND taskId BY REFERENCE HENCE THERE’S NO OVERHEAD OF COPYING 
// THE ENTIRE OBJECT.
// THE & ENSURES THAT THE FUNCTION OPERATES ON THE ORIGINAL OBJECT(taskList), NOT
// A COPY. 
// NO NEED TO RETURN ANYTHING TO THE MAIN FUNCTION
void addTask(list<Task*>& taskList, int& taskId) {
    // GET TASK DETAILS FROM THE USER
    string incomingTaskDetails;
    cout << "Please Enter a Task You Wish to Add: ";
    getline(cin, incomingTaskDetails);

    // CREATE NEW TASK(OBJECT) DYNAMICALLY  - ADDITIONAL REQ.3 USE new OPERATOR
    Task* newTask = new Task(taskId, incomingTaskDetails);
    // Task* newTask = new Task(taskId, taskDetails);
    // ADD TASK TO THE LIST
    taskList.push_back(newTask);
    taskId++;

    // PRINT TASK CONFIRMATION MESSAGE
    cout << "The Task Has Been Added Successfully!\n";
}

// FUNCTION TO REMOVE A TASK FROM TO-DO LIST
void removeTask(list<Task*> &taskList) {
    // CHECK IF THERE TASKS
    if (taskList.empty()) {
        cout << "No tasks available to remove.\n";
        return;
    }

    // DISPLAY LIST OF TASKS TO DELETE FROM
    displayTasks(taskList);

    // GET ID OF TASK TO DELETE
    int taskId;
    cout << "Enter the Task ID of The Task To Delete: ";
    cin >> taskId;
    cin.ignore();

    // DELETE TASK
    // taskList.begin() RETURNS A READ/WRITE ITERATOR THAT POINTS TO THE FIRST 
    // ELEMENT IN THE %LIST. ITERATION IS DONE IN ELEMENT ORDER.
    for (list<Task*>::iterator currentTask = taskList.begin(); currentTask != taskList.end(); ++currentTask) {
        if ((*currentTask)->taskId == taskId) {
            // DELETE DYNAMIC CREATED task
            delete *currentTask;
            // REMOVE THE TASK FROM THE taskList
            taskList.erase(currentTask);
            cout << "Task Removed Successfully!\n";
            return;
        }
    }

}