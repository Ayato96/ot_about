local cwd = (...):gsub("%.[^%.]+$", "") .. "."

return {
    name = "game_outfit",
    description = "Change local player outfit",
    author = "baxnie, edubart",
    website = "https://github.com/edubart/otclient",
    sandboxed = true,
    classPath = cwd .. "outfit"
}
