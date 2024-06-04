
#include <Windows.h>
#include <math.h>

#include <GL/glew.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <stdio.h>
#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>

#include "Memory.h"
#include "Helpers.h"
#include "offsets.h"
#include "visuals.h"
#include "features.h"
#include "aimbot.h"
#include "options.h"
#include "globals.h"

void setImguiStyle() {
    auto& colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_WindowBg] = ImVec4{ 0.1f, 0.1f, 0.13f, 1.0f };
    colors[ImGuiCol_MenuBarBg] = ImVec4{ 0.16f, 0.16f, 0.21f, 1.0f };

    // Border
    colors[ImGuiCol_Border] = ImVec4{ 0.44f, 0.37f, 0.61f, 0.29f };
    colors[ImGuiCol_BorderShadow] = ImVec4{ 0.0f, 0.0f, 0.0f, 0.24f };

    // Text
    colors[ImGuiCol_Text] = ImVec4{ 1.0f, 1.0f, 1.0f, 1.0f };
    colors[ImGuiCol_TextDisabled] = ImVec4{ 0.5f, 0.5f, 0.5f, 1.0f };

    // Headers
    colors[ImGuiCol_Header] = ImVec4{ 0.13f, 0.13f, 0.17, 1.0f };
    colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.19f, 0.2f, 0.25f, 1.0f };
    colors[ImGuiCol_HeaderActive] = ImVec4{ 0.16f, 0.16f, 0.21f, 1.0f };

    // Buttons
    colors[ImGuiCol_Button] = ImVec4{ 0.13f, 0.13f, 0.17, 1.0f };
    colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.19f, 0.2f, 0.25f, 1.0f };
    colors[ImGuiCol_ButtonActive] = ImVec4{ 0.16f, 0.16f, 0.21f, 1.0f };
    colors[ImGuiCol_CheckMark] = ImVec4{ 0.74f, 0.58f, 0.98f, 1.0f };

    // Popups
    colors[ImGuiCol_PopupBg] = ImVec4{ 0.1f, 0.1f, 0.13f, 0.92f };

    // Slider
    colors[ImGuiCol_SliderGrab] = ImVec4{ 0.44f, 0.37f, 0.61f, 0.54f };
    colors[ImGuiCol_SliderGrabActive] = ImVec4{ 0.74f, 0.58f, 0.98f, 0.54f };

    // Frame BG
    colors[ImGuiCol_FrameBg] = ImVec4{ 0.13f, 0.13, 0.17, 1.0f };
    colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.19f, 0.2f, 0.25f, 1.0f };
    colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.16f, 0.16f, 0.21f, 1.0f };

    // Tabs
    colors[ImGuiCol_Tab] = ImVec4{ 0.16f, 0.16f, 0.21f, 1.0f };
    colors[ImGuiCol_TabHovered] = ImVec4{ 0.24, 0.24f, 0.32f, 1.0f };
    colors[ImGuiCol_TabActive] = ImVec4{ 0.2f, 0.22f, 0.27f, 1.0f };
    colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.16f, 0.16f, 0.21f, 1.0f };
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.16f, 0.16f, 0.21f, 1.0f };

    // Title
    colors[ImGuiCol_TitleBg] = ImVec4{ 0.16f, 0.16f, 0.21f, 1.0f };
    colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.16f, 0.16f, 0.21f, 1.0f };
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.16f, 0.16f, 0.21f, 1.0f };

    // Scrollbar
    colors[ImGuiCol_ScrollbarBg] = ImVec4{ 0.1f, 0.1f, 0.13f, 1.0f };
    colors[ImGuiCol_ScrollbarGrab] = ImVec4{ 0.16f, 0.16f, 0.21f, 1.0f };
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4{ 0.19f, 0.2f, 0.25f, 1.0f };
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4{ 0.24f, 0.24f, 0.32f, 1.0f };

    // Seperator
    colors[ImGuiCol_Separator] = ImVec4{ 0.44f, 0.37f, 0.61f, 1.0f };
    colors[ImGuiCol_SeparatorHovered] = ImVec4{ 0.74f, 0.58f, 0.98f, 1.0f };
    colors[ImGuiCol_SeparatorActive] = ImVec4{ 0.84f, 0.58f, 1.0f, 1.0f };

    // Resize Grip
    colors[ImGuiCol_ResizeGrip] = ImVec4{ 0.44f, 0.37f, 0.61f, 0.29f };
    colors[ImGuiCol_ResizeGripHovered] = ImVec4{ 0.74f, 0.58f, 0.98f, 0.29f };
    colors[ImGuiCol_ResizeGripActive] = ImVec4{ 0.84f, 0.58f, 1.0f, 0.29f };

    auto& style = ImGui::GetStyle();
    style.TabRounding = 4;
    style.ScrollbarRounding = 9;
    style.WindowRounding = 7;
    style.GrabRounding = 3;
    style.FrameRounding = 3;
    style.PopupRounding = 4;
    style.ChildRounding = 4;
}

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

