local cwd = (...) .. "."

local _M = {
    require(cwd .. "de"),
    require(cwd .. "en"),
    require(cwd .. "es"),
    require(cwd .. "pl"),
    require(cwd .. "pt"),
    require(cwd .. "sv")
}

return _M
