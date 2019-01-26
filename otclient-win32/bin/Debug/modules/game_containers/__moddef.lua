local cwd = (...):gsub("%.[^%.]+$", "") .. "."

return {
    name = "game_containers",
    description = "Manage containers",
    author = "edubart, baxnie",
    website = "https://github.com/edubart/otclient",
    sandboxed = true,
    classPath = cwd .. "containers"
}
