/*!
  \file calculator.cpp
  \brief Реализация класса Calculator
  \author Alex
*/


#include "calculator.h"
#include <iostream>

Calculator::Calculator(FileHandler &&fh) :_fh(std::move(fh)) {

}


void Calculator::calculate() {

    std::cout << "Идет расчет..." << std::endl;
    InputData input;
    while (_fh.readData(input)) {

        // в зависимости от того, какой пакет получили
        switch (input.dataType) {
            case DataType::SNAPSHOT:
                // снапшот
                _calcSnapshot(input);
                break;
            case DataType::UPDATE:
                // апдейт
                _calcUpdate(input);
                break;
            default:
                throw std::runtime_error(std::string("Неопознаный формат данных!"));
        }
    }
    std::cout << "Расчет завершен" << std::endl;
}

void Calculator::_calcSnapshot(const InputData &input) {
    // формируем текущее состояние стороны заявок на
    // продажу (сортированы по возрастанию)
    for (auto &level : input.asks) {
        // если количество валюты = 0 - отбрасываем запись
        if (level.second == 0)
            continue;

        _asks.insert({level.first, level.second});

        // если при вставке новой записи выясняется, что
        // количество записей на стороне заявок на продажу
        // превысило MAX_ASKS - удаляем наибольшую запись
        // так как нас интересуют только наименьшие записи
        if (_asks.size() > MAX_ASKS) {
            _asks.erase(--_asks.end());
        }
    }

    // формируем текущее состояние стороны заявок на
    // покупку (сортированы по возрастанию)
    for (auto &level : input.bids) {
        if (level.second == 0)
            continue;

        _bids.insert({level.first, level.second});

        // если превысило MAX_BIDS, то удаляем наименьшую запись
        // здесь нас интересуют только наибольшие записи
        if (_bids.size() > 20) {
            _bids.erase(_bids.begin());
        }
    }
}

void Calculator::update(const InputData &input) {
    // применяем полученную запись
    // так как нам точно известно, что все данные в обновлении
    // есть в снэпшоте, то не будем проверять на границы
    for (auto &level : input.asks) {
        // если количество валюты = 0 - отбрасываем запись
        if (level.second == 0)
            continue;
        _asks[level.first] = level.second;
    }

    // формируем текущее состояние стороны заявок на
    // покупку (сортированы по возрастанию)
    for (auto &level : input.bids) {
        if (level.second == 0)
            continue;
        _bids[level.first] = level.second;
    }
}

void Calculator::_calcUpdate(const InputData &input) {
    update(input);

    Level min_ask, max_bid;
    // результирующее значение для заявок на продажу -
    // пара "цена-количество" с наименьшим значением цены
    if (!_asks.empty()) {
        min_ask = *_asks.begin();
    }
    else {
        // = 0, если заявок нет
        min_ask = {"0", 0};
    }

    // результирующее значение для заявок на покупку -
    // пара "цена-количество" с наибольшим значением цены
    if (!_bids.empty()) {
        max_bid = *_bids.rbegin();
    }
    else {
        max_bid = {"0", 0};
    }

    // выводим результирующие значения в файл
    _fh.writeData({input.event_time, std::stof(min_ask.first),
                   min_ask.second, std::stof(max_bid.first), max_bid.second});
}