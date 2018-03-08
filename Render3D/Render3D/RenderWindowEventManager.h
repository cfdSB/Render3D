#ifndef RENDERWINDOWEVENTMANAGER_H
#define RENDERWINDOWEVENTMANAGER_H

#include "RenderWindow.h"
#include "View.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void scroll_callback(GLFWwindow* wnd, double xoffset, double yoffset);
void cursor_position_callback(GLFWwindow* window, double xPos, double yPos);
void mouse_button_callback(GLFWwindow* wnd, int button, int action, int mods);

#endif