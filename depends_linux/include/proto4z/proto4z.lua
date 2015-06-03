
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
 * Copyright (C) 2013-2015 YaweiZhang <yawei.zhang@foxmail.com>.
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



--[[--
encode protocol table to binary stream
@param encode obj.  protocol table 
@param encode name. protocol name
@return binary stream
]]
function Proto4z.encode(obj, name)
    local data = {data=""}
    Proto4z.__encode(obj, name, data)
    return data.data
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
    if Proto4z.__protos == nil then
        Proto4z.__protos = {}
    end
    if Proto4z.__protos[id] ~= nil then
        error("id already register. id=" .. id .. " registrered name=" .. Proto4z.__protos[id]  .. ", new name=" .. name .. ": " .. debug.traceback())
    end
    if type(name) ~= "string" then
        error("name ~= string " .. debug.traceback())
    end
    Proto4z.__protos[id] = name
end

--[[--
get the protocol name from protoco id.
@param register id.  protocol id 
@return  protocol name
]]
function Proto4z.getName(id)
    if Proto4z.__protos == nil then
        return nil
    end
    if Proto4z.__protos[id] == nil then
        return nil
    end
    return Proto4z.__protos[id]
end









------------------------------------------------
-- private impl
------------------------------------------------

--[[
]]
function Proto4z.__checkVal(val)
    local tp = type(val)
    if(tp == "string" or tp == "number" or tp == "table") then
        return true
    end
    error("Proto4z.__checkVal error. val type=" .. tp .. ", trace=" .. debug.traceback())
end
function Proto4z.__isInnerType(tp)
    if tp == "i8" or tp == "ui8" or tp == "i16" or tp == "ui16"
        or tp == "i32" or tp == "ui32" or tp == "i64" or tp == "ui64"
        or tp == "float" or tp == "double" or tp == "string" then
        return true
    end
    return false
end
function Proto4z.__isUserType(tp)
    if type(Proto4z[tp]) == "table" then
        return true
    end
    return false
end

function Proto4z.__checkType(tp)
    if tp == nil then
        error("Proto4z.__checkType error. type == nil, trace=" .. debug.traceback())
    end
    if Proto4z.__isInnerType(tp) then
        return "base"
    end

    if Proto4z.__isUserType(tp) then
        return "table"
    end

    error("Proto4z.__checkType error. unknown val type=" .. tp .. ", trace=" .. debug.traceback())
end


