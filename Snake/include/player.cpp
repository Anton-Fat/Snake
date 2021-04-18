#include "player.h"

/// \todo delete
#include <QDebug>



int Player::count = 0;
const string Player::t_key_up = "key_up";
const string Player::t_key_down = "key_down";
const string Player::t_key_left = "key_left";
const string Player::t_key_right = "key_right";
Player::Player(string name)
{
    _name = name;
    Player::count++;
    qDebug() << "add Player +1 " << _name.c_str();
}

Player::~Player()
{

    delete m_python.release();

    Player::count--;
    qDebug() << "del Player -1 " << _name.c_str();
}



//==============================================================================
void Player::action_angle(int key)
{

    if(m_python){

        if (( inDict(m_dict, t_key_left) ) && (key == m_dict.at(t_key_left))) {
            m_python->moveAngle(animal::stepDegree);
        }

        if (( inDict(m_dict, t_key_right) ) && (key == m_dict.at(t_key_right))) {
            m_python->moveAngle(animal::stepDegree*-1);
        }

        if (( inDict(m_dict, t_key_up) ) && (key == m_dict.at(t_key_up))) {
            m_python->speed += 10;
        }

        if (( inDict(m_dict, t_key_down) ) && (key == m_dict.at(t_key_down))) {
            m_python->speed -= 10;
        }

    }

}

//==============================================================================
void Player::addDict(string text, int val)
{
    //qDebug() << "Setup key " << text.c_str();
    m_dict.insert(pair<string,int>(text, val));
}
//==============================================================================
template<typename T> // typename
bool Player::inDict(const map<string, T> &dict, string text)
{
    return ( dict.find(text) != dict.end() );
}
//==============================================================================


