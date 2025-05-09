cmake_minimum_required(VERSION 3.19)
project(Sample LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Multimedia)

qt_standard_project_setup()

qt_add_executable(Sample
    WIN32 MACOSX_BUNDLE
    main.cpp
)

target_link_libraries(Sample
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Multimedia
)

include(GNUInstallDirs)

install(TARGETS Sample
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET Sample
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})