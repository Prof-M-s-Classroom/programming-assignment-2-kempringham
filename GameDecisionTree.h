#ifndef GAMEDECISIONTREE_H
#define GAMEDECISIONTREE_H

#include <unordered_map>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Node.h"
#include "Story.h"
using namespace std; // From video

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

        // verify that the file actually opened
        if (infile.is_open()) {
            string line;
            while (getline(infile, line)) { // while there is another line in the .txt file
                stringstream ss(line);
                getline(ss, eventNumber, delimiter); // reads the first string in the line(the event number)
                getline(ss, description, delimiter); // reads the second string in the line(the description)
                getline(ss, leftChild, delimiter); // reads the third string in the line(the left child)
                getline(ss, rightChild, delimiter); // reads the fourth string in the line(the right child)
                Story story(description, stoi(eventNumber), stoi(leftChild), stoi(rightChild));
                Node<T>* node = new Node<T>(story);
                }


            infile.close();
        }
        else {
            cout << "Unable to open file" << endl;
        }

        cin.get();
    }

    // TODO: Function to start the game and traverse the tree based on user input
    void playGame() {


    }
};

#endif // GAMEDECISIONTREE_H