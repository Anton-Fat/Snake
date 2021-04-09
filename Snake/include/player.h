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

    const string t_key_up {"key_up"};
    const string t_key_down {"key_down"};
    const string t_key_left {"key_left"};
    const string t_key_right {"key_right"};


    python * m_python {nullptr};

    static int count;

    void action_angle(int key);



    template <typename T> // class
    bool inDict(const map<string, T> &dict, string text);
    void addDict(string text, int val);

    std::string const& name() const { return _name; }

private:

    map <string, int> m_dict;

    string _name;




};

#endif // PLAYER_H
