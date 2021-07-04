#include <UnitTest++/UnitTest++.h>

#include <string>
#include <iostream>
#include <memory>
#include <filesystem>
#include <stdexcept>

#include <stdio.h>

#include <stdint.h>

#include <TestAbs/TestAbs.hpp>


struct NotImplementedException: public std::logic_error
{
	NotImplementedException(): std::logic_error("Not yet implemented!"){}
	NotImplementedException(const std::string& what): std::logic_error(what){}
};



struct UnitTestPPToolkit: public ITestToolkit{
	virtual void delayErrorMessage(std::string &&error) override;
	virtual void assertDelayedSuccess() override;
	virtual void reportError(std::string &&error) override;
	virtual std::string getFile() override;
	virtual std::string getName() override;

	virtual void expectTrue(bool value) override;
	virtual void expectEqual(uint8_t value, uint8_t expectedValue) override;
	virtual void expectEqual(uint16_t value, uint16_t expectedValue) override;
	virtual void expectEqual(uint32_t value, uint32_t expectedValue) override;
	virtual void expectEqual(uint64_t value, uint64_t expectedValue) override;
	virtual void expectEqual(int8_t value, int8_t expectedValue) override;
	virtual void expectEqual(int16_t value, int16_t expectedValue) override;
	virtual void expectEqual(int32_t value, int32_t expectedValue) override;
	virtual void expectEqual(int64_t value, int64_t expectedValue) override;
	virtual void expectEqual(float value, float expectedValue) override;
	virtual void expectEqual(double value, double expectedValue) override;
	virtual void expectEqual(void *value, void *expectedValue) override;
	virtual void expectEqual(std::string value, std::string expectedValue) override;
};

void UnitTestPPToolkit::delayErrorMessage(std::string &&error){throw NotImplementedException();}
void UnitTestPPToolkit::assertDelayedSuccess(){throw NotImplementedException();};
void UnitTestPPToolkit::reportError(std::string &&error){throw NotImplementedException();}

std::string UnitTestPPToolkit::getFile() {throw NotImplementedException();}

std::string UnitTestPPToolkit::getName() {throw NotImplementedException();}

void UnitTestPPToolkit::expectTrue(bool value){CHECK_EQUAL(value, true);}

void UnitTestPPToolkit::expectEqual(std::string value, std::string expectedValue){CHECK_EQUAL(value, expectedValue);}

void UnitTestPPToolkit::expectEqual(int value, int expectedValue){CHECK_EQUAL(value, expectedValue);}

void UnitTestPPToolkit::expectEqual(float value, float expectedValue){CHECK_EQUAL(value, expectedValue);}

void UnitTestPPToolkit::expectEqual(double value, double expectedValue){CHECK_EQUAL(value, expectedValue);}


struct UnitTestPPCLIInitializer: public ITestCLIInitializer{
	UnitTestPPCLIInitializer();
	~UnitTestPPCLIInitializer() = default;

	virtual void addTest(std::shared_ptr<IProtoTest> test) override;

	virtual void parseFrameworkCLIArgs(int argc, const char **argv) override{throw NotImplementedException();}

	virtual int runUnitTestFramework() override{throw NotImplementedException();}
};

void UnitTestPPCLIInitializer::addTest(std::shared_ptr<IProtoTest> test){
	throw NotImplementedException();
}

ITestCLIInitializer * CLIInitializerFactory(){
	return new UnitTestPPCLIInitializer();
};
