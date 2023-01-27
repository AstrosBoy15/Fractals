#include "Gui.h"

void Gui::initGUI(GLFWwindow* window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 430");
}

void Gui::render() {
    ImGui::SetNextWindowSize(ImVec2(350, 150));
    ImGui::Begin("Fractal Settings", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

    std::string fractalSettings;
    if(mode) fractalSettings = "Julia Set Settings";
    else fractalSettings = "Mandelbrot Set Settings";

    auto windowWidth = ImGui::GetWindowSize().x;

    auto textWidth = ImGui::CalcTextSize(fractalSettings.c_str()).x;
    ImGui::SetCursorPosX(125 - textWidth / 2);

    ImGui::Text(fractalSettings.c_str());
    ImGui::SliderInt("Iterations", &iterations, 1, 200);
    if(!mode) ImGui::SliderFloat2("c (a+bi)", &c.x, -1.0f, 1.0f);

    ImGui::Dummy(ImVec2(0.0f, 20.0f));

    std::string modeButton;
    if(mode) modeButton = "Switch to Julia Set";
    else modeButton = "Switch to Mandelbrot Set";

    textWidth = ImGui::CalcTextSize(modeButton.c_str()).x;
    ImGui::SetCursorPosX(125 - textWidth / 2);

    if (ImGui::Button(modeButton.c_str())) mode = !mode;

    ImGui::End();
}

void Gui::renderGUI() {
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    //ImGui::ShowDemoWindow();
    render();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // Update viewports
    GLFWwindow* backup_current_context = glfwGetCurrentContext();
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    glfwMakeContextCurrent(backup_current_context);
}

void Gui::cleanup() {
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}