package.path = package.path .. ";./?.lua;./?/init.lua;./lua/?.lua;./lua/?/init.lua;./src/?.lua;./src/?/init.lua"
package.path = package.path .. ";./lualibs/?.lua;./lualibs/?/init.lua"
package.cpath = package.cpath .. ";./?.dll;./clibs/?.dll"

-- this is the first file executed when the application starts
-- we have to load the first modules form here

-- setup logger
g_logger.setLogFile(g_resources.getWorkDir() .. g_app.getCompactName() .. ".log")
g_logger.info(os.date("== application started at %b %d %Y %X"))

-- print first terminal message
g_logger.info(
    g_app.getName() ..
        " " ..
            g_app.getVersion() ..
                " rev " ..
                    g_app.getBuildRevision() ..
                        " (" ..
                            g_app.getBuildCommit() ..
                                ") built on " .. g_app.getBuildDate() .. " for arch " .. g_app.getBuildArch()
)

-- add data directory to the search path
if not g_resources.addSearchPath(g_resources.getWorkDir() .. "data", true) then
    g_logger.fatal("Unable to add data directory to the search path.")
end

-- add modules directory to the search path
local workdir = g_resources.getWorkDir()
if not g_resources.addSearchPath(g_resources.getWorkDir() .. "modules", true) then
    g_logger.fatal("Unable to add modules directory to the search path." .. workdir)
end

-- try to add mods path too
g_resources.addSearchPath(g_resources.getWorkDir() .. "mods", true)

-- setup directory for saving configurations
g_resources.setupUserWriteDir(("%s/"):format(g_app.getCompactName()))

-- search all packages
g_resources.searchAndAddPackages("/", ".otpkg", true)

-- load settings
g_configs.loadSettings("/config.otml")

-- load modules
g_modules = require("utils.modulemanager")
g_modules.loadModule("corelib")
g_modules.loadModule("gamelib")
g_modules.loadModule("client")
g_modules.loadModule("game_interface")

g_modules.loadModule("tool_monstermaker", "mods.tool_monstermaker")

--
local script = "/" .. g_app.getCompactName() .. "rc.lua"

if g_resources.fileExists(script) then
    dofile(script)
end
