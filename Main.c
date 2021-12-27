
#include "../Library/MainInclude.h"
#include "OKInclude.h"





float HousePosition[100][3] = {
{ 6941, 438, 585 },
{ 7086, 368, -197 },
{ 6874, 221, -918 },
{ 6834, 172, -1573 },
{ 6247, 272, -1521 },
{ 7915, 292, -1207 },
{ 7935, 373, 437 },
{ 9724, -313, -3376 },
{ 9210, -283, -1849 },
{ 8563, -308, -2388 },
{ 8538, -321, -3435 },
{ 7503, -300, -3158 },
{ 7284, -264, -4369 },
{ 6220, -264, -3772 },
{ 6244, -264, -4679 },
{ 6900, -264, -5168 },
{ 8156, -264, -4877 },
{ 5005, -264, -4284 },
{ 4928, -264, -3284 },
{ 4112, -264, -3284 },
{ 3475, -214, -4255 },
{ 3436, -214, -2890 },
{ 2694, -186, -3554 },
{ 2570, -162, -4486 },
{ 1007, -226, -3961 },
{ 774, -266, -4689 },
{ 956, -226, -5591 },
{ 1700, -226, -5891 },
{ -209, -140, -6578 },
{ -1087, -89, -6717 },
{ 128, -199, -5627 },
{ -1187, -170, -5474 },
{ 474, -199, -6513 },
{ -1443, 15, -1964 },
{ -1533, 15, -1157 },
{ -2944, 46, -576 },
{ -3679, 96, -542 },
{ -4115, 160, -1581 },
{ -2544, 92, -1579 },
{ -2561, 121, -2355 },
{ -2506, -17, -3926 },
{ -2890, -42, -4896 },
{ -2767, -42, -5880 },
{ -5765, 271, -399 },
{ -6170, 283, 276 },
{ -4696, 213, -1263 },
{ -6541, 222, 2537 },
{ -6460, 222, 3843 },
{ -6243, 261, 4285 },
{ -5937, 261, 5284 },
{ -5229, 261, 4445 },
{ -4465, 211, 4545 },
{ -3026, 93, 4268 },
{ -2459, 123, 4453 },
{ -3951, 123, 3402 },
{ -3367, 123, 3305 },
{ -4599, 219, 3603 },
{ -5967, 219, 3134 },
{ -5450, 219, 2491 },
{ -1551, 93, 3766 },
{ -1676, 59, 3057 },
{ -2166, 59, 2548 },
{ -3217, 107, 2175 },
{ -2700, 87, 1991 },
{ -2085, 78, 1911 },
{ -1384, 37, 2668 },
{ -817, 60, 3903 },
{ 391, 60, 4083 },
{ -252, -31, 5928 },
{ 58, 39, 4801 },
{ -632, -129, 7226 },
{ 292, -136, 6974 },
{ 387, -93, 6437 },
{ 892, 25, 5139 },
{ 1249, 53, 4667 },
{ -268, 32, 2171 },
{ 78, 72, 2916 },
{ 1238, 90, 3302 },
{ -3263, 107, 1075 },
{ -1318, 53, 984 },
{ -403, 53, 1351 },
{ -3980, 90, 1490 },
{ -4109, 96, 2232 },
{ 305, -208, 7536 },
{ 774, -235, 7290 },
{ 1830, -255, 7278 },
{ 2366, -255, 7858 },
{ 1993, -227, 9237 },
{ 1876, -227, 10362 },
{ 938, -227, 9457 },
{ 1223, -255, 8816 },
{ -45, -221, 8368 },
{ 2738, -233, 10334 },
{ 2424, -233, 11255 },
{ 3187, -233, 11657 },
{ 4238, -200, 12238 },
{ 5315, -167, 11913 },
{ 5037, -177, 11316 },
{ 3801, -197, 10841 },
{ 993, -197, 10863 },
};

short HouseAngles[100] = { 44, 104, 84, 94, 160, 29, -50, -50, 109, 175, 
9, 99, -175, -175, 39, 29, -55, 9, 160, 175, 
14, 150, -175, 14, 150, 80, 120, -59, -4, -14, 
150, 175, 25, -105, -130, -175, 140, 59, 24, 79, 
49, 79, 44, 19, 64, 9, 124, 139, 39, 165, 
160, -175, 170, 175, 30, 150, -49, -89, -129, -94, 
-54, -24, -109, 170, -154, 75, 145, 130, 80, 100, 
100, -144, -109, -149, -109, -104, -4, -39, 20, -29, 
-49, 50, 105, -54, 25, -24, -84, -119, -39, 100, 
65, 170, -4, 140, -179, 170, -69, -19, -14, 140, 
 };

