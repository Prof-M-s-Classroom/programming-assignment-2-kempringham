#ifndef GAMEDECISIONTREE_H
#define GAMEDECISIONTREE_H

#include <unordered_map>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Node.h"
#include "Story.h"
#include <limits> // added

template <typename T>
class GameDecisionTree {
private:
    Node<T>* root;

public:
    // TODO: Constructor
    GameDecisionTree() : root(nullptr) {
    }

    // TODO: Function to load story data from a text file and build the binary tree
    void loadStoryFromFile(const std::string& filename, char delimiter) {
        // Story class variables
        string eventNumber, description, leftChild, rightChild;

        ifstream infile; // our "cin"


        // attempt to open the file
        infile.open(filename);

        unordered_map<int, Node<T>*> nodeMap;
        int mapLength = 1;

        // verify that the file actually opened
        if (infile.is_open()) {
            string line;
            while (getline(infile, line)) {
                // while there is another line in the .txt file
                stringstream ss(line);
                getline(ss, eventNumber, delimiter); // reads the first string in the line(the event number)
                getline(ss, description, delimiter); // reads the second string in the line(the description)
                getline(ss, leftChild, delimiter); // reads the third string in the line(the left child)
                getline(ss, rightChild, delimiter); // reads the fourth string in the line(the right child)
                Story story(description, stoi(eventNumber), stoi(leftChild), stoi(rightChild));
                Node<Story>* node = new Node<Story>(story);
                nodeMap[stoi(eventNumber)] = node;
                mapLength += 1;
            }
        }

        // Error message if file does not open
        else {
            cout << "Unable to open file" << endl;
        }

        // Close the file
        infile.close();

        // Create the binary search tree
        for (int i = 1; i < mapLength; i++) {
            // set the current node to the node at index i
            Node<T>* curr = nodeMap[i];
            Story& story = curr->data;
            int left = story.getLeftEventNumber();
            int right = story.getRightEventNumber();

            // if left child is not -1, set left child to the node at the index of the left child
            if (left != - 1) {
                curr->left = nodeMap[left];
            }
            // if left child is -1, set left child to null
            else {
                curr->left = nullptr;
            }

            // if right child is not -1, set right child to the node at the index of the right child
            if (right != -1) {
                curr->right = nodeMap[right];
            }
            // if right child is -1, set right child to null
            else {
                curr->right = nullptr;
            }
        }

        // Assign root to the first node
        root = nodeMap[1];

        // TODO: delete for memory management

    }

    // TODO: Function to start the game and traverse the tree based on user input
    void playGame() {
        Node<T>* curr = root;

        // Check if root exists
        if (root == nullptr) {
            cout << "No root node found" << std::endl;
            return;
        }

        while (curr != nullptr) {
            // Print the current situation and the paths that the user can take
            cout << curr->data.getDescription() << endl;

            // Print option one
            int option1 = curr->data.getLeftEventNumber();
            if (option1 != -1) {
                cout << "1. " << curr->left->data.getDescription() << endl;
            }

            // Print option two
            int option2 = curr->data.getRightEventNumber();
            if (option2 != -1) {
                cout << "2. " << curr->right->data.getDescription() << endl;
            }

            // If option one and two are -1, the curr node does not have any children, so the game is over
            if (option1 == -1 && option2 == -1) {
                cout << "Game Over";
                break;
            }

            // make sure user choice is valid(can only be 1 or 2)
            int userChoice;
            //while (true) {
                cout << "Enter your choice: ";
                cin >> userChoice;

                //if (userChoice == 1 || userChoice == 2) {
                //    break;
                //}

                // If user choice is invalid, output that the user must choose a valid choice
                //if (userChoice != 1 && userChoice != 2) {
                //    cout << "Must choose either 1 or 2: ";
                //}

                // If user choice is invalid, have user input a valid choice
                //if (cin.fail()) {
                //    cin.clear();
                //    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                //}
            //}
            // If user chooses 1, go left
            if (userChoice == 1) {
                // If curr's left pointer is null then the game ends
                if (option1 == -1) {
                    cout << "Game Over" << endl;
                    curr = nullptr;
                }
                else {
                    curr = curr->left;
                }
            }

            // If user chooses 1, go right
            else if (userChoice == 2) {
                // If curr's right pointer is null then the game ends
                if (option2 == -2) {
                    cout << "Game Over" << endl;
                    curr = nullptr;
                }
                else {
                    curr = curr->right;
                }


            }
        }

    }

};


#endif