local cwd = (...):gsub("%.[^%.]+$", "") .. "."
require(cwd .. "math")
require(cwd .. "string")
require(cwd .. "table")
require(cwd .. "bitwise")
require(cwd .. "struct")

require(cwd .. "const")
require(cwd .. "util")
require(cwd .. "globals")
require(cwd .. "config")
require(cwd .. "settings")
require(cwd .. "keyboard")
require(cwd .. "mouse")
require(cwd .. "net")

--require(cwd .. "classes")

-- ui
require(cwd .. "ui.uiwidget")
require(cwd .. "ui.uiwindow")
require(cwd .. "ui.effects")
require(cwd .. "ui.tooltip")
require(cwd .. "ui.uibutton")
require(cwd .. "ui.uicheckbox")
require(cwd .. "ui.uicombobox")
require(cwd .. "ui.uiimageview")
require(cwd .. "ui.uiinputbox")
require(cwd .. "ui.uilabel")
require(cwd .. "ui.uimessagebox")
require(cwd .. "ui.uiminiwindow")
require(cwd .. "ui.uiminiwindowcontainer")
require(cwd .. "ui.uimovabletabbar")
require(cwd .. "ui.uipopupmenu")
require(cwd .. "ui.uipopupscrollmenu")
require(cwd .. "ui.uiprogressbar")
require(cwd .. "ui.uiradiogroup")
require(cwd .. "ui.uiresizeborder")
require(cwd .. "ui.uiscrollarea")
require(cwd .. "ui.uiscrollbar")
require(cwd .. "ui.uispinbox")
require(cwd .. "ui.uisplitter")
require(cwd .. "ui.uitabbar")
require(cwd .. "ui.uitable")
require(cwd .. "ui.uitextedit")

require(cwd .. "inputmessage")
require(cwd .. "outputmessage")

local _M = {}

function _M.init()

end

function _M.terminate()
    
end

return _M
