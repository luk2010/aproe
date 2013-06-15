-- TestApplication premake script
project "TestApplication"
	kind "ConsoleApp"
	language "C++"
	files { "inc/*.h",
		"src/*.cpp" }
	links { "AProE" }
