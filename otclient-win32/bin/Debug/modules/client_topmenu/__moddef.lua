local cwd = (...):gsub("%.[^%.]+$", "") .. "."

return {
    name = "client_topmenu",
    description = "reate the top menu",
    author = "edubart",
    website = "https://github.com/edubart/otclient",
    sandboxed = true,
    classPath = cwd .. "topmenu"
}
