/**
 * @file main.cpp
 * @brief Program entry point for the system information application.
 */

#include "application.h"

/**
 * @brief Application entry point.
 *
 * Constructs an Application instance, which creates the window, starts the
 * background data-collection thread and runs the main loop until the window
 * is closed. All resource cleanup happens in the Application destructor.
 *
 * @return Process exit status (always 0).
 */
int main()
{
  Application app;
  return 0;
}
