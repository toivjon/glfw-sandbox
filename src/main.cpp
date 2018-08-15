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
