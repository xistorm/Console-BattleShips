//
// Created by Lenovo_302 on 04.12.2020.
//

#pragma once

#ifndef COURSEWORK__TEST__PLAYER_H
#define COURSEWORK__TEST__PLAYER_H

#include "Configuration.h"
#include "Ship.h"
#include "Field.h"

class Player {
protected:
    //данные
    Field field;
    std::vector<std::pair<Coordinates, std::string>> turns;

    static std::string get_shoot_status(int);
public:
    //конструкторы
    Player();

    virtual void display_turns() const;
    virtual void display_field() const;

    //поставить корабль
    void place_ship(ushort, ushort, Coordinates, ushort);
    virtual void place_ship(ushort, ushort);

    //выстрелить
    virtual void shoot(Player*);
    int shoot(Coordinates);

    //все ли корабли мертвы
    bool is_dead() const;
};

#endif //COURSEWORK__TEST__PLAYER_H
