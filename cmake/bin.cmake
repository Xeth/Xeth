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

    set(GETH_BIN_PATH "${PROJECT_BINARY_DIR}/vendor/bin/geth${BIN_EXTENSION}")
    set(IPFS_BIN_PATH "${PROJECT_BINARY_DIR}/vendor/bin/ipfs${BIN_EXTENSION}")

    if(NOT EXISTS ${GETH_BIN_PATH})
        message("downloading geth")
        file(DOWNLOAD ${GETH_DOWNLOAD_URL} ${GETH_BIN_PATH} SHOW_PROGRESS)
    endif()

    if(NOT EXISTS ${IPFS_BIN_PATH})
        message("downloading ipfs")
        file(DOWNLOAD ${IPFS_DOWNLOAD_URL} ${IPFS_BIN_PATH} SHOW_PROGRESS)
    endif()

endif()
