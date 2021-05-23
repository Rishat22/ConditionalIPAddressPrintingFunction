cmake_minimum_required(VERSION 3.5)

if(DEFINED ENV{GITHUB_RUN_NUMBER})
    project(print_ip VERSION 0.0.$ENV{GITHUB_RUN_NUMBER})
else()
    project(print_ip)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(project_sources
    print_ip.hpp
    main.cpp
    interpreter_to_address.hpp
    )

add_executable(print_ip ${project_sources} )

if (MSVC)
    target_compile_options(print_ip PRIVATE
        /W4
    )
else ()
    target_compile_options(print_ip PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS print_ip RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)
