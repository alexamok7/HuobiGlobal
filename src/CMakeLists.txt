add_executable(${PROJECT_NAME}
        main.cpp
        file_handler/file_handler.cpp
        file_handler/file_handler.h
        types.h calculator/calculator.cpp calculator/calculator.h)

include_directories(${PROJECT_SOURCE_DIR}/src ${PROJECT_BINARY_DIR}/src
        ${PROJECT_BINARY_DIR}/third_party ${PROJECT_SOURCE_DIR}/third_party)