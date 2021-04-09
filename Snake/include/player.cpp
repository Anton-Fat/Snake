#include "player.h"

/// \todo delete
#include <QDebug>



int Player::count = 0;



Player::Player(string name)
{
    _name = name;
    Player::count++;
    qDebug() << "add Player +1 " << _name.c_str();
}

Player::~Player()
{

    if (m_python){
        delete m_python;
    }

    Player::count--;
    qDebug() << "del Player -1 " << _name.c_str();
}

//==============================================================================
void Player::action_angle(int key)
{

    if(m_python){

        if (( inDict(m_dict, t_key_left) ) && (key == m_dict.at(t_key_left)) && (m_python->angle != animal::dir_right)) {
            m_python->angle = animal::dir_left;
        }

        if (( inDict(m_dict, t_key_right) ) && (key == m_dict.at(t_key_right)) && (m_python->angle != animal::dir_left)) {
            m_python->angle = animal::dir_right;
        }

        if (( inDict(m_dict, t_key_up) ) && (key == m_dict.at(t_key_up)) && (m_python->angle != animal::dir_down)) {
            m_python->angle = animal::dir_up;
        }

        if (( inDict(m_dict, t_key_down) ) && (key == m_dict.at(t_key_down)) && (m_python->angle != animal::dir_up)) {
            m_python->angle = animal::dir_down;
        }

    }

}
//==============================================================================
void Player::addDict(string text, int val)
{
    m_dict.insert(pair<string,int>(text, val));
}
//==============================================================================
template<typename T> // typename
bool Player::inDict(const map<string, T> &dict, string text)
{
    return ( dict.find(text) != dict.end() );
}
//==============================================================================


