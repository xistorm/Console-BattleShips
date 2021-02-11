//
// Created by Lenovo_302 on 07.12.2020.
//

#include "Game.h"

Game::Game() {
    srand(time(nullptr));
    player = Player();
    enemy = Computer();
    int random = rand() % 3 - 1;
    turn = random == 0 ? TURN::player : TURN::enemy;
}

void Game::create_field() {
    for (int i = 0; i <= 3; ++i) {
        for (int j = 0; j <= 3 - i; ++j) {
            display_info();
            enemy.place_ship(i * 3 + j, i + 1);
            player.place_ship(i * 3 + j, i + 1);
            system("cls");
        }
    }
}

void Game::create_field(const std::string& path) {
    std::ifstream in;
    in.open(path);
    if (!in.is_open())
        throw std::invalid_argument("This is incorrect path");
    Coordinates coords;
    ushort dir, index{}, size;
    while(index < 10) {
        in >> size >> coords >> dir;
        player.place_ship(index, size, coords, dir);
        enemy.place_ship(index, size);
        ++index;
    }
    in.close();
}

void Game::do_turn() {
    switch (turn) {
        case TURN::player:
            player.shoot(&enemy);
            turn = TURN::enemy;
            std::cout << "player turn" << std::endl;
            break;
        case TURN::enemy:
            std::cout << "enemy turn: " << std::endl;
            enemy.shoot(&player);
            turn = TURN::player;
            break;
    }
}

void Game::display_info() const {
    player.display_field();
    std::cout << std::string(50, '-') << std::endl;
    player.display_turns();

    enemy.display_field();
    enemy.display_turns();
}

void Game::menu() {
    char option {'3'};
    std::string temp_path;
    while (option != '1' && option != '2') {
        std::cout << "would it be console[1] or file[2] input?" << std::endl;
        std::cin >> option;
    }
    if (option == '2') {
        std::cout << "enter path to file with ships info" << std::endl;
        std::cin >> temp_path;
        path = temp_path;
    }
    else
        path = "none";
    system("cls");
}

bool Game::is_over(TURN& winner) const {
    if (enemy.is_dead()) {
        winner = TURN::player;
        return true;
    }
    else if (player.is_dead()) {
        winner = TURN::enemy;
        return true;
    }
    else
        return false;
}

void Game::play() {
    menu();
    path == "none" ? create_field() : create_field(path);
    std::cout << "fields created" << std::endl;
    TURN winner {};
    do {
        display_info();
        do_turn();
        system("cls");
    } while(!is_over(winner));
    std::cout << "Winner is " << (winner == TURN::player ? "YOU" : "OPPONENT") << std::endl;
    std::cout << "To exit enter any key" << std::endl;
    while (!_kbhit()) {};
}