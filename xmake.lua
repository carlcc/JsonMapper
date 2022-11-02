set_project("jsonmapper")

option("jsonmapper-build-example")
    set_default(false)
    set_showmenu(true)
option_end()

add_requires("rapidjson")

target("jsonmapper")
    set_kind("headeronly")
    set_languages("cxx17")
    add_includedirs("include", { interface = true })
    add_packages("rapidjson", { public = true })
target_end()

if has_config("jsonmapper-build-example") then
    for _, filepath in ipairs(os.files("example/*.cpp")) do
        local targetName = path.basename(filepath)
        target(targetName)
            set_kind("binary")
            set_languages("cxx17")
            add_files(filepath)
            add_deps("jsonmapper")
        target_end()
    end
end
