-- This is the Premake script for Atlanti's Project Engine

-- Change configurations in this file :
dofile "config.lua"

print ("=== Atlanti's Project Engine Premake4 script ===")
print ("Showing configuration :")
print ("Application dir : "..appdir)
print ("Plugins dir : "..appdir.."/<Config>/"..plugindir)
print ("Library dir : "..appdir.."/<Config>/"..libdir)
print ("Objects dir : "..objectdir)
print ("Library relativ path : "..appdir.."/<Config>/"..libdir)

-- Use this function in your plugin script to set the correct location dir
function setupplugintarget()
	configuration { "Debug" }
		targetdir (appdir.."/Debug/"..plugindir)
	configuration { "Release" }
		targetdir (appdir.."/Debug/"..plugindir)

	vpaths { ["Headers"] = "**.h",
	         ["Sources"] = "**.cpp" }
end

-- Loads scripts actions
if (scriptpath) then
                        local scripts  = dofile("manifest.lua")
                        for _,v in ipairs(scripts) do
                                dofile(scriptpath .. "/" .. v)
                        end
                end

solution "Atlanti's Project Engine"

	configurations { "Release", "Debug" }
	flags { "ExtraWarnings" }
	buildoptions { "-std=c++11" }
	location "projects"
	includedirs { "inc/" } -- Every project should include this directory

	configuration { "Debug" }
		defines "DEBUG"
		objdir (objectdir.."/Debug")
		targetdir (appdir.."/Debug")
		linkoptions { "-Wl,-rpath,"..appdir.."/Debug/"..libdir..",-rpath,/usr/lib/,-rpath,/usr/lib32/" }
		flags { "Symbols" }

	configuration { "Release" }
		objdir (objectdir.."/Release")
		targetdir (appdir.."/Release")
		linkoptions { "-Wl,-rpath,"..appdir.."/Release/"..libdir..",-rpath,/usr/lib/,-rpath,/usr/lib32/" }

	configuration { "x64" }
		linkoptions { "fPIC" }
		flags { "OptimizeSpeed" }
		
	

	-- Defines the main library project
	project "AProE"
	uuid "35ABE42F-A9D2-11E2-9E96-0800200C9A66"
	kind "SharedLib"
	language "C++"
	files { "inc/*.h", "src/*.cpp" }
	defines "BUILD_DLL"
	links { "dl" }
	vpaths { ["Headers"] = "**.h",
	         ["Sources"] = "**.cpp" }

	-- Defines examples and plugins projects

	include "examples"
	include "plugins"

print "=== Build finshed ! ==="
