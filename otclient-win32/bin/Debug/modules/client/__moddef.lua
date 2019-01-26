local cwd = (...):gsub("%.[^%.]+$", "") .. "."

return {
    name = "client",
    description = "Initialize the client and setups its main window",
    author = "edubart",
    website = "https://github.com/edubart/otclient",
    reloadable = false,
    sandboxed = true,
    loadLater = {
        {"client_styles"},
        {"client_locales"},
        {"client_topmenu"},
        {"client_background"},
        {"client_options"},
        {"client_entergame"},
        {"client_terminal"},
        {"client_modulemanager"},
        {"client_serverlist"},
        {"client_stats"}
    },
    classPath = cwd .. "client"
}
