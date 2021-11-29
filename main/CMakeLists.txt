project(main)

file(GLOB SRC */*.cpp)

add_executable(main ${SRC})

target_link_libraries(main Eigen3::Eigen)
target_link_libraries(main ${VTK_LIBRARIES})
vtk_module_autoinit(
    TARGETS main
    MODULES ${VTK_LIBRARIES}
)

