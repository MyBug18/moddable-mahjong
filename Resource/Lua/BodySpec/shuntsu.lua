local m = {}

m.Name = 'shuntsu'
m.BodyType = 'triplet'
m.Properties = { 'shuntsu' }

m.CompleteCount = 3
m.GetCandidates = function(extractor)
    local haiSpec = extractor.HaiSpec
    local type = haiSpec.HaiType
    local number = haiSpec.Number

    local from = math.max(number - 2, 1)

    for i in from, number do
        local form = {}
        local to = math.min(number + 2, 9)

        for j in i, to do
            if i ~= number then
                form[HaiSpec.new(type, i)] = 1
            end
        end

        extractor:PushForm(form)
    end
end

m.GetMachiName = function(haiSpecs)

end

return m
