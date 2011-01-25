require("oosocks")

local connection = OOSock(IPPROTO_UDP);

Kleiner = ents.Create("prop_ragdoll")
Kleiner:SetModel("models/Kleiner.mdl")
Kleiner:Spawn()

ControlNodes = {}

/* For Human Models (excepting Eli)
0 = pelvis
1 = chest
2 = right upper arm
3 = left upper arm
4 = left forearm
5 = left hand
6 = right forearm
7 = right hand
8 = right thigh
9 = right calf
10 = head
11 = left thigh
12 = left calf
13 = left foot
14 = right foot
*/

PhysicsObjectToNameForKleiner = {lh=5, rh=7, ls=3, rs=2, lk=12, rk=9, hh=10, lf=13, rf=14, le=4, re=6 }
ScaleFactor = 0.056

function WeldKleinerBoneToNode(Bone, NodeName)
	local node
	if (!ControlNodes[NodeName]) then
		node = ents.Create("positiontracker")
		// Collide does wierd things when you put hoverballs inside ragdolls, disable it
		node:SetCollisionGroup( COLLISION_GROUP_NONE )
		node.CollisionGroup = COLLISION_GROUP_NONE
		node:SetStrength(0.001)
		node:Spawn()
		ControlNodes[NodeName] = node
	else
		node = ControlNodes[NodeName]
	end
	local physObject = Kleiner:GetPhysicsObjectNum(Bone)
	node:SetPos(physObject:GetPos())
	Msg("Setting " .. NodeName .. " to ")
	MsgN(physObject)
	constraint.Weld(node, Kleiner, 0, Bone, 0 ,true)
end

function UnWeldNode(NodeName)
	constraint.RemoveAll(ControlNodes[NodeName])
end

function UnWeldAll()
	for joint, index in pairs(PhysicsObjectToNameForKleiner) do
		UnWeldNode(joint)
	end
end

function RemoveNode(NodeName)
	ControlNodes[NodeName]:Remove()
	ControlNodes[NodeName] = nil	
end

function RemoveAll()
	for joint, index in pairs(PhysicsObjectToNameForKleiner) do
		RemoveNode(joint)
	end
	Kleiner:Remove()
end

function WeldBones()
	for joint, index in pairs(PhysicsObjectToNameForKleiner) do
		WeldKleinerBoneToNode(index, joint)
	end
	//ControlNodes['hh']:SetStrength(2)
end

WeldBones()

function UpdateSkeleton(skeleton)
    -- Figure out how much to adjust the position of the ground based on the current position of the feet
    local zoffset = math.min(skeleton['lf'].z, skeleton['rf'].z)
    for joint, point in pairs(skeleton) do
        skeleton[joint].z = skeleton[joint].z - zoffset
    end
	// Some corrections specific to humans
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