project(plasma-applet-procrastinate-no-more)

set(procrastinate-no-more_SRCS
    tomat.cpp)

kde4_add_plugin(plasma_applet_procrastinate-no-more ${procrastinate-no-more_SRCS})
target_link_libraries(plasma_applet_procrastinate-no-more ${KDE4_PLASMA_LIBS})

install(TARGETS plasma_applet_procrastinate-no-more
        DESTINATION ${PLUGIN_INSTALL_DIR})
