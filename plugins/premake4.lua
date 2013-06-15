-- Plugins premake4 script
-- To add your plugin's script, just add the include command.

include "Cross-platform"

if os.is("windows") then
include "Windows"
end

if os.is("linux") then
include "Unix"
end

if os.is("macosx") then
include "MacOSX"
end
