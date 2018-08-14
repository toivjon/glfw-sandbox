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
  return 0;
}
