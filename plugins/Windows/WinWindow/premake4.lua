-- Windows WindowSystem plugin premake4 script
project "WinWindowSystem"
	kind "SharedLib"
	language "C++"
	includedirs { "inc/" }
	files { "inc/*.h",
		"src/*.cpp" }
	links { "AProE" }
setupplugintarget()
