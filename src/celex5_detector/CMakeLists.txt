cmake_minimum_required(VERSION 3.0.2)
project(celex5_detector)
set(CMAKE_CXX_STANDARD 11)

# add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
        roscpp
        cv_bridge
        celex5_msgs
        std_msgs
        sensor_msgs
        )
find_package(OpenCV REQUIRED)


catkin_package(
        #  INCLUDE_DIRS include
        #  LIBRARIES celex_ros_tools
        #  CATKIN_DEPENDS roscpp
        #  DEPENDS system_lib
)

include_directories(
        # include
        ${catkin_INCLUDE_DIRS}
)


## Declare a C++ library
# add_library(${PROJECT_NAME}
#   src/${PROJECT_NAME}/celex_ros_tools.cpp
# )
#message(${CMAKE_SOURCE_DIR})
#CMAKE_SOURCE_DIRcatkin_ec_celex5/src文件夹里的那个cmakelist
#set(CeleX ${CMAKE_SOURCE_DIR}/celex5_ros_eventdata/sdk)
#set(CeleX_LIB CeleX)

#include_directories(${CeleX}/include)
#link_directories(${CeleX}/lib/Linux/x64)


include_directories(
        ${CeleX}/include
)
link_directories(
        ${CeleX}/lib/Linux/x64
)

# for clion
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/../devel/include)
#include_directories(${CMAKE_SOURCE_DIR}/celex5_ros_eventdata/sdk/include)
include_directories(${CMAKE_SOURCE_DIR}/celex5_detector/include)
#for clion end

# get data from camera
add_executable(${PROJECT_NAME}
        src/celex5_detector_node.cpp src/celex5_detector.cpp src/cluster_detector.cpp)
#src/celex5_detector_node.cpp)

target_link_libraries(${PROJECT_NAME}
        ${catkin_LIBRARIES}
        ${CeleX_LIB}
        ${OpenCV_LIBRARIES})


# get data from bin file
#add_executable(celex_readBin src/celex_readBin_ros.cpp)
#target_link_libraries(
#        celex_readBin
#        ${catkin_LIBRARIES}
##        ${OpenCV_LIBRARIES}
#        ${CeleX_LIB}
#)

#add_executable(event_vector_show src/celex5_getdata_ros/get_event_vector_show.cpp)
#target_link_libraries(
#        event_vector_show
#        ${catkin_LIBRARIES}
##        ${OpenCV_LIBRARIES}
#)