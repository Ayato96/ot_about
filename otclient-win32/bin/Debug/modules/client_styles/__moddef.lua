local cwd = (...):gsub("%.[^%.]+$", "") .. "."

return {
    name = "client_styles",
    description = "Load client fonts and styles",
    author = "edubart",
    website = "https://github.com/edubart/otclient",
    sandboxed = true,
    classPath = cwd .. "styles"
}
