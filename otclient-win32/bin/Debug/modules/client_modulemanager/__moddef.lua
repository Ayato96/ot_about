local cwd = (...):gsub("%.[^%.]+$", "") .. "."

return {
    name = "client_modulemanager",
    description = "Manage other modules",
    author = "baxnie, edubart",
    website = "https://github.com/edubart/otclient",
    sandboxed = true,
    dependencies = {{"client_topmenu"}},
    classPath = cwd .. "modulemanager"
}
