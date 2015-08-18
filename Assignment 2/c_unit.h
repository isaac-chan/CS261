/*	c_unit.h : A lightweight unit test struct
	AND some simple functions to process unit test results
 */
#ifndef C_UNIT_H_INCLUDED
#define C_UNIT_H_INCLUDED 1

struct UnitTestResult {
	char* testName;
	char* errMsg; /* holds an informative string about what happened */
	int success; /* really a boolean, but encodes whether or not the test succeeded */
	int testNum; /* just for better output formatting, we store the test number */
};

/*	this line will allow us to refer to this type as simply "UnitTestResult."
	Note that normally, we would need to put struct in front of it.
 */
typedef struct UnitTestResult UnitTestResult;

void initTestResult(UnitTestResult* result, int testNumber, char* unitTestName)
{
	result->success = 0;
	result->testNum = testNumber;
	result->testName = unitTestName;
	result->errMsg = "Test Not Written";
}

void printResults(UnitTestResult* testResults)
{
	if(testResults->success)
		printf("[ Passed ]");
	else
		printf("[*FAILED*]");
		
	printf("\tTest %i\t\t%s\n", testResults->testNum, testResults->testName);
	
	if(testResults->success == 0)
		printf("\t--> ERROR:\t%s\n", testResults->errMsg);
}

#endif
