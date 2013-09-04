newoption {
	trigger 	= "with-exceptions",
	description	= "Set on debug mode only, allow throwing of exceptions."
}

newoption {
	trigger 	= "with-memorytracker",
	description	= "Set on debug mode only, allow memory tracking."
}

newoption {
	trigger 	= "wall",
	description	= "Set on debug mode only, allow everything you can."
}

newoption {
	trigger 	= "threadsapi",
	value		= "API",
	description	= "Choose if engine must use plugin or pthread thread API.",
	allowed		= {
		{ "plugin", "Thread API is given by a plugin implementation." },
		{ "pthread", "Thread API is provided natively by pthread. This is the quickest and efficientest method." }
	}
}

if not _OPTIONS["threadsapi"] then
  _OPTIONS["threadsapi"] = "pthread"
end

solution "aproe"
	configurations { "Debug", "Release" }
	
project("core")
	kind "SharedLib"
	includedirs { "inc", "src" }
	targetdir "bin"

	language "c++"
	files { "inc/*.h", "src/*.cpp" };

	configuration "windows"
		defines {"WIN32"}

	configuration "Xbox360"
		defines {"_XBOX360_"}
	
	configuration "linux"
		defines {"LINUX"}
		defines {"_HAVE_POSIX_"}

	configuration "PS3"
		defines {"_PS3_"}
		defines {"_HAVE_POSIX_"}

	configuration "macosx"
		defines {"_MACOSX_"}
		defines {"_HAVE_POSIX_"}

	configuration "with-exceptions"
		defines {"_HAVE_EXCEPTIONS_"}

	configuration "with-memorytracker"
		defines {"_HAVE_MEMORYTRACKER_"}

	configuration "wall"
		defines {"_HAVE_EXCEPTIONS_"}
		defines {"_HAVE_MEMORYTRACKER_"}
	
	configuration "pthread"
		defines {"_COMPILE_WITH_PTHREAD_"}
		links   {"pthread"}

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
		objdir "obj_release"
		targetname "aproe_core";
		targetdir "bin/release";
