//
// Created by demid on 24.06.19.
//

#include "general.h"
#include <string>


class Foo{
public:
    void set(){
        i = 20;
    }
    int i = 10;
    std::string name = "main";
};

void global_initialize_cpp(){
   Foo templ_obj;
   templ_obj.set();
}
