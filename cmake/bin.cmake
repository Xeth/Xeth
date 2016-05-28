function(VENDOR_CHECK_DOWNLOAD EXEC PLATFORM ARCH)

    find_program(${EXEC}_PATH ${EXEC})

    if(${EXEC}_PATH)
        message(${EXEC} " - found ${${EXEC}_PATH}")
    else()
        message(${EXEC} " - not found")
    endif()
    
    if(NOT ${EXEC}_PATH AND NOT EXISTS ${PROJECT_BINARY_DIR}/vendor/bin/${EXEC})
        set(DOWNLOAD_URL "https://sourceforge.net/projects/xeth/files/${PLATFORM}/${ARCH}/${EXEC}/download")
        file(DOWNLOAD ${DOWNLOAD_URL} ${PROJECT_BINARY_DIR}/download/${EXEC} SHOW_PROGRESS)
        file(COPY ${PROJECT_BINARY_DIR}/download/${EXEC} DESTINATION ${PROJECT_BINARY_DIR}/vendor/bin FILE_PERMISSIONS OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE NO_SOURCE_PERMISSIONS)
        file(REMOVE ${PROJECT_BINARY_DIR}/download/${EXEC})
    endif()

endfunction(VENDOR_CHECK_DOWNLOAD)

if(NOT NO_BIN_DOWNLOAD)

    include(CheckTypeSize)
    check_type_size("void*" SIZEOF_VOID_P BUILTIN_TYPES_ONLY)

    if(SIZEOF_VOID_P EQUAL 8)
        set(ARCH "x86_64")
    else()
        set(ARCH "x86")
    endif()


    set(GETH_BIN "geth")
    set(IPFS_BIN "ipfs")

    if(MSVC OR WIN32)
        set(PLATFORM "windows")
        set(GETH_BIN "geth.exe")
        set(IPFS_BIN "ipfs.exe")
    elseif(APPLE)
        set(PLATFORM "osx")
        set(ARCH "x86_64")
    else()
        set(PLATFORM "linux")
    endif()


    VENDOR_CHECK_DOWNLOAD(${GETH_BIN} ${PLATFORM} ${ARCH})
    VENDOR_CHECK_DOWNLOAD(${IPFS_BIN} ${PLATFORM} ${ARCH})

endif()
