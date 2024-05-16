#include <iostream>
#include <unordered_map>
#include <string>

using namespace std; // Директива using namespace

class AssociativeEntity {
private:
    unordered_map<string, string> data;
    int codeError;

public:
    AssociativeEntity() : codeError(0) {}

    // Function to create a set of associative entities
    void createEntities(const unordered_map<string, string>& entities) {
        data = entities;
    }

    // Overloaded index operator to access entities by country
    string& operator[](const string& country) {
        if (data.find(country) != data.end()) {
            return data[country];
        }
        else {
            codeError = 1; // Entity not found error
            static string emptyString; // Return empty string if entity not found
            return emptyString;
        }
    }

    // Function call operator to access entities by country
    string& operator()(const string& country) {
        return (*this)[country];
    }

    // Friend functions for stream operators
    friend ostream& operator<<(ostream& out, const AssociativeEntity& entities);
    friend istream& operator>>(istream& in, AssociativeEntity& entities);
};

// Stream operators
ostream& operator<<(ostream& out, const AssociativeEntity& entities) {
    for (const auto& pair : entities.data) {
        out << "Country: " << pair.first << ", Capital: " << pair.second << endl;
    }
    return out;
}

istream& operator>>(istream& in, AssociativeEntity& entities) {
    int numEntries;
    cout << "Enter the number of entries: ";
    in >> numEntries;

    cout << "Enter country-capital pairs:" << endl;
    for (int i = 0; i < numEntries; ++i) {
        string country, capital;
        cout << "Country: ";
        in >> country;
        cout << "Capital: ";
        in >> capital;
        entities.data[country] = capital;
    }
    return in;
}

int main() {
    AssociativeEntity countries;

    // Create entities using overloaded insertion operator >>
    cin >> countries;

    // Access entities using overloaded index operator []
    cout << "Capital of France: " << countries["France"] << endl;

    // Access entities using overloaded function call operator ()
    cout << "Capital of Germany: " << countries("Germany") << endl;

    // Output all entities using overloaded extraction operator <<
    cout << "All country-capital pairs:" << endl;
    cout << countries;

    return 0;
}
