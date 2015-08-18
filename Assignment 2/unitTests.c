/* unitTests.c : dynamic array unit tests */
#include <stdio.h>
#include "dynArray.h"
#include "c_unit.h"

void testInitDynArr(UnitTestResult* result)
{
    /* declare (and maybe initialize) variables */
    int capacity = 183;
    
    /* perform the test */
    DynArr myAry;
    initDynArr(&myAry, capacity);
    
    /* check return values and postconditions */
    if(myAry.size != 0)
        result->errMsg = "Size is not zero";
    else if(myAry.capacity != capacity)
        result->errMsg = "Capacity is wrong";
    else if(myAry.data == 0)
        result->errMsg = "Data is not allocated";
    else
        result->success = 1;
}

void testNewDynArr(UnitTestResult* result)
{
    int capacity = 629;
    
    DynArr* myAry = newDynArr(capacity);
    /* will leak memory, but cleaning up complicates the test... */
    
    if(myAry->size != 0)
        result->errMsg = "Size is not zero";
    else if(myAry->capacity != capacity)
        result->errMsg = "Capacity is wrong";
    else if(myAry->data == 0)
        result->errMsg = "Data is not allocated";
    else
        result->success = 1;
}

void testFreeDynArr(UnitTestResult* result)
{
    int capacity = 19172;
    
    DynArr* myAry = newDynArr(capacity);
    freeDynArr(myAry);
    
    if(myAry->size != 0)
        result->errMsg = "Size is not zero";
    else if(myAry->capacity != 0)
        result->errMsg = "Capacity is wrong";
    else if(myAry->data != 0)
        result->errMsg = "Data is still allocated";
    else
        result->success = 1;
}

void testDynArrSetCapacity(UnitTestResult* result)
{
    int initialCapacity = 9237;
    int finalCapacity = 459;
    
    DynArr* myAry = newDynArr(initialCapacity);
    _dynArrSetCapacity(myAry, finalCapacity);
    
    if(myAry->size != 0)
        result->errMsg = "Size is not zero";
    else if(myAry->capacity != finalCapacity)
        result->errMsg = "Capacity is wrong";
    else if(myAry->data == 0)
        result->errMsg = "Data is not allocated";
    else
        result->success = 1;
}

void testAddDynArr(UnitTestResult* result)
{
    int capacity = 5;
    TYPE valToAdd = 12;
    
    DynArr* myAry = newDynArr(capacity);
    addDynArr(myAry, valToAdd);
    
    if(myAry->size != 1)
        result->errMsg = "Size is not one";
    else if(myAry->capacity != capacity)
        result->errMsg = "Capacity is wrong";
    else if(myAry->data[0] != valToAdd)
        result->errMsg = "Value not added";
    else
        result->success = 1;
}

void testAddDynArrResizing(UnitTestResult* result)
{
    int capacity = 2;
    TYPE firstValToAdd = 12;
    TYPE secondValToAdd = 24;
    TYPE thirdValToAdd = 36;
    
    DynArr* myAry = newDynArr(capacity);
    addDynArr(myAry, firstValToAdd);
    addDynArr(myAry, secondValToAdd);
    addDynArr(myAry, thirdValToAdd);
    
    if(myAry->size != 3)
        result->errMsg = "Size is wrong";
    else if(myAry->capacity != 2*capacity)
        result->errMsg = "Capacity is wrong";
    else if(myAry->data[0] != firstValToAdd)
        result->errMsg = "First value not added";
    else if(myAry->data[1] != secondValToAdd)
        result->errMsg = "Second value not added";
    else if(myAry->data[2] != thirdValToAdd)
        result->errMsg = "Third value not added";
    else
        result->success = 1;
}

