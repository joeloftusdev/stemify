include_directories(${CMAKE_SOURCE_DIR}/SpleeterLib/deps/spleeterpp/build/_deps/wave-src/src)
include_directories(${CMAKE_SOURCE_DIR}/SpleeterLib/deps/spleeterpp/src)
include_directories(${CMAKE_SOURCE_DIR}/SpleeterLib/deps/spleeterpp/build/_deps/eigen3-src)


# Set the source directory
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Use file(GLOB ...) to get a list of all .cpp and .h files in the directory
file(GLOB SOURCES ${SOURCE_DIR}/*.cpp ${SOURCE_DIR}/*.h)

# Create the shared library target
add_library(SpleeterLib SHARED ${SOURCES})


target_compile_definitions(SpleeterLib PRIVATE SPLEETERLIB_EXPORTS)



target_link_libraries(SpleeterLib
  ${CMAKE_SOURCE_DIR}/SpleeterLib/deps/spleeterpp/build/_deps/wave-build/src/wave/Debug/waved.lib
  ${CMAKE_SOURCE_DIR}/SpleeterLib/deps/spleeterpp/build/src/spleeter/Debug/spleeter.lib
  ${CMAKE_SOURCE_DIR}/SpleeterLib/deps/spleeterpp/build/tensorflow/lib/tensorflow.lib
  ${CMAKE_SOURCE_DIR}/SpleeterLib/deps/spleeterpp/build/src/spleeter_common/Debug/spleeter_common.lib

)

install(TARGETS SpleeterLib
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)

install(FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/framework.h
  ${CMAKE_CURRENT_SOURCE_DIR}/pch.h
  ${CMAKE_CURRENT_SOURCE_DIR}/SpleeterLib.h
  ${CMAKE_CURRENT_SOURCE_DIR}/SpleeterService.h
  DESTINATION include/
)

