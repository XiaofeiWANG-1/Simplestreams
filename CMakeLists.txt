cmake_minimum_required(VERSION 3.14)
project(UbuntuImageTool)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(nlohmann_json REQUIRED)
find_package(CURL REQUIRED)

set(SOURCES
    main.cpp
    SimplestreamsImageFetcher.cpp
)

add_executable(ubuntu_tool ${SOURCES})

target_include_directories(ubuntu_tool
    PRIVATE
    ${CURL_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}
)

target_link_libraries(ubuntu_tool
    PRIVATE
    nlohmann_json::nlohmann_json
    ${CURL_LIBRARIES}
)

if (WIN32)
    target_link_libraries(ubuntu_tool PRIVATE ws2_32 wldap32)
endif()

if(APPLE)
    message(STATUS "Configuring for macOS")

    find_library(SECURITY_FRAMEWORK Security)
    find_library(COREFOUNDATION_FRAMEWORK CoreFoundation)

    if(SECURITY_FRAMEWORK AND COREFOUNDATION_FRAMEWORK)
        target_link_libraries(ubuntu_tool PRIVATE
            ${SECURITY_FRAMEWORK}
            ${COREFOUNDATION_FRAMEWORK}
        )
    endif()

    target_compile_options(ubuntu_tool PRIVATE "-Wno-deprecated-declarations")
endif()



