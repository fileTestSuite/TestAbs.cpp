#pragma once

#include <string>

#ifndef USE_DYLIB
	#include <function_loader/function_loader.hpp>
#else
	#include <DyLib.hpp>
#endif

template <typename FuncT> struct SharedLibFactory{
	#ifndef USE_DYLIB
	using DynLibT = burda::function_loader::function_loader;
	#else
	using DynLibT = DyLib;
	#endif


	DynLibT l;
	std::function<FuncT> f;

	SharedLibFactory(const char * libraryName, const char * funcName): l(DynLibT(libraryName)){
		#ifndef USE_DYLIB
		f = l.get_function<FuncT>(funcName);
		#else
		f = l.getFunction<FuncT>(funcName);
		#endif
	}

	typename std::invoke_result<FuncT>::type operator()(){
		return f();
	}
};
