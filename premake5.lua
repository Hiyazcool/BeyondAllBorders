workspace "BeyondAllBorders"
	architecture "x64"

	configurations {
		"Debug",
		"Release",
		"Distribution"
	}
	startproject "BeyondAllBorders"
	--characterset ("Unicode")
	buildoptions { "/utf-8" } 


	linkoptions { "/utf-8" }
	outputDirectory = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	IncludeDir = {}
	IncludeDir["GLFW"] = "Auxilium/thirdParty/GLFW/include"
	IncludeDir["Glad"] = "Auxilium/thirdParty/Glad/include"
	IncludeDir["ImGUI"] = "Auxilium/thirdParty/imgui"

	include "Auxilium/thirdParty/GLFW"
	include "Auxilium/thirdParty/Glad"
	include "Auxilium/thirdParty/imgui"

	project "Catalyst"
		location "Catalyst"
		kind "SharedLib"
		language "C++"
		files {
			"%{prj.name}/source/**.h",
			"%{prj.name}/source/**.cpp"
		}
		targetdir ("bin/" .. outputDirectory .. "/%{prj.name}")
		objdir ("bin-int/" .. outputDirectory .. "/%{prj.name}")
		includedirs {
			"%{prj.name}/source/",
			"%{prj.name}/source/Events"
		}
		links {
			"GLFW",
			"opengl32.lib"
		}
		filter "system:windows"
			cppdialect "c++20"
			staticruntime "On"
			systemversion "latest"
			defines {
				"CATALYST_WINDOWS_PLATFORM",
				"CATALYST_BUILD_DLL",
				"_CRT_SECURE_NO_WARNINGS",
				"GLFW_INCLUDE_NONE"
			}
			postbuildcommands {
				("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputDirectory .. "/BeyondAllBorders"),
				("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputDirectory .. "/Auxilium")
			}
		filter "configurations:Debug"
			defines "AXLM_DEBUG"
			symbols "On"
		filter "configurations:Release"
			defines "AXLM_RELEASE"
			optimize "On"
		filter "configurations:Distribution"
			defines "AXLM_DIST"
			optimize "On"
	project "Auxilium"
		location "Auxilium"
		kind "SharedLib"
		language "C++"

		targetdir ("bin/" .. outputDirectory .. "/%{prj.name}")
		objdir ("bin-int/" .. outputDirectory .. "/%{prj.name}")

		pchheader "axpch.h"
		pchsource "Auxilium/source/axpch.cpp"

		files {
			"%{prj.name}/source/**.h",
			"%{prj.name}/source/**.cpp",
			"%{IncludeDir.GLFW}",
			"%{IncludeDir.Glad}"
		}
		includedirs {
			"%{prj.name}/thirdParty/spdlog/include",
			"%{prj.name}/source/Auxilium/Utils",
			"%{prj.name}/source/Auxilium/Events",
			"%{prj.name}/source/Auxilium/",
			"%{prj.name}/source/",
			"%{IncludeDir.GLFW}",
			"%{IncludeDir.Glad}",
			"%{IncludeDir.ImGUI}",
			"Catalyst/source/"
		}
		links {
			"Catalyst",
			"GLFW",
			"Glad",
			"ImGUI",
			"opengl32.lib"
		}
		filter "system:windows"
			cppdialect "c++20"
			staticruntime "On"
			systemversion "latest"
			buildoptions "/MDd"
			defines {
				"AXLM_WINDOWS_PLATFORM",
				"AXLM_BUILD_DLL",
				"CATALYST_WINDOWS_PLATFORM",
				"CATALYST_BUILD_DLL"

			}
			postbuildcommands {
				("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputDirectory .. "/BeyondAllBorders")
			}
		filter "configurations:Debug"
			defines "AXLM_DEBUG"
			symbols "On"
		filter "configurations:Release"
			defines "AXLM_RELEASE"
			optimize "On"
		filter "configurations:Distribution"
			defines "AXLM_DIST"
			optimize "On"

	project "BeyondAllBorders"
		location "BeyondAllBorders"
		kind "ConsoleApp"
		language "C++"

		targetdir ("bin/" .. outputDirectory .. "/%{prj.name}")
		objdir ("bin-int/" .. outputDirectory .. "/%{prj.name}")

		files {
			"%{prj.name}/source/**.h",
			"%{prj.name}/source/**.cpp"
		}
		includedirs {
			"Auxilium/thirdParty/spdlog/include",
			"Auxilium/source/Auxilium/Utils",
			"Auxilium/source/Auxilium/Events",
			"Auxilium/source/Auxilium/",
			"Auxilium/source",
			"Catalyst/source/"
		}
		links {
			"Auxilium",
			"Catalyst"
		}
		filter "system:windows"
			cppdialect "c++20"
			staticruntime "On"
			systemversion "latest"

			defines {
				"AXLM_WINDOWS_PLATFORM",
				"AXLM_BUILD_DLL",
				"CATALYST_WINDOWS_PLATFORM",
				"CATALYST_BUILD_DLL"

			}
		filter "configurations:Debug"
			defines "AXLM_DEBUG"
			symbols "On"
		filter "configurations:Release"
			defines "AXLM_RELEASE"
			optimize "On"
		filter "configurations:Distribution"
			defines "AXLM_DIST"
			optimize "On"
