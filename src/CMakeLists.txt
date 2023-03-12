#add_subdirectory(Tests)
#add_subdirectory(Graph)
#add_subdirectory(test)
#add_subdirectory(IntApp)
#add_subdirectory(Interpreter)
#add_subdirectory(Infrastructure)
add_subdirectory(EditorApp)
add_subdirectory(Editor)
add_subdirectory(ProjectMgr)

add_subdirectory(backends)
add_subdirectory(libGraphics)
add_subdirectory(libAssets)

#looks like we are going to use the builder pattern for constructing the input and outputs
#we let the client create the directore object and configure it with the concrete builder


#the client of the library, the one building the application will specify the right builder.
#give the importer a new ioHandler, this is just polymorphism. The io handler will maintain the same behavior
