-- XCBWindowSystem plugin premake script
project "XCBWindowSystem"
	kind "SharedLib"
	language "C++"
	includedirs { "inc/" }
	files { "inc/*.h",
		"src/*.cpp" }
	links { "AProE",  "xcb",
			  "X11",
			  "X11-xcb",
			  "GL" }
setupplugintarget()
