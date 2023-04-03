// Dear ImGui: standalone example application for SDL2 + OpenGL
// (SDL is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan/Metal graphics context creation, etc.)
// If you are new to Dear ImGui, read documentation from the docs/ folder + read the top of imgui.cpp.
// Read online: https://github.com/ocornut/imgui/tree/master/docs

// **DO NOT USE THIS CODE IF YOUR CODE/ENGINE IS USING MODERN OPENGL (SHADERS, VBO, VAO, etc.)**
// **Prefer using the code in the example_sdl2_opengl3/ folder**
// See imgui_impl_sdl2.cpp for details.

#include "imgui.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_opengl2.h"
#include <stdio.h>
#include <SDL.h>
#include <SDL_opengl.h>

#include <iostream>
#include "misc/cpp/imgui_stdlib.h"
#include <fstream>
#include <sstream>

#include <regex>

std::string slurp(std::ifstream& in) {
    std::ostringstream sstr;
    sstr << in.rdbuf();
    return sstr.str();
}

// Main code
int main(int, char**)
{
    // Setup SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
    {
        printf("Error: %s\n", SDL_GetError());
        return -1;
    }

    // From 2.0.18: Enable native IME.
#ifdef SDL_HINT_IME_SHOW_UI
    SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
	std::cout << "HIIIIIIII" std::endl;
#endif

    // Setup window
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Window* window = SDL_CreateWindow("Dear ImGui SDL2+OpenGL example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);
    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, gl_context);
    SDL_GL_SetSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL2_Init();

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
    io.Fonts->AddFontFromFileTTF("misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != NULL);

    // Our state
    // bool show_demo_window = true;
    // bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	std::string	buf = "test";
	std::string filecont;
	std::string	ebuf;
	std::regex	e;
	std::string	rep;
	std::string	regedCont;
	std::ifstream	ifs;
	ImVec4	col;

	std::vector<int>	index_matches;
	std::string			matchidxs;

	buf.reserve(250);
	filecont.reserve(10000);
	// buf.clear();
	
    // Main loop
    bool done = false;
    while (!done)
    {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
                done = true;
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
                done = true;
        }

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        // if (show_demo_window)
        //     ImGui::ShowDemoWindow(&show_demo_window);

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
		// static float f = 0.0f;
		// static int counter = 0;


		// buf = "LICENSE.txt";
		// ifs.open(buf.c_str(), std::ifstream::in);
		// std::cout << ifs.is_open() << std::endl;

		ImGui::Begin("ORIGINAL");                          // Create a window called "Hello, world!" and append into it.

		// buf = "LICENSE.txt";
		if (ImGui::InputText("File Name", &buf, 32))
		{
			if (ifs.is_open())
			{
				std::cout << "Closing old file" << std::endl;
				ifs.close();
			}
			std::cout << "Opening " << buf << std::endl;
			ifs.open(buf.c_str(), std::ifstream::in);
			if (ifs.is_open())
			{
				filecont = slurp(ifs);
				std::cout << filecont << std::endl;
			}
			else
			{
				std::cout << false << std::endl;
			}
		}
		if (ifs.is_open())
		{
			// std::cout << ifs.is_open() << std::endl;
			// ImGui::TextUnformatted(std::string("hello").c_str());
			ImGui::TextUnformatted(filecont.c_str());
		}
		ImGui::End();

		ImGui::Begin("AFFECTED");
		ImGui::InputText("Regex", &ebuf);
		ImGui::InputText("Rep", &rep);
		try {
			e.assign(ebuf);
			regedCont = std::regex_replace(filecont, e, rep);
			index_matches.clear();
			for (auto it = std::sregex_iterator(filecont.begin(), filecont.end(), e);
				it != std::sregex_iterator();
				++it)
			{
				index_matches.push_back(it->position());
			}
		} catch (std::regex_error& e) {
			std::cerr << "Not a valid expression" << std::endl;
		}
	
		matchidxs.clear();
		for(int n: index_matches)
		{
			matchidxs += std::to_string(n) + ", ";
		}
		ImGui::TextWrapped("%s", matchidxs.c_str());

		ImGui::TextUnformatted(regedCont.c_str());
		ImGui::End();
		
		// static float col1[3] = { 1.0f, 0.0f, 0.2f };
		// static float col2[4] = { 0.4f, 0.7f, 0.0f, 0.5f };
		// ImGui::ColorEdit3("color 1", col1);
		// ImGui::SameLine();
		// ImGui::ColorEdit4("color 2", col2);

		// col.x = col1[0],
		// col.y = col1[1];
		// col.z = col1[2];
		// col.w = 255;

		// ImGui::TextColored(col, "%s", "Hello there");

		// ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
		// ImGui::TextWrapped("This is some useful text.");
		// ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
		// ImGui::Checkbox("Another Window", &show_another_window);

		// ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		// ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

		// if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
		//     counter++;
		// ImGui::SameLine();
		// ImGui::Text("counter = %d", counter);

		// ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);

		// ImGui::Begin("AFFECTED");
		// ImGui::Text("Hello");
		// ImGui::End();
        // 3. Show another simple window.
        // if (show_another_window)
        // {
        //     ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        //     ImGui::Text("Hello from another window!");
        //     if (ImGui::Button("Close Me"))
        //         show_another_window = false;
        //     ImGui::End();
        // }

        // Rendering
        ImGui::Render();
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        //glUseProgram(0); // You may want this if using this code in an OpenGL 3+ context where shaders may be bound
        ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);
    }

	if (ifs.is_open())
		ifs.close();
    // Cleanup
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
