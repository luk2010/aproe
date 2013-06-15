-- Thread example premake4 script
project "Thread"
	kind "ConsoleApp"
	language "C++"
	files { "inc/*.h",
		"src/*.cpp" }
	links { "AProE" }
