stock TF2_GetPlayerCond(client)
{
    return GetEntProp(client, Prop_Send, "m_nPlayerCond");
}

stock TF2_SetPlayerCond(client,playerCond)
{
    SetEntProp(client, Prop_Send, "m_nPlayerCond", playerCond);
}

stock TF2_GetNumHealers(client)
{
    return GetEntProp(client, Prop_Send, "m_nNumHealers");
}

stock bool:TF2_IsPlayerZoomed(client)
{
    new pcond = TF2_GetPlayerCond(client);
    return pcond >= 0 ? ((pcond & TF2_PLAYER_ZOOMED) != 0) : false;
}

stock bool:TF2_IsPlayerHealing(client)
{
    new pcond = TF2_GetPlayerCond(client);
    return pcond >= 0 ? ((pcond & TF2_PLAYER_HEALING) != 0) : false;
}

stock bool:TF2_IsPlayerOverHealing(client)
{
    new pcond = TF2_GetPlayerCond(client);
    return pcond >= 0 ? ((pcond & TF2_PLAYER_OVERHEALING) != 0) : false;
}

stock bool:TF2_IsPlayerUrine(client)
{
    new pcond = TF2_GetPlayerCond(client);
    return pcond >= 0 ? ((pcond & TF2_PLAYER_URINE) != 0) : false;
}

stock bool:TF2_IsPlayerTaunt(client)
{
    new pcond = TF2_GetPlayerCond(client);
    return pcond >= 0 ? ((pcond & TF2_PLAYER_TAUNTING) != 0) : false;
}

stock bool:TF2_IsPlayerSlowed(client)
{
    new pcond = TF2_GetPlayerCond(client);
    return pcond >= 0 ? ((pcond & TF2_PLAYER_SLOWED) != 0) : false;
}

stock bool:TF2_IsPlayerDisguised(client)
{
    new pcond = TF2_GetPlayerCond(client);
    return pcond >= 0 ? ((pcond & TF2_PLAYER_DISGUISED) != 0) : false;
}

stock bool:TF2_IsPlayerChangingCloak(client)
{
	if( TF2_GetPlayerClass(client) == TFClass_Spy )
	{
		if(GetGameTime() <= GetEntPropFloat(client, Prop_Send, "m_flInvisChangeCompleteTime"))
		{
			return true;
		}
	}
	return false;
}

stock bool:TF2_IsPlayerCloaked(client)
{
    new pcond = TF2_GetPlayerCond(client);
    return pcond >= 0 ? ((pcond & TF2_PLAYER_CLOAKED) != 0) : false;
}

stock bool:TF2_IsPlayerFeignDeath(client)
{
    new pcond = TF2_GetPlayerCond(client);
    return pcond >= 0 ? ((pcond & TF2_PLAYER_FEIGNDEATH) != 0) : false;
}

stock bool:TF2_IsPlayerBlur(client)
{
    new pcond = TF2_GetPlayerCond(client);
    return pcond >= 0 ? ((pcond & TF2_PLAYER_BLUR) != 0) : false;
}

stock bool:TF2_IsPlayerStun(client)
{
    new pcond = TF2_GetPlayerCond(client);
    return pcond >= 0 ? ((pcond & TF2_PLAYER_STUN) != 0) : false;
}

stock bool:TF2_IsPlayerChargeReleased(client)
{
	new index = GetPlayerWeaponSlot(client, 1);
	if (index > 0)
	{
		new String:classname[64];
		TF2_GetWeaponClass(index, classname, sizeof(classname));
		
		if( StrEqual(classname, "CWeaponMedigun") )
		{
			return bool:GetEntProp(index, Prop_Send, "m_bChargeRelease");
		}
	}		
	return false;
}

stock bool:TF2_IsPlayerUber(client)
{
    new pcond = TF2_GetPlayerCond(client);
    return pcond >= 0 ? ((pcond & (TF2_PLAYER_INVULN | TF2_PLAYER_CRITS)) != 0) : false;
}

stock bool:TF2_IsPlayerInvuln(client)
{
    new pcond = TF2_GetPlayerCond(client);
    return pcond >= 0 ? ((pcond & TF2_PLAYER_INVULN) != 0) : false;
}

