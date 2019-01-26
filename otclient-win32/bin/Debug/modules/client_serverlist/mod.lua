local _M = {}

local cwd = (...):gsub("%.[^%.]+$", "") .. "."

function _M:init()
    require(cwd .. "serverlist")
    require(cwd .. "addserver")

    ServerList.init()
    AddServer.init()
end

function _M:terminate()
    ServerList.terminate()
    AddServer.terminate()
end

return _M
