FIND_PATH (JSONCPP_ROOT_DIR
  NAMES jsoncpp/json/value.h
  PATHS ENV JSONCPPROOT
  DOC "jsoncpp root directory")

FIND_PATH (JSONCPP_INCLUDE_DIR
  NAMES json/value.h
  HINTS ${JSONCPP_ROOT_DIR}
  PATH_SUFFIXES jsoncpp
  DOC "jsoncpp include directory")


find_library(
    JSONCPP_LIBRARY
    NAMES jsoncpp
)

