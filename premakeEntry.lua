workspace "GameEngine"
	architecture "x64"
	startproject "Editor"

	configurations { "Alpha", "Beta", "Release" }
	
	flags {
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.system}/%{cfg.buildcfg}-%{cfg.architecture}"
IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/Engine/vendor/GLFW/include"
IncludeDir["Glad"] = "%{wks.location}/Engine/vendor/Glad/include"

group "Dependencies"
	include "Engine/vendor/GLFW"
	include "Engine/vendor/Glad"
group ""


project "Engine"
	location "Engine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin/int/" .. outputdir .. "/%{prj.name}")

	pchheader "enpch.h"
	pchsource "Engine/src/enpch.cpp"

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	defines {
		"_CRT_SECURE_NO_WARNINGS"
		-- "GLFW_INCLUDE_NONE"
	}

	includedirs {
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{prj.name}/vendor"
	}
	links {
		"GLFW",
		"Glad",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines {
			"ENGINE_PLATFORM_WINDOWS"
		}
		
	filter "configurations:Alpha"
		defines { "ALPHA", "LOGGING", "ENGINE_ENABLE_FATAL" }
		runtime "Debug"
		optimize "on"
	filter "configurations:Beta"
		defines { "BETA", "LOGGING" }
		runtime "Release"
		optimize "on"
	filter "configurations:Release"
		defines { "RELEASE" }
		runtime "Release"
		optimize "on"


project "Editor"
	location "Editor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin/int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"Engine/vendor/spdlog/include",
		"Engine/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"Engine/vendor"
	}

	links {	"Engine" }

	filter "system:windows"
		systemversion "latest"

		defines {
			"ENGINE_PLATFORM_WINDOWS"
		}
		
	filter "configurations:Alpha"
		defines { "ALPHA", "LOGGING", "ENGINE_ENABLE_FATAL" }
		runtime "Debug"
		symbols "on"
	filter "configurations:Beta"
		defines { "BETA", "LOGGING" }
		runtime "Release"
		optimize "on"
	filter "configurations:Release"
		defines { "RELEASE" }
		runtime "Release"
		optimize "on"




