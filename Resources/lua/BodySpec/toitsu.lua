local m = {}

m.Name = 'toitsu'
m.BodyType = 'head'
m.Properties = { 'toitsu' }
m.ShouldFuro = false

m.GetCandidates = function(hais)
    local candidates = HaiCandidates.new()

    local l = #hais

    if (l >= 2) then
        return candidates
    end

    if l == 0 then
        candidates.CompleteCount = 2
        return candidates
    end

    local hai = hais[1]
    local haiSpec = hai.HaiSpec
    local number = haiSpec.Number
    local haiType = haiSpec.HaiType

    candidates:PushHai(HaiSpec.new(haiType, number))
    candidates.CompleteCount = 1

    return candidates
end

return m