short PresentAngles[100];

#if OverKartBuild
void loadLogo()
{
	SetSegment(8,(int)(&ok_Logo));
	*sourceAddress = (int)(&LogoROM);
	*targetAddress = (int)(&ok_FreeSpace);
	dataLength = 0x4014;
	runDMA();
	*sourceAddress = (int)(&ok_FreeSpace);
	*targetAddress = (int)(&ok_Logo);
	runMIO();
	g_NintendoLogoOffset = 0x08005A70;
	g_NintendoLogoBorder = 0x256B9478;

	
	
}
#endif

float ChimneyOffset[] = {-50, 110, -20};



typedef struct OKPresent{

	Vector 	Position;
	Vector 	Velocity;
	Vector 	Target;
	short	Angle[3], Status;
	short	PresentIndex, TargetHouse;
	Bump		BumpData;

} OKPresent;


#define MaxPresents 32
OKPresent PresentArray[MaxPresents];

short HouseStatus[100];
short PresentCount, Score;
float WinTimer;
void SetupPresent()
{
	for (int ThisPresent = 0; ThisPresent < MaxPresents; ThisPresent++)
	{
		PresentArray[ThisPresent].Status = 0;
	}	
}
int FindPresent()
{
	for (int ThisPresent = 0; ThisPresent < MaxPresents; ThisPresent++)
	{
		if (PresentArray[ThisPresent].Status == 0)
		{
			return ThisPresent;
		}
	}
	return -1;
}

void ThrowPresent()
{
	GlobalIntA = FindPresent();
	if (GlobalIntA != -1)
	{
		GlobalShortA = (short)(6 * (float)(((float)GlobalController[0]->AnalogY) / 100.0f));
		PresentArray[GlobalIntA].Status = 1;
		PresentArray[GlobalIntA].Position[0] = GlobalPlayer->position[0];
		PresentArray[GlobalIntA].Position[1] = GlobalPlayer->position[1] + 2;
		PresentArray[GlobalIntA].Position[2] = GlobalPlayer->position[2];
		PresentArray[GlobalIntA].Angle[0] = MakeRandom();
		PresentArray[GlobalIntA].Angle[1] = MakeRandom();
		PresentArray[GlobalIntA].Angle[2] = MakeRandom();
		PresentArray[GlobalIntA].PresentIndex = MakeRandomLimmit(6);
		PresentArray[GlobalIntA].Velocity[0] = 0;
		PresentArray[GlobalIntA].Velocity[1] = 8 + (GlobalShortA * 0.5);
		PresentArray[GlobalIntA].Velocity[2] = 12  + GlobalShortA;
		MakeAlignVector(PresentArray[GlobalIntA].Velocity, GlobalPlayer[0].direction[1]);
	}
	
}

