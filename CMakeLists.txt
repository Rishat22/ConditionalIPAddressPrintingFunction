cmake_minimum_required(VERSION 3.5)

project(ConditionalIPAddressPrintingFunction LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(project_sources
    main.cpp
    interpreter_to_address.hpp
    )

add_executable(ConditionalIPAddressPrintingFunction ${project_sources} )
