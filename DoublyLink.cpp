#include "DoublyLink.h"
#include <iostream>
#include <algorithm>

using std::find;
using std::distance;
using std::cout;
using std::endl;
using std::isupper;
using std::find;
using std::distance;

// -------------Private Functions----------------- //
/*
 * Node* return type
 */
// Search Doubly linked list for player by name
Node* DoublyLink::getPlayer(const string& name, Node* node)
{
    Node* tmp = node;


    if (tmp == nullptr)
        return tmp;

    string player = tmp->getName();

    // return node if player->name == key
    if (player == name)
    {
        return tmp;
    } else // otherwise
    {
        return getPlayer(name, node->next);
    }
}

/*
 * Void return type
 */

// Append a Node
void DoublyLink::append(string name)
{
    Node* tmp = new Node();
    tmp->setName(name);

    // if empty
    if (head == nullptr)
    {
        head = tmp;
    }else // otherwise
    {
        tail->next = tmp;
        tmp->prev = tail;
    }

    tail = tmp;
}

// Prepend a Node
void DoublyLink::prepend(string name)
{
    Node* tmp = new Node();
    tmp->setName(name);

    // if empty List:
    if (tail == nullptr)
        tail = tmp;
    else // Otherwise:
    {
        head->prev = tmp;
        tmp->next = head;
    }

    head = tmp;
}

// Display Player and all their stats
void DoublyLink::displayPlayer(Node* player)
{
    cout << "Name: " << player->getName() << endl;
    cout << "Race: " << player->getRace() << endl;
    cout << "Job: " << player->getJob() << endl;
    cout << "Level: " << player->getLevel() << endl;
    cout << "-------------------------------------------\n";
}

// Display all Players with specified stat
void DoublyLink::searchList(int value, Node* player)
{

    // if empty, return
    if (player == nullptr)
        return;
    else // Otherwise
    {
        int playerLevel {player->getLevel()};

        // Display player if they have matching level
        if (playerLevel == value)
        {
            displayPlayer(player);
        }
    }

    // search at the next node
    return searchList(value, player->next);
}

// Display all Players with specified Race/Job
void DoublyLink::searchList (const string& stat, const string& val, Node* player)
{
    // if empty, return
    if (player == nullptr)
        return;
    else // Otherwise
    {
        if (stat == "Race" || stat == "race") // if Stat is 'race'
        {
            string playerRace {player->getRace()};

            // Display player if they have matching level
            if (playerRace == val)
                displayPlayer(player);

        } else if (stat == "Job" || stat == "job") // Otherwise, if Stat is 'job'
        {
            string playerJob {player->getJob()};

            // Display player if they have matching job
            if (playerJob == val)
                displayPlayer(player);

        } else // Any invalid input will make function return
        {
            cout << "Check your spelling...\n There seems to be an invalid input." << endl;
            return;
        }

    }

    // search at the next node
    return searchList(stat, val, player->next);
}

// Display entire database
void DoublyLink::displayDatabase(Node* player)
{
    if (player == nullptr)
        return;
    else
        displayPlayer(player);

    return displayDatabase(player->next);
}

/*
 * Bool return type
 */
// search for player in the list
bool DoublyLink::findPlayer(string name, Node* player)
{
    // if empty list, or at the end of list
    if (player == nullptr)
        return false;
    else if (name == player->getName()) // or if duplicate name
        return true;
    else // otherwise
        return findPlayer(name, player->next);

}
// find PC by name
bool DoublyLink::findPlayer(string name)
{
    return findPlayer(name, head);
}

// remove PC by name
bool DoublyLink::removePlayer(string name, Node *player)
{
    if (player == nullptr)
        return false;

    string playerName {player->getName()};

    if (name == playerName)
    {
        if (player == head)
        {
            head = nullptr;
            tail = nullptr;
        }else if (player == tail)
        {
            player->prev->next = nullptr;
            tail = player->prev;
        }else
        {
            player->prev->next = player->next;
            player->next->prev = player->prev;
        }

        delete player;
        return true;
    }

    return removePlayer(name, player->next);
}

