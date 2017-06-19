# ---------------------------------------------------#
# Common Source and Header files
# ---------------------------------------------------#


# Header Files
set(H_FILES
    ${DIR_ROOT}/pmc.h
    )

# Source Files

set(IO_SRC
    ${DIR_ROOT}/pmc_graph.cpp
    ${DIR_ROOT}/pmc_utils.cpp
    ${DIR_ROOT}/pmc_clique_utils.cpp
)

set(PMC_SRC
    ${DIR_ROOT}/pmc_heu.cpp
    ${DIR_ROOT}/pmc_maxclique.cpp
    ${DIR_ROOT}/pmcx_maxclique.cpp
    ${DIR_ROOT}/pmcx_maxclique_basic.cpp
)

set(BOUND_LIB_SRC
    ${DIR_ROOT}/pmc_cores.cpp
)

set(PMC_LIB_SRC
        ${IO_SRC}
        ${PMC_SRC}
        ${BOUND_LIB_SRC}
        ${H_FILES}
        ${DIR_ROOT}/PMC.cpp
)

set(PMC_MAIN
    ${DIR_ROOT}/pmc_driver.cpp
)

set(PMC_LIB
    ${DIR_ROOT}/pmc_lib.cpp
)


# ---------------------------------------------------#
# Targets
# ---------------------------------------------------#


add_library(OBJ_PMC OBJECT ${PMC_LIB_SRC})

add_library(${TARGET_PMC} SHARED ${PMC_LIB} $<TARGET_OBJECTS:OBJ_PMC>)
target_include_directories(${TARGET_PMC} PUBLIC ${DIR_ROOT})

add_executable(runPmc ${PMC_MAIN} $<TARGET_OBJECTS:OBJ_PMC>)
target_include_directories(runPmc PUBLIC ${DIR_ROOT})
target_link_libraries(runPmc LINK_PUBLIC ${TARGET_PMC})

if(${PYTHON} STREQUAL "ON")

    # Scan all directories for PY inclusions.
    macro(HEADER_DIRECTORIES return_list)
        file(GLOB_RECURSE new_list *.h)
        set(dir_list "")

        foreach(file_path ${new_list})
            get_filename_component(dir_path ${file_path} PATH)
            set(dir_list ${dir_list} ${dir_path})
        endforeach()

        list(REMOVE_DUPLICATES dir_list)

        set(tmp_list "")
        foreach(dir_path ${dir_list})
            set(tmp_list "${tmp_list} -I${dir_path}")
        endforeach()
        set(${return_list} ${tmp_list})
        message(${return_list})
    ENDMACRO()


    HEADER_DIRECTORIES(py_inclusions)

    # Compile Options
    set(PMC_PY_FLAGS "${py_inclusions} -DCOMPILE_PYTHON")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${PMC_PY_FLAGS}")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${PMC_PY_FLAGS}")
    set(PYBIND11_CPP_STANDARD -std=c++${CMAKE_CXX_STANDARD})

    # Folders
    set(DIR_PY ${DIR_ROOT}/py/)

    # Source Files
    set(SRC
        ${PMC_LIB_SRC}
        ${DIR_PY}/pmc_py.cpp
    )

    # Header Files
    set(PMC_PY_INCLUDE_DIR
            ${DIR_ROOT}
            ${PROJECT_DEPS_DIR}/pybind11
            ${dlib_INCLUDE_DIRS}
            )

    pybind11_add_module(pmc_py ${SRC})
    target_include_directories(pmc_py PUBLIC ${PMC_PY_INCLUDE_DIR})
    target_link_libraries(pmc_py PRIVATE ${TARGET_PMC})
endif()