void testGetDynArr(UnitTestResult* result)
{
    int capacity = 4;
    TYPE firstValToAdd = 734;
    TYPE secondValToAdd = 8246;
    TYPE firstValRetrieved;
    TYPE secondValRetrieved;
    
    DynArr* myAry = newDynArr(capacity);
    addDynArr(myAry, firstValToAdd);
    addDynArr(myAry, secondValToAdd);
    firstValRetrieved = getDynArr(myAry, 0);
    secondValRetrieved = getDynArr(myAry, 1);
    
    if(myAry->size != 2)
        result->errMsg = "Size is wrong";
    else if(firstValRetrieved != firstValToAdd)
        result->errMsg = "First value not correct";
    else if(secondValRetrieved != secondValToAdd)
        result->errMsg = "Second value not correct";
    else
        result->success = 1;
}

void testPutDynArr(UnitTestResult* result)
{
    int capacity = 4;
    TYPE firstValToAdd = 5924;
    TYPE secondValToAdd = 9842;
    TYPE firstValRetrieved;
    
    TYPE valToPut = 965;
    int putIdx = 1;
    TYPE putIdxRetrieved;
    
    DynArr* myAry = newDynArr(capacity);
    addDynArr(myAry, firstValToAdd);
    addDynArr(myAry, secondValToAdd);
    putDynArr(myAry, putIdx, valToPut);
    firstValRetrieved = getDynArr(myAry, 0);
    putIdxRetrieved = getDynArr(myAry, putIdx);
    
    if(myAry->size != 2)
        result->errMsg = "Size is wrong";
    else if(firstValRetrieved != firstValToAdd)
        result->errMsg = "First value not correct";
    else if(putIdxRetrieved != valToPut)
        result->errMsg = "Put value not correct";
    else
        result->success = 1;
}

void testSwapDynArr(UnitTestResult* result)
{
    int capacity = 4;
    TYPE firstValToAdd = 7415;
    TYPE secondValToAdd = 8275;
    TYPE thirdValToAdd = 9072;
    TYPE firstValRetrieved;
    TYPE secondValRetrieved;
    
    DynArr* myAry = newDynArr(capacity);
    addDynArr(myAry, firstValToAdd);
    addDynArr(myAry, secondValToAdd);
    addDynArr(myAry, thirdValToAdd);
    swapDynArr(myAry, 0, 1);
    firstValRetrieved = getDynArr(myAry, 0);
    secondValRetrieved = getDynArr(myAry, 1);
    
    if(myAry->size != 3)
        result->errMsg = "Size is wrong";
    else if(firstValRetrieved != secondValToAdd)
        result->errMsg = "First value not correct (swap failed)";
    else if(secondValRetrieved != firstValToAdd)
        result->errMsg = "Second value not correct (swap failed)";
    else
        result->success = 1;
}

void testRemoveAtDynArr(UnitTestResult* result)
{
    int capacity = 4;
    TYPE firstValToAdd = 1045;
    TYPE secondValToAdd = 73045;
    TYPE firstValRetrieved;
    
    DynArr* myAry = newDynArr(capacity);
    addDynArr(myAry, firstValToAdd);
    addDynArr(myAry, secondValToAdd);
    removeAtDynArr(myAry, 0);
    firstValRetrieved = getDynArr(myAry, 0);
    
    if(myAry->size != 1)
        result->errMsg = "Size is wrong";
    else if(myAry->capacity != capacity)
        result->errMsg = "First value not correct (remove failed)";
    else
        result->success = 1;
}

void testIsEmptyDynArr(UnitTestResult* result)
{
    int capacity = 4;
    TYPE firstValToAdd = 1563;
    TYPE secondValToAdd = 3946;
    int firstSampleEmpty;
    int secondSampleEmpty;
    int thirdSampleEmpty;
    
    DynArr* myAry = newDynArr(capacity);
    firstSampleEmpty = isEmptyDynArr(myAry);
    
    addDynArr(myAry, firstValToAdd);
    addDynArr(myAry, secondValToAdd);
    removeAtDynArr(myAry, 1);
    secondSampleEmpty = isEmptyDynArr(myAry);
    removeAtDynArr(myAry, 0);
    thirdSampleEmpty = isEmptyDynArr(myAry);
    
    if(myAry->size != 0)
        result->errMsg = "Size is wrong";
    else if(firstSampleEmpty != 1)
        result->errMsg = "Array not empty at first sample";
    else if(secondSampleEmpty != 0)
        result->errMsg = "Array empty at second sample";
    else if(thirdSampleEmpty != 1)
        result->errMsg = "Array not empty at THIRD sample";
    else
        result->success = 1;
}

