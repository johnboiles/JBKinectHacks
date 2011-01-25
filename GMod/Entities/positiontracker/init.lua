AddCSLuaFile( "shared.lua" )
include('shared.lua')

local MODEL = Model( "models/dav0r/hoverball.mdl" )

/*---------------------------------------------------------
   Name: Initialize
---------------------------------------------------------*/
function ENT:Initialize()
	Msg("Initializing TR4$HM0NSTRR")
	// Use the helibomb model just for the shadow (because it's about the same size)
	self:SetModel( MODEL )
	
	// Don't use the model's physics object, create a perfect sphere
	--self:PhysicsInitSphere( 8, "metal_bouncy" )
	self:PhysicsInitSphere( 1 )

	// Wake up our physics object so we don't start asleep
	local phys = self:GetPhysicsObject()
	if ( phys:IsValid() ) then 
		phys:SetMass( 150 )
		phys:EnableGravity( false )
		phys:Wake() 
	end
	
	// Start the motion controller (so PhysicsSimulate gets called)
	self:StartMotionController()
	
	self.TargetVelocity = Vector(0,0,0)
	self.dt.TargetPosition = self:GetPos()
end

function ENT:OnRestore()

	self.TargetVelocity = Vector(0,0,0)

end

/*---------------------------------------------------------
   Name: OnTakeDamage
---------------------------------------------------------*/
function ENT:OnTakeDamage( dmginfo )

	//self:TakePhysicsDamage( dmginfo )
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

/*---------------------------------------------------------
   Name: Simulate
---------------------------------------------------------*/
function ENT:PhysicsSimulate( phys, deltatime )

	--Is this necessary?
	self:GetPhysicsObject():Wake()
	
	phys:Wake()
	
	local Pos = phys:GetPos()
	local Vel = phys:GetVelocity()
	local Distance = self.dt.TargetPosition - Pos
	
	if ( Distance == Vector(0,0,0) ) then return end
	
	local Exponent = Vector(Distance.x^2, Distance.y^2, Distance.z^2)
	--Msg(string.format( "Exponent: (%.2f, %.2f, %.2f)\n", Exponent.x, Exponent.y, Exponent.z))

	if ( Distance.x < 0 ) then
		Exponent.x = Exponent.x * -1
	end

	if ( Distance.y < 0 ) then
		Exponent.y = Exponent.y * -1
	end

	if ( Distance.z < 0 ) then
		Exponent.z = Exponent.z * -1
	end
	--Msg(string.format( "Distance: (%.2f, %.2f, %.2f)\n", Distance.x, Distance.y, Distance.z))
	Exponent = Exponent * deltatime * 300
	
	local physVel = phys:GetVelocity()
	
	Exponent = Exponent - (physVel * deltatime * 600 )
	--Msg(string.format( "physVel: (%.2f, %.2f, %.2f)\n", physVel.x, physVel.y, physVel.z))
	// The higher you make this 300 the less it will flop about
	// I'm thinking it should actually be relative to any objects we're connected to
	// Since it seems to flop more and more the heavier the object
	
	Exponent.x = math.Clamp( Exponent.x, -5000, 5000 )
	Exponent.y = math.Clamp( Exponent.y, -5000, 5000 )
	Exponent.z = math.Clamp( Exponent.z, -5000, 5000 )
	
	local Linear = Exponent
	local Angular = Vector(0,0,0)
	--Msg(string.format( "Linear force: (%.2f, %.2f, %.2f)\n", Linear.x, Linear.y, Linear.z))

	return Angular, Linear, SIM_GLOBAL_ACCELERATION
	
end

function ENT:SetTargetPosition( position )
	self:GetPhysicsObject():Wake()
	self.dt.TargetPosition = position
end

function ENT:SetTargetVelocity( velocity )
	Msg(string.format( "Setting velocity to: (%.2f, %.2f, %.2f)\n", velocity.x, velocity.y, velocity.z))
	if ( z != Vector(0,0,0) ) then
		self:GetPhysicsObject():Wake()
	end

--	self.Velocity = velocity * FrameTime() * 5000
	self.TargetVelocity = velocity * 0.033 * 5000
	Msg(string.format( "Self.Velocity is now: (%.2f, %.2f, %.2f) frametime was %.2f\n", self.TargetVelocity.x, self.TargetVelocity.y, self.TargetVelocity.z, FrameTime()))
end

/*---------------------------------------------------------
   SetStrength
---------------------------------------------------------*/
function ENT:SetStrength( strength )

	local phys = self:GetPhysicsObject()
	if ( phys:IsValid() ) then 
		phys:SetMass( 150 * strength )
	end

	self:UpdateLabel()
	
end

