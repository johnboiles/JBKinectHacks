

ENT.Type = "anim"
ENT.Base = "base_gmodentity"

ENT.PrintName		= "Movable Ragdoll"
ENT.Author			= ""
ENT.Contact			= ""
ENT.Purpose			= ""
ENT.Instructions	= ""

ENT.Spawnable			= false
ENT.AdminSpawnable		= false

function ENT:SetupDataTables()


end

function ENT:UpdateLabel()

	self:SetOverlayText( string.format( "Movable ragdoll" ) )

end

function ENT:SetForearmPosition( Position, Angle )
	forearmPos = Position
	forarmAngle = Angle
end


function ENT:ShowBonesMatrices()
	MsgN(self)
	for i=0, self:GetBoneCount() - 1 do
	  MsgN(self:GetBoneName(i));
	  local bonematrix = self:GetBoneMatrix(i)
	  Msg(bonematrix:GetAngle())
	  Msg("\n")
	end 
end

function ENT:ShowBonePositions()
	for i=0, self:GetBoneCount() - 1 do
		MsgN(self:GetBoneName(i));
		local position, angle = self:GetBonePosition( i )
		MsgN("Position: " .. tostring(position) .. "  Angle: " .. tostring(angle))
	end
end

function ENT:GetBonePositionByName( Name )
    local BoneIndex = self:LookupBone( Name )
    local BonePos, BoneAng = self:GetBonePosition( BoneIndex )
    MsgN("BonePos = ".. tostring(BonePos) .."BoneAng = ".. tostring(BoneAng))
end

function ENT:GetForearmPosition()
	self:GetBonePositionByName("ValveBiped.Bip01_R_Forearm")
end