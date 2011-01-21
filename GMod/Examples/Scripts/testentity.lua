function GetFirstPlayer()
    for k, v in pairs(player.GetAll()) do
        return v
    end
end 


 
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

function FlyAlyx()
    local ent = FindTarget("npc_alyx")
    --Msg(ent.."\n")
    if (ent:IsValid()) then
        Msg("found alyx\n")
    end
    --ent:SetLocalVelocity(Vector(0, 0, 1 ))
    ent:SetLocalVelocity(Vector(0, 0, 1 )*1000)

end
concommand.Add("jb_fly_alex",function(p,c,a) FlyAlyx() end)

function BoneMatrices()
    local ent = FindTarget("npc_alyx")
    local boneindex = 7
    local bonematrix = ent:GetBoneMatrix(boneindex)
    Msg(ent:GetBoneName(boneindex).."\n")
    Msg(bonematrix:GetAngle())
    Msg("\n")
    bonematrix:Rotate(Angle( 90, 90, 90 ))
    ent:SetBoneMatrix(boneindex, bonematrix)
end
concommand.Add("jb_bone_matrices",function(p,c,a) BoneMatrices() end)


function BoneNames()
	local ent = FindTarget("npc_alyx")
	for i=0, ent:GetBoneCount() - 1 do
		MsgN(ent:GetBoneName(i));
	end
end
concommand.Add("jb_getbonenames", function(p,c,a) BoneNames() end)

function MoveAlyx()
    local ent = FindTarget("npc_alyx")
    local position = ent:GetLocalPos()
    Msg(position)
    Msg("\n")
    position.x = position.x + 100
    ent:SetLocalPos(position)
end
concommand.Add("jb_move_alyx",function(p,c,a) MoveAlyx() end)

function SpawnAlex(ply)
    local ent = ents.Create( "npc_alyx" )
    local ply = GetFirstPlayer()
    --local ply = Player(2)
    local tr = ply:GetEyeTrace()
    if ( !ent:IsValid() ) then return end
     
    ent:SetPos( tr.HitPos )
    ent:Spawn()
    ent:Activate()
end
concommand.Add("jb_spawn_alex",function(p,c,a) SpawnAlex() end)