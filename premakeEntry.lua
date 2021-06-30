workspace "GameEngine"
	architecture "x64"

	configurations { "Debug", "Beta", "Dist" }

outputdir = "${cfg.system}/%{cfg.buildcfg}-${cfg.architecture}"

project "Engine"
	location "../Engine"
	kind "StaticLib"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/${prj.name}")
	objdir ("bin/int/" .. outputdir .. "/${prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		-- "%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines {
			"EN_PLATFORM_WINDOWS"
		}
		
	filter "configurations:Debug"
		defines "EN_DEBUG"
		symbols "On"
	filter "configurations:Beta"
		defines "EN_BETA"
		symbols "On"
	filter "configurations:Dist"
		defines "EN_DIST"
		symbols "On"

project "Editor"
	location "../Editor"
	kind "ConsoleApp"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/${prj.name}")
	objdir ("bin/int/" .. outputdir .. "/${prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		-- "Engine/vendor/spdlog/include",
		"Engine/src"
	}

	links {	"Engine" }

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines {
			"EN_PLATFORM_WINDOWS"
		}
		
	filter "configurations:Debug"
		defines "EN_DEBUG"
		symbols "On"
	filter "configurations:Beta"
		defines "EN_BETA"
		symbols "On"
	filter "configurations:Dist"
		defines "EN_DIST"
		symbols "On"



