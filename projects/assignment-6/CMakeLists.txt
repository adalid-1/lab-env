#--------------------------------------------------------------------------
# assignment-6 project
#--------------------------------------------------------------------------

PROJECT(assignment-6)
FILE(GLOB assignment-6_headers code/*.h)
FILE(GLOB assignment-6_sources code/*.cc  code/*.cpp shaders.*cpp)


SET(files_assignment-6 ${assignment-6_headers} ${assignment-6_sources})
SOURCE_GROUP("example" FILES ${files_example})

ADD_EXECUTABLE(assignment-6 ${files_assignment-6})
TARGET_LINK_LIBRARIES(assignment-6 core render)
ADD_DEPENDENCIES(assignment-6 core render)



