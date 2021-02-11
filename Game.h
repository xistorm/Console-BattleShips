//
// Created by Lenovo_302 on 07.12.2020.
//

#ifndef COURSEWORK_GAME_H
#define COURSEWORK_GAME_H

#include "Configuration.h"
#include "Player.h"
#include "Computer.h"

class Game {
protected:
    Player player;
    Computer enemy;
    TURN turn;
    std::string path {"none"};

    //TODO: добавить в меню настройки (игрок вс ИИ или вс игрок), файловый или консольный ввод
    void menu();
    bool is_over(TURN&) const;
public:
    Game();

    void create_field();
    void create_field(const std::string&);
    void do_turn();
    void display_info() const;
    void play();
};

#endif //COURSEWORK_GAME_H
