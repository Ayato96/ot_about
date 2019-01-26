local require = require
local type = type
local tbl_insert = table.insert

local _M = {}

function _M:load()
    -- init module
    if type(self.init) == "function" then
        self:init()
    end

    self._m__isLoaded = true
end

function _M:unload()
    if self._mt_canUnload and self._m__isLoaded then
        -- terminate module
        if type(self.terminate) == "function" then
            self:terminate()
        end

        package.loaded[self._mt_modulePath] = nil
 
        self._m__isLoaded = false
    end
end

function _M.newmeta(moddef, modulePath)
    return {
        _mt_name = moddef.name,
        _mt_modulePath = modulePath,
        _mt_author = moddef.author,
        _mt_website = moddef.website,
        _mt_version = moddef.version,
        _mt_description = moddef.description,
        _mt_canReload = moddef.reloadable or false,
        _mt_canUnload = moddef.reloadable or false,
        _mt_sandboxed = moddef.sandboxed or false,
        _mt_dependencies = moddef.dependencies,
        _mt_loadLater = moddef.loadLater,
        _mt_classPath = moddef.classPath,

        _mt_load = _M.load,
        _mt_unload = _M.unload

    }
end

return _M
