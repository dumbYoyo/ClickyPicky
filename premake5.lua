workspace "ClickyPicky"
    architecture "x64"
    
    configurations
    {
        "Debug",
        "Release"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}}"

project "ClickyPicky"
    location "ClickyPicky"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "%{prj.name}")

    files
    {
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/src/**.h",
        "%{prj.name}/libraries/glad/src/glad.c"
    }

    includedirs
    {
        "ClickyPicky/libraries/glm",
        "ClickyPicky/libraries/glad/include",
        "ClickyPicky/libraries/GLFW/include"
    }

    libdirs
    {
        "ClickyPicky/libraries/GLFW/lib"
    }

    links
    {
        "glfw3",
        "opengl32"
    }

    filter "configurations:Debug"
        defines "CP_DEBUG"
        symbols "On"

    filter "configurations:Release"
    defines "CP_RELEASE"
    optimize "On"