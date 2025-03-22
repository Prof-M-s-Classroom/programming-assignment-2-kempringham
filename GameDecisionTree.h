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

        ifstream infile; // our "cin"

        // attempt to open the file
        infile.open(filename);

        // verify that the file actually opened
        if (infile.is_open()) {
            string line;
            while (getline(infile, line)) { // while there is another line in the .txt file
                stringstream ss(line);
                getline(ss, eventNumber, delimiter);
                getline(ss, description, delimiter);
                getline(ss, leftChild, delimiter);
                getline(ss, rightChild, delimiter);
                Story<string> Story;
                Story::Story(description, 1, 2, 3);
                cout << Story << endl;

                }
                // eventNumber is the number before the delimiter
                // description is the whole string before the next delimiter
                // left child is the number before the delimiter
                // right child is the number after the last delimiter
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