project "glfw"
	kind "StaticLib"
	language "C"
	architecture "x64"
	location "./"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	debugdir "./"

	includedirs "include"

	filter "system:windows"
		systemversion "latest"

		files "src/*.c"

		defines 
		{
			"_GLFW_WIN32",
			"_CRT_SECURE_NO_WARNINGS"
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"
	
	filter "configurations:Release"
		runtime "Release"
		symbols "on"
		optimize "Full"