stock bool:TF2_IsPlayerCrits(client)
{
    new pcond = TF2_GetPlayerCond(client);
    return pcond >= 0 ? ((pcond & TF2_PLAYER_CRITS) != 0) : false;
}

stock bool:TF2_IsPlayerOnFire(client)
{
    new pcond = TF2_GetPlayerCond(client);
    return pcond >= 0 ? ((pcond & TF2_PLAYER_ONFIRE) != 0) : false;
}

stock bool:TF2_IsPlayerCharging(client)
{
    new pcond = TF2_GetPlayerCond(client);
    return pcond >= 0 ? ((pcond & TF2_PLAYER_CHARGING) != 0) : false;
}

stock TF2_SetPlayerCloak(client, bool:enabled)
{
    new playerCond = TF2_GetPlayerCond(client);
    if (enabled)
        TF2_SetPlayerCond(client, (playerCond | TF2_PLAYER_CLOAKED));
    else
        TF2_SetPlayerCond(client, (playerCond & (~TF2_PLAYER_CLOAKED)));
}

stock Float:TF2_GetClassSpeed(TFClassType:class)
{
    switch (class)
    {
        case TFClass_Scout:     return 400.0;
        case TFClass_Soldier:   return 240.0;
        case TFClass_DemoMan:   return 280.0;
        case TFClass_Medic:     return 320.0;
        case TFClass_Pyro:      return 300.0;
        case TFClass_Spy:       return 300.0;
        case TFClass_Engineer:  return 300.0;
        case TFClass_Sniper:    return 300.0;
        case TFClass_Heavy:     return 230.0;
    }
    return 0.0;
}

stock Float:TF2_GetPlayerClassSpeed(client)
{
    if( TF2_IsPlayerSlowed( client ) )
	{
		if( TF2_GetItemDefIndex( TF2_GetCurrentWeapon( client ) ) == _:ITEM_WEAPON_HUNTSMAN )
		{
			if( TF2_GetPlayerSniperCharge( client ) > 0 )
			{
				return 160.0;
			}
		}
		
		return 80.0;
	}
	
	if( TF2_GetItemDefIndex( TF2_GetCurrentWeapon( client ) ) == _:ITEM_WEAPON_PICKAXE )
	{
		new health = GetClientHealth( client );
		if( health <= 300 && health > 160)
		{
	        return TF2_GetClassSpeed( TF2_GetPlayerClass( client ) );
		}
		else if( health <= 160 && health > 120)
		{
	        return TF2_GetClassSpeed( TF2_GetPlayerClass( client ) ) * 1.1;
		}
		else if( health <= 120 && health > 80)
		{
	        return TF2_GetClassSpeed( TF2_GetPlayerClass( client ) ) * 1.2;
		}
		else if( health <= 80 && health > 40)
		{
	        return TF2_GetClassSpeed( TF2_GetPlayerClass( client ) ) * 1.4;
		}
		else if( health <= 40 && health > 0)
		{
	        return TF2_GetClassSpeed( TF2_GetPlayerClass( client ) ) * 1.6;
		}
	}
	
	new weaponIndex = GetPlayerWeaponSlot(client, 2);
	if( weaponIndex != -1)
	{
		if( TF2_GetItemDefIndex( weaponIndex ) == _:ITEM_WEAPON_EYELANDER )
		{
			new head = TF2_GetDecapitations( client );
			if( head == 1 )
			{
		        return TF2_GetClassSpeed( TF2_GetPlayerClass( client ) ) * 1.08;
			}
			else if( head == 2 )
			{
		        return TF2_GetClassSpeed( TF2_GetPlayerClass( client ) ) * 1.16;
			}
			else if( head == 3 )
			{
		        return TF2_GetClassSpeed( TF2_GetPlayerClass( client ) ) * 1.24;
			}
			else if( head >= 4 )
			{
		        return TF2_GetClassSpeed( TF2_GetPlayerClass( client ) ) * 1.32;
			}
		}
	}

	if( TF2_IsPlayerCharging( client ) )
	{
		return 750.0;
	}
	
	return TF2_GetClassSpeed(TF2_GetPlayerClass(client));
}

