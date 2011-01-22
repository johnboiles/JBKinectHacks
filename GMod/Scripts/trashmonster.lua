require("oosocks")

local connection = OOSock(IPPROTO_UDP);

TrashMonster = {}

function CreateTrashMonsterNodesWithNames(names)
    for index, name in pairs(names) do
        CreateTrashMonsterNode(name)
        Msg("Created entity in TrashMonster for node name " .. name .. "\n")
    end
end

function UpdateTrashMonsterPositionsWithSkeleton(skeleton)
    for joint, point in pairs(skeleton) do
        Msg("Updating joint " .. joint .. " with x" .. tostring(point.x) .. " y" .. tostring(point.y) .. " z" .. tostring(point.z) .. "\n")
        if (!TrashMonster[joint]) then
			local newNode = ents.Create("positiontracker")
		    newNode:Spawn()
		    TrashMonster[joint] = newNode
		end
		--TrashMonster[joint]:GetPhysicsObject():SetPos(point)
        TrashMonster[joint]:SetTargetPosition(point)
    end
end

function UpdateSkeleton(skeleton)
    -- Figure out how much to adjust the position of the ground based on the current position of the feet
    local zoffset = math.min(skeleton['lf'].z, skeleton['rf'].z)
    for joint, point in pairs(skeleton) do
        skeleton[joint].z = skeleton[joint].z - zoffset
    end
    skeleton['lf'].z = skeleton['lf'].z + 10
    skeleton['rf'].z = skeleton['rf'].z + 10
    --skeleton['lh'].z = skeleton['lh'].z - 100
    --skeleton['rh'].z = skeleton['rh'].z - 100
    UpdateTrashMonsterPositionsWithSkeleton(skeleton)
end
 
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
        Msg("Got '" .. data .. "'  from  " .. peer .. ":" .. tostring(peerPort));
        --socket:Close()
        local point

        skeleton = {}
        for k, x, y, z in string.gmatch(tostring(data), "([a-z][a-z])x([-.0-9]*)y([-.0-9]*)z([-.0-9]*)") do
            skeleton[k] = Vector(-tonumber(x), tonumber(z), tonumber(y)) * 0.2
        end
        UpdateSkeleton(skeleton)

        connection:ReceiveDatagram();
    end
     
    if(err != SCKERR_OK) then
        --socket:Close()
    end
end);

Msg("Gmod UDP Module loaded\n")
-- an IP of "" binds to all interfaces.
connection:Bind("", 50125);