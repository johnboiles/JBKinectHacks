function FindTarget(target)
    local targets = ents.FindByClass(target)
    if (#targets > 1) then 
        Msg("there are multiple alyx's\n")
        return targets[1]
        --local randT = math.Rand( 1, #targets)
        --return randT 
    else
        return targets[1]
    end
end

function MoveAlyx(x)
    local ent = FindTarget("prop_phys*")
    local position = ent:GetLocalPos()
    Msg(position)
    Msg("\n")
    position.x = position.x + x
    ent:SetLocalPos(position)
end

require("oosocks")
 
local connection = OOSock(IPPROTO_UDP);
 
connection:SetCallback(function(socket, callType, callId, err, data, peer, peerPort)
    if(callType == SCKCALL_BIND && err == SCKERR_OK) then
        print("Bound.");
        --connection:Send("rofl", "127.0.0.1", 50007);
        connection:ReceiveDatagram();
    end

    if(callType == SCKCALL_SEND && err == SCKERR_OK) then
        print("Sent.");
    end
     
    if(callType == SCKCALL_REC_DATAGRAM && err == SCKERR_OK) then
        print("Got '" .. data .. "'  from  " .. peer .. ":" .. tostring(peerPort));
        --socket:Close()
        local xpos = tonumber(data)
        Msg(xpos)
        MoveAlyx(xpos)
        connection:ReceiveDatagram();
    end
     
    if(err != SCKERR_OK) then
        --socket:Close()
    end
end);
 
-- an IP of "" binds to all interfaces.
connection:Bind("", 50125);