stock Float:TF2_GetPlayerSpeed(client)
{
	if( client > 0 )
	{
		new Float:vec[3];
		GetEntPropVector(client, Prop_Data, "m_vecAbsVelocity", vec);
		return GetVectorLength(vec);
	}
	return 0.0;
}

stock Float:TF2_SetPlayerSpeed(client, Float:speed)
{
	if( client > 0 )
	{
		SetEntPropFloat(client, Prop_Data, "m_flMaxspeed", speed);
		SetEntPropFloat(client, Prop_Send, "m_flMaxspeed", speed);
	}
}

stock Float:TF2_SetPlayerDefaultSpeed(client)
{
	if( client > 0 )
	{
		SetEntPropFloat(client, Prop_Data, "m_flMaxspeed", TF2_GetPlayerClassSpeed(client));
		SetEntPropFloat(client, Prop_Send, "m_flMaxspeed", TF2_GetPlayerClassSpeed(client));
	}
}

stock TF2_GetPlayerDefaultHealth(client)
{
	if( client > 0 )
	{
	    return GetEntProp(client, Prop_Data, "m_iMaxHealth");
	}  
	return 100;
}

stock TF2_GetPlayerMaxHealth(client)
{
	if( client > 0 )
	{	
		switch ( TF2_GetPlayerClass( client ) )
		{
			case TFClass_Scout:
			{
				new weaponIndex = GetPlayerWeaponSlot( client, 2 );
				if( weaponIndex != -1)
				{
					if( TF2_GetItemDefIndex( weaponIndex ) == _:ITEM_WEAPON_SANDMAN )
					{
						return 140;
					}
					else
					{
						return 185;
					}
				}
			}
			case TFClass_Soldier:	return 300;
			case TFClass_DemoMan:
			{
				new weaponIndex = GetPlayerWeaponSlot( client, 2 );
				if( TF2_GetItemDefIndex( weaponIndex ) == _:ITEM_WEAPON_EYELANDER )
				{
					new head = TF2_GetDecapitations( client );
					if( head == 1 )
					{
				 		return 248;
					}
					else if( head == 2 )
					{
						return 270;
					}
					else if( head == 3 )
					{
				        return 293;
					}
					else if( head >= 4 )
					{
						return 315;
					}
					else
					{
						return 225;
					}
				}	
				else
				{
					return 260;
				}
			}
			case TFClass_Medic:		return 225;
			case TFClass_Pyro:		return 260;
			case TFClass_Spy:		return 185;
			case TFClass_Engineer:		return 185;
			case TFClass_Sniper:		return 185;
			case TFClass_Heavy:		return 450;
		}
	}
	
	return 100;	
}

stock TF2_GetPlayerDominations( client )
{
	new dominations;
	new offset = FindSendPropInfo("CTFPlayerResource", "m_iActiveDominations");
	new ent = FindEntityByClassname(-1, "tf_player_manager");
	if (ent != -1)
		dominations = GetEntData(ent, (offset + client*4), 4);    
	return dominations;
}

stock TF2_GetCurrentWeaponClass(client, String:name[], maxlength)
{
	if( client > 0 )
	{
		new index = GetEntPropEnt(client, Prop_Send, "m_hActiveWeapon");
		if (index > 0)
			GetEntityNetClass(index, name, maxlength);
	}
}

stock TF2_GetWeaponClass(index, String:name[], maxlength)
{
	if (index > 0)
		GetEntityNetClass(index, name, maxlength);
}

stock TF2_GetWeaponEdictName(index, String:name[], maxlength)
{
	if (index > 0)
		GetEdictClassname(index, name, maxlength);
}

stock TF2_GetDecapitations(any:client)
{
	if( client > 0 )
	{
		return GetEntProp(client, Prop_Send, "m_iDecapitations");
	}
	return -1;
}

stock bool:TF2_CurrentWeaponEqual(client, String:name[])
{
	if( client > 0 )
	{
		new String:classname[64];
		TF2_GetCurrentWeaponClass(client, classname, 64);
		return StrEqual(classname, name);
	}
	return false;
}

