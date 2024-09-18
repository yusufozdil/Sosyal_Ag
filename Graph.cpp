#include "Graph.h"
#include "Person.h"
// Constructor
Graph::Graph() : size(0) {}


void Graph::addPerson(int id, const Person &person) {
    graph.emplace_back(id, person);
    size++;
}

//kişiyi döndür
const Person* Graph::getPerson(int id) const {
    for (const auto& pair : graph) {
        if (pair.first == id) {
            return &(pair.second);
        }
    }
    return nullptr;
}

std::vector<int> Graph::getCommonFriends(const Person* person1, const Person* person2) {
    std::vector<int> commonFriends;

    if (person1 == nullptr || person2 == nullptr) {
        // Geçersiz kişiler için boş vektör döndür
        return commonFriends;
    }

    // person1'in arkadaşlarını al
    std::vector<int> person1Friends = person1->getFriends();

    // person2'nin arkadaşlarını al
    std::vector<int> person2Friends = person2->getFriends();

    // İki kişinin ortak arkadaşlarını bul
    for (int friendId : person1Friends) {
        if (std::find(person2Friends.begin(), person2Friends.end(), friendId) != person2Friends.end()) {
            commonFriends.push_back(friendId);
        }
    }

    return commonFriends;
}


//Ortak arkadaşlara göre arkadaş önerisi
std::vector<int> Graph::suggestFriendsByCommonFriends(const Person* person, const std::vector<Person>& people) {
    std::vector<int> suggestedFriends;

    // Verilen kişinin arkadaşlarını al
    std::vector<int> personFriends = person->getFriends();

    // Her kişi için
    for (const Person& p : people) {
        // Kendisiyle aynı kişi ise veya zaten arkadaş listesinde ise atla
        if (p.getId() == person->getId() || std::find(personFriends.begin(), personFriends.end(), p.getId()) != personFriends.end()) {
            continue;
        }

        // Kişinin ortak arkadaşlarını al
        std::vector<int> commonFriends = getCommonFriends(person, &p);

        // Eğer ortak arkadaş sayısı 1'den fazlaysa, bu kişiyi öner
        if (commonFriends.size() > 1) {
            suggestedFriends.push_back(p.getId());
        }
    }

    return suggestedFriends;
}

// Mesleğe göre arkadaş önerisi
std::vector<int> Graph::suggestFriendsByOccupation(const Person* person, const std::vector<Person>& people) {
    std::vector<int> suggestedFriends;

    // Verilen kişinin mesleğini al
    std::string personOccupation = person->getOccupation();

    // Her kişi için
    for (const Person& p : people) {
        // Kendisiyle aynı kişi ise veya zaten arkadaş listesinde ise atla
        std::vector<int> personFriends = p.getFriends();
        if (p.getId() == person->getId() || std::find(personFriends.begin(), personFriends.end(), p.getId()) != personFriends.end()) {
            continue;
        }

        // Kişinin mesleğini al
        std::string occupation = p.getOccupation();

        // Eğer meslekler aynıysa, bu kişiyi öner
        if (occupation == personOccupation) {
            suggestedFriends.push_back(p.getId());
        }
    }

    return suggestedFriends;
}

// Yaşa göre arkadaş önerisi
std::vector<int> Graph::suggestFriendsByAge(const Person* person, const std::vector<Person>& people) {
    std::vector<int> suggestedFriends;

    // Verilen kişinin yaşını al
    int personAge = person->getAge();

    // Her kişi için
    for (const Person& p : people) {
        // Kendisiyle aynı kişi ise veya zaten arkadaş listesinde ise atla
        std::vector<int> personFriends = p.getFriends();
        if (p.getId() == person->getId() || std::find(personFriends.begin(), personFriends.end(), p.getId()) != personFriends.end()) {
            continue;
        }

        // Kişinin yaşını al
        int age = p.getAge();

        // Eğer yaşlar benzerse, bu kişiyi öner
        if (std::abs(age - personAge) <= 3) { // 3 yaş farkını kabul ediyoruz
            suggestedFriends.push_back(p.getId());
        }
    }

    return suggestedFriends;
}