void testPushDynArr(UnitTestResult* result)
{
    int capacity = 2;
    TYPE firstValToPush = 76321;
    TYPE secondValToPush = 8102;
    TYPE thirdValToPush = 3014;
    
    DynArr* myAry = newDynArr(capacity);
    pushDynArr(myAry, firstValToPush);
    pushDynArr(myAry, secondValToPush);
    pushDynArr(myAry, thirdValToPush);
    
    if(myAry->size != 3)
        result->errMsg = "Size is wrong";
    else if(myAry->capacity != 2*capacity)
        result->errMsg = "Capacity is wrong";
    else if(myAry->data[0] != firstValToPush)
        result->errMsg = "First value not pushed";
    else if(myAry->data[1] != secondValToPush)
        result->errMsg = "Second value not pushed";
    else if(myAry->data[2] != thirdValToPush)
        result->errMsg = "Third value not pushed";
    else
        result->success = 1;
}

void testTopDynArr(UnitTestResult* result)
{
    int capacity = 2;
    TYPE firstValToPush = 1325;
    TYPE secondValToPush = 1084;
    TYPE firstTopSample;
    TYPE secondTopSample;
    
    DynArr* myAry = newDynArr(capacity);
    pushDynArr(myAry, firstValToPush);
    firstTopSample = topDynArr(myAry);
    pushDynArr(myAry, secondValToPush);
    secondTopSample = topDynArr(myAry);
    
    if(myAry->size != 2)
        result->errMsg = "Size is wrong";
    else if(myAry->capacity != capacity)
        result->errMsg = "Capacity is wrong";
    else if(firstTopSample != firstValToPush)
        result->errMsg = "Top incorrect at Sample 1";
    else if(secondTopSample != secondValToPush)
        result->errMsg = "Top incorrect at Sample 2";
    else
        result->success = 1;
}

void testPopDynArr(UnitTestResult* result)
{
    int capacity = 2;
    TYPE firstValToPush = 7381;
    TYPE secondValToPush = 63913;
    TYPE firstTopSample;
    TYPE secondTopSample;
    
    DynArr* myAry = newDynArr(capacity);
    pushDynArr(myAry, firstValToPush);
    pushDynArr(myAry, secondValToPush);
    firstTopSample = topDynArr(myAry);
    popDynArr(myAry);
    secondTopSample = topDynArr(myAry);
    popDynArr(myAry);
    
    if(myAry->size != 0)
        result->errMsg = "Size is wrong";
    else if(myAry->capacity != capacity)
        result->errMsg = "Capacity is wrong";
    else if(firstTopSample != secondValToPush)
        result->errMsg = "Top incorrect at Sample 1";
    else if(secondTopSample != firstValToPush )
        result->errMsg = "Top incorrect at Sample 2";
    else
        result->success = 1;
}

void testContainsDynArr(UnitTestResult* result)
{
    /* FIXME you will write this function */
    int capacity = 2;
    TYPE valueToFind = 42;
    int testResult;
    DynArr* myAry = newDynArr(capacity);
    addDynArr(myAry, valueToFind);
    testResult = containsDynArr(myAry, valueToFind);
    
    if(myAry->size == 0)
        result->errMsg = "Size is zero";
    else if(myAry->capacity == 0)
        result->errMsg = "Capacity is wrong";
    else if(myAry->data == 0)
        result->errMsg = "Data is not allocated";
    else if(testResult == -1)
        result->errMsg = "Number is not found";
    else
        result->success = 1;
}

