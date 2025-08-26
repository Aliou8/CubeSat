SET(SOURCES screens/ui_Screen2.c
    screens/ui_Screen1.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    images/ui_img_nucleaire_png.c
    images/ui_img_avion_png.c
    images/ui_img_nord_png.c
    fonts/ui_font_Display16.c
    fonts/ui_font_Display24.c)

add_library(ui ${SOURCES})
