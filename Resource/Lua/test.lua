local m = {}

m.spec1 = HaiSpec.new(1, 3)
m.spec2 = HaiSpec.new(1, 2)
m.res = 0

for index, value in pairs(a) do
    m.res = m.res + value
    value = 2
end

return m
