#include <iostream>
#include <filesystem>
#include "Graph.h"
#include "Person.h"
#include "utils.h"

using namespace std;



int main() {
    // Sosyal ağ verilerini dosyadan oku
    cout << "Current path is " << filesystem::current_path()
         << endl;

    std::string filename = "social_network.csv";
    Graph graph;
    try {
        graph = readData("social_network.csv");
    } catch (const std::exception& e) {
        std::cerr << "Error reading data from file: " << e.what() << std::endl;
        return 1;
    }

    int choice;
    do {
        // Menüyü göster
        std::cout << "\nSocial Network Analysis Menu:" << std::endl;
        std::cout << "1. Display the social network" << std::endl;
        std::cout << "2. Suggest friends for users" << std::endl;
        std::cout << "3. Calculate degree centrality" << std::endl;
        std::cout << "4. Calculate clustering coefficient" << std::endl;
        std::cout << "5. Detect communities using Girvan-Newman algorithm" << std::endl;
        std::cout << "6. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                // Sosyal ağı göster
            {
                std::cout << "\nSocial Network:" << std::endl;
                auto network = graph.getGraph();
                for (const auto& pair : network) {
                    int id = pair.first;
                    const Person& person = pair.second;
                    std::cout << "Person ID: " << id << ", Name: " << person.getName() << ", Age: " << person.getAge() <<", Gender: " <<person.getGender()<<", Occupation: "<<person.getOccupation()<< std::endl;
                    std::cout << "\tFriend' ID: ";
                    const auto& friends = person.getFriends();
                    for (int friendId : friends) {
                        std::cout << friendId << " ";
                    }
                    std::cout << std::endl;
                }
            }
                break;

            case 2:
                // Kullanıcılara arkadaş önerileri yap
            {
                int personId;
                std::cout << "\nEnter the person ID for whom you want friend suggestions: ";
                std::cin >> personId;

                std::cout << "\nChoose mode for friend suggestions:" << std::endl;
                std::cout << "1. Common Friends" << std::endl;
                std::cout << "2. Similar Occupation" << std::endl;
                std::cout << "3. Similar Age" << std::endl;

                int mode;
                std::cout << "Enter your choice: ";
                std::cin >> mode;

                switch (mode) {
                    case 1:
                        // Ortak arkadaşlara göre arkadaş önerisi
                    {
                        std::vector<int> suggestions = graph.suggestFriends(personId, 1);

                        std::cout << "\nFriend suggestions for Person ID " << personId << " based on common friends:" << std::endl;
                        for (size_t i = 0; i < suggestions.size(); ++i) {
                            int friendId = suggestions[i];
                            std::cout << friendId << " ";
                        }
                        std::cout << std::endl;
                    }
                        break;
                    case 2:
                        // Mesleğe göre arkadaş önerisi
                    {
                        auto suggestions = graph.suggestFriends(personId, 2);
                        std::cout << "\nFriend suggestions for Person ID " << personId << " based on similar occupation:" << std::endl;
                        for (int friendId : suggestions) {
                            std::cout << friendId << " ";
                        }
                        std::cout << std::endl;
                    }
                        break;
                    case 3:
                        // Yaşa göre arkadaş önerisi
                    {
                        auto suggestions = graph.suggestFriends(personId, 3);
                        std::cout << "\nFriend suggestions for Person ID " << personId << " based on similar age:" << std::endl;
                        for (int friendId : suggestions) {
                            std::cout << friendId << " ";
                        }
                        std::cout << std::endl;
                    }
                        break;
                    default:
                        std::cout << "Invalid mode choice. Please enter a number between 1 and 3." << std::endl;
                }
            }
                break;

            case 3:
                // Derece merkeziyetini hesapla
            {
                std::cout << "\nDegree Centrality:" << std::endl;
                graph.degreeCentrality();
            }
                break;

            case 4:
                // Küresellik katsayısını hesapla
            {
                int personId;
                std::cout << "\nEnter the person ID for whom you want to calculate clustering coefficient: ";
                std::cin >> personId;

                double coefficient = graph.clusteringCoefficient(personId);
                std::cout << "\nClustering Coefficient for Person ID " << personId << ": " << coefficient << std::endl;
            }
                break;

            case 5:
                // Girvan-Newman algoritmasıyla toplulukları tespit et
            {
                int iterations;
                std::cout << "\nEnter the number of iterations for Girvan-Newman algorithm: ";
                std::cin >> iterations;

                auto communities = graph.girvanNewman(iterations);

                std::cout << "\nCommunities detected using Girvan-Newman algorithm:" << std::endl;
                for (size_t i = 0; i < communities.size(); ++i) {
                    std::cout << "Community " << (i + 1) << ": ";
                    for (int personId : communities[i]) {
                        std::cout << personId << " ";
                    }
                    std::cout << std::endl;
                }
            }
                break;

            case 6:
                std::cout << "Exiting the program..." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please enter a number between 1 and 6." << std::endl;
        }
    } while (choice != 6);

    return 0;
}
