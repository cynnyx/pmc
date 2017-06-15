# ---------------------------------------------------#
# Common Source and Header files
# ---------------------------------------------------#

# Header Files
set(TEST_FILES
    libpmc_test.cpp
    )


# ---------------------------------------------------#
# Targets
# ---------------------------------------------------#


add_executable(pmc_test ${TEST_FILES})
target_include_directories(pmc_test PUBLIC ${DIR_ROOT})
target_link_libraries(pmc_test PRIVATE ${TARGET_PMC})












