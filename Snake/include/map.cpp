#include "map.h"

Map::Map()
{

}

Map::Map(int width, int height)
{
    this->width = width;
    this->height = height;
}

Map::~Map()
{

}

QSize Map::getSize()
{
    return QSize(width, height);

}

QSize Map::getCountPoints()
{
    return QSize(width / grid - 1, height / grid - 1);
}
