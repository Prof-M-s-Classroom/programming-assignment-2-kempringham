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
        int event;

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

        infile.close();
        for (int i = 1; i < mapLength; i++) {
            Node<T>* curr = nodeMap[i];
            Story& story = curr->data;
            int leftChild = story.getLeftEventNumber();
            int rightChild = story.getRightEventNumber();
            if (leftChild != - 1) {
                curr->left = nodeMap[leftChild];
            }
            if (rightChild != -1) {
                curr->right = nodeMap[rightChild];
            }
        }

        //for (int i = 1; i < mapLength; i++) {
        //    Node<Story>* currentNode = nodeMap[i];
        //}

        // Add helper method for creating tree
        //void binaryTree(Node<Story>* root, nodeMap[mapLength]) {
        //    if (stoi(leftChild)!= -1 && stoi(rightChild) != -1)  {
         //       inorder(root->left, );
         //   }
         //   if (stoi(rightChild)!= -1) {
        //        root->right = nodeMap[rightChild];
        //        assigningPointers(root->right, root);
        //    }
        //}
    }



    // TODO: Function to start the game and traverse the tree based on user input
    void playGame() {
    }
};

#endif // GAMEDECISIONTREE_H