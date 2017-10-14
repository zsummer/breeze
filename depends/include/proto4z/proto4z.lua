
--[[
/*
 * proto4z License
 * -----------
 * 
 * proto4z is licensed under the terms of the MIT license reproduced below.
 * This means that proto4z is free software and can be used for both academic
 * and commercial purposes at absolutely no cost.
 * 
 * 
 * ===============================================================================
 * 
 * Copyright (C) 2013-2017 YaweiZhang <yawei.zhang@foxmail.com>.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 * 
 * ===============================================================================
 * 
 * (end of COPYRIGHT)
 */
 ]]--


-- proto4z core file
-- Author: zhangyawei
-- mail:yawei.zhang@foxmail.com
-- date: 2015-01-12



Proto4z = Proto4z or {}

--Proto4z.__with_tag = true


function Proto4z.pack(obj, name)
    local data = {}
    data[1] = Proto4zUtil.pack(0, "ui16") -- reseve field
    data[2] = Proto4zUtil.pack(Proto4z[name].__protoID, "ui16") -- proto id field
    Proto4z.__encode(obj, name, data)
    local dst = table.concat(data)
    local head = Proto4zUtil.pack(#dst+4, "ui32") -- proto len field
    return head .. dst
end


function Proto4z.unpack(binData, name)
    local head = Proto4zUtil.unpack(binData, 1, "ui32")
    local reserve = Proto4zUtil.unpack(binData, 5, "ui16")
    local proto = Proto4zUtil.unpack(binData, 7, "ui16")
    local result = {}
    Proto4z.__decode(binData, 9, name, result)
    return proto, result
end


--[[--
encode protocol table to binary stream
@param encode obj.  protocol table 
@param encode name. protocol name
@return binary stream
]]
function Proto4z.encode(obj, name)
    local data = {}
    Proto4z.__encode(obj, name, data)
    return table.concat(data)
end

--[[--
decode binary stream to protocol table
@param decode binData.  binary stream
@param decode name.  dest protocol name
@return protocol table
]]
function Proto4z.decode(binData, name)
    --print("decode id = " .. id)
    local result = {}
    Proto4z.__decode(binData, 1, name, result)
    return result
end


--[[--
make map [protocol id = protocol name]
@param register id.  protocol id 
@param register name. protocol name
@return  no result
]]
function Proto4z.register(id, name)
    Proto4z.__protoNames = Proto4z.__protoNames or {}
    if Proto4z.__protoNames[id] ~= nil then
        error("id already register. id=" .. id .. " registrered name=" .. Proto4z.__protoNames[id]  .. ", new name=" .. name .. ": " .. debug.traceback())
    end
    if type(name) ~= "string" then
        error("name ~= string " .. debug.traceback())
    end
    Proto4z.__protoNames[id] = name
end

--[[--
get the protocol name from protoco id.
@param register id.  protocol id 
@return  protocol name
]]
function Proto4z.getName(id)
    return Proto4z and Proto4z.__protoNames and Proto4z.__protoNames[id]
end









------------------------------------------------
-- private impl
------------------------------------------------

local function isInnerType(t, withstring)
    return t == "ui16" or t == "ui32" or t == "ui64" or t == "float" or (withstring and t == "string") 
        or t == "i8" or t == "ui8" or t == "i16" or t == "i32" or t == "i64" or t == "double"
end

--[[--
decode binary stream to protocol table
@param __decode binData.  binary stream
@param __decode pos.  current binary begin index
@param __decode name.  dest protocol name
@param __decode result. output protocol table.
@return next begin index
]]
function Proto4z.__decode(binData, pos, name, result)
    --print(name .. ":" .. pos)
    local proto = Proto4z[name]
    local v, p
    p = pos
    if proto.__protoDesc == "array" then
        local len
        len, p = Proto4zUtil.unpack(binData, p, "ui32")
        for i=1, len do
            v, p = Proto4zUtil.unpack(binData, p, proto.__protoTypeV)
            if v ~= nil then
                result[i] = v
            else
                result[i] = {}
                p = Proto4z.__decode(binData, p, proto.__protoTypeV, result[i])
            end
        end
    elseif proto.__protoDesc == "map" then
        local len
        local k
        len, p = Proto4zUtil.unpack(binData, p, "ui32")
        for j=1, len do
            k, p = Proto4zUtil.unpack(binData, p, proto.__protoTypeK)
            v, p = Proto4zUtil.unpack(binData, p, proto.__protoTypeV)
            if v ~= nil then
                result[k] = v
            else
                result[k] = {}
                p = Proto4z.__decode(binData, p, proto.__protoTypeV, result[k])
            end
        end
    else
        local offset, tag
        if Proto4z.__with_tag then 
            offset, p = Proto4zUtil.unpack(binData, p, "ui32")
            offset = p + offset
            tag, p = Proto4zUtil.unpack(binData, p, "ui64")
        end
        for i = 1, #proto do
            local desc = proto[i]
            if (not Proto4z.__with_tag and  not desc.del ) 
                or  (Proto4z.__with_tag and Proto4zUtil.testTag(tag, i)) then
                v, p = Proto4zUtil.unpack(binData, p, desc.type)
                if v ~= nil then
                    result[desc.name] = v
                else
                    result[desc.name] = {}
                    p = Proto4z.__decode(binData, p, desc.type, result[desc.name])
                end
            end
        end
        if Proto4z.__with_tag then
            p = offset
        end
    end
    return p
end


--[[--
encode protocol table to binary stream
@param __encode obj.  protocol table 
@param __encode name. protocol name
@param __encode data.  output binary stream
@return no result
]]
function Proto4z.__encode(obj, name, data)
    local proto = Proto4z[name]
    --array
    --------------------------------------
    if proto.__protoDesc == "array" then
        local obj = obj or {}
        table.insert(data, Proto4zUtil.pack(#obj, "ui32", name))
        for i =1, #obj do
            local v = obj[i]
            if proto.__protoTypeV == "string" then
                local v = ""
                table.insert(data, Proto4zUtil.pack(#v, "ui32", name))
                table.insert(data, v)
            elseif isInnerType(proto.__protoTypeV) then
                table.insert(data, Proto4zUtil.pack(v, proto.__protoTypeV, name))
            else
                Proto4z.__encode(v, proto.__protoTypeV, data)
            end
        end
    --map
    --------------------------------------
    elseif proto.__protoDesc == "map" then
        local obj = obj or {}
        table.insert(data, Proto4zUtil.pack(0, "ui32", name))
        local fixPos = #data
        local mapCount = 0
        for k, v in pairs(obj) do
            mapCount = mapCount + 1
            if proto.__protoTypeK == "string" then
                table.insert(data, Proto4zUtil.pack(#k, "ui32", name))
                table.insert(data, k)
            else
                table.insert(data, Proto4zUtil.pack(k, proto.__protoTypeK, name))
            end
            if proto.__protoTypeV == "string" then
                local v = v or ""
                table.insert(data, Proto4zUtil.pack(#v, "ui32", name))
                table.insert(data, v)
            elseif  isInnerType(proto.__protoTypeV) then
                table.insert(data, Proto4zUtil.pack(v, proto.__protoTypeV, name))
            else
                Proto4z.__encode(v, proto.__protoTypeV, data)
            end
        end
        data[fixPos] = Proto4zUtil.pack(mapCount, "ui32", name)
    --base typ or struct or proto
    --------------------------------------
    else
        local curdata, offset
        curdata = {}
        for i=1, #proto do
            local desc = proto[i]
            if not desc.del then
                if type(obj) ~= "table" then obj = {} end
                local val = obj[desc.name]
                if desc.type == "string" then
                    local val = val or ""
                    table.insert(curdata, Proto4zUtil.pack(#val, "ui32", name))
                    table.insert(curdata, val)
                elseif isInnerType(desc.type)  then
                    table.insert(curdata, Proto4zUtil.pack(val, desc.type, name))
                else
                    Proto4z.__encode(val, desc.type, curdata)
                end
            end
        end
        curdata = table.concat(curdata)
        table.insert(data, curdata)
    end
end



--------------------------------------------------------------------------
-----  assist
--------------------------------------------------------------------------

--[[--
print binary stream with hexadecimal string
@param decode binData.  binary stream
@return no result
]]
function Proto4z.putbin(binData)
    local str = ""
    for i = 1, #binData do
        str = str .. string.format("%02x ",string.byte(binData, i))
    end
    print("[len:" .. #binData .. "]" .. str)
end



--[[--
trim string
]]
function Proto4z.trim(input)
    input = string.gsub(input, "^[ \t\n\r]+", "")
    return string.gsub(input, "[ \t\n\r]+$", "")
end



--[[--
split string
]]
function Proto4z.split(input, delimiter)
    input = tostring(input)
    delimiter = tostring(delimiter)
    if (delimiter=='') then return false end
    local pos,arr = 0, {}
    -- for each divider found
    for st,sp in function() return string.find(input, delimiter, pos, true) end do
        table.insert(arr, string.sub(input, pos, st - 1))
        pos = sp + 1
    end
    table.insert(arr, string.sub(input, pos))
    return arr
end

--[[--
dump table with nesting
]]
function Proto4z.dump(value, desciption, nesting)
    local nesting = nesting or 5
    local log = (summer and summer.logdd) or print

    local lookupTable = {}

    local function _v(v)
        if type(v) == "string" then
            v = "\"" .. v .. "\""
        end
        return tostring(v)
    end

    local traceback = Proto4z.split(debug.traceback("", 2), "\n")
    log("dump from: ", Proto4z.trim(traceback[3]))


    local function _dump(value, desciption, indent, nest, keylen)
        desciption = desciption or "<var>"
        local spc = ""
        if type(keylen) == "number" then
            spc = string.rep(" ", keylen - string.len(_v(desciption)))
        end
        if type(value) ~= "table" then
            log(indent, _v(desciption), spc, " = ", _v(value))
        elseif lookupTable[value] then
            log(indent, desciption, spc, " = *REF*")
        else
            lookupTable[value] = true
            if nest > nesting then
                log(indent, desciption, " = *MAX NESTING*")
            else
                log(indent, _v(desciption), " = {")
                local indent2 = indent.."    "
                local keys = {}
                local keylen = 0
                local values = {}
                for k, v in pairs(value) do
                    keys[#keys + 1] = k
                    local vk = _v(k)
                    local vkl = string.len(vk)
                    if vkl > keylen then keylen = vkl end
                    values[k] = v
                end
                table.sort(keys, function(a, b)
                    if type(a) == "number" and type(b) == "number" then
                        return a < b
                    else
                        return tostring(a) < tostring(b)
                    end
                end)
                for i, k in ipairs(keys) do
                    _dump(values[k], k, indent2, nest + 1, keylen)
                end
                log(indent, "}")
            end
        end
    end
    _dump(value, desciption, "- ", 1)

end


--[[--
fastdump table with nesting
]]
function Proto4z.fastdump(value, desciption, nesting)
    local nesting = nesting or 5
    local log = (summer and summer.logdd) or print

    local lookupTable = {}



    local traceback = Proto4z.split(debug.traceback("", 2), "\n")
    log("dump from: ", Proto4z.trim(traceback[3]))

    local function fastIndent(nest)
        if nest <= 1 then return "- "
        elseif nest == 2 then return "-     "
        elseif nest == 3 then return "-         "
        elseif nest == 4 then return "-             "
        elseif nest == 5 then return "-                 "
        else return "- " .. string.rep("    ", nest - 1) 
        end
    end

    local function _dump(value, desciption, nest)
        desciption = desciption or "<var>"
        if type(value) ~= "table" then
            log(fastIndent(nest), desciption, " = ", value)
        elseif lookupTable[value] then
            log(fastIndent(nest), desciption, " = *REF*")
        else
            lookupTable[value] = true
            if nest > nesting then
                log(fastIndent(nest), desciption, " = *MAX NESTING*")
            else
                log(fastIndent(nest), desciption, " = {")
                for k, v in pairs(value) do
                    _dump(v, k, nest + 1)
                end
                log(fastIndent(nest), "}")
            end
        end
    end
    _dump(value, desciption, 1)
end

