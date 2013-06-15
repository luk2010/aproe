-- Example plugin premake4 script
project "ExamplePlugin"
	kind "SharedLib"
	language "C++"
	includedirs { "inc/" }
	files {	"src/*.cpp" }
	links { "AProE" }
setupplugintarget()
