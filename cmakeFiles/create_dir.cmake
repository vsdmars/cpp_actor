# For build directory
SET(BIN_DIR "${PROJECT_BINARY_DIR}/bin")
SET(BIN_DIR_TEST "${PROJECT_BINARY_DIR}/test_bin")

SET(BUILD_DIRS include lib)

foreach(d ${BUILD_DIRS})
   file(MAKE_DIRECTORY "${BIN_DIR}/${d}")
   file(MAKE_DIRECTORY "${BIN_DIR_TEST}/${d}")
endforeach(d)
