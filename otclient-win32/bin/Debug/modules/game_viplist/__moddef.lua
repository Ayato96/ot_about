local cwd = (...):gsub("%.[^%.]+$", "") .. "."

return {
    name = "game_viplist",
    description = "Manage vip list window",
    author = "baxnie, edubart",
    website = "https://github.com/edubart/otclient",
    sandboxed = true,
    classPath = cwd .. "viplist"
}
