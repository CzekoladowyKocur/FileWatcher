-- Workspace

OutputDirectory = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

workspace("FileWatcher")
	architecture "x64"
	platforms "x64"
	startproject "FileWatcher"
	targetdir (OutputDirectory)

	configurations 
	{
		"Debug",
		"Release",
	}

	flags
	{
		"MultiProcessorCompile",
		"FatalCompileWarnings",
		"FatalLinkWarnings",
	}
	
	filter "configurations:Debug"
		symbols "On"				
		optimize "Off"				
		runtime "Debug"				
		staticruntime "on"		
		
project("FileWatcher")
	location "FileWatcher"
	language "C++"
	cppdialect "C++20"
	kind "ConsoleApp"
	warnings "Extra"				

	local ProjectOutputDirectory = "binaries/bin/" .. (OutputDirectory) .. "/%{prj.name}";
	local ProjectIntermediateOutputDirectory = "binaries/bin-int/" .. (OutputDirectory) .. "/%{prj.name}";

	targetdir (ProjectOutputDirectory)
	objdir (ProjectIntermediateOutputDirectory)

	files 
	{ 
		"%{prj.name}/FileWatcher.hpp",
		"%{prj.name}/main.cpp",
	}
	
	includedirs
	{
		"%{prj.name}/",
	}

	filter "system:windows"
		files 
		{ 
			"%{prj.name}/WindowsFileWatcher.cpp",
		}
	
	filter "system:linux"
		files 
		{ 
			"%{prj.name}/LinuxFileWatcher.cpp",
		}
		