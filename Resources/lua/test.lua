local m = {}

local spec = HaiSpec.new(HaiType.Wan, 1)

m.h1 = Hai.new(1, spec)
m.h2 = 1;
m.h1:AddProperty('asf')

return m