void CheckPresents()
{
	PresentCount = 0;

	for (int ThisPresent = 0; ThisPresent < MaxPresents; ThisPresent++)
	{
		switch (PresentArray[ThisPresent].Status)
		{
			case 1:
			{
				PresentCount++;
				PresentArray[ThisPresent].Position[0] += PresentArray[ThisPresent].Velocity[0];
				PresentArray[ThisPresent].Position[1] += PresentArray[ThisPresent].Velocity[1];
				PresentArray[ThisPresent].Position[2] += PresentArray[ThisPresent].Velocity[2];

				
				CheckBump2((Bump*)&PresentArray[ThisPresent].BumpData, 4.0, PresentArray[ThisPresent].Position[0], PresentArray[ThisPresent].Position[1], PresentArray[ThisPresent].Position[2], PresentArray[ThisPresent].Position[0] - PresentArray[ThisPresent].Velocity[0], PresentArray[ThisPresent].Position[1] - PresentArray[ThisPresent].Velocity[1], PresentArray[ThisPresent].Position[2] - PresentArray[ThisPresent].Velocity[2] );
				ManualBump((Bump*)&PresentArray[ThisPresent].BumpData, PresentArray[ThisPresent].Position);     
				if ((PresentArray[ThisPresent].Position[1] < g_waterHeight) || (PresentArray[ThisPresent].BumpData.distance_xy < 0) || (PresentArray[ThisPresent].BumpData.distance_yz < 0) || (PresentArray[ThisPresent].BumpData.distance_zx < 0))
				{
					PresentArray[ThisPresent].Status = 0;
				}
				else
				{
					PresentArray[ThisPresent].Velocity[1] -= 0.25;
					if (PresentArray[ThisPresent].Velocity[1] < -1.5)
					{
						PresentArray[ThisPresent].Velocity[1] = -1.5;
					}
				}
				DrawGeometryScale(PresentArray[ThisPresent].Position, PresentArray[ThisPresent].Angle, PresentModels[(int)PresentArray[ThisPresent].PresentIndex], 0.01);
				break;
			}
			case 2:
			{
				PresentArray[ThisPresent].Velocity[0] = 0;
				PresentArray[ThisPresent].Velocity[1] = 0;
				if (PresentArray[ThisPresent].Position[1] < PresentArray[ThisPresent].Target[1])
				{
					PresentArray[ThisPresent].Velocity[1] = 1;
				}
				else if (PresentArray[ThisPresent].Position[1] > PresentArray[ThisPresent].Target[1])
				{
					PresentArray[ThisPresent].Velocity[1] = -1;
				}
				
				PresentArray[ThisPresent].Velocity[2] = 3;
				
				MakeAlignVector(PresentArray[ThisPresent].Velocity, -1 * ((short)CalcDirection(PresentArray[ThisPresent].Position, PresentArray[ThisPresent].Target)) );

				
				PresentArray[ThisPresent].Position[0] += PresentArray[ThisPresent].Velocity[0];
				PresentArray[ThisPresent].Position[1] += PresentArray[ThisPresent].Velocity[1];
				PresentArray[ThisPresent].Position[2] += PresentArray[ThisPresent].Velocity[2];

				if (TestCollideSphere(PresentArray[ThisPresent].Position, 3, PresentArray[ThisPresent].Target, 3) )
				{
					if (HouseStatus[(int)PresentArray[ThisPresent].TargetHouse] == 0)
					{
						HouseStatus[(int)PresentArray[ThisPresent].TargetHouse] = 1;
						PresentArray[ThisPresent].Status = 3;
						Score++;	
						NAPlyTrgStart(0, 0x49008017);  //coin sfx				
						if (Score % 3 == 0)
						{
							NAPlyTrgStart(0, 0x29008016);  //coin sfx	
						}
						if (Score == 100)
						{
							WinTimer = g_gameTimer;
						}
					}
					else
					{
						PresentArray[ThisPresent].Status = 0;
					}

				}
				DrawGeometryScale(PresentArray[ThisPresent].Position, PresentArray[ThisPresent].Angle, PresentModels[(int)PresentArray[ThisPresent].PresentIndex], 0.02);
				break;

			}
			case 3:
			{
				PresentArray[ThisPresent].Velocity[0] = 0;
				PresentArray[ThisPresent].Velocity[1] = -3;
				PresentArray[ThisPresent].Velocity[2] = 0;

				PresentArray[ThisPresent].Position[0] += PresentArray[ThisPresent].Velocity[0];
				PresentArray[ThisPresent].Position[1] += PresentArray[ThisPresent].Velocity[1];
				PresentArray[ThisPresent].Position[2] += PresentArray[ThisPresent].Velocity[2];

				if (PresentArray[ThisPresent].Target[1] - PresentArray[ThisPresent].Position[1] > 150)
				{
					PresentArray[ThisPresent].Status = 0;
					HouseStatus[(int)PresentArray[ThisPresent].TargetHouse] = PresentArray[ThisPresent].PresentIndex + 2;
				}
				DrawGeometryScale(PresentArray[ThisPresent].Position, PresentArray[ThisPresent].Angle, PresentModels[(int)PresentArray[ThisPresent].PresentIndex], 0.03);
				break;
			}
			default:
			{
				break;
			}
		}
		
		
	}
	for (int ThisHouse = 0; ThisHouse < 100; ThisHouse++)
	{
		if (HouseStatus[ThisHouse] == 0)
		{		
			if (TestCollideSphere(GlobalPlayer[0].position, 10, HousePosition[ThisHouse], 1750))
			{
				for (int ThisPresent = 0; ThisPresent < MaxPresents; ThisPresent++)
				{
					if (PresentArray[ThisPresent].Status == 1)
					{
						objectPosition[0] = ChimneyOffset[0];
						objectPosition[1] = ChimneyOffset[1];
						objectPosition[2] = ChimneyOffset[2];
						MakeAlignVector(objectPosition, (-1 * ((short)(HouseAngles[ThisHouse] * DEG1))));
						objectPosition[0] += HousePosition[ThisHouse][0];
						objectPosition[1] += HousePosition[ThisHouse][1];
						objectPosition[2] += HousePosition[ThisHouse][2];

						if (TestCollideSphere(PresentArray[ThisPresent].Position, 5, objectPosition, 75))
						{
							PresentArray[ThisPresent].Target[0] = objectPosition[0];
							PresentArray[ThisPresent].Target[1] = objectPosition[1];
							PresentArray[ThisPresent].Target[2] = objectPosition[2];
							PresentArray[ThisPresent].TargetHouse = ThisHouse;
							PresentArray[ThisPresent].Status = 2;
						}
					}
				}
			}
		}
		else
		{
			if (TestCollideSphere(GlobalPlayer[0].position, 10, HousePosition[ThisHouse], 2500))
			{
				objectPosition[0] = ChimneyOffset[0];
				objectPosition[1] = ChimneyOffset[1];
				objectPosition[2] = ChimneyOffset[2];
				MakeAlignVector(objectPosition, (-1 * ((short)(HouseAngles[ThisHouse] * DEG1))));
				objectPosition[0] += HousePosition[ThisHouse][0];
				objectPosition[1] += HousePosition[ThisHouse][1] - 50;
				objectPosition[2] += HousePosition[ThisHouse][2];
				PresentAngles[ThisHouse] += DEG1 * 3;
				objectAngle[1] = PresentAngles[ThisHouse];
				DrawGeometryScale(objectPosition, objectAngle, PresentModels[HouseStatus[ThisHouse] - 2], 0.05);
			}
		}
	}

	for (int ThisCycle = 0; ThisCycle < 4; ThisCycle++)
	{
		*(long*)*graphPointer = (long)(0x06000000);
		*graphPointer = *graphPointer + 4;
		*(long*)*graphPointer = (long)(HouseTextures[ThisCycle]);
		*graphPointer = *graphPointer + 4;

		objectAngle[0] = 0;
		objectAngle[2] = 0;
		for (int ThisHouse = 0; ThisHouse < 100; ThisHouse++)
		{
			if (TestCollideSphere(GlobalPlayer[0].position, 10, HousePosition[ThisHouse], 2500))
			{
				objectPosition[0] = ChimneyOffset[0];
				objectPosition[1] = ChimneyOffset[1];
				objectPosition[2] = ChimneyOffset[2];
				MakeAlignVector(objectPosition, (HouseAngles[ThisHouse] * DEG1));
				objectPosition[0] += HousePosition[ThisHouse][0];
				objectPosition[1] += HousePosition[ThisHouse][1];
				objectPosition[2] += HousePosition[ThisHouse][2];
				objectAngle[1] = HouseAngles[ThisHouse]  * DEG1;
				DrawGeometryScale(HousePosition[ThisHouse], objectAngle, HouseModels[ThisCycle], 0.75);
				
			}
		}
	}
}


