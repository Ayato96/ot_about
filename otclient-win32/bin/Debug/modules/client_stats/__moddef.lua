local cwd = (...):gsub("%.[^%.]+$", "") .. "."

return {
    name = "client_stats",
    description = "Sends client statistics to a server",
    author = "baxnie",
    website = "https://github.com/edubart/otclient",
    sandboxed = true,
    classPath = cwd .. "stats"
}
