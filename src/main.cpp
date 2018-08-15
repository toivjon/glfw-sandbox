#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include <glad.h>
#include <GLFW/glfw3.h>

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600

// ============================================================================
// FUNCTION PROTOTYPES
// ============================================================================

static void init();
static void shutdown();
static void handleError(int code, const char* description);
static void handleKey(GLFWwindow* window, int key, int code, int action, int mods);
static void handleMouseButton(GLFWwindow* window, int button, int action, int mods);
static void handleFramebufferResize(GLFWwindow* window, int width, int height);

// ============================================================================
// GLOBAL VARIABLES
// ============================================================================

static GLFWwindow* sWindow = nullptr;

// ============================================================================
// Initialize all necessary components to start the application.
// ============================================================================
static void init()
{
  printf("Initializing application\n");

  // define an error callback which handles GLFW errors.
  glfwSetErrorCallback(handleError);

  // initialize the GLFW framework.
  if (glfwInit() == GLFW_FALSE) {
    exit(EXIT_FAILURE);
  }

  // enumerate connected monitors and check which is the primary monitor.
  int monitorCount = 0;
  GLFWmonitor** monitors = glfwGetMonitors(&monitorCount);
  GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
  printf("Detected %d connected monitors:\n", monitorCount);
  for (auto i = 0; i < monitorCount; i++) {
    const auto monitor = monitors[i];
    auto name = glfwGetMonitorName(monitor);
    auto mode = glfwGetVideoMode(monitor);
    auto isPrimary = (monitor == primaryMonitor);
    printf("\t[%s] %s (%dx%d)\n", (isPrimary ? "x" : " "), name, mode->width, mode->height);
  }

  // specify that we want to use modern OpenGL.
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // create the main window for the application in the primary monitor.
  sWindow = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "GLFW", NULL, NULL);
  assert(sWindow != NULL);

  // move the main window into the center of the monitor.
  auto mode = glfwGetVideoMode(primaryMonitor);
  auto x = (mode->width / 2) - (WINDOW_WIDTH / 2);
  auto y = (mode->height / 2) - (WINDOW_HEIGHT / 2);
  glfwSetWindowPos(sWindow, x, y);

  // activate the GL context from the window.
  glfwMakeContextCurrent(sWindow);

  // initialize GLAD to get access to modern OpenGL functions.
  gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

  // define a callback to listen keyboard events.
  glfwSetKeyCallback(sWindow, &handleKey);

  // define a callback to listen mouse button events.
  glfwSetMouseButtonCallback(sWindow, handleMouseButton);

  // define a callback to listen for window framebuffer size changes.
  glfwSetFramebufferSizeCallback(sWindow, handleFramebufferResize);

  printf("Using GLFW (%s)\n", glfwGetVersionString());
}

// ============================================================================
// Close the application and deinitialize all initialized and reserved items.
//
// NOTE: This function is automatically called with via the atexit function.
// ============================================================================
static void shutdown()
{
  printf("Closing application\n");
  glfwDestroyWindow(sWindow);
  glfwTerminate();
}

// ============================================================================
// An error callback to listen and handle GLFW errors.
//
// @param code An GLFW specific error code.
// @param description A UTF-8 encoded string describing the error.
// ============================================================================
static void handleError(int code, const char* description)
{
  printf("GLFW error [%d]: %s\n", code, description);
  exit(EXIT_FAILURE);
}

// ============================================================================
// A key callback to listen and handle keyboard events.
//
// @param window The window that received the event.
// @param key The keyboard key that was pressed or released.
// @param code The system-specific scancode of the key.
// @param action GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT.
// @param mods Bit field describing which modifier keys were held down.
// ============================================================================
static void handleKey(GLFWwindow* window, int key, int code, int action, int mods)
{
  assert(window != nullptr);
  printf("key [key=%d, code=%d, action=%d, mods=%d]\n", key, code, action, mods);
}

// ============================================================================
// A mouse button callback to listen mouse button events.
//
// @param window The window that received the event.
// @param button The mouse button that was pressed or released.
// @param action One of GLFW_PRESS or GLFW_RELEASE.
// @param mods Bit field describing which modifier keys were hold down.
// ============================================================================
static void handleMouseButton(GLFWwindow* window, int button, int action, int mods)
{
  assert(window != nullptr);
  printf("mouse [button=%d, action=%d, mods=%d]\n", button, action, mods);
}

// ============================================================================
// A framebuffer resize callback to listen for framebuffer size changes. Useful
// to apply new size for the OpenGL viewport size whenever window framebuffer
// is being resized (e.g. on window resize or dragged between monitors).
//
// @param window The window that received the event.
// @param width The new width of the framebuffer.
// @param height The new height of the framebuffer.
// ============================================================================
static void handleFramebufferResize(GLFWwindow* window, int width, int height)
{
  assert(window != nullptr);
  printf("framebuffer [width=%d height=%d]\n", width, height);
  glViewport(0, 0, width, height);
}

// ============================================================================

int main()
{
  atexit(shutdown);
  init();
  while (!glfwWindowShouldClose(sWindow))
  {
    glClear(GL_COLOR_BUFFER_BIT);

    // TODO ... render stuff here.

    glfwSwapBuffers(sWindow);
    glfwPollEvents();
  }
  return 0;
}
