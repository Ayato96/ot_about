local cwd = (...):gsub("%.[^%.]+$", "") .. "."

return {
    name = "game_playermount",
    description = "Manage player mounts",
    author = "BeniS",
    website = "https://github.com/edubart/otclient",
    sandboxed = true,
    classPath = cwd .. "playermount"
}
