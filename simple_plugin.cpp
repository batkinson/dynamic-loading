#include "plugin.h"

using namespace std;

class simple_plugin : public plugin {
   private:
      string mName;
   public:
      simple_plugin();
      string name();
};

simple_plugin::simple_plugin() : mName("simple") {
}

string simple_plugin::name() {
   return mName;
}

shared_ptr<plugin> get_plugin() {
   return make_shared<simple_plugin>();
}
