set(LIBNAME mgraph)

add_library(${LIBNAME} STATIC
    graph.cpp
)

# target_include_directories(${LIBNAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

# install(TARGETS ${LIBNAME} ARCHIVE DESTINATION lib)