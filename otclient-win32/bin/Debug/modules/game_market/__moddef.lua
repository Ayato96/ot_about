local cwd = (...):gsub("%.[^%.]+$", "") .. "."

return {
    name = "game_market",
    description = "Global item market system",
    author = "BeniS",
    website = "https://github.com/edubart/otclient",
    sandboxed = true,
    classPath = cwd .. "market"
}
