-- Unix Thread plugin premake4 script
project "UnixThread"
	kind "SharedLib"
	language "C++"
	includedirs { "inc/" }
	files { "inc/*.h",
		"src/*.cpp" }
	links { "AProE", "pthread" }
setupplugintarget()
