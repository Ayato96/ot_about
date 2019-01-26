local cwd = (...):gsub("%.[^%.]+$", "") .. "."

return {
    name = "corelib",
    description = "Contains core lua classes, functions and constants used by other modules",
    author = "OTClient team",
    website = "https://github.com/edubart/otclient",
    reloadable = false,
    classPath = cwd .. "corelib"
}
