
workspace "Melisma"
    architecture "x64"
    configurations {
        "Debug",
        "Release"
    }

    files {
        "premake5.lua",
        ".gitignore"
    }

    startproject "SandBox"

    project "Melisma"
        location "Melisma"
        kind "StaticLib"
        language "C++"
        cppdialect "C++20"
        staticruntime "On"

        targetdir ("%{prj.name}/lib/%{cfg.buildcfg}/")
        objdir ("obj/%{cfg.buildcfg}/%{prj.name}")

        files {
            "%{prj.name}/include/**.h",
            "%{prj.name}/src/**.h",
            "%{prj.name}/src/**.cpp",

            "%{prj.name}/dependencies/**.cpp",
            "%{prj.name}/dependencies/**.h",
            "%{prj.name}/dependencies/**.c"
        }

        includedirs {
            "%{prj.name}/include",

            "%{prj.name}/dependencies/glad/include",
            "%{prj.name}/dependencies/stbi/include",
            
            "C:/vclib/GLFW/include"
        }
        excludes {
            "%{prj.name}/include/melisma.h"
        }

        libdirs {
            "C:/vclib/GLFW/%{cfg.buildcfg}/lib"
        }

        links {
            "opengl32.lib",
            "glfw3.lib"
        }

        defines {
            "ML_BUILD"
        }            


        filter "configurations:Debug"
		    defines {
                "ML_DEBUG"
		    }
		    buildoptions "/MDd"
		    symbols "On"

        filter "configurations:Release"
            defines "ML_RELEASE"
            buildoptions "/MD"
            optimize "On"


    project "SandBox"
        location "SandBox"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++20"
        staticruntime "On"

        targetdir ("bin/%{cfg.buildcfg}/%{prj.name}")
        objdir ("obj/%{cfg.buildcfg}/%{prj.name}")

        files {
            "%{prj.name}/src/**.cpp",
            "%{prj.name}/src/**.h",
            "%{prj.name}/debugdir/shaders/**.glsl"
        }

        includedirs {
            "Melisma/include"
        }

        links {
            "Melisma"
        }

        debugdir "%{prj.name}/debugdir"


        filter "configurations:Debug"
            defines "ML_DEBUG"
            buildoptions "/MDd"
            symbols "On"

        filter "configurations:Release"
            defines "ML_RELEASE"
            buildoptions "/MD"
            optimize "On"