stock TF2_GetCurrentWeapon(any:client)
{
	if( client > 0 )
	{
		new weaponIndex = GetEntPropEnt(client, Prop_Send, "m_hActiveWeapon");
		return weaponIndex;
	}
	return -1;
}

stock TF2_GetSlotAmmo(any:client, slot)
{
	if( client > 0 )
	{
		new offset = FindDataMapOffs(client, "m_iAmmo") + ((slot + 1) * 4);
		return GetEntData(client, offset, 4);
	}
	return -1;
}

stock TF2_GetSlotClip(any:client, slot)
{
	if( client > 0 )
	{
		new weaponIndex = GetPlayerWeaponSlot(client, slot);
		if( weaponIndex != -1 )
		{
			return GetEntProp( weaponIndex, Prop_Send, "m_iClip1" );
		}
	}
	return -1;
}

stock TF2_GetSlotWeapon(any:client, slot)
{
	if( client > 0 && slot >= 0)
	{
		new weaponIndex = GetPlayerWeaponSlot(client, slot-1);
		return weaponIndex;
	}
	return -1;
}

stock TF2_DeletePlayerSlot(any:client, deleteSlot, afterSlot)
{
	if( IsClientInGame(client) && IsPlayerAlive(client) )
	{
		new weaponIndex = GetPlayerWeaponSlot(client, deleteSlot);
		if( weaponIndex != -1 )
		{
			RemovePlayerItem(client, weaponIndex);
			RemoveEdict(weaponIndex);
			TF2_RemoveWeaponSlot(client, deleteSlot);
			
			if(GetEntPropEnt(client, Prop_Send, "m_hActiveWeapon") == -1)
			{
				ClientCommand(client, "slot%d", afterSlot);
			}
		}	
	}			
}

stock bool:TF2_IsAllowPlantSapper(client)
{
	if( client > 0 )
	{
		if(TF2_CurrentWeaponEqual(client, "CTFWeaponBuilder"))
		{
			new weaponIndex = GetEntPropEnt(client, Prop_Send, "m_hActiveWeapon");
			if (weaponIndex > 0)
			{
				if(GetEntProp(weaponIndex, Prop_Send, "m_iBuildState")==2)
				{
					return true;
				}
			}
		}
	}
	return false;
}

stock bool:TF2_EdictNameEqual(entity, String:name[])
{
	if( entity > 0 )
	{
		if(IsValidEdict(entity))
		{
			new String:edictName[64];
			GetEdictClassname(entity, edictName, sizeof(edictName)); 
			return StrEqual(edictName, name);
		}
	}
	return false;
}
		
stock TF2_GetPlayerUberLevel(client)
{
	new index = GetPlayerWeaponSlot(client, 1);
					
	if (index > 0)
	{
		new String:classname[64];
		TF2_GetWeaponClass(index, classname, sizeof(classname));
		
		if( StrEqual(classname, "CWeaponMedigun") )
		{
			return RoundFloat(GetEntPropFloat(index, Prop_Send, "m_flChargeLevel")*100);
		}
		
	}
	return 0;
}

stock TF2_SetPlayerUberLevel(client, uberlevel)
{
	new index = GetPlayerWeaponSlot(client, 1);
	if (index > 0)
	{
		new String:classname[64];
		TF2_GetWeaponClass(index, classname, sizeof(classname));
		
		if( StrEqual(classname, "CWeaponMedigun") )
		{
			SetEntPropFloat(index, Prop_Send, "m_flChargeLevel", uberlevel*0.01);
		}
	}
}

stock TF2_GetHealingTarget(client)
{
	new String:classname[64];
	TF2_GetCurrentWeaponClass(client, classname, sizeof(classname));
	
	if( StrEqual(classname, "CWeaponMedigun") )
	{
		new index = GetEntPropEnt(client, Prop_Send, "m_hActiveWeapon");
		if( GetEntProp(index, Prop_Send, "m_bHealing") == 1 )
		{
			return GetEntPropEnt(index, Prop_Send, "m_hHealingTarget");
		}
	}
		
	return -1;
}

stock bool:TF2_IsReadyFeignDeath(client)
{
	if( TF2_GetPlayerClass(client) == TFClass_Spy )
	{
	    return bool:GetEntProp(client, Prop_Send, "m_bFeignDeathReady");
	}
	
	return false;
}

