//
// Created by Lenovo_302 on 07.12.2020.
//

#include "Computer.h"

Computer::Computer() : Player() {
    srand(time(nullptr));
    shooting_direction = DIR::unknown;
    choose_direction = 0;
}

void Computer::place_ship(ushort index, ushort _size) {
    Coordinates _coords;
    DIR _direction;
    while (true) {
        _coords.set_x(rand() % 10 + 'a');
        _coords.set_y(rand() % 10);
        if (field.add_ship(index, _size, _coords, DIR::up))
            return;
        else if (field.add_ship(index, _size, _coords, DIR::down))
            return;
        else if (field.add_ship(index, _size, _coords, DIR::left))
            return;
        else if (field.add_ship(index, _size, _coords, DIR::right))
            return;
    }
}

void Computer::reset_shooting() {
    shooted_cells.clear();
    shooting_direction = DIR::unknown;
    choose_direction = 0;
}

void Computer::shoot(Player* enemy) {
    int shooted = 0;
    Coordinates temp_coord;

    //пока не будет корректная клетка
    do {
        Sleep(1000);
        if (shooted_cells.empty()) { //если ещё не попал в корабль
            temp_coord = Coordinates(rand() % 10 + 'a', rand() % 10);
            shooted = enemy->shoot(temp_coord);
            if (shooted == -1)
                shooted_cells.push_back(temp_coord);
        } else { //если попал
            try { //если вдруг вышли за пределы поля
                switch (shooting_direction) { //то слудем по направлению корабля
                    case DIR::unknown: {
                        std::cout << choose_direction << std::endl;
                            switch (choose_direction) {
                                case 0:
                                    temp_coord = Coordinates(shooted_cells.back().get_x() - 1,
                                                             shooted_cells.back().get_y());
                                    shooted = enemy->shoot(temp_coord);
                                    if (shooted == -1)
                                        shooting_direction = DIR::up;
                                    break;
                                case 1:
                                    temp_coord = Coordinates(shooted_cells.back().get_x() + 1,
                                                             shooted_cells.back().get_y());
                                    shooted = enemy->shoot(temp_coord);
                                    if (shooted == -1)
                                        shooting_direction = DIR::down;
                                    break;
                                case 2:
                                    temp_coord = Coordinates(shooted_cells.back().get_x(),
                                                             shooted_cells.back().get_y() + 1);
                                    shooted = enemy->shoot(temp_coord);
                                    if (shooted == -1)
                                        shooting_direction = DIR::right;
                                    break;
                                case 3:
                                    temp_coord = Coordinates(shooted_cells.back().get_x(),
                                                             shooted_cells.back().get_y() - 1);
                                    shooted = enemy->shoot(temp_coord);
                                    if (shooted == -1)
                                        shooting_direction = DIR::left;
                                    break;
                                default:
                                    shooted = 0;
                                    break;
                            }
                        ++choose_direction;
                        break;
                    }
                    case DIR::up:
                        temp_coord = shooted_cells.back();
                        temp_coord.set_x(temp_coord.get_x() - 1);
                        shooted = enemy->shoot(temp_coord);
                        shooted_cells.push_back(temp_coord);
                        break;
                    case DIR::down:
                        temp_coord = shooted_cells.back();
                        temp_coord.set_x(temp_coord.get_x() + 1);
                        shooted = enemy->shoot(temp_coord);
                        shooted_cells.push_back(temp_coord);
                        break;
                    case DIR::right:
                        temp_coord = shooted_cells.back();
                        temp_coord.set_y(temp_coord.get_y() + 1);
                        shooted = enemy->shoot(temp_coord);
                        shooted_cells.push_back(temp_coord);
                        break;
                    case DIR::left:
                        temp_coord = shooted_cells.back();
                        temp_coord.set_y(temp_coord.get_y() - 1);
                        shooted = enemy->shoot(temp_coord);
                        shooted_cells.push_back(temp_coord);
                        break;
                    default:
                        break;
                }
            }
            catch (...) {
                ++choose_direction;
                shooted = 0;
            }
            //если начали убивать корабль с середины
            if (shooted == 1 && shooted_cells.size() > 1) {
                std::reverse(shooted_cells.begin(), shooted_cells.end());

                switch (shooting_direction) {
                    case DIR::up:
                        shooting_direction = DIR::down;
                        break;
                    case DIR::down:
                        shooting_direction = DIR::up;
                        break;
                    case DIR::right:
                        shooting_direction = DIR::left;
                        break;
                    case DIR::left:
                        shooting_direction = DIR::right;
                        break;
                    case DIR::unknown:
                    default:
                        break;
                }
            }
        }
    } while (shooted == 0);
    turns.emplace_back(temp_coord, get_shoot_status(shooted));
    if (shooted == 2)
        reset_shooting();
}

void Computer::display_turns() const {
    short index {1};

    std::for_each(turns.begin(), turns.end(), [&index](const auto& turn) {
        std::string output = std::string(std::to_string(index) + " turn: " + turn.first.to_string() + " - " + turn.second);
        write_at((PG_SIZE + 3) * 2, PG_SIZE + index + 1, output);
        ++index;
    });

    std::cout << std::endl;
}

void Computer::display_field() const {

    for (int i = 0; i < PG_SIZE; ++i) {
        write_at((PG_SIZE + 3 + i) * 2 + 2, 0, (std::to_string(i) + " "));
    }
    for (char i = 'a'; i < PG_SIZE + 'a'; ++i) {
        write_at((PG_SIZE + 3) * 2, i - 'a' + 1, (std::string(1, i) + " "));
        for (int j = 0; j < PG_SIZE; ++j)
            //write_at((PG_SIZE + 4 + j) * 2, i - 'a' + 1, (std::string(1, (char)field.cell_status(Coordinates(i, j)))));
            field.cell_status(Coordinates(i, j)) == STATUS::ship ?
            write_at((PG_SIZE + 4 + j) * 2, i - 'a' + 1, (std::string(1, (char)STATUS::nothing) + " ")) :
            write_at((PG_SIZE + 4 + j) * 2, i - 'a' + 1, (std::string(1, (char) field.cell_status(Coordinates(i, j)))) + " ");
    }

    std::cout << std::endl;
}

