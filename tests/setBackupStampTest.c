#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <unistd.h>

#include "../backup-util.h"

const int MIN_DST_SIZE = 22;

/*
 * CUnit Test Suite
 */

int init_getBackupStampSuite(void) {
    return 0;
}

int clean_getBackupStampSuite(void) {
    return 0;
}

void setBackupStamp_NullDestination() {
    struct tm tm;
    int status = setBackupStamp(NULL, MIN_DST_SIZE, "", "", &tm);
    CU_ASSERT_EQUAL(1, status);
}

void setBackupStamp_NullBase() {
    char buffer[MIN_DST_SIZE];
    struct tm tm;
    int status = setBackupStamp(buffer, sizeof (buffer), NULL, "", &tm);
    CU_ASSERT_EQUAL(2, status);
}

void setBackupStamp_ZeroSize() {
    char buffer[MIN_DST_SIZE];
    struct tm tm;
    int status = setBackupStamp(buffer, 0, "", "", &tm);
    CU_ASSERT_EQUAL(3, status);
}

void setBackupStamp_NullHostname() {
    char buffer[MIN_DST_SIZE];
    struct tm tm;
    int status = setBackupStamp(buffer, sizeof (buffer), "", NULL, &tm);
    CU_ASSERT_EQUAL(4, status);
}

void setBackupStamp_NullTime() {
    char buffer[MIN_DST_SIZE];
    int status = setBackupStamp(buffer, sizeof (buffer), "", "", NULL);
    CU_ASSERT_EQUAL(5, status);
}

void setBackupStamp_CorrectInput() {
    char buffer[100];
    struct tm tm;
    tm.tm_year = 100;
    tm.tm_mon = 1;
    tm.tm_mday = 2;
    tm.tm_hour = 3;
    tm.tm_min = 4;
    tm.tm_sec = 5;
    int status = setBackupStamp(buffer, sizeof (buffer), "base", "host", &tm);
    CU_ASSERT_EQUAL(0, status);
    CU_ASSERT_EQUAL(0, strcmp("base/host_2000-01-02_03-04-05", buffer));
}

int setBackupStampSuite() {
    /* Add a suite to the registry */
    CU_pSuite pSuite = CU_add_suite("getBackupStamp test", init_getBackupStampSuite, clean_getBackupStampSuite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    if ((NULL == CU_add_test(pSuite, "setBackupStamp_NullDestination", setBackupStamp_NullDestination)) ||
            (NULL == CU_add_test(pSuite, "setBackupStamp_NullBase", setBackupStamp_NullBase)) ||
            (NULL == CU_add_test(pSuite, "setBackupStamp_ZeroSize", setBackupStamp_ZeroSize)) ||
            (NULL == CU_add_test(pSuite, "setBackupStamp_NullHostname", setBackupStamp_NullHostname)) ||
            (NULL == CU_add_test(pSuite, "setBackupStamp_NullTime", setBackupStamp_NullTime)) ||
            (NULL == CU_add_test(pSuite, "setBackupStamp_CorrectInput", setBackupStamp_CorrectInput))) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    return CU_get_error();
}

