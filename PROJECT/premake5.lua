workspace "Project"
    architecture "x64"
    multiprocessorcompile "On"
    startproject "Game"

    configurations
    {
        "Debug",
        "Release"  
    }

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    include "vendor/glfw"
    include "vendor/glad"

    filter "action:vs*"
        buildoptions {"/utf-8"}

project "Core"
    location "%{prj.name}"
    kind "StaticLib"
    language "C++"
    cppdialect "C++23"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/src",
        "vendor/glfw/include",
        "vendor/glad/include",
        "%{prj.name}/vendor"
    }
    
    links
    {
        "GLFW",
        "glad"
    }

    filter "system:windows"
        systemversion "latest"
        links "opengl32"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        runtime "Release"
        optimize "On"

    filter {}

    postbuildcommands
    {
        "{COPYDIR} %{prj.location}/assets %{wks.location}/bin/" .. outputdir .. "/Game/assets"
    }
    
project "Game"
    location "%{prj.name}"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++23"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
    debugdir ("bin/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "Core/src",
        "vendor/glfw/include",
        "vendor/glad/include",
        "Core/vendor"
    }

    links
    {
        "Core"
    }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        runtime "Release"
        optimize "On"

    filter {}

    
-- CUSTOM PREMAKE ACTIONS
newaction {
    trigger = "clean",
    description = "Remove all binaries, intermediate binaries, and vs files.",
    execute = function()
        print("Removing binaries")
        os.rmdir("./bin")
        print("Removing intermediate binaries")
        os.rmdir("./bin-int")
        print("Removing project files")
        os.rmdir("./.vs")
        os.remove("**.sln")
        os.remove("**.vcxproj")
        os.remove("**.vcxproj.filters")
        os.remove("**.vcxproj.user")
        print("Done")
    end
}
