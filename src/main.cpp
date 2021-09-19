/*!
  \mainpage Документация утилиты HuobiGlobal
  \section intro Описание
  HuobiGlobal - утилита, позволяющая отслеживать состояние биржевого стакана
  с заявками на продажу и покупку какого либо актива.
  Утилита получает на вход файл, в котором содержатся биржевые сообщения в формате JSON -
  полный снепшот стакана и набор апдейтов этого стакана с временными метками.
  Утилита восстанавливает снепшоты стаканов на каждый апдейт.
  В выходной файл выводятся цены и объемы лучших уровней заявок на продажу и
  покупку с временной меткой
  \file main.cpp
  \brief Главная функция HuobiGlobal
  \copyright Copyright (C) 2021
  \author Alex
  \version 1.0.0
  \date 19.09.2021
*/
#include <iostream>
#include "calculator/calculator.h"
#include "config.h"

int main() {

    try {
        // создаем класс для расчета, перемещая в него класс-обработчик файлов
        Calculator calc({INPUT_FILE, OUTPUT_FILE});
        // расчитываем результирующие параметры
        calc.calculate();
    }
    catch(const std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}