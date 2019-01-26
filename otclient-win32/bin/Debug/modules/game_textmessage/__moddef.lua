local cwd = (...):gsub("%.[^%.]+$", "") .. "."

return {
    name = "game_textmessage",
    description = "Manage game text messages",
    author = "edubart",
    website = "https://github.com/edubart/otclient",
    sandboxed = true,
    classPath = cwd .. "textmessage"
}
