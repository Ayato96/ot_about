local cwd = (...):gsub("%.[^%.]+$", "") .. "."

return {
    name = "game_playerdeath",
    description = "Manage player deaths",
    author = "BeniS, edubart",
    website = "https://github.com/edubart/otclient",
    sandboxed = true,
    classPath = cwd .. "playerdeath"
}
