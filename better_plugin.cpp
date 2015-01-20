#include "plugin.h"

using namespace std;

class better_plugin : public plugin {
   private:
      string mName;
   public:
      better_plugin();
      string name();
};

better_plugin::better_plugin() : mName("better") {
}

string better_plugin::name() {
   return mName;
}

shared_ptr<plugin> get_plugin() {
   return make_shared<better_plugin>();
}
