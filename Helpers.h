#pragma once

void ShowMenu(GLFWwindow* Window) {
	glfwSetWindowAttrib(Window, GLFW_MOUSE_PASSTHROUGH, false);
}

void HideMenu(GLFWwindow* Window) {
	glfwSetWindowAttrib(Window, GLFW_MOUSE_PASSTHROUGH, true);
}