-- lua 5.1 + lpack
function Proto4z.__pack(val, tp)
    if val == nil or tp == nil then
        error(debug.traceback())
    end
    --print(tp .. "[" .. val .. "]")
    -- integer type
    if     tp == "i8" or tp == "char" then
        return bpack("<c", val)
    elseif tp == "ui8" or tp == "unsigned char" then
        return bpack("<b", val)
    elseif tp == "i16" or tp == "short" then
        return bpack("<h", val)
    elseif tp == "ui16" or tp == "unsigned short" then
        return bpack("<H", val)    
    elseif tp == "i32" or tp == "int" then
        return bpack("<i", val)
    elseif tp == "ui32" or tp == "unsigned int" then
        return bpack("<I", val)    
    elseif tp == "i64" or tp == "long long" or tp == "ui64" or tp == "unsigned long long" then
        return string.sub(val, 1, 8)


    -- string type
    elseif tp == "string" then
        local i = bpack("<I", #val)
        i = i .. bpack("A", val)
        return i

    -- float type
    elseif tp == "float" then
        return bpack("<f", val)
    elseif tp == "double" then
        return bpack("<d", val)

    -- error
    else
        error("unknown base data type when __pack it. val type=" .. type(val) .. "trace: " .. debug.traceback())
    end
end


-- lua 5.1 + lpack
function Proto4z.__unpack(binData, pos, tp)
    if binData == nil or tp == nil or pos == nil then
        error("can't unpack binData. " .. debug.traceback())
    end
    local n
    local v
    -- integer type
    if     tp == "i8" or tp == "char" then
        n, v = bunpack(binData, "<c", pos)
    elseif tp == "ui8" or tp == "unsigned char" then
        n, v = bunpack(binData, "<b", pos)
    elseif tp == "i16" or tp == "short" then
        n, v = bunpack(binData, "<h", pos)
    elseif tp == "ui16" or tp == "unsigned short" then
        n, v = bunpack(binData, "<H", pos)
    elseif tp == "i32" or tp == "int" then
        n, v = bunpack(binData, "<i", pos)
    elseif tp == "ui32" or tp == "unsigned int" then
        n, v = bunpack(binData, "<I", pos)
    elseif tp == "i64" or tp == "long long" or tp == "ui64" or tp == "unsigned long long" then
        v = string.sub(binData, pos, pos+7)
        n = pos +8
    -- string type
    elseif tp == "string" then
        n, v = bunpack(binData, "<I", pos)
        n, v = bunpack(binData, "<A" .. v, pos+4)

    -- float type
    elseif tp == "float" then
        n, v = bunpack(binData, "<f", pos)
    elseif tp == "double" then
        n, v = bunpack(binData, "<d", pos)

    else
        --error("unknown binData to unpack . pos=" .. pos .. " tp=" .. tp .." trace: " .. debug.traceback())
        n, v = pos, nil
    end
    return v, n
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
    Proto4z.__checkType(name)
    local proto = Proto4z[name]

    local v, p
    p = pos

    if proto.__getDesc == "array" then
        local len

        len, p = Proto4z.__unpack(binData, p, "ui32")
        for i=1, len do
            v, p = Proto4z.__unpack(binData, p, proto.__getTypeV)
            if v ~= nil then
                result[i] = v
            else
                result[i] = {}
                p = Proto4z.__decode(binData, p, proto.__getTypeV, result[i])
            end
        end
    elseif proto.__getDesc == "map" then
        local len
        local k
        len, p = Proto4z.__unpack(binData, p, "ui32")
        for j=1, len do
            k, p = Proto4z.__unpack(binData, p, proto.__getTypeK)
            v, p = Proto4z.__unpack(binData, p, proto.__getTypeV)
            if v ~= nil then
                result[k] = v
            else
                result[k] = {}
                p = Proto4z.__decode(binData, p, proto.__getTypeV, result[k])
            end
        end
    else
        local offset, tag
        offset, p = Proto4z.__unpack(binData, p, "ui32")
        offset = p + offset
        tag, p = Proto4z.__unpack(binData, p, "ui64")
        for i = 1, #proto do
            if Proto4z.checkIntegerBitTrue(tag, i-1) ~= nil then
                local desc = proto[i]
                v, p = Proto4z.__unpack(binData, p, desc.type)
                if v ~= nil then
                    result[desc.name] = v
                else
                    result[desc.name] = {}
                    p = Proto4z.__decode(binData, p, desc.type, result[desc.name])
                end
            end
        end
        p = offset
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
    Proto4z.__checkVal(obj)
    Proto4z.__checkType(name)

    local proto = Proto4z[name]
    --array
    --------------------------------------
    if proto.__getDesc == "array" then
        Proto4z.__checkType(proto.__getTypeV)
        data.data = data.data .. bpack("<I", #obj) --this line lua5.3 or lua5.1+lpack all compatibility 
        for i =1, #obj do
            if type(obj[i]) ~= "table" then
                data.data = data.data .. Proto4z.__pack(obj[i], proto.__getTypeV)
            else
                Proto4z.__encode(obj[i], proto.__getTypeV, data)
            end
        end
    --map
    --------------------------------------
    elseif proto.__getDesc == "map" then
        Proto4z.__checkType(proto.__getTypeK)
        Proto4z.__checkType(proto.__getTypeV)
        data.data = data.data .. bpack("<I", #obj)--this line lua5.3 or lua5.1+lpack all compatibility 
        for i =1, #obj do
            if not Proto4z.__isInnerType(proto.__getTypeK) or type(obj[i].k) == "table" then
                error("unknown member type(obj[i].k)=" .. type(obj[i].k) .. ", type=" .. name .. "." .. proto.__getTypeK)
            end
            data.data = data.data .. Proto4z.__pack(obj[i].k, proto.__getTypeK)
            if type(obj[i].v) ~= "table" and Proto4z.__isInnerType(proto.__getTypeV) then
                data.data = data.data .. Proto4z.__pack(obj[i].v, proto.__getTypeV)
            elseif type(obj[i].v) == "table" and Proto4z.__isUserType(proto.__getTypeV) then
                Proto4z.__encode(obj[i].v, proto.__getTypeV, data)
            else
                error("unknown member type(obj[i].v)=" .. type(obj[i].v) .. ", type=" .. name .. "." .. proto.__getTypeV)
            end
        end
    --base typ or struct or proto
    --------------------------------------
    else
        local curdata, offset
        curdata = {data=""}
        for i=1, #proto do
            local desc = proto[i]
            if type(desc) ~= "table" or type(desc.name) ~= "string" or type(desc.type) ~= "string" then
                error("parse Proto error. name[" .. name .. "] " .. debug.traceback())
            end
            if desc.del == nil or desc.del ~= true then
                local val = obj[desc.name]
                if val == nil then
                    error("not found the dest object. name[" ..name .. "." .. desc.name .. "] " .. debug.traceback())
                end

                if type(val) ~= "table" and Proto4z.__isInnerType(desc.type) then
                    curdata.data = curdata.data .. Proto4z.__pack(val, desc.type)
                elseif type(val) == "table" and Proto4z.__isUserType(desc.type) then
                    Proto4z.__encode(val, desc.type, curdata)
                else
                    error("unknown member type(val)=" .. type(val) .. ", type=" .. name .. "." .. desc.type)
                end
            end
        end
        local tag = Proto4z.sequenceToInteger(proto.__getTag)
        offset = #curdata.data + #tag
        offset = Proto4z.__pack(offset, "ui32")
        data.data = data.data .. offset .. tag .. curdata.data
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
function Proto4z.dump(value, desciption, nesting, showULL)
    if type(nesting) ~= "number" then nesting = 5 end

    local lookupTable = {}
    local result = {}

    local function _v(v)
        if type(v) == "string" then
            if showULL and #v == 8 then
                return Proto4z.streamToString(v)
            end
            v = "\"" .. v .. "\""
        end
        return tostring(v)
    end

    local traceback = Proto4z.split(debug.traceback("", 2), "\n")
    print("dump from: " .. Proto4z.trim(traceback[3]))

    local function _dump(value, desciption, indent, nest, keylen)
        desciption = desciption or "<var>"
        spc = ""
        if type(keylen) == "number" then
            spc = string.rep(" ", keylen - string.len(_v(desciption)))
        end
        if type(value) ~= "table" then
            result[#result +1 ] = string.format("%s%s%s = %s", indent, _v(desciption), spc, _v(value))
        elseif lookupTable[value] then
            result[#result +1 ] = string.format("%s%s%s = *REF*", indent, desciption, spc)
        else
            lookupTable[value] = true
            if nest > nesting then
                result[#result +1 ] = string.format("%s%s = *MAX NESTING*", indent, desciption)
            else
                result[#result +1 ] = string.format("%s%s = {", indent, _v(desciption))
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
                result[#result +1] = string.format("%s}", indent)
            end
        end
    end
    _dump(value, desciption, "- ", 1)

    for i, line in ipairs(result) do
        print(line)
    end
end

