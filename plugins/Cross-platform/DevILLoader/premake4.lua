-- DevIL Loader premake4 script
project "DevILLoader"
	kind "SharedLib"
	language "C++"
	includedirs { "inc/" }
	files {	"inc/*.h", 
                "src/*.cpp" }
	links { "AProE", "DevIL" }
setupplugintarget()
