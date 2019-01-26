local cwd = (...):gsub("%.[^%.]+$", "") .. "."

return {
    name = "game_combatcontrols",
    description = "Combat controls window",
    author = "edubart, BeniS",
    website = "https://github.com/edubart/otclient",
    sandboxed = true,
    classPath = cwd .. "combatcontrols"
}
