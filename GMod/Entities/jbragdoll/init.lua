--local thing = ents.Create("positiontracker")
--thing:Spawn()

AddCSLuaFile( "shared.lua" )
include('shared.lua')

local MODEL = Model( "models/player/Group01/male_01.mdl" )

/*---------------------------------------------------------
   Name: Initialize
---------------------------------------------------------*/
function ENT:Initialize()
	self:SetModel( MODEL )
	
	// Wake up our physics object so we don't start asleep
	local phys = self:GetPhysicsObject()
	if ( phys:IsValid() ) then 
		phys:Wake() 
	end
	
	MsgN("Initializing jbragdoll")
	
end

function ENT:OnRestore()


end

/*---------------------------------------------------------
   Name: OnTakeDamage
---------------------------------------------------------*/
function ENT:OnTakeDamage( dmginfo )

	Msg("Oww")
	
end


/*---------------------------------------------------------
   Name: Think
---------------------------------------------------------*/
function ENT:Think()

	self:NextThink( CurTime() + 0.25 )
	return true
	
end



/*---------------------------------------------------------
   Name: Use
---------------------------------------------------------*/
function ENT:Use( activator, caller )

end
