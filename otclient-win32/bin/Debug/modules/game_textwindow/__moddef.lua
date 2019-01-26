local cwd = (...):gsub("%.[^%.]+$", "") .. "."

return {
    name = "game_textwindow",
    description = "Allow to edit text books and lists",
    author = "edubart, BeniS",
    website = "https://github.com/edubart/otclient",
    sandboxed = true,
    dependencies = {{"game_interface"}},
    classPath = cwd .. "textwindow"
}
