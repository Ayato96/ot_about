local cwd = (...):gsub("%.[^%.]+$", "") .. "."

return {
    name = "client_locales",
    description = "Translates texts to selected language",
    author = "baxnie, edubart",
    website = "https://github.com/edubart/otclient",
    sandboxed = true,
    dependencies = {{"client_topmenu"}},
    classPath = cwd .. "locales"
}
