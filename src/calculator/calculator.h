/*!
  \file calculator.h
  \brief Интерфейс класса Calculator
  \author Alex
  \copyright Copyright (C) 2021
  \version 1.0
  \date 19.09.2021
*/

#ifndef HUOBIGLOBAL_CALCULATOR_H
#define HUOBIGLOBAL_CALCULATOR_H

#include "file_handler/file_handler.h"
#include <set>

/*!
  \class Calculator calculator.h
  \brief Класс для расчета
  \author Alex

  Данный класс расчитывает текущее состояние биржевого
  стакана и результирующие данные по этому состоянию.
  Расчет производится на основе одной записи
  биржевых данных, полученных из выходного файла.
  Результирующие данные выводятся в выходной файл.
  Не предусматривает копирования и перемещения
*/
class Calculator {
public:
    /*!
      Конструктор
      \param[in] FileHandler Объект класса-обработчика
                             файлов FileHandler
    */
    explicit Calculator(FileHandler &&fh);

    /// \brief Удаленный конструктор копирования.
    Calculator(const Calculator&) = delete;
    /// \brief Удаленное копирующее присваивание.
    Calculator& operator=(const Calculator&) = delete;
    /// \brief Удаленный конструктор перемещения.
    Calculator(Calculator&&) = delete;
    /// \brief Удаленное перемещающее присваивание.
    Calculator& operator=(Calculator&&) = delete;

    /*!
      Расчет состояния биржевого стакана
    */
    void calculate();

    /*!
      Одно обновление данных и вывод результирующих показателей
      (для бенчмарка)
    */
    void calculateForBenchmark();

private:
    // объект для чтения/записи файлов (перемещенный)
    FileHandler _fh;
    // текущее состояние биржевого стакана -
    // сторона заявок на продажу (не более MAX_ASKS)
    // одна запись в стакане - пара "цена-количество"
    std::set<Level> _asks;
    // текущее состояние биржевого стакана -
    // сторона заявок на продажу (не более MAX_BIDS)
    std::set<Level> _bids;

    // расчет состояния стакана после получения снапшота input
    void _calcSnapshot(const InputData &input);
    // расчет состояния стакана после получения апдейта input
    void _calcUpdate(const InputData &input);
};


#endif //HUOBIGLOBAL_CALCULATOR_H
