#include "VDAString.hh"
using namespace vda;

int main(int argc, char **argv)
{
    //  nteste = std::make_shared<VDAString>();
    //  VDAString *nteste = new VDAString();
    auto nteste = std::make_unique<VDAString>();
    nteste->setString("testes2");
    printf("Hello World:%s\n", nteste->getString());
    // delete nteste;
    //  printf("obj{%s}", obj1->getString());
    return 0;
};