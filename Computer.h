//
// Created by Lenovo_302 on 07.12.2020.
//

#ifndef COURSEWORK_COMPUTER_H
#define COURSEWORK_COMPUTER_H

#include "Configuration.h"
#include "Player.h"

class Computer : public Player {
private:
    std::vector<Coordinates> shooted_cells;
    DIR shooting_direction;
    ushort choose_direction;
public:
    //конструкторы
    Computer();

    void display_turns() const override;
    void display_field() const override;

    //когда убил корабль, убрать пресет выстрела
    void reset_shooting();

    //поставить корабль
    void place_ship(ushort, ushort) override;

    //выстрелить
    void shoot(Player*) override;
};

#endif //COURSEWORK_COMPUTER_H
