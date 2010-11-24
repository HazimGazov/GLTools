# compute default library install dir

set (_DEFAULT_LIBRARY_INSTALL_DIR lib)
if (EXISTS "${CMAKE_INSTALL_PREFIX}/lib32/" AND CMAKE_SIZEOF_VOID_P EQUAL 4)
 set (_DEFAULT_LIBRARY_INSTALL_DIR lib32)
elif (EXISTS "${CMAKE_INSTALL_PREFIX}/lib64/" AND CMAKE_SIZEOF_VOID_P EQUAL 8)
 set (_DEFAULT_LIBRARY_INSTALL_DIR lib64)
endif ()
# the library install dir
set(LIBRARY_INSTALL_DIR "${_DEFAULT_LIBRARY_INSTALL_DIR}" CACHE PATH 
"Installation directory for libraries")
# make the library install dir an absolute path (can be important e.g. when using CONFIGURE_FILE to embed
# the library installation directory into a file)
if(NOT IS_ABSOLUTE "${LIBRARY_INSTALL_DIR}")
  set(LIBRARY_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/${LIBRARY_INSTALL_DIR}")
endif()

set(HEADER_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/include" CACHE PATH "Installation directory for headers")
