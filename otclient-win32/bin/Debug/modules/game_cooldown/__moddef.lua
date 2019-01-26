local cwd = (...):gsub("%.[^%.]+$", "") .. "."

return {
    name = "game_cooldown",
    description = "Spellcooldowns",
    author = "OTClient team",
    website = "https://github.com/edubart/otclient",
    sandboxed = true,
    classPath = cwd .. "cooldown"
}
