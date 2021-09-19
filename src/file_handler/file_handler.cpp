/*!
  \file file_handler.cpp
  \brief Реализация класса FileHandler
  \author Alex
*/

#include "file_handler.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/optional/optional.hpp>


#include <iostream>


FileHandler::FileHandler(const std::string &inFilePath, const std::string &outFilePath) {

    // открываем входной файл
    _inpFile.open(inFilePath);
    if (!_inpFile.is_open()) {
        throw std::runtime_error(std::string("Ошибка открытия входного файла! ")
              + strerror(errno));
    }

    // создаем выходной файл
    _outFile.open(outFilePath);
    if (!_outFile.is_open()) {
        throw std::runtime_error(std::string("Ошибка создания выходного файла! ")
              + strerror(errno));
    }


//    catch (const std::ofstream::failure &e) {
//        throw std::runtime_error(std::string("Ошибка создания выходного файла: ")
//                                 + e.what());
//    }
}

FileHandler::~FileHandler() {
    _inpFile.close();
    _outFile.close();
}

bool FileHandler::readData(InputData &input) {

    if (_inpFile.is_open()) {
        std::string str;
        // вычитываем одну строку из файла
        if (getline (_inpFile, str)) {

            // вычленяем из строки JSON структуру
            // начинающуюся с символа '{'
            std::size_t found = str.find('{');
            if (found != std::string::npos) {
                str = str.substr(found);
            }
            else {
                throw std::runtime_error(std::string("Не удалось найти JSON-структуру!"));
            }

            // парсим JSON структуру
            try {
                _parseJSON(str, input);
            }
            catch (const std::exception &e) {
                throw std::runtime_error(std::string("Ошибка парсинга JSON: ")
                                         + e.what());
            }
            return true;
        }
        else
            return false;
    }
    else {
        throw std::runtime_error(std::string("Входной файл не валиден!"));
    }
}

void FileHandler::writeData(const OutputData &output) {
    if (_outFile.is_open()) {
        // вывести результирующие параметры во входной файл
        _outFile << output.event_time << " ";
        _outFile << std::fixed;
        _outFile << std::setprecision(2) << output.best_bid_price << " ";
        _outFile << std::setprecision(6) << output.best_bid_amount << " ";
        _outFile << std::setprecision(2) << output.best_ask_price << " ";
        _outFile << std::setprecision(6) << output.best_ask_amount << " ";
        _outFile << std::endl;
    }
    else {
        throw std::runtime_error(std::string("Выходной файл не валиден!"));
    }
}

void FileHandler::_clear(InputData &input) const noexcept {
    input.dataType = DataType::NONE;
    input.symbol.clear();
    input.event_id = 0;
    input.event_time = 0;
    input.exchange_time = 0;
    input.seq_num = 0;
    input.prev_seq_num = 0;
    input.asks.clear();
    input.bids.clear();
}

void FileHandler::_parseJSON(const std::string &json, InputData &input) const {
    // используем класс property_tree из boost
    namespace pt = boost::property_tree;
    pt::ptree root;
    std::stringstream ss;

    // парсим
    ss << json;
    pt::read_json(ss, root);

    // зануляем
    _clear(input);

    // вычитываем тип пакета (если он есть)
    boost::optional<std::string> opt_str;
    opt_str = root.get_optional<std::string>("type");
    if (*opt_str == "snapshot") {
        input.dataType = DataType::SNAPSHOT;
    }
    else if (*opt_str == "update") {
        input.dataType = DataType::UPDATE;
    }
    else {
        input.dataType = DataType::NONE;
    }

    // вычитываем метку пакета
    opt_str = root.get_optional<std::string>("symbol");
    if (opt_str) {
        input.symbol = *opt_str;
    }

    // вычитываем идентификатор события
    boost::optional<std::time_t> opt_time;
    opt_time = root.get_optional<std::time_t>("event_id");
    if (opt_time) {
        input.event_id = *opt_time;
    }

    // вычитываем временную метку события
    opt_time = root.get_optional<std::time_t>("event_time");
    if (opt_time) {
        input.event_time = *opt_time;
    }

    // вычитываем временную метку торговой операции
    opt_time = root.get_optional<std::time_t>("exchange_time");
    if (opt_time) {
        input.exchange_time = *opt_time;
    }

    // вычитываем номер последовательности
    boost::optional<std::time_t> opt_int;
    opt_int = root.get_optional<uint64_t>("seq_num");
    if (opt_int) {
        input.seq_num = *opt_int;
    }

    // вычитываем предыдущий номер последовательности
    opt_int = root.get_optional<uint64_t>("prev_seq_num");
    if (opt_int) {
        input.prev_seq_num = *opt_int;
    }

    // вычитываем массив заявок на продажу
    std::vector<double> levels;
    for (auto &elem : root.get_child("asks")) {
        for (auto &item : elem.second) {
            levels.push_back(std::stof(item.second.data()));
        }
        // в массиве levels первый элемент - цена
        // второй элемент - количество
        Level level(levels[0], levels[1]);
        input.asks.push_back(level);
        levels.clear();
    }

    // вычитываем массив заявок на покупку
    for (auto &elem : root.get_child("bids")) {
        for (auto &item : elem.second) {
            levels.push_back(std::stof(item.second.data()));
        }
        Level level(levels[0], levels[1]);
        input.bids.push_back(level);
        levels.clear();
    }
}
