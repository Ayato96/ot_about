local cwd = (...):gsub("%.[^%.]+$", "") .. "."

return {
    name = "game_modaldialog",
    description = "Show and process modal dialogs",
    author = "Summ",
    website = "https://github.com/edubart/otclient",
    sandboxed = true,
    dependencies = {{"game_interface"}},
    classPath = cwd .. "modaldialog"
}
