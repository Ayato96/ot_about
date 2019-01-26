local cwd = (...):gsub("%.[^%.]+$", "") .. "."

return {
    name = "gamelib",
    description = "Contains game related classes",
    author = "OTClient team",
    website = "https://github.com/edubart/otclient",
    dependencies = {{"game_things"}},
    classPath = cwd .. "gamelib"
}
