add_subdirectory(Vector)

file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} cxxopts httplib matplot Vector OpenSSL::SSL OpenSSL::Crypto nlohmann_json::nlohmann_json)
