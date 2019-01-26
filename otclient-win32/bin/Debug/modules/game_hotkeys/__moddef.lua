local cwd = (...):gsub("%.[^%.]+$", "") .. "."

return {
    name = "game_hotkeys",
    description = "Manage client hotkeys",
    author = "andrefaramir, BeniS",
    website = "https://github.com/edubart/otclient",
    sandboxed = true,
    classPath = cwd .. "hotkeys_manager"
}