std::vector<Person> Graph::getPeople() const {
    std::vector<Person> people;
    for (const auto& pair : graph) {
        people.push_back(pair.second);
    }
    return people;
}


std::vector<int> Graph::suggestFriends(int person_id, int mode) const {
    const Person* person = getPerson(person_id);
    if (person == nullptr) {
        std::cerr << "Person with ID " << person_id << " not found." << std::endl;
        std::vector<int> emptyVector;
        return emptyVector;
    }

    const std::vector<Person>& people = getPeople();

    switch (mode) {
        case 1:
            //Ortak arkadaşlara göre arkadaş önerisi
            return suggestFriendsByCommonFriends(person, people);
        case 2:
            // Mesleğe göre arkadaş önerisi
            return suggestFriendsByOccupation(person, people);
        case 3:
            // Yaşa göre arkadaş önerisi
            return suggestFriendsByAge(person, people);
        default:
            std::cerr << "Invalid mode." << std::endl;
            std::vector<int> emptyVector;
            return emptyVector;
    }
}


int Graph::getSize() const {
    return size;
}

void Graph::degreeCentrality() const {
    std::cout << "Degree Centrality:" << std::endl;
    for (const auto& pair : graph) {
        int id = pair.first;
        const Person& person = pair.second;
        int degree = person.getFriends().size();
        std::cout << "Person ID: " << id << ", Degree Centrality: " << degree << std::endl;
    }
}


double Graph::clusteringCoefficient(int id) const {
    const Person* person = getPerson(id);
    if (person == nullptr) {
        std::cerr << "Person with ID " << id << " not found." << std::endl;
        return 0.0;
    }

    const std::vector<int>& personFriends = person->getFriends();
    int totalPossibleTriangles = 0;
    int actualTriangles = 0;

    // Her bir arkadaşın birbiriyle olan ilişkisini kontrol etmek için iki döngü
    for (int friendId1 : personFriends) {
        for (int friendId2 : personFriends) {
            if (friendId1 != friendId2) {
                // İki arkadaşın da birbirleriyle arkadaş olup olmadığını kontrol edin
                const Person* friend1 = getPerson(friendId1);
                const Person* friend2 = getPerson(friendId2);
                if (friend1 != nullptr && friend2 != nullptr) {
                    const std::vector<int>& friend1Friends = friend1->getFriends();
                    const std::vector<int>& friend2Friends = friend2->getFriends();
                    if (std::find(friend1Friends.begin(), friend1Friends.end(), friendId2) != friend1Friends.end() &&
                        std::find(friend2Friends.begin(), friend2Friends.end(), friendId1) != friend2Friends.end()) {
                        // Üçgen oluşturma durumu
                        actualTriangles++;
                    }
                    totalPossibleTriangles++;
                }
            }
        }
    }

    // Küresellik katsayısını hesapla
    if (totalPossibleTriangles == 0) {
        return 0.0; // Hiçbir üçgen yoksa, katsayı 0'dır
    } else {
        return static_cast<double>(actualTriangles) / totalPossibleTriangles;
    }
}


std::vector<std::pair<int, Person>> Graph::getGraph() const {
    return graph;
}

