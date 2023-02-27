project "DrowFortress"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	characterset ("ASCII")

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp",
	}

	defines
	{
		"SFML_STATIC"
	}

	includedirs
	{
		"src",
		"%{IncludeDir.entt}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.SFML}"
	}

	libdirs
	{
		"%{wks.location}/vendor/SFML/lib"
	}

	links
	{
		"flac.lib",
		"freetype.lib",
		"opengl32.lib",
		"winmm.lib",
		"gdi32.lib"
	}

	buildoptions
	{
		"/permissive"
	}


	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "DF_DEBUG"
		runtime "Debug"
		symbols "On"

		links
		{
			"sfml-graphics-s-d.lib",
			"sfml-window-s-d.lib",
			"sfml-system-s-d.lib"
		}

	filter "configurations:Release"
		defines "DF_RELEASE"
		runtime "Release"
		optimize "On"

		links
		{
			"sfml-graphics-s.lib",
			"sfml-window-s.lib",
			"sfml-system-s.lib"
		}