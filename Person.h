#pragma once
#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <vector>

class Person {
public:
    // Constructor
    Person(int id, std::string  name, int age, std::string& gender, std::string  occupation, const std::vector<int>& friends);

    // Getters
    int getId() const;
    std::string getName() const;
    int getAge() const;
    std::string getGender() const;
    std::string getOccupation() const;
    std::vector<int> getFriends() const;

    //Functions
    static void removeFriend(int friendId);

private:
    int id;
    std::string name;
    int age;
    std::string gender;
    std::string occupation;
    std::vector<int> friends;
};

#endif // PERSON_H