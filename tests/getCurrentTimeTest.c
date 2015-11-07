#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <unistd.h>

#include "../backup-util.h"

/*
 * CUnit Test Suite
 */

int init_getCurrenTimeSuite(void) {
    return 0;
}

int clean_getCurrenTimeSuite(void) {
    return 0;
}

void getCurrentTime_GMT() {
    struct tm *tm = getCurrentTime(false);
    CU_ASSERT_EQUAL(0, tm->tm_gmtoff);
}

int getCurrenTimeSuite() {
    /* Add a suite to the registry */
    CU_pSuite pSuite = CU_add_suite("getCurrentTime test", init_getCurrenTimeSuite, clean_getCurrenTimeSuite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    if ((NULL == CU_add_test(pSuite, "getCurrentTime_GMT", getCurrentTime_GMT))) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    return CU_get_error();
}

