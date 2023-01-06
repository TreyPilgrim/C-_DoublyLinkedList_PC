#include "Tokenizer.h"
#include "DoublyLink.h"
#include <fstream>

using std::ifstream;
using std::cin;
using std::cout;
using std::endl;

// please note that the following function will normally
// have a function prototype more like
// bool processText(istream& is, <type> &b, bool interactive = true)
// where <type> is the type of the data structure we are working with
bool processText(istream& is, DoublyLink& list, bool interactive = true)
{
    // implement support for
    // exit ... exit the program
    // add string string ... concatenate two strings
    // add double double ... sum two integers
    // load file ... loads a file containing supported commands
    string line;
    string command;
    string arg1, arg2, arg3;
    int num1;
    Tokenizer tkn;
    while (true)
    {
        if (!interactive)
        {
            if (is.eof()) return true;
        }
        else { cout << ">> "; }

        getline(is, line);
        tkn.setString(line);

        tkn.readWord(command);
        if (command == "exit")
        {
            cout << "Exiting ...." << endl;
            return false;
        }
        if (command == "load")
        {
            // load expects a filename .. so read one more word
            if (!tkn.readWord(arg1)) {
                cout << "Missing file name" << endl;
                continue; // skip back to the top of the read loop
            }
            ifstream fin;
            bool status = true;
            fin.open(arg1);
            if (fin.is_open())
            {
                // keeping in mind the note about the definition for the processText function
                // the following line of code is closer to
                // status = processText(fin, b, false);
                status = processText(fin, list, false);
            }
            else { cout << "Failed to open the file" << endl; }
            fin.close();
            if (!status) return false;
        }
        if (command == "add")
        {
            // add works with two different syntaxes ...
            // we need to check them in the proper order which is
            //     add double double
            //     add string string
            // for the moment we are making a simple assumption .. if the first argument is a double, the second argument must be a doublle
            // so although add 2.0 this could result in 2.0this .. it will not, it will be treated as a error.

           if (tkn.readWord(arg1))
           {
               list.addPlayer(arg1);
               cout << arg1 << " has been added to the list of PCs" << endl;
           }

           continue;

        }
        if (command == "remove")
        {
            tkn.readWord(arg1);
            bool done {list.removePlayer(arg1)};

            if (done)
            {
                cout << arg1 << " has been removed from the PC database." << endl;
                continue;
            }else
            {
                cout << arg1 << " is not a player in the PC database." << endl;
                continue;
            }
        }
        if (command == "set")
        {
            tkn.readWord(arg1);
            tkn.readWord(arg2);
            if (tkn.readInteger(num1))
                list.updatePlayer(arg1, arg2, num1);
            else
            {
                tkn.readWord(arg3);
                list.updatePlayer(arg1, arg2, arg3);
            }

            continue;
        }
        if (command == "search")
        {
            tkn.readWord(arg1);

            if (tkn.readInteger(num1))
                list.searchList(num1);
            else
            {
                tkn.readWord(arg2);
                list.searchList(arg1, arg2);
            }

            continue;
        }
        if (command == "display")
        {
            bool empty;
            empty = list.peek();

            if (empty)
            {
                cout << "There aren't any players in the database" << endl;
                continue;
            }

            // otherwise
            list.displayDatabase();
        }
    }


}


int main()
{
// the following line of code is normally closer to this
// <type> inst;
// processText(cin, inst);
// where <type> is the type of the data structure we are working with

    DoublyLink list;
    processText(cin, list);
    return 0;

}
