require("oosocks")

local connection = OOSock(IPPROTO_UDP);

Dog = ents.Create("prop_ragdoll")
Dog:SetModel("models/dog.mdl")
--I'm not sure if friction > 1 actually does anything
Dog:SetFriction(100)
Dog:Spawn()

ControlNodes = {}

PhysicsObjectToNameForDog = { pp=0, le=4, lh=5, re=7, rh=8, lk=13, lf=14, rk=10, rf=11, hh=15}
ScaleFactor = 0.10

function WeldDogBoneToNode(Bone, NodeName)
	local node
	if (!ControlNodes[NodeName]) then
		node = ents.Create("positiontracker")
		// Collide does wierd things when you put hoverballs inside ragdolls, disable it
		node:SetCollisionGroup( COLLISION_GROUP_NONE )
		node.CollisionGroup = COLLISION_GROUP_NONE
		node:Spawn()
		ControlNodes[NodeName] = node
	else
		node = ControlNodes[NodeName]
	end
	local physObject = Dog:GetPhysicsObjectNum(Bone)
	node:SetPos(physObject:GetPos())
	Msg("Setting " .. NodeName .. " to ")
	MsgN(physObject)
	constraint.Weld(node, Dog, 0, Bone, 0 ,true)
end

function UnWeldNode(NodeName)
	constraint.RemoveAll(ControlNodes[NodeName])
end

function UnWeldAll()
	for joint, index in pairs(PhysicsObjectToNameForDog) do
		UnWeldNode(joint)
	end
end

function RemoveNode(NodeName)
	ControlNodes[NodeName]:Remove()
	ControlNodes[NodeName] = nil	
end

function RemoveAll()
	for joint, index in pairs(PhysicsObjectToNameForDog) do
		RemoveNode(joint)
	end
end

function RemoveDog()
	Dog:Remove()
end

function WeldBones()
	for joint, index in pairs(PhysicsObjectToNameForDog) do
		WeldDogBoneToNode(index, joint)
	end
	ControlNodes['hh']:SetStrength(2)
end

WeldBones()

function UpdateSkeleton(skeleton)
    -- Figure out how much to adjust the position of the ground based on the current position of the feet
    local zoffset = math.min(skeleton['lf'].z, skeleton['rf'].z) + 10
    for joint, point in pairs(skeleton) do
        skeleton[joint].z = skeleton[joint].z - zoffset
    end
	// Some corrections specific to dog
    skeleton['lf'].z = skeleton['lf'].z + 12
    skeleton['rf'].z = skeleton['rf'].z + 12
    skeleton['lk'].z = skeleton['lk'].z + 10
    skeleton['rk'].z = skeleton['rk'].z + 10
    skeleton['lh'].z = skeleton['lh'].z - 10
    skeleton['rh'].z = skeleton['rh'].z - 10
	skeleton['hh'].y = skeleton['hh'].y - 20
	skeleton['hh'].z = skeleton['hh'].z - 10
	// TODO: make a pelvis point that's right between the hips
	pelvis = skeleton['ri'] + skeleton['li']
	pelvis = pelvis / 2
	skeleton['pp'] = pelvis
	for joint, point in pairs(skeleton) do
		if (ControlNodes[joint]) then
			ControlNodes[joint]:SetTargetPosition(point)
		end
	end
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
            skeleton[k] = Vector(-tonumber(x), tonumber(z), tonumber(y)) * ScaleFactor
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