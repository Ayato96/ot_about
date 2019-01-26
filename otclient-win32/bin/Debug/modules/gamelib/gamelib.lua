local cwd = (...):gsub("%.[^%.]+$", "") .. "."
require(cwd .. "const")
require(cwd .. "util")
require(cwd .. "protocol")
require(cwd .. "protocollogin")
require(cwd .. "protocolgame")
require(cwd .. "position")
require(cwd .. "game")

require(cwd .. "creature")
require(cwd .. "player")
require(cwd .. "market")
require(cwd .. "textmessages")
require(cwd .. "thing")
require(cwd .. "spells")

local _M = {}

function _M:init()

end

function _M:terminate()
    
end

return _M
