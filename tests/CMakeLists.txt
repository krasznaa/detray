enable_testing()

add_subdirectory(common)
add_subdirectory(io)

if(DETRAY_UNIT_TESTS)
    add_subdirectory(unit_tests)
endif()

if(DETRAY_BENCHMARKS)
    add_subdirectory(benchmarks)
endif()
