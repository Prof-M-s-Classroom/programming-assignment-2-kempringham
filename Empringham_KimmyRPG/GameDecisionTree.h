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

        // Create unordered map to store nodes using hashing
        unordered_map<int, Node<T>*> nodeMap;

        // Initialize mapLength variable to determine the number of nodes in the unordered map
        int mapLength = 1;

        // Verify that the file actually opened
        if (infile.is_open()) {
            // Create a string variable to store each line from story.txt
            string line;

            // Create a loop that continues as long as there is another line in the story.txt file
            while (getline(infile, line)) {
                // Create a stringstream so that we can parse through each line of text
                stringstream ss(line);
                // Reads the current line before the delimiter(the event number)
                getline(ss, eventNumber, delimiter);
                // Reads the current line before the delimiter(the event description)
                getline(ss, description, delimiter);
                // Reads the current line before the delimiter(the left child)
                getline(ss, leftChild, delimiter);
                // Reads the last part of the current line(the right child)
                getline(ss, rightChild, delimiter);
                // Creates a story object to store the events
                // Also converts the event number, left child, and right child to integers
                Story story(description, stoi(eventNumber), stoi(leftChild), stoi(rightChild));
                // Create a node that contains the story information
                Node<Story>* node = new Node<Story>(story);
                // Stores each node in our node map at the index of the event number
                nodeMap[stoi(eventNumber)] = node;
                // Increments map length
                mapLength += 1;
            }
        }

        // Output an error message if file does not open
        else {
            cout << "Unable to open file" << endl;
        }

        // Close the file
        infile.close();

        // Create the binary search tree
        // Loop through from 1 to the number of events
        for (int i = 1; i < mapLength; i++) {
            // set the current node to the node at index i
            Node<T>* curr = nodeMap[i];
            // Get the left and right event numbers
            int left = curr->data.getLeftEventNumber();
            int right = curr->data.getRightEventNumber();

            // If the left child is not -1, set left child to the node at the index of the left child
            if (left != - 1) {
                curr->left = nodeMap[left];
            }
            // If the left child is -1, set left child to null
            else {
                curr->left = nullptr;
            }

            // If the right child is not -1, set right child to the node at the index of the right child
            if (right != -1) {
                curr->right = nodeMap[right];
            }
            // If the right child is -1, set right child to null
            else {
                curr->right = nullptr;
            }
        }

        // Set root equal to the first node
        root = nodeMap[1];

    }

    // TODO: Function to start the game and traverse the tree based on user input
    void playGame() {
        // Set the current node to the root node(we always start at the root)
        Node<T>* curr = root;

        // Check if root exists
        if (root == nullptr) {
            std::cout << "No root node found" << std::endl;
            return;
        }

        // Loop through until we get to a leaf node
        while (curr != nullptr) {

            // Get the indexes of the two options
            int option1 = curr->data.getLeftEventNumber();
            int option2 = curr->data.getRightEventNumber();

            // Print the current situation
            if (option1 != -1 || option2 != -1) {
                std::cout << curr->data.getDescription() << std::endl;
            }

            // Print option one
            if (option1 != -1) {
                std::cout << "1. " << curr->left->data.getDescription() << std::endl;
            }

            // Print option two
            if (option2 != -1) {
                std::cout << "2. " << curr->right->data.getDescription() << std::endl;
            }

            // If option one and two are -1, the curr node is a leaf, so the game is over
            if (option1 == -1 && option2 == -1) {
                std::cout << "You got caught.";
                break;
            }

            int userChoice;
            while (true) {
                // Prompt user to input their choice
                std::cout << "Enter your choice: ";
                std::cin >> userChoice;

                // Make sure user choice is valid(can only be 1 or 2)
                if (userChoice == 1 || userChoice == 2) {
                    break;
                }

                // If user choice is invalid, output that the user must choose a valid choice
                if (userChoice != 1 && userChoice != 2) {
                    std::cout << "Must choose either 1 or 2: ";
                }

                // If user choice is invalid, have user input a valid choice
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }

            // If user chooses 1, go left
            if (userChoice == 1) {
                if (curr->left != nullptr) {
                    curr = curr->left;
                }
                // If curr's left pointer is null then the game ends
                else {
                    std::cout << "You were caught." << std::endl;
                    curr = nullptr;
                }
            }

            // If user chooses 1, go right
            else if (userChoice == 2) {
                // If curr's right pointer is null then the game ends
                if (curr->right != nullptr) {
                    curr = curr->right;
                }
                // If curr's right pointer is null then the game ends
                else {
                    std::cout << "You were caught." << std::endl;
                    curr = nullptr;
                }

            }
        }

    }

};


#endif