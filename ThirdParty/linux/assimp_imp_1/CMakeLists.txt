add_library(assimp SHARED IMPORTED GLOBAL)

find_library(ASSIMP_LIB
  NAMES assimp
  PATHS
  .
  DOC "The simple2d library")
message("ASSIMP PATH IS "${ASSIMP_LIB})

#apparently it needs the full path, or the binary should be moven next to the executable
set_target_properties(assimp PROPERTIES
             IMPORTED_LOCATION ${ASSIMP_LIB})
target_include_directories(assimp INTERFACE ./ )

#set_property(TARGET assimp APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES .)

#glmemoryserver
#memoryserver

#allocate resources in memory

#problem: model makes opnegl calls

#solution1: create a wrapper to opengl, call it rendering backend. contains virtual functions.
#each backend overrides it.

#back end class.

#this backend could be higher level than opengl
#this will remove glad from the rest of the code and localize it.

#determine the function to override.


#func1 create and return a texture, a texture is represented by it's id.

#1 replace texture struct by a class.

#function for creating and loading a mesh, creating the buffers, and loading the verstex attributes.

#the backend's methods will be static. no 
#the backend will be a singleton.
#which classes should have access to the backend.

#the backend will be a singleton that will be set at the begining of the app. all classes that need it will access it.
#the could have an instance of it, or just query it every time they need it.


#the backend will be set by the engine user.

#the back end will not depend on other parts of the engine.

#not all backends will compile on all platforms.

#check that the backend has been set. engine module manager.
