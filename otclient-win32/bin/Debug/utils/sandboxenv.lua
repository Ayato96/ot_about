local getfenv, setfenv = getfenv, setfenv
local setmetatable = setmetatable

local _M = {
    _env_G = getfenv(0) or _Env,
}

function _M.getGlobalEnvironment()
    return _M._env_G
end

function _M.setGlobalEnvironment(env)
    -- setfenv (f, table)
    -- Sets the environment to be used by the given function. f can be a Lua function or a number that specifies the function at 
    --     that stack level: Level 1 is the function calling setfenv. setfenv returns the given function.
    -- As a special case, when f is 0 setfenv changes the environment of the running thread. In this case, setfenv returns no values.
    setfenv(0, env)
end

function _M.resetGlobalEnvironment()
    _M.setGlobalEnvironment(_M._env_G)
end

--/// @brief Creates a new environment table
--/// The new environment table is redirected to the global environment (aka _G),
--/// this allows to access global variables from _G in the new environment and
--/// prevents new variables in this new environment to be set on the global environment
function _M.new()
    local env = {}
    local env_mt = {__index = _M._env_G}
    return setmetatable(env, env_mt)
end

return _M
