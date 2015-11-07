#include <stdio.h>
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

/*
 * CUnit Test Suite
 */

int setBackupStampSuite();
int getConfigFileSuite();
int getCurrenTimeSuite();    

int main() {
    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();
    
    setBackupStampSuite();
    getConfigFileSuite();
    getCurrenTimeSuite();

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}

