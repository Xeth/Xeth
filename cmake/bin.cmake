if(NOT NO_BIN_DOWNLOAD)

    include(CheckTypeSize)
    check_type_size("void*" SIZEOF_VOID_P BUILTIN_TYPES_ONLY)

    if(SIZEOF_VOID_P EQUAL 8)
        set(BIN_ARCH_PREFIX "x86_64")
    else()
        set(BIN_ARCH_PREFIX "x86")
    endif()


    set(BIN_EXTENSION "")

    if(MSVC OR WIN32)
        set(GETH_DOWNLOAD_URL "https://sourceforge.net/projects/xeth/files/windows/${BIN_ARCH_PREFIX}/geth.exe/download")
        set(IPFS_DOWNLOAD_URL "https://sourceforge.net/projects/xeth/files/windows/${BIN_ARCH_PREFIX}/ipfs.exe/download")
        set(BIN_EXTENSION ".exe")
    elseif(APPLE)
        set(GETH_DOWNLOAD_URL "https://sourceforge.net/projects/xeth/files/osx/x86_64/geth/download")
        set(IPFS_DOWNLOAD_URL "https://sourceforge.net/projects/xeth/files/osx/x86_64/ipfs/download")
    else()
        set(GETH_DOWNLOAD_URL "https://sourceforge.net/projects/xeth/files/linux/${BIN_ARCH_PREFIX}/geth/download")
        set(IPFS_DOWNLOAD_URL "https://sourceforge.net/projects/xeth/files/linux/${BIN_ARCH_PREFIX}/ipfs/download")
    endif()

    set(GETH_BIN "geth${BIN_EXTENSION}")
    set(IPFS_BIN "ipfs${BIN_EXTENSION}")


    if(NOT EXISTS ${PROJECT_BINARY_DIR}/vendor/bin/${GETH_BIN})
        message("downloading geth")
        file(DOWNLOAD ${GETH_DOWNLOAD_URL} ${PROJECT_BINARY_DIR}/download/${GETH_BIN} SHOW_PROGRESS)
        file(COPY ${PROJECT_BINARY_DIR}/download/${GETH_BIN} DESTINATION ${PROJECT_BINARY_DIR}/vendor/bin FILE_PERMISSIONS OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE NO_SOURCE_PERMISSIONS)
        file(REMOVE ${PROJECT_BINARY_DIR}/download/${GETH_BIN})
    endif()


    if(NOT EXISTS ${PROJECT_BINARY_DIR}/vendor/bin/${IPFS_BIN})
        message("downloading ipfs")
        file(DOWNLOAD ${IPFS_DOWNLOAD_URL} ${PROJECT_BINARY_DIR}/download/${IPFS_BIN} SHOW_PROGRESS)
        file(COPY ${PROJECT_BINARY_DIR}/download/${IPFS_BIN} DESTINATION ${PROJECT_BINARY_DIR}/vendor/bin FILE_PERMISSIONS OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE NO_SOURCE_PERMISSIONS)
        file(REMOVE ${PROJECT_BINARY_DIR}/download/${IPFS_BIN})
    endif()

endif()
