cmake_minimum_required(VERSION 3.10)

project(SEHH2042_Group_Project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(SMS SEHH2042_Group_Project/SMS.cpp)

# Add this block to handle platform-specific libraries if needed in the future,
# for now the preprocessor directives in the code are sufficient.
if (WIN32)
    # Add Windows-specific libraries here, e.g., target_link_libraries(sms ws2_32)
else()
    # Add Linux/macOS-specific libraries here
endif()
