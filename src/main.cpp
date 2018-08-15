#include <cassert>
#include <cstdio>
#include <cstdlib>

#include <GLFW/glfw3.h>

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

  // specify that we want to use modern OpenGL.
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // create the main window for the application.
  sWindow = glfwCreateWindow(800, 600, "GLFW", NULL, NULL);
  assert(sWindow != NULL);

  // activate the GL context from the window.
  glfwMakeContextCurrent(sWindow);

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
