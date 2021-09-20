# HuobiGlobal

## [Содержание](#Содержание)

* [**Описание**](#Описание)
* [**Конфигурирование**](#Конфигурирование)
* [**Сборка проекта**](#Сборка-проекта)
* [**Авторы**](#Авторы)

## [Описание](#Описание)

  HuobiGlobal - утилита, позволяющая отслеживать состояние биржевого стакана
  с заявками на продажу и покупку какого-либо актива.
  Утилита получает на вход файл, в котором содержатся биржевые сообщения в формате JSON -
  полный снепшот стакана и набор апдейтов этого стакана с временными метками.
  Утилита восстанавливает снепшоты стаканов на каждый апдейт.
  В выходной файл выводятся цены и объемы лучших уровней заявок на продажу и
  покупку с временной меткой.
  Утилита написана и тестировалась под ОС Centos 8
  
## [Конфигурирование проекта](#Конфигурирование-проекта)
  
  Перед сборкой необходимо установить директории для входного и выходного файлов 
  в главном файле CMakeLists.txt проекта:
  <pre>
  set(INPUT_FILE "\"huobi_global_depth.log\"")
  set(OUTPUT_FILE "\"qwerty.txt\"")
  </pre> 
  В данном примере входной и выходной файлы расположены в
  одной директории с исполняемым файлом, но можно указать и абсолютные
  пути
  
## [Сборка проекта](#Сборка-проекта)
  
  Для сборки, в директории с исходным кодом программы, необходимо выполнить следующие действия
  (для cmake > 3.14):
  <pre>
  ./app_build
  </pre> 
  
  После этого в директории bin/ появятся исполняемые файлы
  HuobiGlobal и huobi_benchmark
  
  
## [Авторы](#Авторы)
  <pre>
  Copyright &copy; 2021
  Алексей Кузнецов &lt;amok777@mail.ru&gt;
  </pre>