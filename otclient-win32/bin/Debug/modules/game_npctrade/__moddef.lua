local cwd = (...):gsub("%.[^%.]+$", "") .. "."

return {
    name = "game_npctrade",
    description = "NPC trade interface",
    author = "andrefaramir, baxnie",
    website = "https://github.com/edubart/otclient",
    sandboxed = true,
    classPath = cwd .. "npctrade"
}
