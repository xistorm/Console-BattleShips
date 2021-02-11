//
// Created by Lenovo_302 on 04.12.2020.
//

#ifndef COURSEWORK__TEST__CONFIGURATION_H
#define COURSEWORK__TEST__CONFIGURATION_H

#pragma once

#define ushort unsigned short
#define uchar unsigned char

#include <regex>
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <conio.h>
#include <cstdlib>
#include <vector>
#include <unordered_map>
#include <windows.h>
#include <ctime>
#include <algorithm>
#include <random>

enum class TURN            {player = '0', enemy = '1'};
enum class STATUS          {miss = '0', nothing = ' ', killed = 'x', damaged = '+', ship = '|'};
//TODO: попробовать сделать Coordination + DIR
enum class DIR             {up = 0, down, right, left, unknown};
const ushort PG_SIZE       = 10;
const ushort FLOTILLA_SIZE = 10;

static void write_at(short x, short y, std::string output) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cPos {x, y};
    SetConsoleCursorPosition(hConsole, cPos);
    std::cout << output;
}

#endif //COURSEWORK__TEST__CONFIGURATION_H