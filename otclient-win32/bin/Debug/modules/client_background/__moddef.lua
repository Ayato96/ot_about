local cwd = (...):gsub("%.[^%.]+$", "") .. "."

return {
    name = "client_background",
    description = "Handles the background of the login screen",
    author = "edubart",
    website = "https://github.com/edubart/otclient",
    sandboxed = true,
    dependencies = {{"client_topmenu"}},
    classPath = cwd .. "background"
}
