
ENT.RenderGroup		= RENDERGROUP_BOTH

include('shared.lua')

forearmPos = Vector(0,0,0)
forearmAngle = Angle(20,90,0)
printBones = 1

/*---------------------------------------------------------
   Name: Initialize
---------------------------------------------------------*/
function ENT:Initialize()

	self.Refraction = Material( "sprites/heatwave" )
	self.Glow		= Material( "sprites/light_glow02_add" )
	self.ShouldDraw = 1
	
	self.NextSmokeEffect = 0

end


/*---------------------------------------------------------
   Name: Draw
---------------------------------------------------------*/
function ENT:Draw()

	if ( self.ShouldDraw == 0 ) then return end
	self.BaseClass.Draw( self ) 
		
end

function ENT:BuildBonePositions( NumBones, NumPhysBones )
	if ( printBones == 1 ) then
		for i=0, self:GetBoneCount() - 1 do
			MsgN(self:GetBoneName(i));
			local position, angle = self:GetBonePosition( boneindex )
			MsgN("Position: " .. tostring(postion) .. "  Angle: " .. tostring(angle))
		end
	end
	printBones = 0
	local BoneIndex = self:LookupBone( "ValveBiped.Bip01_R_Forearm" )
	--self:SetBonePosition( BoneIndex, forearmPos, forearmAngle )
	bonePos, boneAngle = self:GetBonePosition(BoneIndex)
	self:SetBonePosition( BoneIndex, bonePos, forearmAngle )
	forearmAngle:RotateAroundAxis(  Vector(1,0,0),  1 )
--	MsgN("HeadPos = ".. tostring(BonePos) .."HeadAng = ".. tostring(BoneAng))
--	for i = 1, 128 do --An entity cannot have more than 128 bones
--		self:SetBonePosition( i, VectorRand() * 32, VectorRand():Angle() )
--	end
end

-- It seems like functions we put here can't be called.. hmmm
