add_rules("mode.debug", "mode.release")
add_rules("plugin.compile_commands.autoupdate", {outputdir = "."})

set_languages("c17")
set_warnings("all", "extra")
add_includedirs("includes")

target("simple_shell")
    set_kind("binary")
    add_files("src/**.c")
