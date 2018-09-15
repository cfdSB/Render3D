#ifndef RENDERWINDOWEVENTMANAGER_H
#define RENDERWINDOWEVENTMANAGER_H

#include "RenderWindow.h"
#include "View.h"
#include "BoundingBox.h"
#include "GeometryUtility.h"

class RenderWindow; //forward definition
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void scroll_callback(GLFWwindow* wnd, double xoffset, double yoffset);
void cursor_position_callback(GLFWwindow* window, double xPos, double yPos);
void mouse_button_callback(GLFWwindow* wnd, int button, int action, int mods);
void calculatePositionChange(GLFWwindow* wnd, double xPos, double yPos, double* xPosChange, double* yPosChange);
void key_callback(GLFWwindow* wnd, int key, int scancode, int action, int mods);
float findZoomOffDistance(const BoundingBox* box);
void calculateViewingVolume(const RenderWindow* window, float* volume);
void computeClickLocation(RenderWindow *window, double xPos, double yPos);
#endif
