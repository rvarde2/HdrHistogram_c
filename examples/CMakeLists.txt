if (HDR_LOG_ENABLED)
    add_executable(hdr_decoder
        hdr_decoder.c)
    
    find_package(PkgConfig REQUIRED)
        pkg_check_modules(DPDK REQUIRED libdpdk)

    # Retrieve DPDK flags using pkg-config
    execute_process(
        COMMAND pkg-config --cflags --libs libdpdk
        OUTPUT_VARIABLE DPDK_FLAGS
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    
    target_link_libraries(hdr_decoder
        PRIVATE
            $<$<BOOL:${WIN32}>:hdr_histogram_static>
            $<$<NOT:$<BOOL:${WIN32}>>:hdr_histogram>
            ${DPDK_FLAGS})
    install(
        TARGETS hdr_decoder
        EXPORT ${PROJECT_NAME}-targets
        DESTINATION ${CMAKE_INSTALL_BINDIR})

    if(CMAKE_SYSTEM_NAME MATCHES "Linux")
        find_package(Threads)

        add_executable(hiccup
            hiccup.c)
        target_link_libraries(hiccup
            PRIVATE
                hdr_histogram
                Threads::Threads
                ${DPDK_FLAGS})
        install(
            TARGETS hiccup
            EXPORT ${PROJECT_NAME}-targets
            DESTINATION ${CMAKE_INSTALL_BINDIR})
    endif()
endif()
