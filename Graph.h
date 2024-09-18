#pragma once
#ifndef GRAPH_H
#define GRAPH_H

#include "Person.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <map>


class Graph {
public:
    //Constructor
    Graph();

    //Getters
    int getSize() const;
    const Person* getPerson(int id) const;
    std::vector<std::pair<int, Person>> getGraph() const;
    std::vector<Person> getPeople() const;
    static std::vector<int> getCommonFriends(const Person *person1, const Person *person2) ;

    //Functions
    void addPerson(int id, const Person &person);
    void degreeCentrality() const;
    double clusteringCoefficient(int id) const;
    std::vector<std::vector<int>> girvanNewman(int iterations);
    double edgeWeight(const Graph &graph, int u, int v) const;
    std::vector<int> suggestFriends(int person_id, int mode) const;
    void removeFriendship(int id1, int id2);
    static std::vector<int> suggestFriendsByCommonFriends(const Person *person, const std::vector<Person> &people) ;
    static std::vector<int>suggestFriendsByOccupation(const Person *person, const std::vector<Person> &people) ;
    static std::vector<int> suggestFriendsByAge(const Person *person, const std::vector<Person> &people) ;
    friend std::ostream& operator<<(std::ostream& os, const Graph& graph);

private:
    std::vector<std::pair<int, Person>> graph;
    int size{};
    std::vector<std::vector<int>> adjacencyList;
};

#endif //GRAPH_H