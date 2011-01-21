test = "x5.7y3.1z0.8"
print(test)
for x,y,z in string.gmatch(test, "x(%w+)y(%w+)z(%w+)") do
    print(x)
    print(y)
    print(z)
end


s = "hello world from Lua"
for w in string.gmatch(s, "%a+") do
    print(w)
end

t = {}
s = "x1.4y2.5z4.9, x5y6z9, x-23.42y53.2333z322.0"
for x, k, v in string.gmatch(s, "x([-.0-9]*)y([-.0-9]*)z([-.0-9]*)") do
    print(x)
    print(k)
    print(v)
end