void okSetup(void)
{

	SaveFunc800B45E0 = 0x03E0000800000000;
	SaveFunc800B4670 = 0x03E0000800000000;
	SaveFunc800B559C = 0x03E0000800000000;
	SaveFunc800B5948 = 0x03E0000800000000;
	LoadFunc800B4A10 = 0x03E0000800000000;
	
	ConsolePlatform = CheckPlatform();
	EmulatorPlatform = CheckEmulator();	
	
	loadHeaderOffsets();

	if (SwopCheck == 0x11342067)
	{
		StopSwop = true;
	}
	else
	{
		StopSwop = false;		
	}
	SwopCheck = 0x11342067;
	
	
	*(short*)(0x800DC6FE) = 0xFFFF;

	
	loadEEPROM((uint)&SaveGame);	
	
	if ((GlobalController[0]->ButtonHeld & BTN_L) == BTN_L)
	{
		if ((GlobalController[0]->ButtonHeld & BTN_DDOWN) == BTN_DDOWN)
		{	
			SaveGame.GameSettings.GameMode = 2;
			SaveGame.ModSettings.PracticeMode = 2;			
		}
	}

	
	dataLength = 8;
	*sourceAddress = (long)((long)(&g_SequenceTable) + (3 * 8) + 4);	
	*targetAddress = (long)&ok_Sequence;
	runRAM();

	*sourceAddress = (long)((long)(&g_InstrumentTable) + (3 * 8) + 4);
	*targetAddress = (long)&ok_Instrument;
	runRAM();

	*sourceAddress = (int)&g_BombTable;
	*targetAddress = (long)&ok_Bomb;	
	dataLength = 0xA8;
	runRAM();
	
	#if OverKartBuild
	loadLogo();
	#endif
	copyCourseTable(1);
	NopSplashCheckCode();
	
	startupSwitch = 1;
	nopASM = 0;
	HotSwapID = 0;
	asm_SongA = 0x240E0001;
	asm_SongB = 0x240E0001;
	g_sfxPause = 0; //Just for Amped Up (To fix some mute sfx when pausing the game)
	hsGP = 0;
	
	ok_Knowledge = (long)(&ok_Target);

	/*
	*targetAddress = (long)&BackupPortraitTable;
	*sourceAddress = (long)&SelectPortraitTable;
	dataLength = 288;
	runRAM();
	
	asm_PlayerSelectController = 0;
	//asm_PlayerSelectDoObjectP5 = 0;
	//asm_PlayerSelectDoObjectP6 = 0;
	//asm_PlayerSelectDoObjectP7 = 0;
	//asm_PlayerSelectDoObjectP8 = 0;
	asm_DispOBSubPSelCursor1[0] = 0x800A08C8;
	asm_DispOBSubPSelCursor1[1] = 0x800A08C8;
	asm_DispOBSubPSelCursor1[2] = 0x800A08C8;
	asm_DispOBSubPSelCursor1[3] = 0x800A08C8;
	//asm_DOBPSelTurnIn = 0;
	//asm_DOBPSelTurnOut = 0;
	
	PlayerSelectPositions[0].y -= 10;
	PlayerSelectPositions[1].y -= 10;
	PlayerSelectPositions[2].y -= 10;
	PlayerSelectPositions[3].y -= 10;
	
	*targetAddress = (long)&BackupNamePlateTable;
	*sourceAddress = (long)&SelectNamePlateTable;
	dataLength = 32;
	runRAM();
	*/
	
	*(long*)(&ok_USAudio) = *(long*)(&g_RawAudio + 1);
	*(long*)(&ok_USAudio + 1) = *(long*)(&g_InstrumentTable + 1);


	*(long*)(&ok_MRSong) = *(long*)(&g_SequenceTable + (3 * 2) + 1);
	*(long*)(&ok_MRSong + 1) = *(long*)(&g_InstrumentTable + (3 * 2) + 1);

	
	
	FreeSpaceAddress = (int)&ok_Storage;
	SaveGame.TENNES = false;
}

