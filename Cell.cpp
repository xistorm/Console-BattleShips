//
// Created by Lenovo_302 on 03.12.2020.
//

#include "Cell.h"

//-------------------------------------Coordinates---------------------------------------
bool Coordinates::is_correct(uchar _x, ushort _y) {
    _x += _x < 10 ? 'a' : 0;
    return std::regex_match(std::string(1, toupper(_x)) + std::to_string(_y), std::regex("[A-Z][0-9]|[0-9][0-9]"));
}
bool Coordinates::is_correct(const Coordinates& _coords) {
    return is_correct(_coords.get_x(), _coords.get_y());
}

//конструкторы
Coordinates::Coordinates() = default;
Coordinates::Coordinates(uchar _x, ushort _y) {
    set_x(_x);
    set_y(_y);
}

//геттеры и сеттеры
void Coordinates::set_x(uchar _x) {
    if (is_correct(_x, 0))
        if (isalpha(_x))
            x = toupper(_x) - 'A';
        else
            x = _x;
    else
        throw std::invalid_argument("Something went wrong");
}

ushort Coordinates::get_x() const {
    return x;
}

void Coordinates::set_y(ushort _y) {
    if (is_correct('0', _y))
        y = _y;
    else
        throw std::invalid_argument("Something went wrong");
}

ushort Coordinates::get_y() const {
    return y;
}

std::string Coordinates::to_string() const {
    return std::string(1, x + 'A') + std::to_string(y);
}

//операторы
bool operator== (const Coordinates& coords1, const Coordinates& coords2) {
    return coords1.x == coords2.x && coords1.y == coords2.y;
}

std::istream& operator>> (std::istream& in, Coordinates& _coords) {
    char x {'n'};
    ushort y {10};
    while (!Coordinates::is_correct(x, y))
        in >> x >> y;
    _coords.set_x(x);
    _coords.set_y(y);

    return in;
}

std::ostream& operator<< (std::ostream& os, Coordinates& _coords) {
    os << char(_coords.get_x() + 'A') << _coords.get_y();

    return os;
}

//----------------------------------------Cell-------------------------------------------
//конструкторы
Cell::Cell() = default;
Cell::Cell(STATUS _status) : Coordinates(), status(_status) {}
Cell::Cell(Coordinates _coords, STATUS _status) : Cell(_coords.get_x(), _coords.get_y(), _status) {}
Cell::Cell(uchar _x, ushort _y, STATUS _status) : Coordinates(_x, _y), status(_status) {}

//геттеры и сеттеры
void Cell::set_status(STATUS _status) {
    status = _status;
}

STATUS Cell::get_status() const {
    return status;
}