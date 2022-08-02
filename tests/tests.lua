#!/usr/bin/lua5.3

package.cpath = package.cpath .. ";./?.so" .. ";../out/?.so" .. ";./out/?.so"

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

function test_set(n)
    local b = bitr.new(n)
    b:set(n)
    if not b:test(n) then
        return false
    end

    return true
end

function test_clear(n)
    local b = bitr.new(n, true)
    b:clear(n)
    if b:test(n) then
        return false
    end

    return true
end

-- state is the state to toggle FROM.
-- e.g. if state is 1, toggle from 1 TO 0.
function test_toggle(n, state)
    local b = bitr.new(n, state and true or false)
    b:toggle(n)
    if state then
        if b:test(n) then
            return false
        end
    elseif not state then
        if not b:test(n) then
            return false
        end
    end

    return true
end



print("")
print("#######################################################")
print("################ Running Lua tests #################### ")
print("#######################################################")

print("\nValidating bit testing...")
run(test_all_ones, 101)
run(test_all_ones, 33)
run(test_all_ones, 10000)
run(test_all_ones, 1)

run(test_all_zeroes, 101)
run(test_all_zeroes, 33)
run(test_all_zeroes, 10000)
run(test_all_zeroes, 1)

print("\nTesting bit setting...")
run(test_set,5)
run(test_set,55)
run(test_set,555)
run(test_set,5555)
run(test_set,55555)
run(test_set,1)
run(test_set,91)

print("\nTesting bit clearing...")
run(test_set,2)
run(test_set,55)
run(test_set,2102)
run(test_set,74)
run(test_set,55555)
run(test_set,1)
run(test_set,93)

print("\nTesting bit toggling...")
run(test_toggle, 9, 1)
run(test_toggle, 55, 0)
run(test_toggle, 2102, 0)
run(test_toggle, 74, 1)
run(test_toggle, 55555, 0)
run(test_toggle, 1,0)
run(test_toggle, 93, 0)

print(string.format("passed: %s / %s", num_passed, num_run))
if (num_passed ~= num_run) then os.exit(1) end
