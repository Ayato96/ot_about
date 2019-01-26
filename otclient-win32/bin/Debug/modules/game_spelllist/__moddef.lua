local cwd = (...):gsub("%.[^%.]+$", "") .. "."

return {
    name = "game_spelllist",
    description = "View available spells",
    author = "Summ, Edubart",
    website = "https://github.com/edubart/otclient",
    sandboxed = true,
    classPath = cwd .. "spelllist"
}
