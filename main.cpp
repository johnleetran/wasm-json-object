#include <iostream>
#include <string>
#if __EMSCRIPTEN__
#include "emscripten/bind.h"
#include "emscripten/emscripten.h"
#include "emscripten/val.h"
#endif //__EMSCRIPTEN__

std::string print_json(const emscripten::val &jsobj)
{
    if (jsobj.isString())
    {
        return jsobj.as<std::string>();
    }
    emscripten::val result = emscripten::val::global("JSON")
                                 .call<emscripten::val>("stringify", jsobj);
    if (result.isUndefined())
    {
        return "";
    }
    return result.as<std::string>();
}

// only works with {s : string, i: int, f: float}
void parse_json(const emscripten::val &jsobj)
{
    std::string s = jsobj["s"].as<std::string>();
    int i = jsobj["i"].as<int>();
    float f = jsobj["f"].as<float>();

    std::cout << " s: " << s << 
                 " i: " << i << 
                 " f: " << f << std::endl; 
}

emscripten::val return_json()
{
    emscripten::val jsobj = emscripten::val::object();
    emscripten::val nest0 = emscripten::val::object();
    nest0.set("myNum", 1);
    nest0.set("myStr", "blah");
    jsobj.set("nest0", nest0);

    return jsobj;
}

void isitup()
{
    std::cout << "si" << std::endl;
}

int main(int argc, char *argv[])
{
    std::cout << "hello" << std::endl;
    return 0;
}

#if __EMSCRIPTEN__
EMSCRIPTEN_BINDINGS(json_object){
    emscripten::function("isitup", &isitup);
    emscripten::function("print_json", &print_json);
    emscripten::function("return_json", &return_json);
    emscripten::function("parse_json", &parse_json);
}
#endif //__EMSCRIPTEN__