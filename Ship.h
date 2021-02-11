//
// Created by Lenovo_302 on 03.12.2020.
//

/*
 * TODO: деструктор
 */

#ifndef COURSEWORK__TEST__SHIP_H
#define COURSEWORK__TEST__SHIP_H

#include "Configuration.h"
#include "Cell.h"

class Ship {
protected:
    //данные
    ushort size {0};
    std::vector<Cell*> cells;
    DIR direction {DIR::unknown};

public:
    //конструкторы
    Ship();
    Ship(Cell**, ushort, DIR);

    //геттеры и сеттеры
    std::vector<Cell*> get_cells() const;

    ushort get_size() const;

    DIR get_direction() const;

    //проверка не тонет ли
    bool is_alive() const;
    //потопить корабль
    void sink();
};

#endif //COURSEWORK__TEST__SHIP_H
