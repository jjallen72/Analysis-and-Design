// Project2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);


// define a structure to hold bid information
struct Course {
    string code; // unique identifier
    string title;
    vector<string> pre_reqs;
    Course(string c, string t, vector<string> pqs) {
        code = c;
        title = t;
        pre_reqs = pqs;
    }
};





// Internal structure for tree node
struct Node {
    Course *course;
    Node* left;
    Node* right;

    Node(Course *c) {
        course = c;
        right = NULL;
        left = NULL;
    }


};

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:
    Node* root;

    void addNode(Node* node, Course *c);
    void inOrder(Node* node);
    void preOrder(Node* node);
    void postOrder(Node* node);
    void removeNode(Node* node);
    Node* searchNode(string bidId);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void PostOrder();
    void PreOrder();
    void Insert(Course *c);
    void Remove(string code);
    Course * Search(string code);
};

void displayCourse(Course* c, BinarySearchTree* bst);

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    // FixMe (1): initialize housekeeping variables
    //root is equal to nullptr
    root = NULL;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    // recurse from root deleting every node
    while (root) {
        Remove(root->course->code);
    }
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
    // FixMe (2): In order root
    // call inOrder fuction and pass root 
    inOrder(root);
}

/**
 * Traverse the tree in post-order
 */
void BinarySearchTree::PostOrder() {
    // FixMe (3): Post order root
    // postOrder root
    postOrder(root);
}

/**
 * Traverse the tree in pre-order
 */
void BinarySearchTree::PreOrder() {
    // FixMe (4): Pre order root
    // preOrder root
    preOrder(root);
}

/**
 * Insert a bid
 */
void BinarySearchTree::Insert(Course *c) {
    // FIXME (5) Implement inserting a bid into the tree
    // if root equarl to null ptr
      // root is equal to new node bid
    // else
      // add Node root and bid
    if (root == NULL) {
        root = new Node(c);
    }
    else {
        addNode(root, c);
    }
}

/**
 * Remove a bid
 */
void BinarySearchTree::Remove(string course) {
    // FIXME (6) Implement removing a bid from the tree
    // remove node root bidID
    Node* start_node = searchNode(course);
    if (!start_node) {
        return;
    }

    if (root == start_node && root->left == NULL && root->right == NULL) {
        delete root;
        root = NULL;
        return;
    }

    removeNode(start_node);
}

/**
 * Search for a bid
 */
Course * BinarySearchTree::Search(string code) {
    // FIXME (7) Implement searching the tree for a bid
    // set current node equal to root

    // keep looping downwards until bottom reached or matching bidId found
        // if match found, return current bid

        // if bid is smaller than current node then traverse left
        // else larger so traverse right
    Course *c;
    Node* cur_node = root;
    while (cur_node != NULL) {
        if (code < cur_node->course->code) {
            //going left
            cur_node = cur_node->left;
        }
        else if (code > cur_node->course->code) {
            //going right 
            cur_node = cur_node->right;
        }
        else {
            //means we found it
            return cur_node->course;
        }
    }

    return NULL;
}

Node* BinarySearchTree::searchNode(string code) {
    // else larger so traverse right
    //Bid bid;
    Node* cur_node = root;
    while (cur_node != NULL) {
       
        if (code < cur_node->course->code) {
            //going left
            cur_node = cur_node->left;
        }
        else if (code > cur_node->course->code) {
            //going right 
            cur_node = cur_node->right;
        }
        else {
            //means we found it
            return cur_node;
        }
    }

    return NULL;
}

void BinarySearchTree::removeNode(Node* cur_node) {
    if (cur_node->left != NULL) {
        cur_node->course = cur_node->left->course;
        if (cur_node->left->left != NULL || cur_node->left->right != NULL)
            removeNode(cur_node->left);
        else {
            delete cur_node->left;
            cur_node->left = NULL;
        }
    }
    else if (cur_node->right != NULL) {
        cur_node->course = cur_node->right->course;
        if (cur_node->right->left != NULL || cur_node->right->right != NULL)
            removeNode(cur_node->right);
        else {
            delete cur_node->right;
            cur_node->right = NULL;
        }
    }
}

