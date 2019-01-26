local cwd = (...):gsub("%.[^%.]+$", "") .. "."

return {
    name = "client_serverlist",
    description = "Manages a server list of previously entered servers",
    author = "BeniS",
    website = "https://github.com/edubart/otclient",
    sandboxed = true,
    dependencies = {{"client_entergame"}},
    classPath = cwd .. "mod"
}
