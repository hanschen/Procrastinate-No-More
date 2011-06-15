project(plasma-applet-procrastinate-no-more)

find_package(KDE4 REQUIRED)
include(KDE4Defaults)

add_definitions(${QT_DEFINITIONS} ${KDE4_DEFINITIONS})
include_directories(${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR} ${KDE4_INCLUDES})

add_subdirectory(images)
add_subdirectory(src)

install(FILES plasma-applet-procrastinate-no-more.desktop
        DESTINATION ${SERVICES_INSTALL_DIR})
