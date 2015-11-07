/*
 * File:   backuptest.c
 * Author: Alex de Kruijff <alex.de.kruijff@MazarineBlue.org>
 *
 * Created on Nov 6, 2015, 7:08:05 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <unistd.h>

#include "../backup-util.h"

/*
 * CUnit Test Suite
 */

int init_getConfigFileSuite(void) {
    return 0;
}

int clean_getConfigFileSuite(void) {
    return 0;
}

char *strset(char *str, int c, size_t n) {
    int max = strlen(str);
    char *ret = memset(str, c, n);
    str[n] = 0;
    return ret;
}

void getConfigFile_ZeroSize_ReturnsSucces() {
    int status = getConfigFile(NULL, 0, NULL, NULL);
    CU_ASSERT_EQUAL(0, status);
}

void getConfigFile_NullDestination_ReturnsError() {
    int status = getConfigFile(NULL, 1, NULL, NULL);
    CU_ASSERT_EQUAL(1, status);
}

void getConfigFile_DestinationToSmallForPrefix_ReturnsError() {
    char buffer[0];
    int status = getConfigFile(buffer, sizeof(buffer), "foo-", NULL);
    CU_ASSERT_EQUAL(2, status);
}

void getConfigFile_DestinationToSmallForDot_ReturnsError() {
    char buffer[0];
    int status = getConfigFile(buffer, sizeof(buffer), NULL, NULL);
    CU_ASSERT_EQUAL(3, status);
}

void getConfigFile_DestinationToSmallForHostfile_ReturnsError() {
    char buffer[1];
    int status = getConfigFile(buffer, sizeof(buffer), NULL, NULL);
    CU_ASSERT_EQUAL(4, status);
}

void getConfigFile_DestinationToSmallForPostfix_ReturnsError() {
    char buffer[_SC_HOST_NAME_MAX], postfix[_SC_HOST_NAME_MAX + 1];
    strset(postfix, 'a', _SC_HOST_NAME_MAX);
    int status = getConfigFile(buffer, sizeof(buffer), NULL, postfix);
    CU_ASSERT_EQUAL(5, status);
}

void getConfigFile_LargeDestination_ReturnsSuccess() {
    char buffer1[_SC_HOST_NAME_MAX + 512], buffer2[_SC_HOST_NAME_MAX + 512];
    int status1 = getConfigFile(buffer1, sizeof(buffer1), NULL, NULL);
    int status2 = getConfigFile(buffer2, sizeof(buffer2), "foo-", "-foo");
    CU_ASSERT_EQUAL(0, status1);
    CU_ASSERT_EQUAL(0, status2);
    CU_ASSERT_EQUAL(8, strlen(buffer2) - strlen(buffer1));
    CU_ASSERT_EQUAL(0, memcmp(buffer2, "foo-", 4));
    CU_ASSERT_EQUAL(0, memcmp(buffer2 + 4, buffer1, strlen(buffer1)));
    CU_ASSERT_EQUAL(0, memcmp(buffer2 + 4 + strlen(buffer1), "-foo", 4));
}

int getConfigFileSuite() {
    /* Add a suite to the registry */
    CU_pSuite pSuite = CU_add_suite("getConfigFile test", init_getConfigFileSuite, clean_getConfigFileSuite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    if ((NULL == CU_add_test(pSuite, "getConfigFile_ZeroSize_ReturnsSucces", getConfigFile_ZeroSize_ReturnsSucces)) ||
            (NULL == CU_add_test(pSuite, "getConfigFile_NullDestination_ReturnsError", getConfigFile_NullDestination_ReturnsError)) ||
            (NULL == CU_add_test(pSuite, "getConfigFile_DestinationToSmallForPrefix_ReturnsError", getConfigFile_DestinationToSmallForPrefix_ReturnsError)) ||
            (NULL == CU_add_test(pSuite, "getConfigFile_DestinationToSmallForDot_ReturnsError", getConfigFile_DestinationToSmallForDot_ReturnsError)) ||
            (NULL == CU_add_test(pSuite, "getConfigFile_DestinationToSmallForHostfile_ReturnsError", getConfigFile_DestinationToSmallForHostfile_ReturnsError)) ||
            (NULL == CU_add_test(pSuite, "getConfigFile_DestinationToSmallForPostfix_ReturnsError", getConfigFile_DestinationToSmallForPostfix_ReturnsError)) ||
            (NULL == CU_add_test(pSuite, "getConfigFile_LargeDestination_ReturnsSuccess", getConfigFile_LargeDestination_ReturnsSuccess))) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    return CU_get_error();
}
