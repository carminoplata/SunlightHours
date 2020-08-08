#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <boost/assign.hpp>
#include <boost/bimap.hpp>
/**
 * Define the Cell type which is the unit inside the Room. Its values are:
 * - 'S': cleanable space
 * - 'C': column (not cleanable)
 * - 'W': wall/empty space (not cleanable)
 * */
enum class Cell { S = 'S', C = 'C', W=0};

enum Direction{
    N = 'N',
    W = 'W',
    E = 'E',
    S = 'S'
};

inline bool isValidDirection(char direction){
    return direction == Direction::N || direction == Direction::E || 
        direction == Direction::W || direction == Direction::S;
}
/**
 * Define the Command type which estabilishes the available actions for the
 * robot.
 * - 'TL': turn left
 * - 'TR': turn right
 * - 'A': advance
 * - 'B': back
 * - 'C': clean
 * */
enum class Command { TL, TR, A, B, C };

template<typename T>
using enumMap = boost::bimap<T, std::string>;

template<typename T>
inline enumMap<T> createMap(std::initializer_list<typename enumMap<T>::value_type> list)
{
    return enumMap<T>{list.begin(), list.end()};
}


static enumMap<Cell> cellValues = createMap<Cell>({
    {Cell::S, "S"},
    {Cell::C, "C"},
    {Cell::W, "null"}
});
    
static enumMap<Command> commandValues = createMap<Command>({
    {Command::TL, "TL"},
    {Command::TR, "TR"},
    {Command::A, "A"},
    {Command::B, "B"},
    {Command::C, "C"}
});

static const std::vector<std::vector<Command>> backoffStrategy = {
    {Command::TR, Command::A, Command::TL},
    {Command::TR, Command::A, Command::TR},
    {Command::TR, Command::A, Command::TR},
    {Command::TR, Command::B, Command::TR, Command::A},
    {Command::TL, Command::TL, Command::A}
};

#endif