std::vector<std::vector<int>> Graph::girvanNewman(int iterations) {
    // Girvan-Newman algoritması için başlangıçta her düğüm bir topluluk olarak kabul edilir
    std::vector<std::vector<int>> communities;
    communities.reserve(graph.size());
for (const auto& pair : graph) {
        communities.push_back({pair.first}); // Her düğüm kendi başlangıçta kendi topluluğunda
    }

    // Belirtilen iterasyon sayısı kadar algoritmayı çalıştır
    for (int i = 0; i < iterations; ++i) {
        // Her bir iterasyonda, en yüksek ağırlıklı kenarlar çıkarılarak topluluklar belirlenir
        while (true) {
            // Grafın tüm kenarlarının ağırlığını hesapla
            std::map<std::pair<int, int>, double> edgeWeights;
            for (const auto& pair : graph) {
                int id = pair.first;
                const Person& person = pair.second;
                const std::vector<int>& friends = person.getFriends();
                for (int friendId : friends) {
                    edgeWeights[{id, friendId}] = edgeWeight(*this, id, friendId);
                }
            }

            // En yüksek ağırlıklı kenarı bul
            double maxWeight = -1;
            std::pair<int, int> maxEdge;
            for (const auto& entry : edgeWeights) {
                if (entry.second > maxWeight) {
                    maxWeight = entry.second;
                    maxEdge = entry.first;
                }
            }

            // En yüksek ağırlıklı kenarı çıkar
            removeFriendship(maxEdge.first, maxEdge.second);

            // Çıkarılan kenar sonrası toplulukları yeniden hesapla
            std::vector<std::vector<int>> updatedCommunities;
            for (const auto& pair : graph) {
                int id = pair.first;
                const Person& person = pair.second;
                std::vector<int> community;
                for (const auto& c : communities) {
                    if (std::find(c.begin(), c.end(), id) != c.end()) {
                        community = c;
                        break;
                    }
                }
                const std::vector<int>& friends = person.getFriends();
                for (int friendId : friends) {
                    if (std::find(community.begin(), community.end(), friendId) == community.end()) {
                        community.push_back(friendId);
                    }
                }
                updatedCommunities.push_back(community);
            }

            // Topluluklar değişmediyse çık
            if (updatedCommunities == communities) {
                break;
            }

            communities = updatedCommunities;
        }
    }

    return communities;
}


double Graph::edgeWeight(const Graph &graph, int u, int v) const {
    // İki düğüm arasındaki kenarın ağırlığını hesaplamak için bir metrik kullanılmalıdır.
    // Bu metrik, genellikle iki düğüm arasındaki bağlantının gücünü veya önemini yansıtır.
    // Basitçe iki düğüm arasındaki doğrudan arkadaşlık sayısını kullandım.

    const Person* personU = getPerson(u);
    const Person* personV = getPerson(v);

    if (personU == nullptr || personV == nullptr) {
        std::cerr << "One or both of the persons not found." << std::endl;
        return 0.0;
    }

    const std::vector<int>& friendsU = personU->getFriends();
    const std::vector<int>& friendsV = personV->getFriends();

    // İki düğüm arasındaki doğrudan ortak arkadaş sayısını hesapla
    int commonFriends = 0;
    for (int friendId : friendsU) {
        if (std::find(friendsV.begin(), friendsV.end(), friendId) != friendsV.end()) {
            commonFriends++;
        }
    }

    // Ağırlık, ortak arkadaş sayısının bir fonksiyonu olabilir.
    return static_cast<double>(commonFriends);
}


void Graph::removeFriendship(int id1, int id2) {
    Person *person1 = const_cast<Person *>(getPerson(id1));
    Person *person2 = const_cast<Person *>(getPerson(id2));

    if (person1 == nullptr || person2 == nullptr) {
        std::cerr << "One or both persons not found." << std::endl;
        return;
    }

    person1->removeFriend(id2);
    person2->removeFriend(id1);

    //std::cout << "Friendship between Person ID " << id1 << " and Person ID " << id2 << " removed successfully." << std::endl;
}


std::ostream& operator<<(std::ostream& os, const Graph& graph) {
    // Graph'i yazdırmak için aşırı yüklü akım ekleme operatörü

    os << "Graph:\n";
    for (size_t i = 0; i < graph.adjacencyList.size(); ++i) {
        os << i << " -> ";
        for (int j : graph.adjacencyList[i]) {
            os << j << " ";
        }
        os << "\n";
    }
    return os;
}





