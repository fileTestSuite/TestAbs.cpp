#include <cpptest.h>



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

struct OurTestSuite;

struct CPPTestToolkit: public ITestToolkit{
	OurTestSuite *ts = nullptr;

	CPPTestToolkit(OurTestSuite *ts);
	virtual ~CPPTestToolkit();

	void assertment(Test::Source s);
	bool continue_after_failure() const;

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

struct OurTestSuite: public Test::Suite{
	friend CPPTestToolkit;

	std::shared_ptr<IProtoTest> protoTest;
	CPPTestToolkit toolKit;

	OurTestSuite(std::shared_ptr<IProtoTest> protoTest);
	void execute();
	void assertment_public(Test::Source s);
	bool continue_after_failure_public() const;

};


CPPTestToolkit::CPPTestToolkit(OurTestSuite *ts): ts(ts){}
CPPTestToolkit::~CPPTestToolkit() = default;
void CPPTestToolkit::assertment(Test::Source s){
	ts->assertment_public(s);
}
bool CPPTestToolkit::continue_after_failure() const {
	return ts->continue_after_failure_public();
}

void CPPTestToolkit::delayErrorMessage(std::string &&error) {throw NotImplementedException();}
void CPPTestToolkit::assertDelayedSuccess() {throw NotImplementedException();}
void CPPTestToolkit::reportError(std::string &&error) {throw NotImplementedException();}
std::string CPPTestToolkit::getFile() {throw NotImplementedException();}
std::string CPPTestToolkit::getName() {throw NotImplementedException();}

void CPPTestToolkit::expectTrue(bool value) {
	TEST_ASSERT_EQUALS(true, value)
}

void CPPTestToolkit::expectEqual(uint8_t value, uint8_t expectedValue) {
	TEST_ASSERT_EQUALS(expectedValue, value)
}
void CPPTestToolkit::expectEqual(uint16_t value, uint16_t expectedValue) {
	TEST_ASSERT_EQUALS(expectedValue, value)
}
void CPPTestToolkit::expectEqual(uint32_t value, uint32_t expectedValue) {
	TEST_ASSERT_EQUALS(expectedValue, value)
}
void CPPTestToolkit::expectEqual(uint64_t value, uint64_t expectedValue) {
	TEST_ASSERT_EQUALS(expectedValue, value)
}
void CPPTestToolkit::expectEqual(int8_t value, int8_t expectedValue) {
	TEST_ASSERT_EQUALS(expectedValue, value)
}
void CPPTestToolkit::expectEqual(int16_t value, int16_t expectedValue) {
	TEST_ASSERT_EQUALS(expectedValue, value)
}
void CPPTestToolkit::expectEqual(int32_t value, int32_t expectedValue) {
	TEST_ASSERT_EQUALS(expectedValue, value)
}
void CPPTestToolkit::expectEqual(int64_t value, int64_t expectedValue) {
	TEST_ASSERT_EQUALS(expectedValue, value)
}
void CPPTestToolkit::expectEqual(float value, float expectedValue) {
	TEST_ASSERT_EQUALS(expectedValue, value)
}
void CPPTestToolkit::expectEqual(double value, double expectedValue) {
	TEST_ASSERT_EQUALS(expectedValue, value)
}
void CPPTestToolkit::expectEqual(void *value, void *expectedValue) {
	TEST_ASSERT_EQUALS(expectedValue, value)
}
void CPPTestToolkit::expectEqual(std::string value, std::string expectedValue) {
	TEST_ASSERT_EQUALS(expectedValue, value)
}

OurTestSuite::OurTestSuite(std::shared_ptr<IProtoTest> protoTest) : protoTest(protoTest), toolKit(this){
	register_test(static_cast<Func>(&OurTestSuite::execute), "shit");
}
void OurTestSuite::execute(){
	(*protoTest)(&toolKit);
}
void OurTestSuite::assertment_public(Test::Source s){
	assertment(s);
}
bool OurTestSuite::continue_after_failure_public() const {
	return continue_after_failure();
}



struct CPPTestCLIInitializer: public ITestCLIInitializer{
	CPPTestCLIInitializer();
	~CPPTestCLIInitializer() = default;

	virtual void addTest(std::shared_ptr<IProtoTest> test) override;

	virtual void parseFrameworkCLIArgs(int argc, const char **argv) override{throw NotImplementedException();}

	virtual int runUnitTestFramework() override{throw NotImplementedException();}
};


void CPPTestCLIInitializer::addTest(std::shared_ptr<IProtoTest> test){
	OurTestSuite ots(test);
}

ITestCLIInitializer * CLIInitializerFactory(){
	return new CPPTestCLIInitializer();
};

