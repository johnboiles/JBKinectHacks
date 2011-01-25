

ENT.Type = "anim"
ENT.Base = "base_gmodentity"

ENT.PrintName		= "Hover Ball"
ENT.Author			= ""
ENT.Contact			= ""
ENT.Purpose			= ""
ENT.Instructions	= ""

ENT.Spawnable			= false
ENT.AdminSpawnable		= false

function ENT:SetupDataTables()
	self:DTVar( "Vector", 0, "TargetPosition" );
end


function ENT:GetTargetPosition( position )
	return self.dt.TargetPosition
end


function ENT:UpdateLabel()

	self:SetOverlayText( string.format( "TR4$HM0NSTRR\nPosition: (%.2f, %.2f, %.2f)", self:GetTargetPosition().x, self:GetTargetPosition().y, self:GetTargetPosition().z ) )

end
