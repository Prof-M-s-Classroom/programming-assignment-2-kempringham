#ifndef GAMEDECISIONTREE_H
#define GAMEDECISIONTREE_H

#include <unordered_map>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Node.h"
#include "Story.h"

template <typename T>
class GameDecisionTree {
private:
    Node<T>* root;

public:
    // TODO: Constructor
    GameDecisionTree() : root(nullptr) {
        root = nullptr;
    }

    // TODO: Function to load story data from a text file and build the binary tree
    void loadStoryFromFile(const std::string& filename, char delimiter) {
        // Story class variables
        string eventNumber, description, leftChild, rightChild;

        ifstream infile; // our "cin"

        // attempt to open the file
        infile.open(filename);

        int mapLength = 1;
        unordered_map<int, Node<T>*> nodeMap;

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
                nodeMap[mapLength] = node;
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
            Node<T>* curr = nodeMap[i];
            Story& story = curr->data;
            int left = story.getLeftEventNumber();
            int right = story.getRightEventNumber();
            if (left != - 1) {
                curr->left = nodeMap[left];
            }
            if (right != -1) {
                curr->right = nodeMap[right];
            }
        }
        root = nodeMap[1];

        // delete?

    }



    // TODO: Function to start the game and traverse the tree based on user input
    void playGame() {
        Node<T>* curr = root;


        // Check if root exists
        if (root == nullptr) {
            cout << "No root node found" << endl;
        }
        int userChoice;
        while (curr != nullptr) {
            // Print the current situation and the paths that the user can take
            cout << curr->data.getDescription() << endl;
            int option1 = curr->data.getLeftEventNumber();
            string option1_description = curr->left->data.getDescription();
            int option2 = curr->data.getRightEventNumber();
            string option2_description = curr->right->data.getDescription();
            cout << "1. " << option1_description << endl;
            cout << "2. " << option2_description << endl;
            std::cin >> userChoice;
            if (cin.fail()) {
                cout << "Invalid input" << endl;
            }
            else {
                break;
            }

            if (userChoice == 1) {
                curr = curr->left;
            }
            if (userChoice == 2) {
                curr = curr->right;
            }

        }

            //Story& story = curr->data;
            //cout << story.getDescription() << endl;
            //int option1 = story.getLeftEventNumber();
            //cout << option1 << endl;
            //int option2 = story.getRightEventNumber();
            //cout << option2 << endl;
            //if (userChoice == option1) {
            //    curr = curr->left;
            //}
            //else if (userChoice == option2) {
            //    curr = curr->right;
            //}
            //else {
            //    cout << "Invalid option entered" << endl;
            //}
        }

        // print the description of the node at the event number
        // print "1. " + description of node at left child number
        // print "2. " + description of node at right child number
        // if user inputs one, the current node becomes the node at the index of the left child
        // if user input two, the current node becomes the node at the index of the right child
        // repeat
        // 1 | You wake up in a forest clearing. There are two paths. | 2 | 3


    //}
};

#endif // GAMEDECISIONTREE_H