local cwd = (...):gsub("%.[^%.]+$", "") .. "."

return {
    name = "game_battle",
    description = "Manage battle window",
    author = "andrefaramir, BeniS",
    website = "https://github.com/edubart/otclient",
    sandboxed = true,
    classPath = cwd .. "battle"
}
