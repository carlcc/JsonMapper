set_project("jsonmapper")

option("jsonmapper-build-example")
    set_default(false)
    set_showmenu(true)
option_end()

option("jsonmapper-use-bundled-rapidjson")
    set_default(false)
    set_showmenu(true)
option_end()

if not has_config("jsonmapper-use-bundled-rapidjson") then
    add_requires("rapidjson")
end

target("jsonmapper")
    set_kind("headeronly")
    set_languages("cxx17")
    add_includedirs("include", { interface = true })

    if has_config("jsonmapper-use-bundled-rapidjson") then
        add_includedirs("thirdparty/rapidjson/include", { interface = true })
    else
        add_packages("rapidjson", { public = true })
    end
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
