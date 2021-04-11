#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>

#include "python.h"

using namespace std;

//template <class T>
class Player
{
    //Q_OBJECT

public:

    Player(string name);

    ~Player();

    static const string t_key_up;
    static const string t_key_down;
    static const string t_key_left;
    static const string t_key_right;


    // python * m_python {nullptr};

    std::unique_ptr<python> m_python;

    static int count;


    map <string, int> m_dict;

    void action_angle(int key);





    template <typename T> // class
    bool inDict(const map<string, T> &dict, string text);
    void addDict(string text, int val);

    std::string const& name() const { return _name; }

    static string getT_key_up();

private:



    string _name;




};

#endif // PLAYER_H
