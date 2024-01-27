include(FetchContent)

set(FETCH_CONTENT_SOURCE_DIR ${CMAKE_SOURCE_DIR}/SpleeterLib/deps/spleeterpp)

FetchContent_Declare(
  spleeterpp
  GIT_REPOSITORY https://github.com/joeloftusdev/spleeterpp
 # GIT_TAG        develop
  SOURCE_DIR ${FETCH_CONTENT_SOURCE_DIR}
)


FetchContent_GetProperties(spleeterpp)
if(NOT spleeterpp_POPULATED)
  FetchContent_Populate(spleeterpp)
  add_subdirectory(${spleeterpp_SOURCE_DIR} ${spleeterpp_BINARY_DIR})
endif()