#--------------------------------------------------------------------------
# assignment-3 project
#--------------------------------------------------------------------------

PROJECT(assignment-3)
FILE(GLOB assignment-3_headers code/*.h)
FILE(GLOB assignment-3_sources code/*.cc  code/*.cpp)

SET(files_assignment-3 ${assignment-3_headers} ${assignment-3_sources})
SOURCE_GROUP("example" FILES ${files_example})

ADD_EXECUTABLE(assignment-3 ${files_assignment-3})
TARGET_LINK_LIBRARIES(assignment-3 core render)
ADD_DEPENDENCIES(assignment-3 core render)



