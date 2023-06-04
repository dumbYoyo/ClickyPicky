workspace "FlappyBird"
    architecture "x64"
    
    configurations
    {
        "Debug",
        "Release"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}}"

project "FlappyBird"
    location "FlappyBird"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    targetdir ("bin/" .. outputdir .. "%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "%{prj.name}")

    files
    {
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/src/**.h",
        "%{prj.name}/libraries/glad/src/glad.c",
        "%{prj.name}/libraries/stb/stb/stb_image.cpp"
    }

    includedirs
    {
        "FlappyBird/libraries/glm",
        "FlappyBird/libraries/glad/include",
        "FlappyBird/libraries/GLFW/include",
        "FlappyBird/libraries/glm",
        "FlappyBird/libraries/stb"
    }

    libdirs
    {
        "FlappyBird/libraries/GLFW/lib"
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