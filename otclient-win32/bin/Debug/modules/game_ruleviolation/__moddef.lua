local cwd = (...):gsub("%.[^%.]+$", "") .. "."

return {
    name = "game_ruleviolation",
    description = "Rule violation interface (Ctrl+Y)",
    author = "andrefaramir",
    website = "https://github.com/edubart/otclient",
    sandboxed = true,
    classPath = cwd .. "ruleviolation"
}
