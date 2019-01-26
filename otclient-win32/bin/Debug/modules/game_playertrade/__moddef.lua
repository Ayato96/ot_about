local cwd = (...):gsub("%.[^%.]+$", "") .. "."

return {
    name = "game_playertrade",
    description = "Allow to trade items with players",
    author = "edubart",
    website = "https://github.com/edubart/otclient",
    sandboxed = true,
    classPath = cwd .. "playertrade"
}