void testRemoveDynArr(UnitTestResult* result)
{
    /* FIXME you will write this function */
    int capacity = 2;
    TYPE firstValToAdd = 1045;
    TYPE secondValToAdd = 73045;
    
    DynArr* myAry = newDynArr(capacity);
    addDynArr(myAry, firstValToAdd);
    addDynArr(myAry, secondValToAdd);
    removeDynArr(myAry, firstValToAdd);
    
    if(myAry->size != 1)
        result->errMsg = "Size is wrong";
    else if(myAry->capacity != capacity)
        result->errMsg = "First value not correct (remove failed)";
    else
        result->success = 1;
        
    
}

/*******************************************************************
 Test Bundling Functions
 *******************************************************************/
void allDynArrBasicFunctionTests()
{
    int testNum = 1;
    /*	create a container to manage test results */
    /*	note that this is a stack variable, so despite the fact that
     we will use & to pass a pointer to it into functions, we
     DO NOT need to free() it.
     */
    UnitTestResult testResults;
    
    printf("\nTesting Basic Dynamic Array Functions\n****************************************\n");
    
    /* set up the unit test results container for the next test */
    initTestResult(&testResults, testNum++, "testInitDynArr");
    /* perform the test */
    testInitDynArr(&testResults);
    /* show us the results from the test */
    printResults(&testResults);
    
    /* Start second test */
    initTestResult(&testResults, testNum++, "testNewDynArr");
    testNewDynArr(&testResults);
    printResults(&testResults);
    
    initTestResult(&testResults, testNum++, "testFreeDynArr");
    testFreeDynArr(&testResults);
    printResults(&testResults);
    
    initTestResult(&testResults, testNum++, "testDynArrSetCapacity");
    testDynArrSetCapacity(&testResults);
    printResults(&testResults);
    
    initTestResult(&testResults, testNum++, "testAddDynArr");
    testAddDynArr(&testResults);
    printResults(&testResults);
    
    initTestResult(&testResults, testNum++, "testAddDynArrResizing");
    testAddDynArrResizing(&testResults);
    printResults(&testResults);
    
    initTestResult(&testResults, testNum++, "testGetDynArr");
    testGetDynArr(&testResults);
    printResults(&testResults);
    
    initTestResult(&testResults, testNum++, "testPutDynArr");
    testPutDynArr(&testResults);
    printResults(&testResults);
    
    initTestResult(&testResults, testNum++, "testSwapDynArr");
    testSwapDynArr(&testResults);
    printResults(&testResults);
    
    initTestResult(&testResults, testNum++, "testRemoveAtDynArr");
    testRemoveAtDynArr(&testResults);
    printResults(&testResults);
}

void allDynArrStackFunctionTests()
{
    int testNum = 1;
    UnitTestResult testResults;
    printf("\nTesting Stack Dynamic Array Functions\n****************************************\n");
    
    initTestResult(&testResults, testNum++, "testIsEmptyDynArr");
    testIsEmptyDynArr(&testResults);
    printResults(&testResults);
    
    initTestResult(&testResults, testNum++, "testPushDynArr");
    testPushDynArr(&testResults);
    printResults(&testResults);
    
    initTestResult(&testResults, testNum++, "testTopDynArr");
    testTopDynArr(&testResults);
    printResults(&testResults);
    
    initTestResult(&testResults, testNum++, "testPopDynArr");
    testPopDynArr(&testResults);
    printResults(&testResults);
}

void allDynArrBagFunctionTests()
{
    int testNum = 1;
    UnitTestResult testResults;
    printf("\nTesting Bag Dynamic Array Functions\n****************************************\n");
    
    initTestResult(&testResults, testNum++, "testContainsDynArr");
    testContainsDynArr(&testResults);
    printResults(&testResults);
    
    initTestResult(&testResults, testNum++, "testRemoveDynArr");
    testRemoveDynArr(&testResults);
    printResults(&testResults);
}

/*******************************************************************
 Main Function Definition
 ********************************************************************/
int main()
{	
    allDynArrBasicFunctionTests();
    
    allDynArrStackFunctionTests();
    
    allDynArrBagFunctionTests();
    
    return 0;
}