local cwd = (...):gsub("%.[^%.]+$", "") .. "."

return {
    name = "game_skills",
    description = "Manage skills window",
    author = "baxnie, edubart",
    website = "https://github.com/edubart/otclient",
    sandboxed = true,
    dependencies = {{"game_interface"}},
    classPath = cwd .. "skills"
}
