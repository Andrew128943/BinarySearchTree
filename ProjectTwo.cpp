#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// Course Structure
struct Course {
    string courseNumber;
    string title;
    vector<string> prerequisites;
};

// Binary Search Tree Node
struct Node {
    Course course;
    Node* left;
    Node* right;

    Node(Course c) {
        course = c;
        left = nullptr;
        right = nullptr;
    }
};

// Binary Search Tree Class
class BinarySearchTree {
private:
    Node* root;

    Node* insert(Node* node, Course course) {
        if (node == nullptr) {
            return new Node(course);
        }
        if (course.courseNumber < node->course.courseNumber) {
            node->left = insert(node->left, course);
        }
        else {
            node->right = insert(node->right, course);
        }
        return node;
    }

    Node* search(Node* node, const string& courseNumber) {
        if (node == nullptr || node->course.courseNumber == courseNumber) {
            return node;
        }
        if (courseNumber < node->course.courseNumber) {
            return search(node->left, courseNumber);
        }
        return search(node->right, courseNumber);
    }

    void printInOrder(Node* node) {
        if (node == nullptr) {
            return;
        }
        printInOrder(node->left);
        cout << node->course.courseNumber << ", " << node->course.title << endl;
        printInOrder(node->right);
    }

public:
    BinarySearchTree() {
        root = nullptr;
    }
    void Insert(Course course) {
        root = insert(root, course);
    }
    Node* Search(const string& courseNumber) {
        return search(root, courseNumber);
    }
    void PrintCourseList() {
        printInOrder(root);
    }
};

// Functions
void displayMenu() {
    cout << "\nMenu:\n";
    cout << "1. Load Data Structure\n";
    cout << "2. Print Course List\n";
    cout << "3. Print Course\n";
    cout << "9. Exit\n";
    cout << "Enter choice: ";
}

// Load Course Data
void loadCourses(const string& filename, BinarySearchTree& bst) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not open file.\n";
        return;
    }

    string line;

    while (getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        stringstream ss(line);
        string token;
        vector<string> tokens;
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }
        if (tokens.size() < 2) {
            cout << "Error: Invalid line format.\n";
            continue;
        }
        Course course;
        course.courseNumber = tokens[0];
        course.title = tokens[1];

        for (size_t i = 2; i < tokens.size(); i++) {
            course.prerequisites.push_back(tokens[i]);
        }
        bst.Insert(course);
    }
    file.close();
    cout << "Courses successfully loaded.\n";
}

// Print Single Course Info
void printCourseInfo(BinarySearchTree& bst, const string& courseNumber) {
    Node* node = bst.Search(courseNumber);
    if (node == nullptr) {
        cout << "Course not found\n";
        return;
    }

    cout << node->course.courseNumber << "," << node->course.title << endl;
    if (node->course.prerequisites.empty()) {
        cout << "Prerequisites: None\n";
    } 
    else {
        cout << "Prerequisites: ";
        for (size_t i = 0; i < node->course.prerequisites.size(); i++) {
            cout << node->course.prerequisites[i];
            if (i < node->course.prerequisites.size() - 1) {
                cout << ", ";
            }
        }
        cout << endl;
    }
}

// Main Program
int main() {
    BinarySearchTree bst;
    int choice = 0;
    string filename;
    bool loaded = false;

    while (choice != 9) {
        displayMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter filename: ";
            cin >> filename;
            loadCourses(filename, bst);
            loaded = true;
            break;

        case 2:
            if (!loaded) {
                cout << "Please load the data first\n";
            }
            else {
                cout << "\nCourse List:\n";
                bst.PrintCourseList();
            }
            break;

        case 3:
            if (!loaded) {
                cout << "Please load the data first\n";
            }
            else {
                cout << "Enter course number: ";
                cin >> filename;
                printCourseInfo(bst, filename);
            }
            break;

        case 9:
            cout << "Goodbye!\n";
            break;

        default:
            cout << "Invlaid option.\n";
        }
    }
    return 0;
}