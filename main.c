#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include "plugin.h"

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
   typedef char* (*name_func)();
   typeof (get_name) *fn = dlsym(plugin_handle, "get_name");
   char *error = dlerror();
   if (error != NULL) {
      fprintf(stderr, "Failed to find plugin name function: %s\n", error);
      exit(1);
   }

   /* output the result of calling the loaded function */
   printf("plugin name: %s\n", fn());
   if (dlclose(plugin_handle) != 0) {
      fprintf(stderr, "Failed to close plugin handle: %s\n", dlerror());
      exit(1);
   }
}
