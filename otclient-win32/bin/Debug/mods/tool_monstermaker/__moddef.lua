local cwd = (...):gsub("%.[^%.]+$", "") .. "."

return {
    name = "tool_monstermaker",
    description = "Monster maker.",
    author = "Egzo",
    website = "-",
    version = "0.9.0",
    sandboxed = true,
    dependencies = {{"game_interface"}},
    classPath = cwd .. "tool_monstermaker"
}
