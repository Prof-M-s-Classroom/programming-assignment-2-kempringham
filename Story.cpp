#include "Story.h"

// TODO: Default constructor
Story::Story() : description(""), eventNumber(0), leftEventNumber(-1), rightEventNumber(-1) {
    description = "";
    eventNumber = 0;
    leftEventNumber = -1;
    rightEventNumber = -1;
}

// TODO: Parameterized constructor
Story::Story(std::string desc, int num, int leftNum, int rightNum)
        : description(desc), eventNumber(num), leftEventNumber(leftNum), rightEventNumber(rightNum) {
    description = desc;
    eventNumber = num;
    leftEventNumber = leftNum;
    rightEventNumber = rightNum;
}

// Added helper functions

std::string Story::getDescription() {
    return description;
}

int Story::getEventNumber() {
    return eventNumber;
}

int Story::getLeftEventNumber() {
    return leftEventNumber;
}

int Story::getRightEventNumber() {
    return rightEventNumber;
}
