/*!
  \file file_handler.h
  \brief Интерфейс класса FileHandler
  \author Alex
  \copyright Copyright (C) 2021
  \version 1.0
  \date 19.09.2021
*/

#ifndef HUOBIGLOBAL_FILE_HANDLER_H
#define HUOBIGLOBAL_FILE_HANDLER_H

#include <fstream>
#include <sstream>
#include "types.h"

/*!
  \class FileHandler file_handler.h
  \brief Класс для работы с файлами
  \author Alex

  Данный класс выполняет всю необходимую
  работу по чтению/записи файла,
  парсингу его содержимого
  Не предполагает копирование/присвоение
*/
class FileHandler {

public:
    /*!
      Конструктор
      \param[in] inFilePath Путь для входного файла
      \param[in] outFilePath Путь для выходного файла
    */
    FileHandler(const std::string &inFilePath, const std::string &outFilePath);

    /// \brief Деструктор класса.
    ~FileHandler();
    /// \brief Удаленный конструктор копирования.
    FileHandler(const FileHandler&) = delete;
    /// \brief Удаленное копирующее присваивание.
    FileHandler& operator=(const FileHandler&) = delete;
    /// \brief Конструктор перемещения.
    FileHandler(FileHandler&&) = default;
    /// \brief Перемещающее присваивание.
    FileHandler& operator=(FileHandler&&) = default;

    /*!
      Чтение одной строки из входного файла
      \param[out] input Структура с параметрами одной
                        биржевой записи
      \return true если запись успешно прочитана из файла,
              false - если конец файла
    */
    bool readData(InputData &input);
    /*!
      Запись одной строки в выходной файл
      \param[in] output Структура с результирующими параметрами
                        по текущему состоянию биржевого стакана
    */
    void writeData(const OutputData &output);

private:
    // поток для чтения из входного файла
    std::ifstream _inpFile;
    // поток для записи в выходной файл
    std::ofstream _outFile;

    // парсинг JSON-стрктуры из строки json входного файла
    // в структуру input
    void _parseJSON(const std::string &json, InputData &input) const;
    // очистка параметров структуры input
    void _clear(InputData &input) const noexcept;
};


#endif //HUOBIGLOBAL_FILE_HANDLER_H
