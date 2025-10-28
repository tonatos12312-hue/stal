function(add_resources TARGET_NAME)
    set(options "")
    set(oneValueArgs NAMESPACE GENERATOR_PATH)
    set(multiValueArgs FONT_SIZES)

    cmake_parse_arguments(ADD_RESOURCES "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if (NOT ADD_RESOURCES_NAMESPACE)
        set(ADD_RESOURCES_NAMESPACE "generated")
    endif()

    if (NOT ADD_RESOURCES_GENERATOR_PATH)
        set(ADD_RESOURCES_GENERATOR_PATH "${CMAKE_HOME_DIRECTORY}/tools/resource_generator.py")
    endif()

    if (NOT ADD_RESOURCES_FONT_SIZES)
        set(ADD_RESOURCES_FONT_SIZES "16.0")
    endif()

    set(RESOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/resource")
    set(GENERATED_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")
    set(GENERATED_HEADER "${GENERATED_DIR}/resources.h")
    set(GENERATED_SOURCE "${GENERATED_DIR}/resources.cpp")

    file(GLOB_RECURSE RESOURCE_FILES
            "${RESOURCE_DIR}/*.png"
            "${RESOURCE_DIR}/*.jpg"
            "${RESOURCE_DIR}/*.jpeg"
            "${RESOURCE_DIR}/*.bmp"
            "${RESOURCE_DIR}/*.ico"

            "${RESOURCE_DIR}/*.ttf"
            "${RESOURCE_DIR}/*.otf"
    )

    add_custom_command(
            OUTPUT "${GENERATED_HEADER}" "${GENERATED_SOURCE}"
            COMMAND ${CMAKE_COMMAND} -E make_directory "${GENERATED_DIR}"
            COMMAND python "${ADD_RESOURCES_GENERATOR_PATH}"
            "${CMAKE_CURRENT_SOURCE_DIR}"
            --output "${GENERATED_DIR}"
            --namespace "${ADD_RESOURCES_NAMESPACE}"
            --font-sizes ${ADD_RESOURCES_FONT_SIZES}
            DEPENDS ${RESOURCE_FILES} "${ADD_RESOURCES_GENERATOR_PATH}"
            COMMENT "Generating resources for ${TARGET_NAME}"
            VERBATIM
    )

    add_custom_target(${TARGET_NAME}_resources DEPENDS "${GENERATED_HEADER}" "${GENERATED_SOURCE}")

    target_include_directories(${TARGET_NAME} PRIVATE "${GENERATED_DIR}")
    target_sources(${TARGET_NAME} PRIVATE "${GENERATED_HEADER}" "${GENERATED_SOURCE}")

    add_dependencies(${TARGET_NAME} ${TARGET_NAME}_resources)

    message(STATUS "Added resource generation for ${TARGET_NAME}")
    message(STATUS "  Resource directory: ${RESOURCE_DIR}")
    message(STATUS "  Generated files: ${GENERATED_DIR}")
    message(STATUS "  Namespace: ${ADD_RESOURCES_NAMESPACE}")
    message(STATUS "  Font sizes: ${ADD_RESOURCES_FONT_SIZES}")
endfunction()
