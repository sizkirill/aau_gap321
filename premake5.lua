newoption
{
	trigger = "vsversion",
	description = "Specify the Visual Studio version",
	default = "2019",
	allowed = {
		{ "2019", "Visual Studio 2019"},
		{ "2017", "Visual Studio 2017"}
	}
}

newoption
{
	trigger = "vspath",
	description = "Path to Visual Studio",
	default = 'C:\\"Program Files (x86)"\\"Microsoft Visual Studio"\\'
}

newoption
{
	trigger = "vstype",
	description = "Community / Enterprise / Professional",
	allowed = {
		{"Community", "Visual Studio Community"},
		{"Enterprise", "Visual Studio Enterprise"},
		{"Professional", "Visual Studio Professional"}
	}
}

newoption
{
	trigger = "buildconfig",
	description = "Specify the build configurations",
	default = "Both",
	allowed = {
		{"Debug", "Debug"},
		{"Release", "Release"},
		{"Both", "Release and Debug"}
	}
}

newoption
{
	trigger = "buildplatform",
	description = "Specify the build platform",
	default = "Both",
	allowed = {
		{"x86", "x86"},
		{"x64", "x64"},
		{"Both", "x86 and x64"}
	}
}

local BuildSettings = 
{
	vsversion = _OPTIONS["vsversion"] or "2019",
	vspath = _OPTIONS["vspath"] or 'C:\\"Program Files (x86)"\\"Microsoft Visual Studio"\\',
	vstype = _OPTIONS["vstype"] or 'Enterprise',
	buildconfigs = {},
	buildplatforms = {}
}

if _OPTIONS["buildplatform"] == "Both" then
	BuildSettings.buildplatforms = {"x86", "x64"} else
	BuildSettings.buildplatforms = {_OPTIONS["buildplatform"]} end
	
if _OPTIONS["buildconfig"] == "Both" then
	BuildSettings.buildconfigs = {"Release", "Debug"} else
	BuildSettings.buildconfigs = {_OPTIONS["buildconfig"]} end

newaction {
	trigger = "build",
	description = "Build the project",
	execute = function()
		local initVS = BuildSettings.vspath .. BuildSettings.vsversion .. '\\' .. BuildSettings.vstype .. '\\VC\\Auxiliary\\Build\\vcvars32.bat'
		local buildCommandTemplate = 'msbuild "GAP321_KirillSizykh.sln" /p:Platform=%s /p:Configuration=%s /m'
		local buildCommand = ""
		
		for k,config in ipairs(BuildSettings.buildconfigs) do
			for j, platform in ipairs(BuildSettings.buildplatforms) do
				buildCommand = buildCommand .. string.format(buildCommandTemplate, platform, config) .. " && "
			end
		end
		
		buildCommand = buildCommand:sub(1, #buildCommand - 4)
		os.execute('premake5 vs' .. BuildSettings.vsversion .. ' && ' .. initVS .. ' && ' .. buildCommand)
	end
}

workspace "GAP321_KirillSizykh"
	startproject "GAP321_KirillSizykh"
	configurations {"Debug", "Release"}
	platforms {"x86", "x64"}
	language "C++"
	cppdialect "C++17"
	
project "Engine"
	kind "StaticLib"
	location "Yangine/Yangine"
	includedirs {"Yangine/Yangine/Source", "Yangine/Toolset/Include"}
	files {"Yangine/Yangine/Source/**.h", "Yangine/Yangine/Source/**.cpp"}
	
	filter {"configurations:Debug", "platforms:x86"}
		architecture "x86"
		targetdir "Yangine/Yangine/Binaries/Debug_x86"
		
	filter {"configurations:Release", "platforms:x86"}
		architecture "x86"
		targetdir "Yangine/Yangine/Binaries/Release_x86"
		
	filter {"configurations:Debug", "platforms:x64"}
		architecture "x86_64"
		targetdir "Yangine/Yangine/Binaries/Debug_x64"
		
	filter {"configurations:Release", "platforms:x64"}
		architecture "x86_64"
		targetdir "Yangine/Yangine/Binaries/Release_x64"
	
	filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
		optimize "Full"

project "GAP321_KirillSizykh"
kind "ConsoleApp"
location "GAP321_KirillSizykh"
includedirs {"Yangine/Yangine/Source", "Yangine/Toolset/Include", "GAP321_KirillSizykh/Source"}
files {"GAP321_KirillSizykh/Source/**.h", "GAP321_KirillSizykh/Source/**.cpp"}
links {"Engine", "vld", "SDL2", "SDL2_image", "SDL2_mixer", "SDL2_ttf", "SDL2main", "Lua-5.3.5_$(PlatformShortName)_$(Configuration)"}

postbuildcommands { 'xcopy "$(SolutionDir)Yangine\\Toolset\\$(PlatformShortName)\\*.dll" "$(OutDir)" /d /i /y',
'xcopy "$(SolutionDir)Yangine\\Toolset\\$(PlatformShortName)\\*.manifest" "$(OutDir)" /d /i /y',
'xcopy "$(ProjectDir)\\Assets" "$(OutDir)Assets" /e /s /h /i /y',
'xcopy "$(ProjectDir)\\Data" "$(OutDir)Data" /e /s /h /i /y'}

filter {"platforms:x86"}
    libdirs{"Yangine/Toolset/x86"}
    
filter {"platforms:x64"}
    libdirs{"Yangine/Toolset/x64"}

filter {"configurations:Debug", "platforms:x86"}
    architecture "x86"
    targetdir "GAP321_KirillSizykh/Builds/Debug_x86"
    libdirs "Yangine/Yangine/Binaries/Debug_x86"
    
filter {"configurations:Release", "platforms:x86"}
    architecture "x86"
    targetdir "GAP321_KirillSizykh/Builds/Release_x86"
    libdirs "Yangine/Yangine/Binaries/Release_x86"
    
filter {"configurations:Debug", "platforms:x64"}
    architecture "x86_64"
    targetdir "GAP321_KirillSizykh/Builds/Debug_x64"
    libdirs "Yangine/Yangine/Binaries/Debug_x64"
    
filter {"configurations:Release", "platforms:x64"}
    architecture "x86_64"
    targetdir "GAP321_KirillSizykh/Builds/Release_x64"
    libdirs "Yangine/Yangine/Binaries/Release_x64"

filter "configurations:Debug"
    defines { "DEBUG" }
    symbols "On"
    postbuildcommands {'xcopy "$(SolutionDir)Yangine\\Toolset\\$(PlatformShortName)\\*.pdb" "$(OutDir)" /d /i /y'}

filter "configurations:Release"
    defines { "NDEBUG" }
    optimize "Full"
    