int main(int, char**)
{
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    const char* glsl_version = "#version 130";

    GLFWmonitor* Monitor = glfwGetPrimaryMonitor();
    if (!Monitor) {
        return 1;
    }

    globals::screenWidth = glfwGetVideoMode(Monitor)->width;
    globals::screenHeight = glfwGetVideoMode(Monitor)->height;

    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    glfwWindowHint(GLFW_FLOATING, true);
    glfwWindowHint(GLFW_RESIZABLE, false);
    glfwWindowHint(GLFW_MAXIMIZED, true);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, true);

    // Create window with graphics context
    GLFWwindow* window = glfwCreateWindow(globals::screenWidth, globals::screenHeight, "External overlay", nullptr, nullptr);
    if (window == nullptr)
        return 1;

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.Fonts->AddFontFromFileTTF("C:/dlls/fonts/onest-regular.ttf", 16);
    io.FontDefault = io.Fonts->AddFontFromFileTTF("C:/dlls/fonts/onest-regular.ttf", 16);

    // Setup Dear ImGui style
    setImguiStyle();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    Memory mem(L"ac_client.exe");
    uintptr_t Module = mem.GetModuleAddress(L"ac_client.exe");

    if (Module == NULL) {
        return 0;
    }

    while (!glfwWindowShouldClose(window))
    {
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        glClear(GL_COLOR_BUFFER_BIT);

        if (GetAsyncKeyState(VK_INSERT) &1) {
            menu::bMenuVisible = !menu::bMenuVisible;
            if (menu::bMenuVisible) {
                ShowMenu(window);
            }
            else {
                HideMenu(window);
            }
        }

        //DRAW HERE
        if (menu::bMenuVisible) {
            if (ImGui::BeginTabBar("")) {   
                if (ImGui::BeginTabItem("ESP")) {
                    ImGui::Checkbox("Draw lines", &menu::bEnableLines);
                    ImGui::Checkbox("Draw boxes", &menu::bEnableBoxes);
                    ImGui::Checkbox("Draw health", &menu::bEnableHealth);
                    ImGui::Checkbox("Team Visible", &menu::bShowTeam);
                    ImGui::EndTabItem();
                }

                if (ImGui::BeginTabItem("Aim")) {
                    ImGui::Checkbox("Aimbot", &menu::bEnableAim);
                    ImGui::Checkbox("Friendly fire", &menu::bFriendlyFire);
                    ImGui::Checkbox("Smoothness", &menu::bSmooth);
                    ImGui::SliderFloat("Smooth delay", &options::smoothness, 1.0f, 50.0f, "%.1f", ImGuiSliderFlags_AlwaysClamp);
                    ImGui::Checkbox("FOV", &menu::bFOV);
                    ImGui::SliderFloat("FOV Circle", &options::fovCircle, 1.0f, 300.0f, "%.1f", ImGuiSliderFlags_AlwaysClamp);
                    ImGui::EndTabItem();
                }

                if (ImGui::BeginTabItem("Misc")) {
                    ImGui::Checkbox("No recoil", &menu::bNoRecoil);
                    ImGui::Checkbox("No firerate", &menu::bFireRate);
                    ImGui::Checkbox("Infinite ammo", &menu::bInfiniteAmmo);
                    ImGui::Checkbox("No knockback", &menu::bNoGunKnockback);
                    ImGui::EndTabItem();
                }

                if (ImGui::BeginTabItem("Fun")) {
                    ImGui::Checkbox("Trip", &menu::bTrip);
                    ImGui::EndTabItem();
                }

                ImGui::EndTabBar();
            }

            if (ImGui::Button("Exit")) {
                return 0;
            }
        }

        uintptr_t localPlayer = mem.Read<uintptr_t>(Module + offsets::localPlayer);
        uintptr_t entityList = mem.Read<uintptr_t>(Module + offsets::entityList);

        glLoadIdentity();

        drawEsp(mem, localPlayer, entityList);

        if (menu::bEnableAim && (GetAsyncKeyState(VK_RBUTTON) & 0x8000)) {
            aimEnable(mem, localPlayer, entityList);
        }

        if (menu::bFOV) {
            drawFovCircle();
        }

        if (menu::bFireRate && !toggled::noFireRate) {
            noFireRate(mem, true);
            toggled::noFireRate = !toggled::noFireRate;
        }
        else if (!menu::bFireRate && toggled::noFireRate){
            noFireRate(mem, false);
            toggled::noFireRate = !toggled::noFireRate;
        }

        if (menu::bTrip && !toggled::trip) {
            trip(mem, true);
            toggled::noFireRate = !toggled::trip;
        }
        else if (!menu::bTrip && toggled::trip) {
            trip(mem, false);
            toggled::trip = !toggled::trip;
        }

        if (menu::bNoRecoil && !toggled::noRecoil) {
            noRecoil(mem, true);
            toggled::noRecoil = !toggled::noRecoil;
        }
        else if (!menu::bNoRecoil && toggled::noRecoil) {
            noRecoil(mem, false);
            toggled::noRecoil = !toggled::noRecoil;
        }

        if (menu::bInfiniteAmmo && !toggled::infiniteAmmo) {
            infAmmo(mem, true);
            toggled::infiniteAmmo = !toggled::infiniteAmmo;
        }
        else if (!menu::bInfiniteAmmo && toggled::infiniteAmmo) {
            infAmmo(mem, false);
            toggled::infiniteAmmo = !toggled::infiniteAmmo;
        }

        if (menu::bNoGunKnockback && !toggled::noGunKnockback) {
            noGunKnockback(mem, true);
            toggled::noGunKnockback = !toggled::noGunKnockback;
        }
        else if (!menu::bNoGunKnockback && toggled::noGunKnockback) {
            noGunKnockback(mem, false);
            toggled::noGunKnockback = !toggled::noGunKnockback;
        }

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}