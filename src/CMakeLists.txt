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

set(PMC_MAIN
    ${DIR_ROOT}/pmc_driver.cpp
)

set(PMC_LIB
    ${DIR_ROOT}/pmc_lib.cpp
)


# ---------------------------------------------------#
# Targets
# ---------------------------------------------------#


add_library(OBJ_PMC OBJECT ${IO_SRC} ${PMC_SRC} ${BOUND_LIB_SRC} ${H_FILES})

add_executable(runPmc ${PMC_MAIN} $<TARGET_OBJECTS:OBJ_PMC>)
target_include_directories(runPmc PUBLIC ${DIR_ROOT})
#target_link_libraries(pmc PRIVATE ${OBJ_PMC})

add_library(${TARGET_PMC} SHARED ${PMC_LIB} $<TARGET_OBJECTS:OBJ_PMC>)
target_include_directories(${TARGET_PMC} PUBLIC ${DIR_ROOT})
