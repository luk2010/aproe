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
	
	configuration "linux"
		defines {"LINUX"}

	configuration "debug"
		defines {"_HAVE_DEBUG_MODE_"}
		flags "Symbols"
		flags "Unicode"
		objdir "obj_debug"
		targetname "aproe_cored";

	configuration "release"
		flags {"OptimizeSpeed", "NoFramePointer", "ExtraWarnings", "NoEditAndContinue"};
		flags "Unicode"
		objdir "obj_release"
		targetname "aproe_core";
