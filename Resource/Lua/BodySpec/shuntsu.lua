local m = {}

m.Name = 'shuntsu'
m.BodyType = 'triplet'
m.Properties = { 'shuntsu' }

m.CompleteCount = 3
m.GetCandidates = function(bodyCandidate)
    local hais = bodyCandidate.ComponentHais;

    local l = #hais

    if (l >= 3 or l == 0) then
        return false
    end

    local hai1 = hais[1]
    local haiSpec1 = hai1.HaiSpec
    local number1 = haiSpec1.Number
    local haiType1 = haiSpec1.HaiType

    if hai1.HaiType == 4 or hai1.HaiType == 5 then
        return false
    end

    if l == 1 then
        if number1 - 2 >= 1 then
            candidates:PushHai(HaiSpec.new(haiType1, number1 - 2))
        end

        if number1 - 1 >= 1 then
            candidates:PushHai(HaiSpec.new(haiType1, number1 - 1))
        end

        if number1 + 1 <= 9 then
            candidates:PushHai(HaiSpec.new(haiType1, number1 + 1))
        end

        if number1 + 2 <= 9 then
            candidates:PushHai(HaiSpec.new(haiType1, number1 + 2))
        end

        candidates:SetName('single')
    end

    if l == 2 then
        local hai2 = hais[2]
        local number2 = hai2.HaiSpec.Number

        if number2 - number1 == 1 then
            local isBenChan = false

            if number1 - 1 >= 1 then
                candidates:PushHai(HaiSpec.new(haiType1, number1 - 1))
            else
                isBenChan = true
            end

            if number2 + 1 <= 9 then
                candidates:PushHai(HaiSpec.new(haiType1, number2 + 1))
            else
                isBenChan = true
            end

            if (isBenChan) then
                candidates:SetName('benchan')
            else
                candidates:SetName('ryanmen')
            end
        end

        if number2 - number1 == 2 then
            candidates:PushHai(HaiSpec.new(haiType1, number2 - 1))
            candidates:SetName('kanchan')
        end
    end

    return true
end

return m
