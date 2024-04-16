cmake_minimum_required(VERSION 3.0.1)
project(ssl-tls-example)

include_directories(${PROJECT_SOURCE_DIR}/openssl/include)
link_directories(${PROJECT_SOURCE_DIR}/openssl/lib)

# https server
add_executable(https_server https_server_example.c)
target_link_libraries(https_server ssl crypto)

# https client
link_directories(${PROJECT_SOURCE_DIR}/openssl/lib)
add_executable(https_client https_client_example.c)
target_link_libraries(https_client ssl crypto)