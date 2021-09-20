/*!
  \file types.h
  \brief Типы данных
  \author Alex
  \copyright Copyright (C) 2021
  \version 1.0
  \date 19.09.2021
*/

#ifndef HUOBIGLOBAL_TYPES_H
#define HUOBIGLOBAL_TYPES_H

#include <string>
#include <ctime>
#include <vector>

/*!
  \defgroup Константы
*/
/// Максимальное количество заявок на продажу в
/// биржевом стакане
const auto MAX_ASKS = 20;
/// Максимальное количество заявок на покупку в
/// биржевом стакане
const auto MAX_BIDS = 20;

/*!
  \enum DataType
  \brief Список значений поля "type" биржевых данных
*/
enum class DataType: unsigned {
    NONE,      ///< нет значения
    SNAPSHOT,  ///< первоначальный снимок стакана
    UPDATE     ///< обновление
};

/*!
  \typedef Level
  \brief Описываетает пару "цена-количество" одной заявки
         на продажу/покупку
         Цена в формате string, так как она определяет
         четкий фиксированный уровень
*/
using Level = std::pair<std::string, double>;

/*!
  \struct InputData
  \brief Описывает одну строку входных данных
*/
struct InputData {
    /// тип входных данных
    DataType dataType;
    /// служебная метка пакета
    std::string symbol;
    /// идентификатор события
    std::time_t event_id;
    /// время события
    std::time_t event_time;
    /// время торговой операции
    std::time_t exchange_time;
    /// номер последовательности
    uint64_t seq_num;
    /// предыдущий номер последовательности
    uint64_t prev_seq_num;
    /// список заявок на продажу
    std::vector<Level> asks;
    /// список заявок на покупку
    std::vector<Level> bids;
};

/*!
  \struct OutputData
  \brief Описывает одну строку выходных данных
*/
struct OutputData {
    /// временная метка события
    std::time_t event_time;
    /// лучшая цена заявки на покупку
    double best_bid_price;
    /// количество валюты по лучшей цене на покупку
    double best_bid_amount;
    /// лучшая цена заявки на продажу
    double best_ask_price;
    /// количество валюты по лучшей цене на продажу
    double best_ask_amount;
};

#endif //HUOBIGLOBAL_TYPES_H
