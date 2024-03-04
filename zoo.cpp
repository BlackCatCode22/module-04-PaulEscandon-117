#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>

using namespace std;

// Animal class
class Animal {
protected:
    string name;
    int age;
    string species;

public:
    Animal(string name, int age, string species) : name(name), age(age), species(species) {}

    string getName() const {
        return name;
    }

    int getAge() const {
        return age;
    }

    string getSpecies() const {
        return species;
    }
};

// Subclasses
class Hyena : public Animal {
public:
    Hyena(string name, int age) : Animal(name, age, "Hyena") {}
};

class Lion : public Animal {
public:
    Lion(string name, int age) : Animal(name, age, "Lion") {}
};

class Tiger : public Animal {
public:
    Tiger(string name, int age) : Animal(name, age, "Tiger") {}
};

class Bear : public Animal {
public:
    Bear(string name, int age) : Animal(name, age, "Bear") {}
};

int main() {
    ifstream inputFile("arrivingAnimals.txt");
    if (!inputFile) {
        cerr << "Error: Unable to open input file." << endl;
        return 1;
    }

    vector<Animal*> animals;
    map<string, int> speciesCount;

    string name, species;
    int age;

    // Read animal details from the input file
    while (inputFile >> age >> species) {
        getline(inputFile, name);
        animals.push_back(new Animal(name, age, species));
        speciesCount[species]++;
    }

    // Output report to newAnimals.txt
    ofstream outputFile("newAnimals.txt");
    if (!outputFile) {
        cerr << "Error: Unable to open output file." << endl;
        inputFile.close();
        return 1;
    }

    for (auto it = speciesCount.begin(); it != speciesCount.end(); ++it) {
        outputFile << it->first << " Count: " << it->second << endl;
        for (Animal* animal : animals) {
            if (animal->getSpecies() == it->first) {
                outputFile << "Name: " << animal->getName() << ", Age: " << animal->getAge() << endl;
            }
        }
        outputFile << endl;
    }

    // Free allocated memory
    for (Animal* animal : animals) {
        delete animal;
    }

    // Close files
    inputFile.close();
    outputFile.close();

    return 0;
}
