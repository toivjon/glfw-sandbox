#include <cstdio>
#include <cstdlib>

#include <GLFW/glfw3.h>

// ============================================================================
// FUNCTION PROTOTYPES
// ============================================================================

static void init();
static void shutdown();

// ============================================================================
// Initialize all necessary components to start the application.
// ============================================================================
static void init()
{
  printf("Initializing application\n");

  // TODO set error callback.
  // TODO initialize GLFW.
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

int main()
{
  atexit(shutdown);
  init();
  return 0;
}
