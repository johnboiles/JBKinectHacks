-- Copyright (c) 2010 Aleksey Yeschenko <aleksey@yeschenko.com>
--
-- Permission is hereby granted, free of charge, to any person obtaining a copy
-- of this software and associated documentation files (the "Software"), to deal
-- in the Software without restriction, including without limitation the rights
-- to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
-- copies of the Software, and to permit persons to whom the Software is
-- furnished to do so, subject to the following conditions:
--
-- The above copyright notice and this permission notice shall be included in
-- all copies or substantial portions of the Software.
--
-- THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
-- IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
-- FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
-- AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
-- LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
-- OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
-- THE SOFTWARE.

require("zmq")
local ev = require'ev'
local loop = ev.Loop.default

-- define a sub_worker class
local sub_worker_mt = {}
function sub_worker_mt:close(...)
    self.s_io_idle:stop(self.loop)
    self.s_io_read:stop(self.loop)
    return self.socket:close(...)
end
function sub_worker_mt:bind(...)
    return self.socket:bind(...)
end
function sub_worker_mt:connect(...)
    return self.socket:connect(...)
end
function sub_worker_mt:sub(topic)
    return self.socket:setopt(zmq.SUBSCRIBE, topic)
end
function sub_worker_mt:unsub(topic)
    return self.socket:setopt(zmq.UNSUBSCRIBE, topic)
end
sub_worker_mt.__index = sub_worker_mt

local function sub_worker(loop, ctx, msg_cb)
    local s = ctx:socket(zmq.SUB)
    local self = { loop = loop, socket = s, msg_cb = msg_cb }
    setmetatable(self, sub_worker_mt)
    -- create ev callbacks for recving data.
    -- need idle watcher since ZeroMQ sockets are edge-triggered instead of level-triggered
    local s_io_idle
    local s_io_read
    s_io_idle = ev.Idle.new(function()
        local msg, err = s:recv(zmq.NOBLOCK)
        if err == 'timeout' then
            -- need to block on read IO
            s_io_idle:stop(loop)
            s_io_read:start(loop)
            return
        end
        self:msg_cb(msg)
    end)
    s_io_idle:start(loop)
    s_io_read = ev.IO.new(function()
        s_io_idle:start(loop)
        s_io_read:stop(loop)
    end, s:getopt(zmq.FD), ev.READ)
    self.s_io_idle = s_io_idle
    self.s_io_read = s_io_read
    return self
end

local ctx = zmq.init(1)

-- message handling function.
local function handle_msg(worker, msg)
    local msg_id = tonumber(msg)
    if math.mod(msg_id, 10000) == 0 then print(worker.id, msg_id) end
end

local sub1 = sub_worker(loop, ctx, handle_msg)
sub1.id = 'sub1'
sub1:sub('')
sub1:connect("tcp://localhost:5555")
local sub2 = sub_worker(loop, ctx, handle_msg)
sub2.id = 'sub2'
sub2:sub('')
sub2:connect("tcp://localhost:5555")

loop:loop()

