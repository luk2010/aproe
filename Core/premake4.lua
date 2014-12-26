newoption {
	trigger 	= "with-exceptions",
	description	= "Set on debug mode only, allow throwing of exceptions."
}

newoption {
	trigger 	= "with-memorytracker",
	description	= "Set on debug mode only, allow memory tracing. Note that the MemoryManager will still be available."
}

newoption {
	trigger		= "with-exceptassert",
	description = "If set with '--with-exceptions' and on debug mode, failing assertions will throw an exception."
}

newoption {
	trigger 	= "with-all",
	description	= "Set on debug mode only, allow everything you can."
}

newoption {
	trigger 	= "double-real",
	description	= "Set real type to double, instead of float by default."
}

newoption {
	trigger 	= "double-angle",
	description	= "Set angle type to double, instead of float by default."
}

newoption {
	trigger 	= "no-thread",
	description	= "Disable multithreading support. Use it when your platform doesn't have the 'pthread' library."
}

solution "aproe"
	configurations { "Debug", "Release" }
	
project("core")
	kind "SharedLib"
	includedirs { "inc", "src" }
	targetdir "bin"

	language "c++"
	files { "inc/*.h", "src/*.cpp" };
	defines { "__builddll__" }

	configuration "windows"
		defines {"__windows__"}
		links {"shlwapi", "userenv", "kernel32"}
	
	configuration "linux"
		defines {"__linux__"}
		defines {"_HAVE_POSIX_"}
		links {"dl"}

	configuration "macosx"
		defines {"__macosx__"}
		defines {"_HAVE_POSIX_"}
		links {"dl"}

	configuration "with-exceptions"
		defines {"_HAVE_EXCEPTIONS_"}

	configuration "with-memorytracker"
		defines {"_HAVE_MEMORYTRACKER_"}

	configuration "with-exceptassert"
		defines {"_HAVE_EXCEPT_ON_ASSERT_"}

	configuration "with-all"
		defines {"_HAVE_EXCEPTIONS_"}
		defines {"_HAVE_MEMORYTRACKER_"}
		defines {"_HAVE_EXCEPT_ON_ASSERT_"}

	configuration "double-real"
		defines {"_USE_DOUBLEREAL_"}

	configuration "double-angle"
		defines {"_USE_DOUBLEANGLE_"}
	
	configuration "not no-thread"
		defines {"_COMPILE_WITH_PTHREAD_"}
		links   {"pthread"}
		defines {"_REENTRANT"}

	configuration "debug"
		defines {"_HAVE_DEBUG_MODE_"}
		flags "Symbols"
		flags "Unicode"
		objdir "obj_debug"
		targetname "aproe_cored";
		targetdir "bin/debug";

	configuration "release"
		flags {"OptimizeSpeed", "NoFramePointer", "ExtraWarnings", "NoEditAndContinue"};
		flags "Unicode"
		buildoptions { "-std=c++11" }
		objdir "obj_release"
		targetname "aproe_core";
		targetdir "bin/release";
