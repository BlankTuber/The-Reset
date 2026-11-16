add_rules("mode.debug", "mode.release")
add_rules("plugin.compile_commands.autoupdate", {outputdir = "."})

set_languages("c17")
set_warnings("all", "extra")
add_includedirs("includes")

target("pemdas_calc")
    set_kind("binary")
    add_files("src/**.c")

target("pemdas_tests")
    set_kind("binary")
    set_default(false)
    add_files("src/**.c|main.c")
    add_files("tests/**.c")
    add_tests("default")
