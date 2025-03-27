#ifndef GAMEDECISIONTREE_H
#define GAMEDECISIONTREE_H

#include <unordered_map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <limits>
#include "Node.h"
#include "Story.h"

template <typename T>
class GameDecisionTree {
private:
    Node<T>* root;

public:
    // Constructor
    GameDecisionTree() : root(nullptr) {}

    void loadStoryFromFile(const std::string& filename, char delimiter) {
        std::ifstream infile(filename);

        if (!infile) {
            std::cerr << "Unable to open file: " << filename << std::endl;
            return;
        }

        std::unordered_map<int, Node<T>*> nodeMap;
        std::string line, eventNumber, description, leftChild, rightChild;
        int mapLength = 1;

        while (std::getline(infile, line)) {
            std::stringstream ss(line);

            if (std::getline(ss, eventNumber, delimiter) &&
                std::getline(ss, description, delimiter) &&
                std::getline(ss, leftChild, delimiter) &&
                std::getline(ss, rightChild)) {

                try {
                    int eventNum = std::stoi(eventNumber);
                    int leftNum = std::stoi(leftChild);
                    int rightNum = std::stoi(rightChild);

                    Story story(description, eventNum, leftNum, rightNum);
                    Node<Story>* node = new Node<Story>(story);
                    nodeMap[eventNum] = node;
                    mapLength++;
                }
                catch (const std::exception& e) {
                    std::cerr << "Error processing line: " << line << std::endl;
                }
            }
        }

        // Build tree connections
        for (int i = 1; i < mapLength; i++) {
            if (nodeMap.count(i) == 0) continue;

            Node<T>* curr = nodeMap[i];
            Story& story = curr->data;

            curr->left = (story.getLeftEventNumber() != -1)
                ? nodeMap[story.getLeftEventNumber()]
                : nullptr;

            curr->right = (story.getRightEventNumber() != -1)
                ? nodeMap[story.getRightEventNumber()]
                : nullptr;
        }

        // Set root to first node
        root = nodeMap.count(1) ? nodeMap[1] : nullptr;
    }

    void playGame() {
        Node<T>* curr = root;

        if (root == nullptr) {
            std::cout << "No story loaded. Cannot start the game." << std::endl;
            return;
        }

        while (curr != nullptr) {
            // Print current situation
            std::cout << curr->data.getDescription() << std::endl;

            // Check available options
            bool hasLeftOption = curr->data.getLeftEventNumber() != -1;
            bool hasRightOption = curr->data.getRightEventNumber() != -1;

            // Print available options
            if (hasLeftOption) {
                std::cout << "1. " << curr->left->data.getDescription() << std::endl;
            }
            if (hasRightOption) {
                std::cout << "2. " << curr->right->data.getDescription() << std::endl;
            }

            // Check for game end condition
            if (!hasLeftOption && !hasRightOption) {
                std::cout << "Game Over!" << std::endl;
                break;
            }

            // Get user input
            int userChoice;
            while (true) {
                std::cout << "Enter your choice (1 or 2): ";

                if (!(std::cin >> userChoice)) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid input. Please enter 1 or 2." << std::endl;
                    continue;
                }

                // Validate choice based on available options
                if (userChoice == 1 && hasLeftOption) break;
                if (userChoice == 2 && hasRightOption) break;

                std::cout << "Invalid choice. Please choose an available option." << std::endl;
            }

            // Move to next node
            curr = (userChoice == 1) ? curr->left : curr->right;
        }
    }
};

#endif // GAMEDECISIONTREE_H