file(GLOB_RECURSE srcs
    *.c
    *.cpp
)

set(include_dirs 
    . 
    ui
)

idf_component_register(SRCS ${srcs}
                       INCLUDE_DIRS ${include_dirs})

# Apply flags only to current component
target_compile_options(${COMPONENT_LIB} PRIVATE -Wno-error=dangling-pointer)

# Apply flags to lvgl if available
idf_component_get_property(lvgl_lib lvgl__lvgl COMPONENT_LIB)
if(lvgl_lib)
    target_compile_options(${lvgl_lib} PRIVATE -Wno-format)
endif()