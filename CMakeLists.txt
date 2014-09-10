IF(BIICODE)
  include(${CMAKE_HOME_DIRECTORY}/biicode.cmake)
  # Initializes block variables
  INIT_BIICODE_BLOCK()

  SET(BII_CREATE_LIB True)

  # Include base dir
  INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/include)
  # Include base block dir
  ADD_BIICODE_TARGETS()

  # Link target with dl for linux
  IF (UNIX)
   IF(NOT APPLE)
     TARGET_LINK_LIBRARIES(${BII_LIB_TARGET} PUBLIC dl)
   ENDIF()
  ENDIF()  

ELSE()
  include(${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists_original.txt)
ENDIF()
