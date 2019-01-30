local cwd = (...):gsub("%.[^%.]+$", "") .. "."
require(cwd .. "serverlist")
require(cwd .. "addserver")

function init()
    ServerList.init()
    AddServer.init()
end

function terminate()
    ServerList.terminate()
    AddServer.terminate()
end
