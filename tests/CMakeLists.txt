file(GLOB_RECURSE TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.c")

foreach(TEST_SOURCE ${TEST_SOURCES})
    get_filename_component(name ${TEST_SOURCE} NAME_WE)
    add_executable(${name} ${TEST_SOURCE})
    target_link_libraries(${name} PRIVATE ${PROJECT_NAME})
    add_test(NAME ${name} COMMAND ${name})
endforeach()