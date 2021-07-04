#define CATCH_CONFIG_RUNNER
#include <catch2/catch.hpp>

#include <string>
#include <iostream>
#include <memory>
#include <filesystem>

#include <stdio.h>

#include <stdint.h>

#include <TestAbs/TestAbs.hpp>


struct NotImplementedException: public std::logic_error
{
	NotImplementedException(): std::logic_error("Not yet implemented!"){}
	NotImplementedException(const std::string& what): std::logic_error(what){}
};

struct Catch2Toolkit: public ITestToolkit{
	virtual void delayErrorMessage(std::string &&error) override {
		FAIL( error );
	}
	virtual void assertDelayedSuccess() override {throw NotImplementedException();}
	virtual void reportError(std::string &&error) override {
		FAIL( error );
	}
	virtual std::string getFile() override{
		return "";
	}
	virtual std::string getName() override {
		return Catch::getResultCapture().getCurrentTestName();
	}

	virtual void expectTrue(bool value) override {
		REQUIRE( value );
	}
	virtual void expectEqual(uint8_t value, uint8_t expectedValue) override {
		REQUIRE( value == expectedValue );
	}
	virtual void expectEqual(uint16_t value, uint16_t expectedValue) override {
		REQUIRE( value == expectedValue );
	}
	virtual void expectEqual(uint32_t value, uint32_t expectedValue) override {
		REQUIRE( value == expectedValue );
	}
	virtual void expectEqual(uint64_t value, uint64_t expectedValue) override {
		REQUIRE( value == expectedValue );
	}
	virtual void expectEqual(int8_t value, int8_t expectedValue) override {
		REQUIRE( value == expectedValue );
	}
	virtual void expectEqual(int16_t value, int16_t expectedValue) override {
		REQUIRE( value == expectedValue );
	}
	virtual void expectEqual(int32_t value, int32_t expectedValue) override {
		REQUIRE( value == expectedValue );
	}
	virtual void expectEqual(int64_t value, int64_t expectedValue) override {
		REQUIRE( value == expectedValue );
	}
	virtual void expectEqual(float value, float expectedValue) override {
		REQUIRE( value == expectedValue );
	}
	virtual void expectEqual(double value, double expectedValue) override {
		REQUIRE( value == expectedValue );
	}
	virtual void expectEqual(void *value, void *expectedValue) override {
		REQUIRE( value == expectedValue );
	}
	virtual void expectEqual(std::string value, std::string expectedValue) override {
		REQUIRE( value == expectedValue );
	}
};

struct ourTestInvoker : public Catch::ITestInvoker {
	std::string filePath;
	ourTestInvoker(std::string filePath):filePath(filePath) {}

	void invoke() const override {
	}
};


struct Catch2CLIInitializer: public ITestCLIInitializer{
	Catch2CLIInitializer();
	~Catch2CLIInitializer() = default;

	Catch::Session session;

	virtual void addTest(std::shared_ptr<IProtoTest> test) override;

	virtual void parseFrameworkCLIArgs(int argc, const char **argv) override{
		auto cli = session.cli();
		session.cli( cli );
		int returnCode = session.applyCommandLine(argc, argv);
	}

	virtual int runUnitTestFramework() override{
		return session.run();
	}
};

void Catch2CLIInitializer::addTest(std::shared_ptr<IProtoTest> test){
	Catch::AutoReg autoRegistrar(
		new ourTestInvoker(test->filePath),
		::Catch::SourceLineInfo(test->filePath.c_str(), static_cast<std::size_t>(0)),
		Catch::StringRef(),
		Catch::NameAndTags{ test->suiteName, test->testName }
	);
}

ITestCLIInitializer * CLIInitializerFactory(){
	return new Catch2CLIInitializer();
};
