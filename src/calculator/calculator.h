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
#include <map>

/*!
  \class Calculator calculator.h
  \brief Класс для расчета
  \author Alex

  Данный класс расчитывает текущее состояние биржевого
  стакана и результирующие данные по этому состоянию.
  Расчет производится на основе одной записи
  биржевых данных, полученных из выходного файла.
  Результирующие данные выводятся в выходной файл.
  Не предусматривает перемещения
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
    Calculator(Calculator&&) = default;
    /// \brief Удаленное перемещающее присваивание.
    Calculator& operator=(Calculator&&) = default;
    /// \brief Дефолтный конструктор.
    Calculator() = default;

    /*!
      Расчет состояния биржевого стакана
    */
    void calculate();

    /*!
      Расчет снэпшота и вектора апдейтов (для бенчмарка)
      \param[out] input Вектор с апдейтами для бенчмарка
    */
    void calcSnapshotBench(std::vector<InputData> &vec);

    /*!
     Применение апдейта и получение результирующих значений 
     (в т.ч и для бенчмарка)
     \param[in] input Структура с входными параметрами одной
                        биржевой записи
     \return Структура с результирующими значениями
    */
    OutputData _doUpdate(const InputData &input);

private:
    // объект для чтения/записи файлов (перемещенный)
    FileHandler _fh;
    // текущее состояние биржевого стакана -
    // сторона заявок на продажу (не более MAX_ASKS)
    // ключ - цена (в формате string, потому что double опасно
    // из за точности представления IEEE)
    // значение - количество
    std::map<std::string, double> _asks;
    // текущее состояние биржевого стакана -
    // сторона заявок на продажу (не более MAX_BIDS)
    std::map<std::string, double> _bids;

    // расчет состояния стакана после получения снапшота input
    void _calcSnapshot(const InputData &input);
    // расчет состояния стакана после получения апдейта input
    void _calcUpdate(const InputData &input);
};


#endif //HUOBIGLOBAL_CALCULATOR_H
