#include "pinlog.h"

int main(){
    char* f = "Brian";
    pinlog(ERROR, "Hello there %s", f);

    return 0;
}