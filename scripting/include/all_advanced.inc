new Float:g_LastKeyCheckTime[MAXPLAYERS+1] = 0.0;

stock SaveKeyTime(any:client)
{
	if( IsClientInGame(client) )
	{		
		g_LastKeyCheckTime[client] = GetGameTime();
	}
}

stock bool:CheckElapsedTime(any:client, Float:time)
{
	if( IsClientInGame(client) )
	{	
		if( GetGameTime() - g_LastKeyCheckTime[client] >= time)
		{
			return true;
		}
	}

	return false;
}

stock ClearTimer(&Handle:timer)
{
	if( timer != INVALID_HANDLE )
	{
		KillTimer( timer );
	}
	timer = INVALID_HANDLE;
}

stock bool:EdictEqual(ent, const String:name[])
{
	if( ent != -1 && IsValidEdict( ent ) )
	{
		new String:edictName[32];
		GetEdictClassname( ent, edictName, sizeof( edictName ) );
		return StrEqual( edictName, name );
	}
	return false;
}

stock bool:CanSeeTarget( any:origin, Float:pos[3], any:target, Float:targetPos[3], Float:range, bool:throughPlayer=true, bool:throughBuild=true )
{
	new Float:distance;			
	new Float:backpos[3];		
	backpos = pos;
	
	distance = GetVectorDistanceMeter( pos, targetPos );
		
	if( distance >= range )
	{		
		return false;
	}
		
	new Handle:TraceEx = INVALID_HANDLE
	g_FilteredEntity = origin;
	TraceEx = TR_TraceRayFilterEx( pos, targetPos, MASK_PLAYERSOLID, RayType_EndPoint, TraceFilter );
	new hitEnt = -1;
	hitEnt = TR_GetEntityIndex( TraceEx );	
	new Float:hitPos[3];
	TR_GetEndPosition( hitPos, TraceEx );		
	
	if( GetVectorDistanceMeter( hitPos, targetPos ) <= 1.0 )
	{
		
		if( throughPlayer )
		{
			
			new String:edictName[64];
			GetEdictClassname( hitEnt, edictName, sizeof( edictName ) ); 
			if( StrEqual( edictName, "player" ) )  
			{
				
				GetEntPropVector( hitEnt, Prop_Data, "m_vecAbsOrigin", pos );
				if(GetVectorDistanceMeter( pos, targetPos ) > 1.0)
				{
					g_FilteredEntity = hitEnt;
					TraceEx = TR_TraceRayFilterEx( hitPos, targetPos, MASK_PLAYERSOLID, RayType_EndPoint, TraceFilter );
					hitEnt = TR_GetEntityIndex(TraceEx);	
					TR_GetEndPosition( hitPos, TraceEx );	
				}
				else
				{
					
					pos = targetPos;
				}
			}
		}		
		
		if( throughBuild )
		{
			
			new String:edictName[64];
			GetEdictClassname( hitEnt, edictName, sizeof( edictName ) ); 
			if( StrEqual(edictName, "obj_dispenser")
			|| StrEqual(edictName, "obj_sentrygun") 
			||	StrEqual(edictName, "obj_teleporter_entrance") 
			||	StrEqual(edictName, "obj_teleporter_exit")
			||	StrEqual(edictName, "obj_attachment_sapper")
			)
			{
				
				GetEntPropVector( hitEnt, Prop_Data, "m_vecAbsOrigin", pos );
				if(GetVectorDistanceMeter( pos, targetPos ) > 1.0)
				{
					g_FilteredEntity = hitEnt;
					TraceEx = TR_TraceRayFilterEx( hitPos, targetPos, MASK_PLAYERSOLID, RayType_EndPoint, TraceFilter );
					hitEnt = TR_GetEntityIndex(TraceEx);	
					TR_GetEndPosition( hitPos, TraceEx );	
				}
				else
				{
					
					pos = targetPos;
				}
			}
		}		
	}
	
	if( GetVectorDistanceMeter( hitPos, targetPos ) <= 1.0 )
	{
		pos = backpos;
		return true;
	}
		
	pos = backpos;

	return false;
}

public bool:TraceFilter(ent, contentMask)
{
   return (ent == g_FilteredEntity) ? false : true;
}

stock Float:MeterToUnit(Float:distance)
{
   return distance * 50.00;
}

stock Float:GetVectorDistanceMeter(const Float:vec1[3], const Float:vec2[3], bool:squared=false) 
{
	return UnitToMeter( GetVectorDistance( vec1, vec2, squared ) );
}

stock Float:GetDistanceMeter(const ent1, const ent2, bool:squared=false) 
{
	new Float:pos1[3];
	new Float:pos2[3];
	
	GetEntPropVector( ent1, Prop_Data, "m_vecAbsOrigin", pos1 );
	GetEntPropVector( ent2, Prop_Data, "m_vecAbsOrigin", pos2 );
	
	return UnitToMeter( GetVectorDistance( pos1, pos2, squared ) );
}

stock ScreenFade(client, red, green, blue, alpha, duration, type)
{
	new Handle:msg
	
	msg = StartMessageOne("Fade", client)
	BfWriteShort(msg, 255)
	BfWriteShort(msg, duration)
	BfWriteShort(msg, type)
	BfWriteByte(msg, red)
	BfWriteByte(msg, green)
	BfWriteByte(msg, blue)	
	BfWriteByte(msg, alpha)
	EndMessage()
}

stock Action:UnFade(Handle:timer, any:client)
{
    if (client)
    {
        if (IsClientInGame(client))
        {
            if (IsPlayerAlive(client))
            {
				ScreenFade(client, 0, 0, 0, 0, 2000, IN)
			}
		}
	}
}