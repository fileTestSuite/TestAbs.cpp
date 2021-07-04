#include <iostream>
#include <memory>
#include <filesystem>
#include <functional>
#include <sstream>
#include <type_traits>

#include <stdio.h>

#include <TestAbs/TestAbs.hpp>

#define USE_DYLIB
#include "SharedLibFactoryHelper.hpp"

#include <HydrArgs/HydrArgs.hpp>

using namespace HydrArgs;
using namespace HydrArgs::Backend;


auto CliInitializerFactorySymName = "CLIInitializerFactory";
auto TestsGeneratorFactorySymName = "TestsGeneratorFactory";

auto description = "A tool to run tests using TestAbs - a framework for wrapping unittest frameworks in order to make usage of automatically generated tests easier";
auto usage = "<backend> <your shared library> <args for testing framework and your lib>";

auto programName = "TestAbs Runner";

int main(int argc, const char **argv){
	SArg<ArgType::string> backendLibNameA{'b', "backend_lib", "The library implementing test framework backend", 0, "Path to the lib"};
	SArg<ArgType::string> testGenLibNameA{'t', "test_lib", "The library implementing tests", 0, "Path to the lib"};

	std::vector<Arg*> dashedSpec{};
	std::vector<Arg*> positionalSpec{&backendLibNameA, &testGenLibNameA};

	std::unique_ptr<IArgsParser> ap{argsParserFactory(programName, description, usage, dashedSpec, positionalSpec)};

	if(!ap){
		std::cerr << "Cannot initialize CLI parsing library!" << std::endl;
		return EXIT_FAILURE;
	}

	std::cout << "Parsing CLI args" << std::endl;
	ParseResult res = (*ap)(CLIRawArgs{.argv0=argv[0], .argvRest={&argv[1], static_cast<size_t>(argc - 1)}});

	if(res.parsingStatus){
		std::cout << "Error parsing CLI args, error code " << res.parsingStatus << std::endl;
		return res.parsingStatus.returnCode;
	}

	std::cout << "backendLibNameA=" << backendLibNameA.value << std::endl;
	std::cout << "testGenLibNameA=" << testGenLibNameA.value << std::endl;

	std::cout << "loading backend lib" << std::endl;
	SharedLibFactory<CLIInitializerFactoryT> cliInitFactory(backendLibNameA.value.data(), CliInitializerFactorySymName);
	std::cout << "loading test suite lib" << std::endl;
	SharedLibFactory<TestsGeneratorFactoryT> testGenFactory(testGenLibNameA.value.data(), TestsGeneratorFactorySymName);

	std::cout << "Constructing test" << std::endl;

	auto testGen = testGenFactory();

	std::cout << "Constructing backend" << std::endl;
	auto backendCli = cliInitFactory();


	auto nextStageVector = res.rest.getArgvVector();

	std::cout << "Running" << std::endl;
	auto resCode = (*backendCli).operator()(testGen, nextStageVector.size() - 1, nextStageVector.data());

	delete backendCli;
	delete testGen;

	return res.parsingStatus.returnCode;
}
