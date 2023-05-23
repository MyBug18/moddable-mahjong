local m = {}

m.Name = 'toitsu'
m.BodyType = 'head'
m.Properties = { 'toitsu' }

m.CompleteCount = 2
m.GetCandidates = function(bodyCandidate)
    local hais = bodyCandidate.ComponentHais;

    local l = #hais

    if (l >= 2) then
        bodyCandidate:SetName('toitsu_complete')
        return false
    end

    if l == 0 then
        return false
    end

    local hai = hais[1]
    local haiSpec = hai.HaiSpec
    local number = haiSpec.Number
    local haiType = haiSpec.HaiType

    bodyCandidate:PushHai(HaiSpec.new(haiType, number))
    bodyCandidate:SetName('tanki')

    return true
end

return m
