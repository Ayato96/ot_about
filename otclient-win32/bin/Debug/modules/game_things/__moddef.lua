local cwd = (...):gsub("%.[^%.]+$", "") .. "."

return {
    name = "game_things",
    description = "Contains things spr and dat",
    reloadable = false,
    sandboxed = true,
    classPath = cwd .. "things"
}
