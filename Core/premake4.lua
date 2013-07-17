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
		defines {"_HAVE_POSIX_"}

	configuration "PS3"
		defines {"_PS3_"}
		defines {"_HAVE_POSIX_"}

	configuration "Xbox360"
		defines {"_XBOX360_"}

	configuration "macosx"
		defines {"_MACOSX_"}

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
