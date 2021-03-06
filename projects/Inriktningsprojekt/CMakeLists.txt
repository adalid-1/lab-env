#--------------------------------------------------------------------------
# Inriktningsprojekt project
#--------------------------------------------------------------------------

PROJECT(Inriktningsprojekt)
FILE(GLOB Inriktningsprojekt_headers code/*.h)
FILE(GLOB Inriktningsprojekt_sources code/*.cc  code/*.cpp shaders.*cpp)


SET(files_Inriktningsprojekt ${Inriktningsprojekt_headers} ${Inriktningsprojekt_sources})
SOURCE_GROUP("example" FILES ${files_example})

ADD_EXECUTABLE(Inriktningsprojekt ${files_Inriktningsprojekt})
TARGET_LINK_LIBRARIES(Inriktningsprojekt core render)
ADD_DEPENDENCIES(Inriktningsprojekt core render)



