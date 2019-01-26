local cwd = (...):gsub("%.[^%.]+$", "") .. "."

return {
    name = "game_console",
    description = "anage chat window",
    author = "edubart, andrefaramir, baxnie, sn4ake, BeniS",
    website = "https://github.com/edubart/otclient",
    sandboxed = true,
    classPath = cwd .. "console"
}
