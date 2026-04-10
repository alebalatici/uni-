#include <stdio.h>
#include <stdlib.h>
#include "tests/tests_domain.h"
#include "tests/tests_mylist.h"
#include "tests/tests_service.h"
#include "ui/console.h"
int main(void) {
    test_all_domain();
    test_all_mylist();
    test_all_service();
    run();
    return 0;
}