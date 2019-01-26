local cwd = (...):gsub("%.[^%.]+$", "") .. "."

return {
    name = "client_options",
    description = "Create the options window",
    author = "edubart, BeniS",
    website = "https://github.com/edubart/otclient",
    sandboxed = true,
    classPath = cwd .. "options"
}
