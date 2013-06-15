-- Unix FileSystem plugin premake4 script
project "UnixFileSystem"
	kind "SharedLib"
	language "C++"
	includedirs { "inc/" }
	files { "inc/*.h",
		"src/*.cpp" }
	links { "AProE" }
setupplugintarget()
