project "glad"
	kind "StaticLib"
	language "C"
	architecture "x64"
	location "./"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	debugdir "./"

	includedirs "include"

	files "src/*.c"

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"
	
	filter "configurations:Release"
		runtime "Release"
		symbols "on"
		optimize "Full"