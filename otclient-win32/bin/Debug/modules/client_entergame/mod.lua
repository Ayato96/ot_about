local _M = {}

local cwd = (...):gsub("%.[^%.]+$", "") .. "."

function _M:init()
    require(cwd .. "entergame")
    require(cwd .. "characterlist")

    EnterGame.init()
    CharacterList.init()
end

function _M:terminate()
    EnterGame.terminate()
    CharacterList.terminate()
end

return _M
