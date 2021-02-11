//
// Created by Lenovo_302 on 03.12.2020.
//

#ifndef COURSEWORK__TEST__CELL_H
#define COURSEWORK__TEST__CELL_H

#include "Configuration.h"


class Coordinates {
protected:
    //данные
    ushort y {}, x {};

    //проверка
    static bool is_correct(uchar, ushort);
public:
    //конструкторы
    Coordinates();
    Coordinates(uchar, ushort);

    //проверка
    static bool is_correct(const Coordinates&);

    //геттеры и сеттеры
    void set_x(uchar);
    ushort get_x() const;

    void set_y(ushort);
    ushort get_y() const;

    std::string to_string() const;

    //операторы
    friend bool operator==(const Coordinates&, const Coordinates&);
    friend std::istream& operator>> (std::istream& in, Coordinates&);
    friend std::ostream& operator<< (std::ostream&, Coordinates&);
    //friend Coordinates& operator+ (const Coordinates&, const DIR&);
};

class Cell : public Coordinates {
protected:
    //данные
    STATUS status {STATUS::nothing};
public:
    //конструкторы
    Cell();
    Cell(STATUS);
    Cell(Coordinates, STATUS);
    Cell(uchar, ushort, STATUS);

    //геттеры и сеттеры
    void set_status(STATUS);
    STATUS get_status() const;
};

#endif //COURSEWORK__TEST__CELL_H
