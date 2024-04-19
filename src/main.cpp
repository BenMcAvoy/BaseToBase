#include <GLFW/glfw3.h>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <unordered_map>
#include <stdio.h>
#include <memory>

#include "logging.hpp"
#include "globals.cpp"
#include "theme.hpp"

#include "mappings/hexadecimal.cpp"
#include "mappings/binary.cpp"
#include "mapping.hpp"

#include "font.hpp"

void AddMapping(std::unordered_map<std::string, std::unique_ptr<Mapping>>& mappings, Mapping* mapping) {
	mappings.emplace(mapping->name(), std::unique_ptr<Mapping>(mapping));
}

int main(void) {
	std::unordered_map<std::string, std::unique_ptr<Mapping>> mappings;

	AddMapping(mappings, new Binary());
	AddMapping(mappings, new Hexadecimal());

	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(1280, 720, "GuiClass", NULL, NULL);

	if (!window) {
		ERROR("Failed to create window");
		glfwTerminate();
		return -1;
	}

	INFO("Window created\n");

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	INFO("Made context current\n");

	/* Initialize ImGui */
	IMGUI_CHECKVERSION();

	INFO("ImGui version checked\n");

	INFO("OpenGL version: %s\n", glGetString(GL_VERSION));
	INFO("GLSL version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	INFO("Renderer: %s\n", glGetString(GL_RENDERER));
	INFO("GLFW version: %s\n", glfwGetVersionString());
	INFO("ImGui version: %s\n", IMGUI_VERSION);

	ImGui::CreateContext();
	INFO("ImGui context created\n");

	ImGuiIO& io = ImGui::GetIO();
	ImFontConfig config;
	config.FontDataOwnedByAtlas = false;
	io.Fonts->AddFontFromMemoryTTF(fonts::JetBrainsMonoNerdFont_Regular_ttf, sizeof(fonts::JetBrainsMonoNerdFont_Regular_ttf), 20.0f, &config, io.Fonts->GetGlyphRangesDefault());
	SetupImGuiStyle();

	/* Setup Dear ImGui style */
	ImGui::StyleColorsDark();

	/* Setup Platform/Renderer bindings */
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 130");

	INFO("ImGui initialized\n");

	Mapping *selectedMapping = nullptr;

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window) && !globals::shouldExit) {
		glfwPollEvents();

		ImGui::SetNextWindowPos(ImVec2(0, 0));
		ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x, io.DisplaySize.y));

		/* Start the ImGui frame */
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("BaseToBase", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

		if (ImGui::BeginCombo("Select Item", selectedMapping ? selectedMapping->name() : "Select a mapping")) {
			for (const auto& pair : mappings) {
				if (ImGui::Selectable(pair.first.c_str())) {
					selectedMapping = pair.second.get();
				}
			}

			ImGui::EndCombo();
		}

		ImGui::InputText("Input: ", globals::input, IM_ARRAYSIZE(globals::input));
		ImGui::Text("Output: %d", globals::output);

		if (selectedMapping)
			selectedMapping->Update();

		ImGui::End();

		ImGui::Render();

		/* Render OpenGL */
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window);
	}

	/* Cleanup */
	glfwDestroyWindow(window);
	INFO("Window destroyed\n");

	glfwTerminate();
	INFO("GLFW terminated\n");

	return 0;
}
