//
// Created by Lenovo_302 on 04.12.2020.
//

#include "Player.h"

Player::Player() {
    field = Field();
}

std::string Player::get_shoot_status(int value) {
    switch (value) {
        case 1:
            return std::string("miss");
        case 2:
            return std::string("kill");
        case -1:
            return std::string("hit");
        default:
            return "";
    }
}

void Player::place_ship(ushort index, ushort _size, Coordinates _coords, ushort _direction) {
    if (field.add_ship(index, _size, _coords, DIR(_direction)))
        return;

    std::cout << "Your ship " << index << " have incorrect position. Change it and run game again" << std::endl;
    std::cout << "Press any key to exit" << std::endl;
    while (!_kbhit()) {};
    exit(0);
}

void Player::place_ship(ushort index, ushort _size) {
    Coordinates _coords;
    ushort _direction;
    while (true) {
        std::cout << "coords of " << index + 1 << " ship (of size " << _size << "): " << std::endl;
        std::cin >> _coords;
        std::cout << "dir of " << index + 1 << " ship (of size " << _size << "): ";
        std::cout << "for up stands " << (int)DIR::up << ", for down - " << (int)DIR::down << ", for right - " << (int)DIR::right << ", for left - " << (int)DIR::left << std::endl;
        std::cin >> _direction;
        if (field.add_ship(index, _size, _coords, DIR(_direction)))
            break;
        else
            std::cout << "It's incorrect position, try again." << std::endl;
    }
}

//возвращает 0 если некорректная клетка, 1 - мимо, -1 - попал, 2 - убил
int Player::shoot(Coordinates _coords) {
    switch (field.cell_status(_coords)) {
        case STATUS::miss:
        case STATUS::killed:
        case STATUS::damaged:
            //std::cout << "This cell has been shooted already" << std::endl;
            return 0;
        case STATUS::nothing:
            field.shoot_cell(_coords, STATUS::miss);
            return 1;
        case STATUS::ship:
            field.shoot_cell(_coords, STATUS::damaged);
            if (!field.is_ship_alive(_coords)) {
                field.sink_ship(_coords);
                return 2;
            }
            return -1;
    }
}

void Player::shoot(Player* enemy) {
    Coordinates _coords;
    int res;
    std::string turn_status;

    do {
        std::cout << "where to shoot" << std::endl;
        std::cin >> _coords;
    } while (!Coordinates::is_correct(_coords) || (res = enemy->shoot(_coords)) == 0);

    turns.emplace_back(_coords, get_shoot_status(res));
}

void Player::display_turns() const {
    ushort index {};
    std::for_each(turns.begin(), turns.end(), [&index](const auto& turn){
       std::cout << ++index << " turn: " << turn.first.to_string() << " - " << turn.second << std::endl;
    });
}

void Player::display_field() const {
    std::cout << "  ";
    for (int i = 0; i < PG_SIZE; ++i)
        std::cout  << i << " ";
    std::cout << std::endl;
    for (char i = 'a'; i < PG_SIZE + 'a'; ++i) {
        std::cout << i << " ";
        for (int j = 0; j < PG_SIZE; ++j) {
            //TODO: если в консоле, то лучше бы запихнуть эту проверку в класс STATUS/Field/Ship
            DIR temp = field.ship_dir(Coordinates(i, j));
            if (field.cell_status(Coordinates(i, j)) == STATUS::ship && (temp == DIR::left || temp == DIR::right))
                std::cout << "- ";
            else
                std::cout << (char) field.cell_status(Coordinates(i, j)) << " ";
        }
        std::cout << " | " << std::endl;
    }
}

bool Player::is_dead() const {
    for(int i = 0; i < 10; ++i)
        if (field.is_ship_alive(i))
            return false;
    return true;
}