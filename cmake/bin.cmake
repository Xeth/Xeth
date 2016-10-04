include(${PROJECT_SOURCE_DIR}/cmake/modules/Vendor.cmake)


if(USING_GETH)
    REQUIRE_VENDOR_BIN("geth" "${GETH_PATH}" "")
else()
    REQUIRE_VENDOR_BIN("parity" "${PARITY_PATH}" "C:\\Program Files\\Parity")
endif()


REQUIRE_VENDOR_BIN("ipfs" "${IPFS_PATH}" "C:\\Program Files\\Ipfs")
