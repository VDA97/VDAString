#include "VDAString.hh"
using namespace vda;
int main(int argc, char **argv)
{
    auto nteste = std::make_shared<VDAString>();
    nteste->setString("testes2");
    printf("Hello World:%s\n", nteste->getString());
    //  printf("obj{%s}", obj1->getString());
    return 0;
};