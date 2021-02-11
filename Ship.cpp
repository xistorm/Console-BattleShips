//
// Created by Lenovo_302 on 03.12.2020.
//

#include "Ship.h"

//конструкторы
Ship::Ship() = default;

Ship::Ship(Cell** _cell, ushort _size, DIR _direction) {
    size = _size;
    direction = _direction;
    cells.clear();

    for (int i = 0; i < _size; ++i) {
        switch (_direction) {
            case DIR::up:
                cells.emplace_back(*(_cell - PG_SIZE * i));
                break;
            case DIR::down:
                cells.emplace_back(*(_cell + PG_SIZE * i));
                break;
            case DIR::right:
                cells.emplace_back(*(_cell + i));
                break;
            case DIR::left:
                cells.emplace_back(*(_cell - i));
                break;
        }
        cells[i]->set_status(STATUS::ship);
    }
}

//геттеры и сеттеры
std::vector<Cell*> Ship::get_cells() const {
    return cells;
}

ushort Ship::get_size() const {
    return size;
}

DIR Ship::get_direction() const {
    return direction;
}

//методы
bool Ship::is_alive() const {
    for (int i = 0; i < size; ++i)
        if (cells[i]->get_status() == STATUS::ship)
            return true;

    return false;
}

void Ship::sink() {
    for (int i = 0; i < size; ++i)
        cells[i]->set_status(STATUS::killed);
}
