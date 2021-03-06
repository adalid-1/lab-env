#--------------------------------------------------------------------------
# assignment-2 project
#--------------------------------------------------------------------------

PROJECT(assignment-2)
FILE(GLOB assignment-2_headers code/*.h)
FILE(GLOB assignment-2_sources code/*.cc  code/*.cpp)

SET(files_assignment-2 ${assignment-2_headers} ${assignment-2_sources})
SOURCE_GROUP("example" FILES ${files_example})

ADD_EXECUTABLE(assignment-2 ${files_assignment-2})
TARGET_LINK_LIBRARIES(assignment-2 core render)
ADD_DEPENDENCIES(assignment-2 core render)



