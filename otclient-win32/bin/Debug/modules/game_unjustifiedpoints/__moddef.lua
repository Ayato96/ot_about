local cwd = (...):gsub("%.[^%.]+$", "") .. "."

return {
    name = "game_unjustifiedpoints",
    description = "View unjustified points",
    author = "Summ",
    website = "https://github.com/edubart/otclient",
    sandboxed = true,
    classPath = cwd .. "unjustifiedpoints"
}
