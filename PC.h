#pragma once
#include <string>

using std::string;

class PC
{
private:
    // attributes
    string name {"Trey Pilgrim"};
    string race {"PC"};
    string job {"Villager"};
    int level {1};

public:
    // Public Functions //
    PC() = default;

    // void return type
    void setName (string &str);
    void setRace (string &str);
    void setJob (string &str);
    void setLevel (int &num);

    // String return type
    string getName() const;
    string getRace() const;
    string getJob() const;

    // Int return type
    int getLevel() const;
};