/**
 * Add a bid to some node (recursive)
 *
 * @param node Current node in tree
 * @param bid Bid to be added
 */
void BinarySearchTree::addNode(Node* node, Course *c) {
    // FIXME (8) Implement inserting a bid into the tree
    if (c->code < node->course->code) {
        if (node->left == NULL) {
            node->left = new Node(c);
        }
        else {
            addNode(node->left, c);
        }
    }
    else if (c->code > node->course->code) {
        if (node->right == NULL) {
            node->right = new Node(c);
        }
        else {
            addNode(node->right, c);
        }
    }
}
void BinarySearchTree::inOrder(Node* node) {
    // FixMe (9): Pre order root
    if (node == NULL)
        return;
    inOrder(node->left);
    displayCourse(node->course, this);
    inOrder(node->right);
}
void BinarySearchTree::postOrder(Node* node) {
    // FixMe (10): Pre order root
    if (node == NULL)
        return;
    inOrder(node->left);
    inOrder(node->right);
    displayCourse(node->course, this);

}

void BinarySearchTree::preOrder(Node* node) {
    // FixMe (11): Pre order root
    //if node is not equal to null ptr
    if (node == NULL)
        return;
    displayCourse(node->course, this);
    inOrder(node->left);
    inOrder(node->right);


}

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information to the console (std::out)
 *
 * @param bid struct containing the bid info
 */
void displayCourse(Course *c, BinarySearchTree *bst) {
    cout << c->code << ": " << c->title << endl;
    for (string pr : c->pre_reqs) {
        cout << "\t" <<  pr << "  (" << bst->Search(pr)->title << ")" << endl;
    }
    cout << endl;
    return;
}

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
void loadBids(string filePath, BinarySearchTree* bst) {
    cout << "Loading  file " << endl;
    string line;
    ifstream file(filePath);

    vector<Course *> check_pre;
    
    
    while (getline(file, line)) {
        istringstream lineStream(line);
        string code, title, pre;
        getline(lineStream, code, ',');
        getline(lineStream, title, ',');

        vector<string> pre_z;

        while (getline(lineStream, pre, ',')) {
            pre_z.push_back(pre);
        }

        Course* c = new Course(code, title, pre_z);
        bst->Insert(c);
        check_pre.push_back(c);

       
    }   

    for (Course *c : check_pre) {
        for (string pr : c->pre_reqs) {
            if (!bst->Search(pr)) {
                cout << "Error in file " << endl;
                return;
            }
        }
    }
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // process command line arguments
  

    // Define a timer variable
    clock_t ticks;

    // Define a binary search tree to hold all bids
    BinarySearchTree* bst = NULL;

    string code;
    Course* c;

    int choice = 0;
    while (choice != 4) {
        cout << "Menu:" << endl;
        cout << "  1. Load Courses" << endl;
        cout << "  2. Display All Courses in Order" << endl;
        cout << "  3. Find/Display Specific Course" << endl;
        cout << "  4. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        string filename;

        switch (choice) {

        case 1:
            bst = new BinarySearchTree();

            // Initialize a timer variable before loading bids
            ticks = clock();

            cout << "What file do you want to load?" << endl;
            
            cin >> filename;

            // Complete the method call to load the bids
            loadBids(filename, bst);

            //cout << bst->Size() << " bids read" << endl;

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 2:
            bst->InOrder();
            break;

        case 3:
            ticks = clock();

            cout << "Please enter the code of the class you want to search for: " << endl;
            cin >> code;
            c = bst->Search(code);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (c) {
                displayCourse(c, bst);
            }
            else {
                cout << "A course with code " << code << " not found." << endl;
            }

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 4:
            break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}
