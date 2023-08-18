
#add_subdirectory(ImGuizmo)


add_definitions(-DIMGUI_IMPL_OPENGL_LOADER_GLAD)
set(FILEBROWSERSRC ./FileBrowser/ImGuiFileBrowser.cpp)
set(ImGuizmoSRC ./ImGuizmo/GraphEditor.cpp
	./ImGuizmo/ImCurveEdit.cpp
	./ImGuizmo/ImGradient.cpp
	./ImGuizmo/ImGuizmo.cpp
	./ImGuizmo/ImSequencer.cpp
	./ImGuiColorTextEdit-master/TextEditor.cpp  )

add_library(imgui SHARED imgui.cpp imgui_demo.cpp imgui_draw.cpp imgui_tables.cpp imgui_widgets.cpp ./backends/imgui_impl_opengl3.cpp ./backends/imgui_impl_glfw.cpp ${FILEBROWSERSRC} ${ImGuizmoSRC})
target_include_directories(imgui PUBLIC . ./backends ./FileBrowser ./ImGuizmo ./ImGuiColorTextEdit-master)

target_link_libraries(imgui PUBLIC glfw glad)


