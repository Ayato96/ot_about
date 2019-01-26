local cwd = (...):gsub("%.[^%.]+$", "") .. "."

return {
    name = "game_bugreport",
    description = "Bug report interface (Ctrl+Z)",
    author = "edubart",
    website = "https://github.com/edubart/otclient",
    sandboxed = true,
    classPath = cwd .. "bugreport"
}
