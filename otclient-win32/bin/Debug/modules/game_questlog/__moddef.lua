local cwd = (...):gsub("%.[^%.]+$", "") .. "."

return {
    name = "game_questlog",
    description = "View game quests status",
    author = "edubart",
    website = "https://github.com/edubart/otclient",
    sandboxed = true,
    classPath = cwd .. "questlog"
}