bool checkEndGame()
{
	if (g_playerCount == 0x01)
	{
		if (g_playerPosition1 <= 3)
		{
			return true;
		}
		else if (SaveGame.GameSettings.GPMode == 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		if ((g_playerPosition1 <= 3) || (g_playerPosition2 <= 3))
		{
			return true;
		}
		else if (SaveGame.GameSettings.GPMode == 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}



void startRace()
{
	SetupPresent();
	g_loadedcourseFlag = 0xF0;

	*(int*)(0x8018CAB0) = 0x00B60045;
	*(int*)(0x8018CAB4) = 0x00650000;
	
	if (HotSwapID > 0)
	{
		if (g_gameMode != 0)
		{
			gpCourseIndex = 0;
		}
		
		if (g_gameMode != 3)
		{
			EmptyActionData();
		
			setSky();
			setWater();
			loadMinimap();				
		}
		
		if ((VersionNumber > 4) && (g_gameMode != 3))
		{				
			loadTextureScrollTranslucent();
		}
	}
	

}

void endRace()
{
	if (g_gameMode == 0x00)
	{
		if (checkEndGame())
		{
			scrollLock = false;
		}
		if (!scrollLock)
		{	
			gpTotalTime += g_TrialTime;
			gpCourseIndex++;
		}
	}
}

void MapStartup(short InputID)
{
	LoadCustomHeader(0);
	SetCustomData();
	LoadMapData(0);
	setPath();



}
void InitialMapCode()
{
	
	InitialMap();
}


void DrawPerScreen(Camera* LocalCamera)
{
	DrawOKObjects(LocalCamera);
	CheckPresents();	
}


void gameCode(void) 
{	
	*(int*)(0x800C90F4) = 0x03E00008;
	*(int*)(0x800C90F8) = 0;
	*(int*)(0x801657E4) = 0x01000100;
	*(int*)(0x801657E8) = 0;
	

	PrintNiceTextNumber(50,200,1.0,"",Score);
	if (Score == 100)
	{
		g_gameTimer = WinTimer;
	}
	
	if ((GlobalController[0]->ButtonPressed & BTN_CDOWN) == BTN_CDOWN)
	{	
		ExecuteItem((Player*)&GlobalPlayer[0]);
	}
	
	
	if ((GlobalController[0]->ButtonPressed & BTN_Z) == BTN_Z)
	{
		GlobalIntB = 0;
		ThrowPresent();
	}
	
	else
	{
		GlobalIntB++;
	}
	
	if(SaveGame.TENNES == 1)
	{
		KWSpriteDiv(256,120,(ushort*)&Pirate,512,240,4);
	}
	else
	{


		
		if (HotSwapID > 0)   //Version 4 Texture Scroll Function
		{			
			if ((g_gamePausedFlag == 0) && (scrollLock))
			{
				//runTextureScroll();
				//CheckOKObjects();
				//runDisplayScreen();
				//CheckPaths();
				GetSurfaceID();	
				
				
			}	
		}
		
		if ((HotSwapID > 0) || (SaveGame.RenderSettings.DrawMode == 1))
		{
			g_farClip = 20000;
		}
		else
		{
			g_farClip = 6800;
		}


		if (g_startingIndicator == 0x01)
		{
				// Version 5 and Above.
			// Adds Scrolling Textures.
			// Adds Tranlucent Textures.

			if (raceStatus != 0x01)
			{
				raceStatus = 0x01;
				startRace();
				hsLabel = -1;
				MenuChanged = -1;
			}

			
			GlobalShortD = 0;
			
		}
		if (g_startingIndicator == 0x02)
		{
			raceStatus = 0x02;
			scrollLock = true;
			
			if (GlobalShortD < 60)
			{	
			
				if  (HotSwapID > 0)
				{
					loadFont();
					GlobalIntA = *(long*)(&ok_Credits);
					if (GlobalIntA != 0)
					{		
								
						printString( (140 - (GlobalIntA * 4)), 150, (char*)(&ok_Credits + 1));
					}
					GlobalIntA = *(long*)(&ok_SerialKey);
					if ((SaveGame.GameSettings.GameMode == 1) & (GlobalIntA != 0))
					{
						printString( (140 - (GlobalIntA * 4)), 160, (char*)(&ok_SerialKey + 1));
						printStringNumber(76,170,"Base Version -",OverKartHeader.Version);
					}			
					if (g_gameMode == 0x00)
					{
						printGPTime(gpTotalTime,0);
						if (HotSwapID > 0)
						{
							hsTableSet();
						}				
					}
				}
				

				GlobalShortD += 1;
			}
			else if (GlobalShortD < 99)
			{
				copyCourseTable(0);
				GlobalShortD = 100;
			}
			
			

			
		}
		if (g_startingIndicator == 0x03)
		{
			raceStatus = 0x03;
		}
		
		if (g_startingIndicator == 0x05)
		{
			if (raceStatus != 0x05)
			{
				raceStatus = 0x05;
			}
			if (g_gameMode == 0x00)
			{
				printGPTime(gpTotalTime,30);
			}
		}

		if (g_startingIndicator == 0x07)
		{
			raceStatus = 0x07;
			endRace();
		}	
		
	}
}
void resetMap()
{
	gpTotalTime = 0;
	gpCourseIndex = 0;
}



//
//
//
void allRun(void)
{
	
	switch (startupSwitch)
	{
		case 0:
		okSetup();
		break;

		case 1:
		break;
		
		case 2:
		break;
	}
	
	
	
	
	gMatrixCount = 0;
	
	



	if (SaveGame.GameSettings.CupMode > 0x00)
	{

		asm_CupCount = 15;

		if (gpCourseIndex == 12)
		{
			HotSwapID = 0;
		}
	}
	else
	{
		asm_CupCount = 3;

		if (gpCourseIndex == 4)
		{
			HotSwapID = 0;
		}
	}
	
	
	
	SetCloudType((char)OverKartHeader.SkyType);
	SetWeatherType((char)OverKartHeader.WeatherType);
	SetWeather3D(OverKartHeader.SkyType == 3);
	SetWaterType((char)OverKartHeader.WaterType);
	
	
	
	if (SYSTEM_Region == 0x01)
	{
		
		if (HotSwapID > 0)
		{
			if (g_gameMode != 3)
			{
				g_courseID = 0;
			}
			else
			{
				g_courseID = 15;
			}
		}
		if (g_courseID == 0x14)
		{
			g_player1ScreenWidth = 0x0240;
		}
	}
	
	if (KBGNumber == 10)
	{
		
		g_startingIndicator = 0;
		if (MenuChanged != 10)
		{
			loadNiceFont();	
			MenuChanged = 10;
			startupSwitch = 2;
			*sourceAddress = (int)(&NumbersSpriteROM);
			*targetAddress = (int)(&ok_FreeSpace);
			dataLength = 0x470;
			runDMA();
			*sourceAddress = (int)(&ok_FreeSpace);
			*targetAddress = (int)(&lit_numberSprite);
			runMIO();

			FreeSpaceAddress = (long)&ok_Storage;
			*sourceAddress = (int)&ROMPresents;
			*targetAddress = (int)&ok_FreeSpace;
			dataLength = (int)&ROMPresentsEnd - (int)&ROMPresents;
			runDMA();
			*sourceAddress = (int)&ok_FreeSpace;
			*targetAddress = FreeSpaceAddress + 0x10;
			runMIO();
			SetSegment(8, FreeSpaceAddress + 0x10);

			#if ProtectMode
				SaveGame.TENNES = DPR();
				DPRSave();
			#endif
		}
	}

}
void PrintMenuFunction()
{
	#if ProtectMode
	if(SaveGame.TENNES == 1)
	{		
		if (SaveGame.SaveVersion != 99)
		{
			SaveGame.SaveVersion = 99;
			*sourceAddress = (int)(&Pirate);
			*targetAddress = (int)(&ok_FreeSpace);
			dataLength = (int)&PirateEnd - (int)&Pirate;
			runDMA();
			*sourceAddress = (int)(&ok_FreeSpace);
			*targetAddress = (int)(&ok_Storage);
			runMIO();
		}
		KWSpriteDiv(256,120,(ushort*)&ok_Storage,512,240,4);
	}
	#endif
}

void DisplayCrashScreen()
{
	*sourceAddress = (int)(&Crash);
	*targetAddress = *(uint*)0x80162D5C;
	dataLength = (int)&CrashEnd - (int)&Crash;
	runDMA();
}


void XLUDisplay(Screen* PlayerScreen)
{	
	if ((OverKartHeader.Version > 4) && (HotSwapID > 0))
	{	
		if (g_gameMode != 3)
		{
			DisplayGroupmap(GetRealAddress(SegmentAddress(6,OverKartHeader.XLUSectionViewPosition)), PlayerScreen);
		}
		else
		{
			*(long*)*graphPointer = (long)(0x06000000);
			*graphPointer = *graphPointer + 4;
			*(long*)*graphPointer = (long)(SegmentAddress(6,OverKartHeader.XLUSectionViewPosition));
			*graphPointer = *graphPointer + 4;
		}
	}
}



void titleMenu()
{
	if (titleDemo > 4)
	{
		titleDemo = 4;
	}
	
	g_mracewayTime = 0;
	g_mflagID = 0;
	g_mlogoY = 400;
	KWSpriteDiv(160,90, (ushort*)(&Splash), 128, 128, 16);
	
	if ( ((GlobalController[0]->ButtonPressed & BTN_A) == BTN_A) || ((GlobalController[0]->ButtonPressed & BTN_START) == BTN_START) )
	{
		
		//StartGame
		KBGNumber = 11;
		g_screenSplitA = 0;
		g_ScreenSplitB = 0;
		g_cupSelect = 0;
		g_courseSelect = 0;
		g_courseID = 0;
		*(char*)(0x8018EDF1) = 0;
		g_raceClass = 1;
		g_playerCount = 1;
		g_gameMode = 1;
		g_menuMultiplayerSelection = 1;
		GlobalPlayer[0].kart = 0;
		swapHS(1);
		courseValue = 0;
		
		g_NewSequenceMode = 4;

		
	}
	return;
}