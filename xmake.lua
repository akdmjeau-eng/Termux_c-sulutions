add_rules("mode.debug", "mode.release")

target("kernel_test")
    set_kind("binary")
    add_files("main.c")