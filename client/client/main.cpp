#include "tests.h"







int main() {


    Test t;

    //all successful
    t.test1();
    printf("\n}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}\n");
    //unsuccessful login forbbiden mail addres
    t.test2();
    printf("\n}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}n");
    //wrong password
    t.test3();
    printf("\n}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}\n");
    t.test4();


    return 0;
}
