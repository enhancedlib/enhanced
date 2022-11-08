add_files("sources/**.c", "sources/**.cpp")
add_headerfiles("include/**.h")
add_includedirs("include", {public = true})

add_defines("ENHANCED_BUILDING", {private = true})
add_defines("ENHANCED_CORE_BUILDING", {private = true})

target("core-static")
    set_kind("static")
    set_filename("libenhanced-core.lib")

target("core-shared")
    set_kind("shared")
    set_filename("enhanced-core.dll")

    add_defines("ENHANCED_CORE_SHARED_LIB", {public = true})
