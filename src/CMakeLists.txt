# ─────────────────────────────────────────────────────────────────────────────
# Target: c_linalg
# Alias: c_linalg::c_linalg
# Type: Static Library
# Dependencies: c_linalg::c_linalg_headers
# ─────────────────────────────────────────────────────────────────────────────
# Target definition
add_library(c_linalg STATIC)

# Target alias
add_library(c_linalg::c_linalg ALIAS c_linalg)

# Target sources
target_sources(c_linalg
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/c_linalg.c
)

# Target dependencies
target_link_libraries(c_linalg
    PUBLIC
        c_linalg::c_linalg_headers
)

# Export configuration
include(GenerateExportHeader)

if(BUILD_SHARED_LIBS)
    # Export file name for a shared build
    set(EXPORT_HEADER_FILE export_shared.h)

    # Primary target properties
    set_target_properties(c_linalg PROPERTIES
            OUTPUT_NAME c_linalg
            VERSION ${PROJECT_VERSION}
            SOVERSION ${PROJECT_VERSION_MAJOR}
            C_VISIBILITY_PRESET hidden
            VISIBILITY_INLINES_HIDDEN ON
    )

    # Define compile definitions
    target_compile_definitions(c_linalg
            PUBLIC
                $<$<NOT:$<BOOL:${BUILD_SHARED_LIBS}>>:C_LINALG_STATIC_DEFINE>
    )
else()
    # Export file name for a static build
    set(EXPORT_HEADER_FILE export_static.h)

    # Primary target properties
    set_target_properties(c_linalg PROPERTIES
            OUTPUT_NAME c_linalg
            VERSION ${PROJECT_VERSION}
            SOVERSION ${PROJECT_VERSION_MAJOR}
            POSITION_INDEPENDENT_CODE ON
    )

    # A static build must see the STATIC_DEFINE guard from the generated export header
    target_compile_definitions(c_linalg
            PUBLIC
                C_LINALG_STATIC_DEFINE
    )
endif()

# Generate the export header into the build tree
generate_export_header(c_linalg
        EXPORT_FILE_NAME include/c_linalg/${EXPORT_HEADER_FILE}
)

# Make the generated export header visible to this target and its consumers
target_include_directories(c_linalg
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

if(NOT CMAKE_SKIP_INSTALL_RULES)
    include(GNUInstallDirs)

    # Install the library target (Conan/CMakeDeps provides the config + targets files)
    install(TARGETS c_linalg c_linalg_headers
            RUNTIME COMPONENT c_linalg
            LIBRARY COMPONENT c_linalg
            NAMELINK_COMPONENT c_linalg
            ARCHIVE COMPONENT c_linalg
            INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

    # Install the generated export header
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/include/c_linalg/${EXPORT_HEADER_FILE}
            COMPONENT c_linalg
            DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/c_linalg)
endif()
