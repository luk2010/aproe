-- Premake 4 script for Atlanti's Project Engine.
-- Author : Luk2010
-- Date   : 11/12/2014
-- Copyright : @atlanti's corp, 2012 - 2014

--[[
Option  : --with-exceptions
Summary : When set, enables exceptions in the engine in debug mode.
See     : --with-exceptassert
--]]
newoption {
	trigger 	= "with-exceptions",
	description	= "Set on debug mode only, allow throwing of exceptions."
}

--[[
Option  : --with-memorytracker
Summary : Enables Memory Tracking using the Memory Tracker class.
          Generally produces a Log file in the same directory as the executable.
See     :
--]]
newoption {
	trigger 	= "with-memorytracker",
	description	= "Set on debug mode only, allow memory tracing. Note that the MemoryManager will still be available."
}

--[[
Option  : --with-exceptassert
Summary : Enables Exception throwing when an assertion fails. This option is available only when
          --with-exceptions is set.
See     : --with-exceptions
--]]
newoption {
	trigger		= "with-exceptassert",
	description = "If set with '--with-exceptions' and on debug mode, failing assertions will throw an exception."
}

--[[
Option  : --with-all
Summary : Enables every debug options.
See     :
--]]
newoption {
	trigger 	= "with-all",
	description	= "Set on debug mode only, allow everything you can."
}

--[[
Option  : --double-real
Summary : Change the base type for Real from float to double.
See     : --double-angle
--]]
newoption {
	trigger 	= "double-real",
	description	= "Set real type to double, instead of float by default."
}

--[[
Option  : --double-angle
Summary : Changes the base type for Angle from float to double.
See     : --double-real
--]]
newoption {
	trigger 	= "double-angle",
	description	= "Set angle type to double, instead of float by default."
}

--[[
Option  : --no-thread
Summary : Disale Multithrad support in the Engine. Recommended only if your platform does not support
          pThread library.
See     :
--]]
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