stock TF2_GetPlayerCloakMeter(client)
{
	if( TF2_GetPlayerClass(client) == TFClass_Spy )
	{
	    return RoundFloat(GetEntPropFloat(client, Prop_Send, "m_flCloakMeter"));
	}
	
	return 100;
}

stock TF2_SetPlayerCloakMeter(client, cloakMeter)
{
 	if( TF2_GetPlayerClass(client) == TFClass_Spy )
	{
		SetEntPropFloat(client, Prop_Send, "m_flCloakMeter", cloakMeter*1.0);
	}
}

stock TF2_GetPlayerMetalAmount(client)
{
	return GetEntData(client, FindDataMapOffs(client, "m_iAmmo") + (3 * 4), 4);
}

stock TF2_SetPlayerMetalAmount(client, metal)
{
	SetEntData(client, FindDataMapOffs(client, "m_iAmmo") + (3 * 4), metal, 4);  
}

stock TF2_GetPlayerSniperCharge(client)
{
	new index = GetPlayerWeaponSlot(client, 0);
	if (index > 0)
	{
		if( TF2_GetItemDefIndex( index ) == _:ITEM_WEAPON_SNIPERRIFLE )
		{
			return RoundFloat(GetEntPropFloat(index, Prop_Send, "m_flChargedDamage") * 0.666);
		}
		else if( TF2_GetItemDefIndex( index ) == _:ITEM_WEAPON_HUNTSMAN )
		{
			new Float:charge = GetGameTime() - GetEntPropFloat(index, Prop_Send, "m_flChargeBeginTime");
			
			if( charge > 1.0 )
			{
				charge = 1.0;
			}
			
			if( TF2_IsPlayerSlowed( client ) )
			{
				return RoundFloat( charge * 100.0 ) ;
			}
		}
		
	}
	return 0;
}

stock TF2_SetPlayerSniperCharge(client, chargelevel)
{
	new index = GetPlayerWeaponSlot(client, 0);
	if (index > 0)
	{
		new String:classname[64];
		TF2_GetWeaponClass(index, classname, sizeof(classname));
		
		if( StrEqual(classname, "CTFSniperRifle") )
		{
			SetEntPropFloat(index, Prop_Send, "m_flChargedDamage", chargelevel * 1.5);
		}
	}
}

stock TF2_GetRandomClass() 
{
	return GetRandomInt(1, 9);
}

stock TF2_GetClassPlayers( team, cls ) 
{
	new numPlayers = 0;
	new maxclients = GetMaxClients();
	for (new i = 1; i <= maxclients; i++)
	{
		if( IsClientInGame(i) && IsClientConnected(i) )
		{
			if(GetClientTeam(i) == team && TF2_GetPlayerClass(i) == TFClassType:cls)
			{
				numPlayers++;
			}
		}
	}
	return numPlayers;
}

stock TF2_AddCond( client, cond )
{
	new Handle:cvar = FindConVar( "sv_cheats" );
	new bool:enabled = GetConVarBool( cvar );
	new flags = GetConVarFlags( cvar );
	
	if( !enabled )
	{
		SetConVarFlags( cvar, flags^(FCVAR_NOTIFY|FCVAR_REPLICATED) );
		SetConVarBool( cvar, true );
	}
	FakeClientCommand( client, "addcond %i", cond );
	if( !enabled )
	{
		SetConVarBool( cvar, false );
		SetConVarFlags( cvar, flags );
	}
}

stock TF2_RemoveCond(client, cond)
{
	new Handle:cvar = FindConVar( "sv_cheats" );
	new bool:enabled = GetConVarBool( cvar );
	new flags = GetConVarFlags( cvar );
	
	if( !enabled )
	{
		SetConVarFlags( cvar, flags^(FCVAR_NOTIFY|FCVAR_REPLICATED) );
		SetConVarBool( cvar, true );
	}
	FakeClientCommand(client, "removecond %i", cond);
	if( !enabled )
	{
		SetConVarBool( cvar, false );
		SetConVarFlags( cvar, flags );
	}
}  