local m = {}

m.Name = 'toitsu'
m.BodyType = 'head'
m.Properties = { 'toitsu' }

m.CompleteCount = 2
m.GetCandidates = function(extractor)
    local hais = extractor.Hais;

    local l = #hais

    if (l >= 2) then
        extractor:SetName('toitsu_complete')
        return false
    end

    if l == 0 then
        return false
    end

    local hai = hais.at(0)
    local haiSpec = hai.HaiSpec
    local number = haiSpec.Number
    local haiType = haiSpec.HaiType

    extractor:PushHai(HaiSpec.new(haiType, number))
    extractor:SetName('tanki')

    return true
end

return m
