local m = {}

m.Name = 'shuntsu'
m.BodyType = 'triplet'
m.Properties = { 'shuntsu' }
m.ShouldFuro = false

m.GetCandidates = function(hais)
    local candidates = HaiCandidates.new()

    local l = #hais

    if (l >= 3) then
        return candidates;
    end

    if l == 0 then
        candidates.CompleteCount = 3
        return candidates
    end

    local hai1 = hais[1]
    local haiSpec1 = hai1.HaiSpec
    local number1 = haiSpec1.Number
    local haiType1 = haiSpec1.HaiType

    if hai1.HaiType == HaiType.Kaze or hai1.HaiType == HaiType.Sangen then
        return candidates
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

        candidates.CompleteCount = 2
    end

    if l == 2 then
        local hai2 = hais[2]
        local number2 = hai2.HaiSpec.Number

        if number1 > number2 then
            local temp = number1
            number1 = number2
            number2 = temp
        end

        if number2 - number1 == 1 then
            if number1 - 1 >= 1 then
                candidates:PushHai(HaiSpec.new(haiType1, number1 - 1))
            end

            if number2 + 1 <= 9 then
                candidates:PushHai(HaiSpec.new(haiType1, number2 + 1))
            end
        end

        if number2 - number1 == 2 then
            candidates:PushHai(HaiSpec.new(haiType1, number2 - 1))
        end

        candidates.CompleteCount = 1
    end

    return candidates
end

return m
