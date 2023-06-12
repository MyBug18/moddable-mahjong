local m = {}

m.Name = 'toitsu'
m.BodyType = 'head'
m.Properties = { 'toitsu' }

m.CompleteCount = 2
m.GetCandidates = function(extractor)
    local haiSpec = extractor.HaiSpec
    local type = haiSpec.HaiType
    local number = haiSpec.Number

    local form = {}
    form[HaiSpec.new(type, number)] = 1
    extractor:PushForm(form)
end

return m
