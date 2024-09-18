#include <algorithm>
#include <iostream>
#include <utility>
#include "Person.h"

// Constructor
Person::Person(int id, std::string  name, int age, std::string& gender, std::string  occupation, const std::vector<int>& friends)
        : id(id), name(std::move(name)), age(age), gender(gender), occupation(std::move(occupation)), friends(friends) {}

void Person::removeFriend(int friendId) {
    std::vector<int> friends;
    auto it = std::find(friends.begin(), friends.end(), friendId);
    if (it != friends.end()) {
        friends.erase(it);
        std::cout << "Friend with ID " << friendId << " removed successfully." << std::endl;
    } else {
        //std::cerr << "Friend with ID " << friendId << " not found." << std::endl;
    }
}

// Getters
int Person::getId() const {
    return id;
}

std::string Person::getName() const {
    return name;
}

int Person::getAge() const {
    return age;
}

std::string Person::getGender() const {
    return gender;
}

std::string Person::getOccupation() const {
    return occupation;
}

std::vector<int> Person::getFriends() const {
    return friends;
}
