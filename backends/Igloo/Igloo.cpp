#include <igloo/igloo.h>

#include <string>
#include <iostream>
#include <memory>
#include <filesystem>

#include <stdio.h>

#include <stdint.h>

#include <TestAbs/TestAbs.hpp>


struct IglooToolkit: public ITestToolkit{
	virtual void delayErrorMessage(std::string &&error) override;
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

void IglooToolkit::delayErrorMessage(std::string &&error){
	FAIL( error );
}

std::string IglooToolkit::getFile() {
	return "";
}

std::string IglooToolkit::getName() {
	return Catch::getResultCapture().getCurrentTestName();
}

void IglooToolkit::expectTrue(bool value){
	Assert::That(value, Equals(true));
}

void IglooToolkit::expectEqual(std::string value, std::string expectedValue){
	Assert::That(value, Equals(expectedValue));
}

void IglooToolkit::expectEqual(int value, int expectedValue){
	Assert::That(value, Equals(expectedValue));
}

void IglooToolkit::expectEqual(float value, float expectedValue){
	Assert::That(value, Equals(expectedValue));
}

void IglooToolkit::expectEqual(double value, double expectedValue){
	Assert::That(value, Equals(expectedValue));
}


struct IglooCLIInitializer: public ITestCLIInitializer{
	IglooCLIInitializer();
	~IglooCLIInitializer() = default;

	Catch::Session session;

	virtual void addTest(IProtoTest test) override;


	virtual std::unique_ptr<ITestToolkit> toolkitFactory() override {
		return std::make_unique<IglooToolkit>();
	}

	virtual void parseFrameworkCLIArgs(int argc, const char **argv) override{
		auto cli = session.cli();
		session.cli( cli );
		int returnCode = session.applyCommandLine(argc, argv);
	}

	virtual int runUnitTestFramework() override{
		return TestRunner::RunAllTests(argc, argv);
	}
};

void IglooCLIInitializer::addTest(IProtoTest test){
	Catch::AutoReg autoRegistrar(
		new ourTestInvoker(filePath),
		::Catch::SourceLineInfo(filePath.c_str(), static_cast<std::size_t>( 0 ) ),
		Catch::StringRef(),
		Catch::NameAndTags{ test, testName }
	);
}