/*
 * String return type
 */
// compare 2 string inputs
string DoublyLink::compareNames(string name1, string name2) {
    unsigned int smallLocation;
    unsigned int bigLocation;

    string longerName;
    string shorterName;

    if (name1.length() > name2.length())
    {
        longerName = name1;
        shorterName = name2;
    }else
    {
        longerName = name2;
        shorterName = name1;
    }

    for (int i{0}; i < longerName.length(); i++)
    {
        vector<char>::iterator itrBig = find(lower.begin(), lower.end(), longerName[i]);
        vector<char>::iterator itrSmall = find(lower.begin(), lower.end(), shorterName[i]);


        bigLocation = distance(lower.begin(), itrBig);
        smallLocation = distance(lower.begin(), itrSmall);

        if (bigLocation == smallLocation)
            continue;
        else if ( bigLocation < smallLocation)
            return longerName;
        else
            return shorterName;
    }
}

// -------------Public Functions----------------- //\

/*
 * Void return type
 */
void DoublyLink::addPlayer(string& name)
{
    bool uniqueName;
    uniqueName = findPlayer(name);

    // if name is not in database
    if (!uniqueName)
    {
        // if empty list
        if (head == nullptr)
        {
            prepend(name);
            return;
        }else
        {
            Node* tmp = head;
            while (tmp != nullptr)
            {
                string tmpName = tmp->getName();

                string smallerName;
                smallerName = compareNames(name, tmpName);

                // if name is to be the new Head
                if (smallerName == name && tmpName == head->getName())
                {
                    prepend(name);
                    return;
                }
                else if (smallerName == name)  // or if new name passed is smaller
                {
                    Node *newPC = new Node();
                    newPC->setName(name);

                    // arithmetic to add the new name
                    newPC->next = tmp;
                    newPC->prev = tmp->prev;

                    tmp->prev->next = newPC;
                    tmp->prev = newPC;
                    return;
                } else //otherwise
                {
                    tmp = tmp->next;
                    continue;
                }
            }
            // in the case of name being the new tail
            append(name);
        }

    }else
    {
        cout << name << " already has a player account...\n Either delete that character to add another, or update existing one" << endl;
        return;


    }


}


// Search for ALL players with specific level
void DoublyLink::searchList(int value)
{
    return searchList(value, head);
}

// Serarch for ALL players with specific job/race
void DoublyLink::searchList(string stat, string value)
{
    return searchList(stat, value, head);
}
// Display database by passing in head to private overload Class member function
void DoublyLink::displayDatabase()
{
    return displayDatabase(head);
}

/*
 * Bool return type
 */

// Update player's Level
bool DoublyLink::updatePlayer (const string& name, const string& stat, int newVal)
{
    Node* tmp = getPlayer(name, head);


    if (tmp == nullptr)
    {
        return false;
    }else
    {
        tmp->setLevel(newVal);
    }

    return true;
}

// Update player's Job or Race
bool DoublyLink::updatePlayer (const string& name, const string& stat, string newVal)
{
    Node* tmp = getPlayer(name, head);

    // return false if empty
    if (tmp == nullptr)
    {
        cout << "No player with matching name...\n Check spelling or create a new PC." << endl;
        return false;
    }else // otherwise, check the stat input and update Player accordingly
    {
        if (stat == "race" || stat == "Race") // update the race
            tmp->setRace(newVal);
        else if (stat == "job" || stat == "Job") // or update the job
            tmp->setJob(newVal);
        else // otherwise, invalid inputs return false
        {
            cout << "Invalid input..." << endl;
            return false;
        }
    }

    return true;
}

// Remove node specified by name
bool DoublyLink::removePlayer(string name)
{
    return removePlayer(name, head);
}

bool DoublyLink::peek()
{
    if (head != nullptr)
        return false;
    else
        return true;
}