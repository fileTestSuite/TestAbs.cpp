#include <iostream>
#include <memory>
#include <filesystem>
#include <functional>
#include <sstream>

#include <stdio.h>

#include <TestAbs/TestAbs.hpp>
#include <cstdint>

IProtoTest::IProtoTest(std::string suiteName, std::string testName, std::filesystem::path filePath, int lineInFile):suiteName(suiteName), testName(testName), filePath(filePath), lineInFile(lineInFile) {}

IProtoTest::~IProtoTest() = default;

ITestCLIInitializer::ITestCLIInitializer(){};

ITestsGenerator::ITestsGenerator() {}

void ITestsGenerator::parseUserCLIArgs(ITestCLIInitializer *, int argc, const char **argv){

};

void ITestToolkit::reportError(std::string &&error){
	delayErrorMessage(std::move(error));
	assertDelayedSuccess();
};

void ITestCLIInitializer::parseCLIArgs(ITestsGenerator *tg, int argc, const char **argv){
	tg->parseUserCLIArgs(this, argc, argv);
	parseFrameworkCLIArgs(argc, argv);
};

int ITestCLIInitializer::operator()(ITestsGenerator *tg, int argc, const char **argv){
	parseCLIArgs(tg, argc, argv);
	(*tg)(this);
	auto res = runUnitTestFramework();
	return res;
}
