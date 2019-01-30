local cwd = (...):gsub("%.[^%.]+$", "") .. "."
require(cwd .. "entergame")
require(cwd .. "characterlist")

local _M = {}

function _M.init()
    EnterGame.init()
    CharacterList.init()
end

function _M.terminate()
    EnterGame.terminate()
    CharacterList.terminate()
end

return _M