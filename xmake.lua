set_project("enhanced")

add_rules("mode.release", "mode.debug", "mode.releasedbg", "mode.minsizerel")

set_languages("c17", "c++20")
set_allowedmodes("debug", "release", "releasedbg", "minsizerel")

if get_config("toolchain") == "msvc" or get_config("toolchain") == "clang-cl" then
    if is_mode("debug") or is_mode("releasedbg") then
        add_cxflags("/MDd")
    else
        add_cxflags("/MD")
    end
end

set_warnings("all")

includes("**/xmake.lua")

target("test")
    set_kind("binary")
    add_deps("core-static")
    add_files("test/*.c", "test/*.cpp")
    add_headerfiles("test/*.h")
    add_includedirs("test")
