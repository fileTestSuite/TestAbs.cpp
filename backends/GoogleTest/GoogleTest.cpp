#include <gtest/gtest.h>

#include <string>
#include <iostream>
#include <memory>
#include <filesystem>

#include <stdio.h>

#include <stdint.h>

#include <TestAbs/TestAbs.hpp>


struct GTestToolkit: public ITestToolkit{
	testing::AssertionResult errorMessagesAccumulator = testing::AssertionSuccess();
	virtual void delayErrorMessage(std::string &&error) override {
		errorMessagesAccumulator << error << std::endl;
	}
	virtual void assertDelayedSuccess() override {
		EXPECT_TRUE(errorMessagesAccumulator);
	}
	virtual std::string getFile() override {
		auto inst = ::testing::UnitTest::GetInstance()->current_test_info();
		return std::string(inst->file());
	}
	virtual std::string getName() override {
		auto inst = ::testing::UnitTest::GetInstance()->current_test_info();
		return inst->test_case_name();
	}

	virtual void expectTrue(bool value) override {
		EXPECT_TRUE(value);
	}
	virtual void expectEqual(uint8_t value, uint8_t expectedValue) override {
		EXPECT_EQ(expectedValue, value);
	}
	virtual void expectEqual(uint16_t value, uint16_t expectedValue) override {
		EXPECT_EQ(expectedValue, value);
	}
	virtual void expectEqual(uint32_t value, uint32_t expectedValue) override {
		EXPECT_EQ(expectedValue, value);
	}
	virtual void expectEqual(uint64_t value, uint64_t expectedValue) override {
		EXPECT_EQ(expectedValue, value);
	}
	virtual void expectEqual(int8_t value, int8_t expectedValue) override {
		EXPECT_EQ(expectedValue, value);
	}
	virtual void expectEqual(int16_t value, int16_t expectedValue) override {
		EXPECT_EQ(expectedValue, value);
	}
	virtual void expectEqual(int32_t value, int32_t expectedValue) override {
		EXPECT_EQ(expectedValue, value);
	}
	virtual void expectEqual(int64_t value, int64_t expectedValue) override {
		EXPECT_EQ(expectedValue, value);
	}
	virtual void expectEqual(float value, float expectedValue) override {
		EXPECT_EQ(expectedValue, value);
	}
	virtual void expectEqual(double value, double expectedValue) override {
		EXPECT_EQ(expectedValue, value);
	}
	virtual void expectEqual(void *value, void *expectedValue) override {
		EXPECT_EQ(expectedValue, value);
	}
	virtual void expectEqual(std::string value, std::string expectedValue) override {
		EXPECT_EQ(expectedValue, value);
	}
};

GTestToolkit tk;

struct OurTestClass: public ::testing::Test {
	std::shared_ptr<IProtoTest> protoTest;

	OurTestClass(std::shared_ptr<IProtoTest> protoTest): protoTest(protoTest){}
	virtual ~OurTestClass() override = default;

	OurTestClass(OurTestClass const&) = delete;
	OurTestClass& operator=(OurTestClass const&) = delete;
	OurTestClass(OurTestClass&&) noexcept = delete;
	OurTestClass& operator=(OurTestClass&&) noexcept = delete;

	virtual void TestBody() override {
		protoTest->operator()(&tk);
	}
	static ::testing::TestInfo* const test_info_ GTEST_ATTRIBUTE_UNUSED_;
};

struct OurTestFactory: public ::testing::internal::TestFactoryBase{
	std::shared_ptr<IProtoTest> protoTest;
	OurTestFactory(std::shared_ptr<IProtoTest> protoTest): protoTest(protoTest){

	}
	::testing::Test* CreateTest() override {
		return new OurTestClass(protoTest);
	}
};

struct GTestCLIInitializer: public ITestCLIInitializer{
	std::vector<::testing::TestInfo*> ourTestInfos;

	GTestCLIInitializer() = default;
	~GTestCLIInitializer() = default;

	virtual void addTest(std::shared_ptr<IProtoTest> test) override {
		::testing::TestInfo* ourTestInfo = ::testing::internal::MakeAndRegisterTestInfo(
			test->suiteName.c_str(), test->testName.c_str(), nullptr, nullptr, ::testing::internal::CodeLocation(test->filePath, 0),
			(::testing::internal::GetTestTypeId()),
			::testing::internal::SuiteApiResolver<::testing::Test>::GetSetUpCaseOrSuite(__FILE__, __LINE__),
			::testing::internal::SuiteApiResolver<::testing::Test>::GetTearDownCaseOrSuite(__FILE__, __LINE__),
			new OurTestFactory(test)
		);
		ourTestInfos.emplace_back(ourTestInfo);
	}

	virtual void parseFrameworkCLIArgs(int argc, const char **argv) override{
		::testing::InitGoogleTest(&argc, const_cast<char **>(argv));
	}

	virtual int runUnitTestFramework() override{
		return RUN_ALL_TESTS();
	}
};

ITestCLIInitializer * CLIInitializerFactory(){
	return new GTestCLIInitializer();
};
