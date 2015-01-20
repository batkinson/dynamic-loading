#pragma once
#include <string>
#include <memory>

class plugin {
public:
   virtual std::string name() = 0;
};

extern "C" std::shared_ptr<plugin> get_plugin();

typedef std::shared_ptr<plugin> (*plugin_maker)();
