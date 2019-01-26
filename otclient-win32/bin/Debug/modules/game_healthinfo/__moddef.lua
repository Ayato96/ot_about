local cwd = (...):gsub("%.[^%.]+$", "") .. "."

return {
    name = "game_healthinfo",
    description = "Displays health, mana points, soul points, and conditions",
    author = "edubart, BeniS",
    website = "https://github.com/edubart/otclient",
    sandboxed = true,
    classPath = cwd .. "healthinfo"
}
