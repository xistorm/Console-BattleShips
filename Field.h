//
// Created by Lenovo_302 on 03.12.2020.
//

#ifndef COURSEWORK__TEST__FIELD_H
#define COURSEWORK__TEST__FIELD_H

#include "Configuration.h"
#include "Cell.h"
#include "Ship.h"

class Field {
protected:
    //данные
    Cell* cells[PG_SIZE][PG_SIZE];
    Ship flotilla[FLOTILLA_SIZE];

    //по координатам определить индекс корабля, лежащего в этой точке
    ushort find_ship(Coordinates) const;
    bool correct_coords(Coordinates) const;
    bool correct_pos(ushort, Coordinates, DIR) const;
public:
    //конструкторы
    Field();

    static ushort normalize_coord(int);

    //поставить корабль
    bool add_ship(ushort, ushort, Coordinates, DIR);

    //статус отдельной клетки
    STATUS cell_status(Coordinates) const;
    STATUS cell_status(uchar, ushort) const;

    DIR ship_dir(Coordinates) const;

    //выстрелили в клетку
    void shoot_cell(Coordinates, STATUS) const;
    void shoot_cell(uchar, ushort, STATUS) const;

    //есть ли ненадамаженные клетки
    bool is_ship_alive(Coordinates) const;
    bool is_ship_alive(uchar, ushort) const;
    bool is_ship_alive(ushort) const;

    //потопить корабль
    void sink_ship(Coordinates);
    void sink_ship(uchar, ushort);

    //операторы
    friend std::ostream& operator<< (std::ostream&, const Field&);
};

#endif //COURSEWORK__TEST__FIELD_H
