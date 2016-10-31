file(GLOB tst_SOURCES "test_*.cpp")
file(GLOB tst_HEADERS "${HEADERS_DIR}/*.hpp")

include_directories(${HEADERS_DIR})
add_definitions(-Dprivate=public)

foreach(src ${tst_SOURCES})
  get_filename_component(bin_name ${src} NAME_WE)
  add_executable(${bin_name} ${src})
  qt5_use_modules(${bin_name} Core Test Widgets)
  target_link_libraries(${bin_name} dirtyPDFCore)
  add_test(${bin_name} ${bin_name})

  # Autorun
  add_custom_command(TARGET ${bin_name} POST_BUILD
    COMMAND ${bin_name}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Running ${bin_name}" VERBATIM)
endforeach()
