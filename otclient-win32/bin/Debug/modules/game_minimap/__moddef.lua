local cwd = (...):gsub("%.[^%.]+$", "") .. "."

return {
    name = "game_minimap",
    description = "Manage minimap",
    author = "edubart, BeniS",
    website = "https://github.com/edubart/otclient",
    sandboxed = true,
    classPath = cwd .. "minimap"
}
