#This probably won't build a library for Windows, and it hasn't been tested on OS X

cmake_minimum_required( VERSION 2.6 )

project( GLTools )

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include(Installation)

if(APPLE)
	include(CMakeFindFrameworks)
endif(APPLE)

#make sure we have all of the libraries we need
find_package(X11)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_library(M_LIBRARY m)
find_library(GLEW_LIBRARY GLEW)

set ( CMAKE_BUILD_TYPE Debug )
add_definitions ( -Wall )

set ( INCLUDE_DIRS
	"${CMAKE_SOURCE_DIR}/include"
	${INCLUDE_DIRS}
)

if(UNIX)
	set ( INCLUDE_DIRS 
		"/usr/include"
		"/usr/local/include"
		"/usr/include/GL"
		${INCLUDE_DIRS}
	)
endif(UNIX)

include_directories (
	${INCLUDE_DIRS}
)
	
	
set ( GLTOOLS_HDRS
	"${CMAKE_SOURCE_DIR}/include/GLBatchBase.h"
	"${CMAKE_SOURCE_DIR}/include/GLBatch.h"
	"${CMAKE_SOURCE_DIR}/include/GLFrame.h"
	"${CMAKE_SOURCE_DIR}/include/GLFrustum.h"
	"${CMAKE_SOURCE_DIR}/include/GLGeometryTransform.h"
	"${CMAKE_SOURCE_DIR}/include/GLMatrixStack.h"
	"${CMAKE_SOURCE_DIR}/include/GLShaderManager.h"
	"${CMAKE_SOURCE_DIR}/include/GLTools.h"
	"${CMAKE_SOURCE_DIR}/include/GLTriangleBatch.h"
	"${CMAKE_SOURCE_DIR}/include/math3d.h"
	"${CMAKE_SOURCE_DIR}/include/StopWatch.h"
)

set ( GLTOOLS_SRCS
	"${CMAKE_SOURCE_DIR}/src/GLBatch.cpp"
	"${CMAKE_SOURCE_DIR}/src/GLShaderManager.cpp"
	"${CMAKE_SOURCE_DIR}/src/GLTools.cpp"
	"${CMAKE_SOURCE_DIR}/src/GLTriangleBatch.cpp"
	"${CMAKE_SOURCE_DIR}/src/math3d.cpp"
)

add_library ( gltools-static ${GLTOOLS_SRCS})	
add_library ( gltools SHARED ${GLTOOLS_SRCS})

target_link_libraries (gltools ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${GLEW_LIBRARY} ${M_LIBRARY} ${X11_LIBRARIES})
target_link_libraries (gltools-static ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${GLEW_LIBRARY} ${M_LIBRARY} ${X11_LIBRARIES})
set_target_properties(gltools-static PROPERTIES OUTPUT_NAME gltools)

install(TARGETS gltools gltools-static
	LIBRARY DESTINATION ${LIBRARY_INSTALL_DIR}
	ARCHIVE DESTINATION ${LIBRARY_INSTALL_DIR}
)

install(FILES
	${GLTOOLS_HDRS}
	DESTINATION ${HEADER_INSTALL_DIR}
)
