-- global function used to translate texts
function _G.tr(text, ...)
    --[[
    local currentLocale = g_q.client_locales:getCurrentLocale()
    if currentLocale then
        if tonumber(text) and currentLocale.formatNumbers then
            local number = tostring(text):split(".")
            local out = ""
            local reverseNumber = number[1]:reverse()
            for i = 1, #reverseNumber do
                out = out .. reverseNumber:sub(i, i)
                if i % 3 == 0 and i ~= #number then
                    out = out .. currentLocale.thousandsSeperator
                end
            end

            if number[2] then
                out = number[2] .. currentLocale.decimalSeperator .. out
            end
            return out:reverse()
        elseif tostring(text) then
            local translation = currentLocale.translation[text]
            if not translation then
                if translation == nil then
                    if currentLocale.name ~= defaultLocaleName then
                        pdebug('Unable to translate: "' .. text .. '"')
                    end
                end
                translation = text
            end
            return string.format(translation, ...)
        end
    end
    ]]
    return text
end
