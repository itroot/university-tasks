#include <string>
#include <iostream>
#include <stdexcept>

#include <jsapi.h>


namespace {
    std::string usage="Usage:\n"
    "cbshell [name of file]\n";
    const uint32 maxbytes=0x1000000;
}

int main(int argc, char* argv[]) {
    if (2!=argc) {
        std::cout << usage;
    }
    JSRuntime* runtime=JS_NewRuntime(maxbytes);
    //if (NULL==runtime) throw 
}
