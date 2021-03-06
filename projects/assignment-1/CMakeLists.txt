#--------------------------------------------------------------------------
# assignment-1 project
#--------------------------------------------------------------------------

PROJECT(assignment-1)
FILE(GLOB assignment-1_headers code/*.h)
FILE(GLOB assignment-1_sources code/*.cc  code/*.cpp)

SET(files_assignment-1 ${assignment-1_headers} ${assignment-1_sources})
SOURCE_GROUP("example" FILES ${files_example})

ADD_EXECUTABLE(assignment-1 ${files_assignment-1})
TARGET_LINK_LIBRARIES(assignment-1 core render)
ADD_DEPENDENCIES(assignment-1 core render)