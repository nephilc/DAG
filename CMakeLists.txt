cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 14)

project(DAG VERSION 1.0  LANGUAGES CXX C)
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /ZI")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /INCREMENTAL /EDITANDCONTINUE")

#this doesnt work when switching between build types in msvc
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
#link_directories(${CMAKE_SOURCE_DIR}/lib)
#include_directories(../include)
#message(${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

add_subdirectory(src)
add_subdirectory(ThirdParty)

#

if(WIN32)


    file(COPY ${ASSIMP_DLL} DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/EditorBin")
    file(COPY ${GLFW_DLL} DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/EditorBin")

endif()

enable_testing()


#the editor is suposed to configure scene nodes, so encapsulation will be put on hold, to some extent. We will, however configure the object through a specific interface which obsures some details to external clients.
#plus we can implement recursivity outside of the node class, just like we have already done. We will need access to a Node's children nodes. We will act, while working on the editor, as if we cannot modify the Node class, Thus keeping the two classes' independent of each other.


include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

