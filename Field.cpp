//
// Created by Lenovo_302 on 03.12.2020.
//

#include "Field.h"

#undef max
#undef min

Field::Field() {
    for (char i = 'a'; i < 'a' + PG_SIZE; ++i)
        for (int j = 0; j < PG_SIZE; ++j)
            cells[i - 'a'][j] = new Cell(i, j, STATUS::nothing);
}

ushort Field::find_ship(Coordinates _coords) const {
    for (auto ship : flotilla)
        for (int i = 0; i < FLOTILLA_SIZE; ++i)
            for (int j = 0; j < flotilla[i].get_size(); ++j)
                if (*flotilla[i].get_cells()[j] == _coords)
                    return i;
    return 0;
}

//чтобы не было выхода за границы поля
ushort Field::normalize_coord(int value) {
    return std::min(std::max(value, 0), PG_SIZE - 1);
}

bool Field::correct_coords(Coordinates _coords) const {
    for (int i = normalize_coord(_coords.get_x() - 1); i <= normalize_coord(_coords.get_x() + 1); ++i)
        for (int j = normalize_coord(_coords.get_y() + 1); j >= normalize_coord(_coords.get_y()-1); --j)
            if (cells[i][j]->get_status() == STATUS::ship)
                return false;
    return true;
}

bool Field::correct_pos(ushort _size, Coordinates _coords, DIR _direction) const {
    //сначала проверяем, не выйдет ли он за поле
    switch (_direction) {
        case DIR::up:
            if (_coords.get_x() - _size + 1 < 0)
                return false;
            break;
        case DIR::down:
            if (_coords.get_x() + _size - 1 > 9)
                return false;
            break;
        case DIR::right:
            if (_coords.get_y() + _size - 1 > 9)
                return false;
            break;
        case DIR::left:
            if (_coords.get_y() - _size + 1 < 0)
                return false;
            break;
        case DIR::unknown:
        default:
            break;
    }
    //после проверяем каждую клетку на конфликт с уже существующим кораблём
    for (int i = 0; i < _size; ++i) {
        switch (_direction) {
            case DIR::up:
                if (!correct_coords(Coordinates(_coords.get_x() - i , _coords.get_y())))
                    return false;
                break;
            case DIR::down:
                if (!correct_coords(Coordinates(_coords.get_x() + i, _coords.get_y())))
                    return false;
                break;
            case DIR::right:
                if (!correct_coords(Coordinates(_coords.get_x(), _coords.get_y() + i)))
                    return false;
                break;
            case DIR::left:
                if (!correct_coords(Coordinates(_coords.get_x(), _coords.get_y() - i)))
                    return false;
                break;
            case DIR::unknown:
            default:
                break;
        }
    }
    return true;
}

bool Field::add_ship(ushort index, ushort _size, Coordinates _coords, DIR _direction) {
    if (correct_pos(_size, _coords, _direction)) {
        flotilla[index] = Ship(&cells[_coords.get_x()][_coords.get_y()], _size, _direction);
        return true;
    }
    else
        return false;
}

STATUS Field::cell_status(Coordinates _coords) const {
    return cell_status(_coords.get_x(), _coords.get_y());
}

STATUS Field::cell_status(uchar x, ushort y) const {
    return cells[x][y]->get_status();
}

DIR Field::ship_dir(Coordinates coords) const {
    return flotilla[find_ship(coords)].get_direction();
}

void Field::shoot_cell(Coordinates _coords, STATUS _status) const {
    shoot_cell(_coords.get_x(), _coords.get_y(), _status);
}

void Field::shoot_cell(uchar x, ushort y, STATUS _status) const {
    cells[x][y]->set_status(_status);
}

bool Field::is_ship_alive(Coordinates _coords) const {
    return flotilla[find_ship(_coords)].is_alive();
}

bool Field::is_ship_alive(uchar x, ushort y) const {
    return is_ship_alive(Coordinates(x, y));
}

bool Field::is_ship_alive(ushort index) const {
    return flotilla[index].is_alive();
}

//потопить корабль
 void Field::sink_ship(Coordinates _coords) {
    flotilla[find_ship(_coords)].sink();
}

void Field::sink_ship(uchar x, ushort y) {
    sink_ship(Coordinates(x, y));
}

std::ostream& operator<< (std::ostream& os, const Field& field) {
    std::cout << "  ";
    for (int i = 0; i < PG_SIZE; ++i)
        std::cout  << i << " ";
    std::cout << std::endl;
    for (char i = 'a'; i < PG_SIZE + 'a'; ++i) {
        std::cout << i << " ";
        for (int j = 0; j < PG_SIZE; ++j)
            std::cout << (char)field.cell_status(Coordinates(i, j)) << " ";
        std::cout << std::endl;
    }

    return os;
}
