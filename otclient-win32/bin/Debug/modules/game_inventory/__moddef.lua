local cwd = (...):gsub("%.[^%.]+$", "") .. "."

return {
    name = "game_inventory",
    description = "View local player equipments window",
    author = "baxnie, edubart, BeniS",
    website = "https://github.com/edubart/otclient",
    sandboxed = true,
    classPath = cwd .. "inventory"
}
