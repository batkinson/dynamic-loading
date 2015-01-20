#include <dlfcn.h>
#include <stdio.h>
#include <iostream>
#include "plugin.h"

using namespace std;

/**
 * An example of how to dynamically load alternative versions of a function.
 * It demonstrates the basic mechanics necessary for developing a native plugin
 * capability for a program.
 */
int main(int argc, char *argv[]) {

   if (argc != 2) {
      fprintf(stderr, "Specify path to plugin (with leading './')\n");
      exit(1);
   }

   char *plugin_path = argv[1];

   /* load the specified plugin */
   void *plugin_handle = dlopen(plugin_path, RTLD_NOW);
   if (!plugin_handle) {
      fprintf(stderr, "Failed to load plugin %s: %s\n", plugin_path, dlerror());
      exit(1);
   }

   /* lookup the get_name symbol from the library */
   auto create_plugin = reinterpret_cast<plugin_maker>(dlsym(plugin_handle, "get_plugin"));
   char *error = dlerror();
   if (error != NULL) {
      fprintf(stderr, "Failed to find plugin name function: %s\n", error);
      exit(1);
   }

   /* 
      output the result of calling the loaded function
      extra block ensures destructors called before being unloaded 
   */
   {
      shared_ptr<plugin> plugin = create_plugin();
      cout << "plugin name: " << plugin->name() << endl;
   } 

   if (dlclose(plugin_handle) != 0) {
      fprintf(stderr, "Failed to close plugin handle: %s\n", dlerror());
      exit(1);
   }
}
