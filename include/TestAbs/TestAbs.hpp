#pragma once

#include <cstdint>
#include <cstdlib>
#include <string>
#include <span>
#include <memory>
#include <filesystem>

#ifdef _MSC_VER
	#define LIBTESTABS_EXPORT_API __declspec(dllexport)
	#define LIBTESTABS_IMPORT_API __declspec(dllimport)
#else
	#ifdef _WIN32
		#define LIBTESTABS_EXPORT_API [[gnu::dllexport]]
		#define LIBTESTABS_IMPORT_API [[gnu::dllimport]]
	#else
		#define LIBTESTABS_EXPORT_API __attribute__((visibility("default")))
		#define LIBTESTABS_IMPORT_API
	#endif
#endif

#ifdef LIBTESTABS_EXPORTS
	#define LIBTESTABS_API LIBTESTABS_EXPORT_API
#else
	#define LIBTESTABS_API LIBTESTABS_IMPORT_API
#endif

#ifdef TESTABS_BACKEND_EXPORTS
	#define TESTABS_BACKEND_API LIBTESTABS_EXPORT_API
#else
	#define TESTABS_BACKEND_API LIBTESTABS_IMPORT_API
#endif

#ifdef TESTABS_TESTER_EXPORTS
	#define TESTABS_TESTER_API LIBTESTABS_EXPORT_API
#else
	#define TESTABS_TESTER_API LIBTESTABS_IMPORT_API
#endif


struct LIBTESTABS_API ITestToolkit{
	virtual ~ITestToolkit() = default;

	virtual void delayErrorMessage(std::string &&error) = 0;
	virtual void assertDelayedSuccess() = 0;
	virtual void reportError(std::string &&error);
	virtual std::string getFile() = 0;
	virtual std::string getName() = 0;

	virtual void expectTrue(bool value) = 0;
	virtual void expectEqual(uint8_t value, uint8_t expectedValue) = 0;
	virtual void expectEqual(uint16_t value, uint16_t expectedValue) = 0;
	virtual void expectEqual(uint32_t value, uint32_t expectedValue) = 0;
	virtual void expectEqual(uint64_t value, uint64_t expectedValue) = 0;
	virtual void expectEqual(int8_t value, int8_t expectedValue) = 0;
	virtual void expectEqual(int16_t value, int16_t expectedValue) = 0;
	virtual void expectEqual(int32_t value, int32_t expectedValue) = 0;
	virtual void expectEqual(int64_t value, int64_t expectedValue) = 0;
	virtual void expectEqual(float value, float expectedValue) = 0;
	virtual void expectEqual(double value, double expectedValue) = 0;
	virtual void expectEqual(void *value, void *expectedValue) = 0;
	virtual void expectEqual(std::string value, std::string expectedValue) = 0;
};

struct ITestCLIInitializer;

struct LIBTESTABS_API IProtoTest{
	std::string suiteName;
	std::string testName;
	std::filesystem::path filePath;
	int lineInFile;

	IProtoTest(std::string suiteName, std::string testName, std::filesystem::path filePath, int lineInFile=0);
	virtual ~IProtoTest();

	virtual void operator()(ITestToolkit *) = 0;
};

struct LIBTESTABS_API ITestCLIInitializer;

struct LIBTESTABS_API ITestsGenerator{
	ITestsGenerator();
	virtual ~ITestsGenerator() = default;
	virtual void parseUserCLIArgs(ITestCLIInitializer * ti, int argc, const char **argv) = 0;
	virtual int operator()(ITestCLIInitializer * ti) = 0;
};

struct LIBTESTABS_API ITestCLIInitializer{
	std::shared_ptr<ITestToolkit> toolKit;

	ITestCLIInitializer();
	virtual ~ITestCLIInitializer() = default;

	virtual void addTest(std::shared_ptr<IProtoTest> test) = 0;
	virtual void parseFrameworkCLIArgs(int argc, const char **argv) = 0;
	virtual void parseCLIArgs(ITestsGenerator *tg, int argc, const char **argv);

	virtual int runUnitTestFramework() = 0;

	int operator()(ITestsGenerator *tg, int argc, const char **argv);
};


extern "C" {
TESTABS_BACKEND_API ITestCLIInitializer * CLIInitializerFactory();
TESTABS_TESTER_API ITestsGenerator *  TestsGeneratorFactory();
};

using CLIInitializerFactoryT = decltype(CLIInitializerFactory);
using TestsGeneratorFactoryT = decltype(TestsGeneratorFactory);

