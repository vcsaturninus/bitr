#!/usr/bin/lua5.3

package.cpath = package.cpath .. ";" .. "./luabitr?.so;"

local bitr = require("luabitr")

local num_run = 0
local num_passed = 0

-- run test functions
local function run(f, ...)
    local res = f(...)

    num_run = num_run+1

    print(string.format("[ ] test %s %s", num_run, res and "Passed" or "FAILED !!"))

    if res then num_passed = num_passed+1 end
end

-- check bit array initialized to all 1s indeed has all bits set
function test_all_ones(num)
    local b = bitr.new(num, true)
    for i=1,num do
        if not b:test(i) then
            return false
        end
    end

    return true
end

-- check bit array initialized to all 1s indeed has all bits unset
function test_all_zeroes(num)
    local b = bitr.new(num)
    for i=1,num do
        if b:test(i) then
            return false
        end
    end

    return true
end


print("################ Running Lua tests #################### ")

print("\nValidating bit testing ")
run(test_all_ones, 101)
run(test_all_ones, 33)
run(test_all_ones, 10000)
run(test_all_ones, 1)

run(test_all_zeroes, 101)
run(test_all_zeroes, 33)
run(test_all_zeroes, 10000)
run(test_all_zeroes, 1)


print(string.format("passed: %s / %s", num_passed, num_run))
if (num_passed ~= num_run) then os.exit(1) end
