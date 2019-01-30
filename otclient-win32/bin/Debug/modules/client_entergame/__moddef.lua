local cwd = (...):gsub("%.[^%.]+$", "") .. "."

return {
    name = "client_entergame",
    description = "Manages enter game and character list windows",
    author = "edubart",
    website = "https://github.com/edubart/otclient",
    sandboxed = false, -- 'EnterGame' and 'CharacterList' is global var
    dependencies = {{"client_topmenu"}},
    classPath = cwd .. "mod"
}
