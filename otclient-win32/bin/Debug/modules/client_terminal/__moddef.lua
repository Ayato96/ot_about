local cwd = (...):gsub("%.[^%.]+$", "") .. "."

return {
    name = "client_terminal",
    description = "Terminal for executing lua functions",
    author = "edubart",
    website = "https://github.com/edubart/otclient",
    sandboxed = true,
    classPath = cwd .. "terminal"
}
