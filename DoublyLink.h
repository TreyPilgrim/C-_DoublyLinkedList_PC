#pragma once
#include "Node.h"
#include "PC.h"
#include <string>
#include <vector>

using std::vector;
using std::string;
class DoublyLink
{
private:
    // attributes
    Node* head{nullptr};
    Node* tail {nullptr};

    // alphabet for string comparison
    vector<char> upper {' ','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    vector<char> lower {' ','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

    // Private Member Functions Below //

    // Node return type
    Node* getPlayer(const string& name, Node* node);

    // void return type
    static void displayPlayer(Node* player);
    void searchList (int value, Node* player);
    void searchList (const string& stat, const string& val, Node* player);
    void displayDatabase(Node* player);

    // bool return type
    bool findPlayer (string name, Node* player);
    bool findPlayer (string name);
    bool removePlayer (string name, Node* player);

    string compareNames (string name1, string name2);


public:

    // Void return type
    void append(string name);
    void prepend (string name);
    void addPlayer (string& name);
    void searchList (int value);
    void searchList (string stat, string value);
    void displayDatabase();

    // Bool return type
    bool updatePlayer (const string& name, const string& stat, int newVal);
    bool updatePlayer (const string& name, const string& stat, string newVal);
    bool removePlayer(string name);
    bool peek();




};