#include "SoundManager.h"


void SoundManager::init(){
	//SDL_Init( SDL_INIT_AUDIO);
	Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ); 


	this->music = Mix_LoadMUS(MUSICAFONDO);
	
	this->fxAIRSTRIKE =  Mix_LoadWAV(AIRSTRIKE);
	this->fxARMAGEDDON =  Mix_LoadWAV(ARMAGEDDON);
	this->fxBANANAIMPACT =  Mix_LoadWAV(BANANAIMPACT);
	this->fxBASEBALLBATIMPACT =  Mix_LoadWAV(BASEBALLBATIMPACT);
	this->fxBASEBALLBATJINGLE =  Mix_LoadWAV(BASEBALLBATJINGLE);
	this->fxBASEBALLBATRELEASE =  Mix_LoadWAV(BASEBALLBATRELEASE);
	this->fxBLOWTORCH =  Mix_LoadWAV(BLOWTORCH);
	this->fxCAMERAPAN =  Mix_LoadWAV(CAMERAPAN);
	this->fxCOLLECT =  Mix_LoadWAV(COLLECT);
	this->fxCOMMUNICATOR =  Mix_LoadWAV(COMMUNICATOR);
	this->fxCOUGH1 =  Mix_LoadWAV(COUGH1);
	this->fxCOUGH2 =  Mix_LoadWAV(COUGH2);
	this->fxCOUGH3 =  Mix_LoadWAV(COUGH3);
	this->fxCOUGH4 =  Mix_LoadWAV(COUGH4);
	this->fxCOUGH5 =  Mix_LoadWAV(COUGH5);
	this->fxCOUGH6 =  Mix_LoadWAV(COUGH6);
	this->fxCOWMOO =  Mix_LoadWAV(COWMOO);
	this->fxCRATEIMPACT =  Mix_LoadWAV(CRATEIMPACT);
	this->fxCRATEPOP =  Mix_LoadWAV(CRATEPOP);
	this->fxCROSSIMPACT =  Mix_LoadWAV(CROSSIMPACT);
	this->fxCROWDPART1 =  Mix_LoadWAV(CROWDPART1);
	this->fxCROWDPART2 =  Mix_LoadWAV(CROWDPART2);
	this->fxCURSORSELECT =  Mix_LoadWAV(CURSORSELECT);
	this->fxDONORCARDAPPEARS =  Mix_LoadWAV(DONORCARDAPPEARS);
	this->fxDONORCARDCOLLECT =  Mix_LoadWAV(DONORCARDCOLLECT);
	this->fxDRAGONBALLIMPACT =  Mix_LoadWAV(DRAGONBALLIMPACT);
	this->fxDRAGONBALLRELEASE =  Mix_LoadWAV(DRAGONBALLRELEASE);
	//this->fxDRILL =  Mix_LoadWAV(DRILL);
	this->fxDRILLIMPACT =  Mix_LoadWAV(DRILLIMPACT);
	this->fxEXPLOSION1 =  Mix_LoadWAV(EXPLOSION1);
	this->fxEXPLOSION2 =  Mix_LoadWAV(EXPLOSION2);
	this->fxEXPLOSION3 =  Mix_LoadWAV(EXPLOSION3);
	this->fxFIREPUNCHIMPACT =  Mix_LoadWAV(FIREPUNCHIMPACT);
	this->fxFLAMETHROWERATTACK =  Mix_LoadWAV(FLAMETHROWERATTACK);
	this->fxFLAMETHROWERLOOP =  Mix_LoadWAV(FLAMETHROWERLOOP);
	this->fxFREEZE =  Mix_LoadWAV(FREEZE);
	this->fxFRENCHANTHEM =  Mix_LoadWAV(FRENCHANTHEM);
	this->fxFROZENWORMIMPACT =  Mix_LoadWAV(FROZENWORMIMPACT);
	this->fxFUSE =  Mix_LoadWAV(FUSE);
	this->fxGIRDERIMPACT =  Mix_LoadWAV(GIRDERIMPACT);
	this->fxGRENADEIMPACT =  Mix_LoadWAV(GRENADEIMPACT);
	this->fxHANDGUNFIRE =  Mix_LoadWAV(HANDGUNFIRE);
	this->fxHOLYDONKEY =  Mix_LoadWAV(HOLYDONKEY);
	this->fxHOLYDONKEYIMPACT =  Mix_LoadWAV(HOLYDONKEYIMPACT);
	this->fxHOLYGRENADE =  Mix_LoadWAV(HOLYGRENADE);
	this->fxHOLYGRENADEIMPACT =  Mix_LoadWAV(HOLYGRENADEIMPACT);
	this->fxINDIANANTHEM =  Mix_LoadWAV(INDIANANTHEM);
	this->fxJETPACKFINISH =  Mix_LoadWAV(JETPACKFINISH);
	this->fxJETPACKLOOP1 =  Mix_LoadWAV(JETPACKLOOP1);
	this->fxJETPACKLOOP2 =  Mix_LoadWAV(JETPACKLOOP2);
	this->fxJETPACKSTART =  Mix_LoadWAV(JETPACKSTART);
	this->fxKAMIKAZERELEASE =  Mix_LoadWAV(KAMIKAZERELEASE);
	this->fxKEYCLICK =  Mix_LoadWAV(KEYCLICK);
	this->fxKEYERASE =  Mix_LoadWAV(KEYERASE);
	this->fxLOADINGTICK =  Mix_LoadWAV(LOADINGTICK);
	this->fxLONGBOWIMPACT =  Mix_LoadWAV(LONGBOWIMPACT);
	this->fxLONGBOWRELEASE =  Mix_LoadWAV(LONGBOWRELEASE);
	this->fxMAGICBULLET =  Mix_LoadWAV(MAGICBULLET);
	this->fxMINEARM =  Mix_LoadWAV(MINEARM);
	this->fxMINEDUD =  Mix_LoadWAV(MINEDUD);
	this->fxMINEIMPACT =  Mix_LoadWAV(MINEIMPACT);
	this->fxMINETICK =  Mix_LoadWAV(MINETICK);
	this->fxMINIGUNFIRE =  Mix_LoadWAV(MINIGUNFIRE);
	this->fxMOLEBOMBDIGGINGLOOP =  Mix_LoadWAV(MOLEBOMBDIGGINGLOOP);
	this->fxMOLEBOMBSQUEAK =  Mix_LoadWAV(MOLEBOMBSQUEAK);
	this->fxMOLEBOMBWALKLOOP =  Mix_LoadWAV(MOLEBOMBWALKLOOP);
	this->fxMORSE =  Mix_LoadWAV(MORSE);
	this->fxNINJAROPEFIRE =  Mix_LoadWAV(NINJAROPEFIRE);
	this->fxNINJAROPEIMPACT =  Mix_LoadWAV(NINJAROPEIMPACT);
	this->fxNUKEFLASH =  Mix_LoadWAV(NUKEFLASH);
	this->fxNUKEPART1 =  Mix_LoadWAV(NUKEPART1);
	this->fxNUKEPART2 =  Mix_LoadWAV(NUKEPART2);
	this->fxOILDRUMIMPACT =  Mix_LoadWAV(OILDRUMIMPACT);
	this->fxOLDWOMAN =  Mix_LoadWAV(OLDWOMAN);
	this->fxPAUSETICK =  Mix_LoadWAV(PAUSETICK);
	this->fxPETROL =  Mix_LoadWAV(PETROL);
	this->fxPIGEONCOO =  Mix_LoadWAV(PIGEONCOO);
	this->fxRICOCHET =  Mix_LoadWAV(RICOCHET);
	this->fxROCKETPOWERDOWN =  Mix_LoadWAV(ROCKETPOWERDOWN);
	this->fxROCKETPOWERUP =  Mix_LoadWAV(ROCKETPOWERUP);
	this->fxROCKETRELEASE =  Mix_LoadWAV(ROCKETRELEASE);
	this->fxSALVATIONARMY =  Mix_LoadWAV(SALVATIONARMY);
	this->fxSCALESOFJUSTICE =  Mix_LoadWAV(SCALESOFJUSTICE);
	this->fxSHEEPBAA =  Mix_LoadWAV(SHEEPBAA);
	this->fxSHOTGUNFIRE =  Mix_LoadWAV(SHOTGUNFIRE);
	this->fxSHOTGUNRELOAD =  Mix_LoadWAV(SHOTGUNRELOAD);
	this->fxSIZZLE =  Mix_LoadWAV(SIZZLE);
	this->fxSKUNKGASLOOP =  Mix_LoadWAV(SKUNKGASLOOP);
	this->fxSKUNKSQUEAK =  Mix_LoadWAV(SKUNKSQUEAK);
	this->fxSKUNKWALKLOOP =  Mix_LoadWAV(SKUNKWALKLOOP);
	this->fxSNOTPLOP =  Mix_LoadWAV(SNOTPLOP);
	this->fxSPLASH =  Mix_LoadWAV(SPLASH);
	this->fxSPLISH =  Mix_LoadWAV(SPLISH);
	this->fxSTARTROUND =  Mix_LoadWAV(STARTROUND);
	this->fxSUDDENDEATH =  Mix_LoadWAV(SUDDENDEATH);
	this->fxSUPERSHEEPRELEASE =  Mix_LoadWAV(SUPERSHEEPRELEASE);
	this->fxSUPERSHEEPWHOOSH =  Mix_LoadWAV(SUPERSHEEPWHOOSH);
	this->fxTEAMBOUNCE =  Mix_LoadWAV(TEAMBOUNCE);
	this->fxTEAMDROP =  Mix_LoadWAV(TEAMDROP);
	this->fxTELEPORT =  Mix_LoadWAV(TELEPORT);
	this->fxTHROWPOWERDOWN =  Mix_LoadWAV(THROWPOWERDOWN);
	this->fxTHROWPOWERUP =  Mix_LoadWAV(THROWPOWERUP);
	this->fxTHROWRELEASE =  Mix_LoadWAV(THROWRELEASE);
	this->fxTIMERTICK =  Mix_LoadWAV(TIMERTICK);
	this->fxTWANG1 =  Mix_LoadWAV(TWANG1);
	this->fxTWANG2 =  Mix_LoadWAV(TWANG2);
	this->fxTWANG3 =  Mix_LoadWAV(TWANG3);
	this->fxTWANG4 =  Mix_LoadWAV(TWANG4);
	this->fxTWANG5 =  Mix_LoadWAV(TWANG5);
	this->fxTWANG6 =  Mix_LoadWAV(TWANG6);
	this->fxUNDERWATERLOOP =  Mix_LoadWAV(UNDERWATERLOOP);
	this->fxUNFREEZE =  Mix_LoadWAV(UNFREEZE);
	this->fxUZIFIRE =  Mix_LoadWAV(UZIFIRE);
	this->fxVASESMASH =  Mix_LoadWAV(VASESMASH);
	this->fxVIKINGAXEIMPACT =  Mix_LoadWAV(VIKINGAXEIMPACT);
	this->fxVIKINGAXERELEASE =  Mix_LoadWAV(VIKINGAXERELEASE);
	this->fxWALK_COMPRESS =  Mix_LoadWAV(WALK_COMPRESS);
	//this->fxWALK_EXPAND =  Mix_LoadWAV(WALK_EXPAND);
	this->fxWARNINGBEEP =  Mix_LoadWAV(WARNINGBEEP);
	this->fxWEAPONHOMING =  Mix_LoadWAV(WEAPONHOMING);
	this->fxWORMBURNED =  Mix_LoadWAV(WORMBURNED);
	this->fxWORMIMPACT =  Mix_LoadWAV(WORMIMPACT);
	this->fxWORMLANDING =  Mix_LoadWAV(WORMLANDING);
	this->fxWORMPOP =  Mix_LoadWAV(WORMPOP);
	this->fxWORMSELECT =  Mix_LoadWAV(WORMSELECT);
	this->fxWORMSPRING =  Mix_LoadWAV(WORMSPRING);

	this->fxAMAZING =  Mix_LoadWAV(AMAZING);
	this->fxBORING =  Mix_LoadWAV(BORING);
	this->fxBRILLIANT =  Mix_LoadWAV(BRILLIANT);
	this->fxBUMMER =  Mix_LoadWAV(BUMMER);
	this->fxBUNGEE =  Mix_LoadWAV(BUNGEE);
	this->fxBYEBYE =  Mix_LoadWAV(BYEBYE);
	this->fxCOMEONTHEN =  Mix_LoadWAV(COMEONTHEN);
	this->fxCOWARD =  Mix_LoadWAV(COWARD);
	this->fxDRAGONPUNCH =  Mix_LoadWAV(DRAGONPUNCH);
	this->fxDROP =  Mix_LoadWAV(DROP);
	this->fxEXCELLENT =  Mix_LoadWAV(EXCELLENT);
	this->fxFATALITY =  Mix_LoadWAV(FATALITY);
	this->fxFIRE =  Mix_LoadWAV(FIRE);
	this->fxFIREBALL =  Mix_LoadWAV(FIREBALL);
	this->fxFIRSTBLOOD =  Mix_LoadWAV(FIRSTBLOOD);
	this->fxFLAWLESS =  Mix_LoadWAV(FLAWLESS);
	this->fxGOAWAY =  Mix_LoadWAV(GOAWAY);
	this->fxGRENADE =  Mix_LoadWAV(FXGRENADE);
	this->fxHELLO =  Mix_LoadWAV(HELLO);
	this->fxHURRY =  Mix_LoadWAV(HURRY);
	this->fxILLGETYOU =  Mix_LoadWAV(ILLGETYOU);
	this->fxINCOMING =  Mix_LoadWAV(INCOMING);
	this->fxJUMP1 =  Mix_LoadWAV(JUMP1);
	this->fxJUMP2 =  Mix_LoadWAV(JUMP2);
	this->fxJUSTYOUWAIT =  Mix_LoadWAV(JUSTYOUWAIT);
	this->fxKAMIKAZE =  Mix_LoadWAV(KAMIKAZE);
	this->fxLAUGH =  Mix_LoadWAV(LAUGH);
	this->fxLEAVEMEALONE =  Mix_LoadWAV(LEAVEMEALONE);
	this->fxMISSED =  Mix_LoadWAV(MISSED);
	this->fxNOOO =  Mix_LoadWAV(NOOO);
	this->fxOHDEAR =  Mix_LoadWAV(OHDEAR);
	this->fxOINUTTER =  Mix_LoadWAV(OINUTTER);
	this->fxOOFF1 =  Mix_LoadWAV(OOFF1);
	this->fxOOFF2 =  Mix_LoadWAV(OOFF2);
	this->fxOOFF3 =  Mix_LoadWAV(OOFF3);
	this->fxOOPS =  Mix_LoadWAV(OOPS);
	this->fxORDERS =  Mix_LoadWAV(ORDERS);
	this->fxOUCH =  Mix_LoadWAV(OUCH);
	this->fxOW1 =  Mix_LoadWAV(OW1);
	this->fxOW2 =  Mix_LoadWAV(OW2);
	this->fxOW3 =  Mix_LoadWAV(OW3);
	this->fxPERFECT =  Mix_LoadWAV(PERFECT);
	this->fxREVENGE =  Mix_LoadWAV(REVENGE);
	this->fxRUNAWAY =  Mix_LoadWAV(RUNAWAY);
	this->fxSTUPID =  Mix_LoadWAV(STUPID);
	this->fxTAKECOVER =  Mix_LoadWAV(TAKECOVER);
	this->fxTRAITOR =  Mix_LoadWAV(TRAITOR);
	this->fxUH_OH =  Mix_LoadWAV(UH_OH);
	this->fxVICTORY =  Mix_LoadWAV(VICTORY);
	this->fxWATCHTHIS =  Mix_LoadWAV(WATCHTHIS);
	this->fxWHATTHE =  Mix_LoadWAV(WHATTHE);
	this->fxWOBBLE =  Mix_LoadWAV(WOBBLE);
	this->fxYESSIR =  Mix_LoadWAV(YESSIR);
	this->fxYOULLREGRETTHAT =  Mix_LoadWAV(YOULLREGRETTHAT);





	if (this->music == NULL) Log::i(SOUND,"Error al cargar %s",MUSICAFONDO);
	

	if (this->fxAIRSTRIKE == NULL) Log::i(SOUND,"Error al cargar %s",AIRSTRIKE);
	if (this->fxARMAGEDDON == NULL) Log::i(SOUND,"Error al cargar %s",ARMAGEDDON);
	if (this->fxBANANAIMPACT == NULL) Log::i(SOUND,"Error al cargar %s",BANANAIMPACT);
	if (this->fxBASEBALLBATIMPACT == NULL) Log::i(SOUND,"Error al cargar %s",BASEBALLBATIMPACT);
	if (this->fxBASEBALLBATJINGLE == NULL) Log::i(SOUND,"Error al cargar %s",BASEBALLBATJINGLE);
	if (this->fxBASEBALLBATRELEASE == NULL) Log::i(SOUND,"Error al cargar %s",BASEBALLBATRELEASE);
	if (this->fxBLOWTORCH == NULL) Log::i(SOUND,"Error al cargar %s",BLOWTORCH);
	if (this->fxCAMERAPAN == NULL) Log::i(SOUND,"Error al cargar %s",CAMERAPAN);
	if (this->fxCOLLECT == NULL) Log::i(SOUND,"Error al cargar %s",COLLECT);
	if (this->fxCOMMUNICATOR == NULL) Log::i(SOUND,"Error al cargar %s",COMMUNICATOR);
	if (this->fxCOUGH1 == NULL) Log::i(SOUND,"Error al cargar %s",COUGH1);
	if (this->fxCOUGH2 == NULL) Log::i(SOUND,"Error al cargar %s",COUGH2);
	if (this->fxCOUGH3 == NULL) Log::i(SOUND,"Error al cargar %s",COUGH3);
	if (this->fxCOUGH4 == NULL) Log::i(SOUND,"Error al cargar %s",COUGH4);
	if (this->fxCOUGH5 == NULL) Log::i(SOUND,"Error al cargar %s",COUGH5);
	if (this->fxCOUGH6 == NULL) Log::i(SOUND,"Error al cargar %s",COUGH6);
	if (this->fxCOWMOO == NULL) Log::i(SOUND,"Error al cargar %s",COWMOO);
	if (this->fxCRATEIMPACT == NULL) Log::i(SOUND,"Error al cargar %s",CRATEIMPACT);
	if (this->fxCRATEPOP == NULL) Log::i(SOUND,"Error al cargar %s",CRATEPOP);
	if (this->fxCROSSIMPACT == NULL) Log::i(SOUND,"Error al cargar %s",CROSSIMPACT);
	if (this->fxCROWDPART1 == NULL) Log::i(SOUND,"Error al cargar %s",CROWDPART1);
	if (this->fxCROWDPART2 == NULL) Log::i(SOUND,"Error al cargar %s",CROWDPART2);
	if (this->fxCURSORSELECT == NULL) Log::i(SOUND,"Error al cargar %s",CURSORSELECT);
	if (this->fxDONORCARDAPPEARS == NULL) Log::i(SOUND,"Error al cargar %s",DONORCARDAPPEARS);
	if (this->fxDONORCARDCOLLECT == NULL) Log::i(SOUND,"Error al cargar %s",DONORCARDCOLLECT);
	if (this->fxDRAGONBALLIMPACT == NULL) Log::i(SOUND,"Error al cargar %s",DRAGONBALLIMPACT);
	if (this->fxDRAGONBALLRELEASE == NULL) Log::i(SOUND,"Error al cargar %s",DRAGONBALLRELEASE);
	if (this->fxDRILL == NULL) Log::i(SOUND,"Error al cargar %s",DRILL);
	if (this->fxDRILLIMPACT == NULL) Log::i(SOUND,"Error al cargar %s",DRILLIMPACT);
	if (this->fxEXPLOSION1 == NULL) Log::i(SOUND,"Error al cargar %s",EXPLOSION1);
	if (this->fxEXPLOSION2 == NULL) Log::i(SOUND,"Error al cargar %s",EXPLOSION2);
	if (this->fxEXPLOSION3 == NULL) Log::i(SOUND,"Error al cargar %s",EXPLOSION3);
	if (this->fxFIREPUNCHIMPACT == NULL) Log::i(SOUND,"Error al cargar %s",FIREPUNCHIMPACT);
	if (this->fxFLAMETHROWERATTACK == NULL) Log::i(SOUND,"Error al cargar %s",FLAMETHROWERATTACK);
	if (this->fxFLAMETHROWERLOOP == NULL) Log::i(SOUND,"Error al cargar %s",FLAMETHROWERLOOP);
	if (this->fxFREEZE == NULL) Log::i(SOUND,"Error al cargar %s",FREEZE);
	if (this->fxFRENCHANTHEM == NULL) Log::i(SOUND,"Error al cargar %s",FRENCHANTHEM);
	if (this->fxFROZENWORMIMPACT == NULL) Log::i(SOUND,"Error al cargar %s",FROZENWORMIMPACT);
	if (this->fxFUSE == NULL) Log::i(SOUND,"Error al cargar %s",FUSE);
	if (this->fxGIRDERIMPACT == NULL) Log::i(SOUND,"Error al cargar %s",GIRDERIMPACT);
	if (this->fxGRENADEIMPACT == NULL) Log::i(SOUND,"Error al cargar %s",GRENADEIMPACT);
	if (this->fxHANDGUNFIRE == NULL) Log::i(SOUND,"Error al cargar %s",HANDGUNFIRE);
	if (this->fxHOLYDONKEY == NULL) Log::i(SOUND,"Error al cargar %s",HOLYDONKEY);
	if (this->fxHOLYDONKEYIMPACT == NULL) Log::i(SOUND,"Error al cargar %s",HOLYDONKEYIMPACT);
	if (this->fxHOLYGRENADE == NULL) Log::i(SOUND,"Error al cargar %s",HOLYGRENADE);
	if (this->fxHOLYGRENADEIMPACT == NULL) Log::i(SOUND,"Error al cargar %s",HOLYGRENADEIMPACT);
	if (this->fxINDIANANTHEM == NULL) Log::i(SOUND,"Error al cargar %s",INDIANANTHEM);
	if (this->fxJETPACKFINISH == NULL) Log::i(SOUND,"Error al cargar %s",JETPACKFINISH);
	if (this->fxJETPACKLOOP1 == NULL) Log::i(SOUND,"Error al cargar %s",JETPACKLOOP1);
	if (this->fxJETPACKLOOP2 == NULL) Log::i(SOUND,"Error al cargar %s",JETPACKLOOP2);
	if (this->fxJETPACKSTART == NULL) Log::i(SOUND,"Error al cargar %s",JETPACKSTART);
	if (this->fxKAMIKAZERELEASE == NULL) Log::i(SOUND,"Error al cargar %s",KAMIKAZERELEASE);
	if (this->fxKEYCLICK == NULL) Log::i(SOUND,"Error al cargar %s",KEYCLICK);
	if (this->fxKEYERASE == NULL) Log::i(SOUND,"Error al cargar %s",KEYERASE);
	if (this->fxLOADINGTICK == NULL) Log::i(SOUND,"Error al cargar %s",LOADINGTICK);
	if (this->fxLONGBOWIMPACT == NULL) Log::i(SOUND,"Error al cargar %s",LONGBOWIMPACT);
	if (this->fxLONGBOWRELEASE == NULL) Log::i(SOUND,"Error al cargar %s",LONGBOWRELEASE);
	if (this->fxMAGICBULLET == NULL) Log::i(SOUND,"Error al cargar %s",MAGICBULLET);
	if (this->fxMINEARM == NULL) Log::i(SOUND,"Error al cargar %s",MINEARM);
	if (this->fxMINEDUD == NULL) Log::i(SOUND,"Error al cargar %s",MINEDUD);
	if (this->fxMINEIMPACT == NULL) Log::i(SOUND,"Error al cargar %s",MINEIMPACT);
	if (this->fxMINETICK == NULL) Log::i(SOUND,"Error al cargar %s",MINETICK);
	if (this->fxMINIGUNFIRE == NULL) Log::i(SOUND,"Error al cargar %s",MINIGUNFIRE);
	if (this->fxMOLEBOMBDIGGINGLOOP == NULL) Log::i(SOUND,"Error al cargar %s",MOLEBOMBDIGGINGLOOP);
	if (this->fxMOLEBOMBSQUEAK == NULL) Log::i(SOUND,"Error al cargar %s",MOLEBOMBSQUEAK);
	if (this->fxMOLEBOMBWALKLOOP == NULL) Log::i(SOUND,"Error al cargar %s",MOLEBOMBWALKLOOP);
	if (this->fxMORSE == NULL) Log::i(SOUND,"Error al cargar %s",MORSE);
	if (this->fxNINJAROPEFIRE == NULL) Log::i(SOUND,"Error al cargar %s",NINJAROPEFIRE);
	if (this->fxNINJAROPEIMPACT == NULL) Log::i(SOUND,"Error al cargar %s",NINJAROPEIMPACT);
	if (this->fxNUKEFLASH == NULL) Log::i(SOUND,"Error al cargar %s",NUKEFLASH);
	if (this->fxNUKEPART1 == NULL) Log::i(SOUND,"Error al cargar %s",NUKEPART1);
	if (this->fxNUKEPART2 == NULL) Log::i(SOUND,"Error al cargar %s",NUKEPART2);
	if (this->fxOILDRUMIMPACT == NULL) Log::i(SOUND,"Error al cargar %s",OILDRUMIMPACT);
	if (this->fxOLDWOMAN == NULL) Log::i(SOUND,"Error al cargar %s",OLDWOMAN);
	if (this->fxPAUSETICK == NULL) Log::i(SOUND,"Error al cargar %s",PAUSETICK);
	if (this->fxPETROL == NULL) Log::i(SOUND,"Error al cargar %s",PETROL);
	if (this->fxPIGEONCOO == NULL) Log::i(SOUND,"Error al cargar %s",PIGEONCOO);
	if (this->fxRICOCHET == NULL) Log::i(SOUND,"Error al cargar %s",RICOCHET);
	if (this->fxROCKETPOWERDOWN == NULL) Log::i(SOUND,"Error al cargar %s",ROCKETPOWERDOWN);
	if (this->fxROCKETPOWERUP == NULL) Log::i(SOUND,"Error al cargar %s",ROCKETPOWERUP);
	if (this->fxROCKETRELEASE == NULL) Log::i(SOUND,"Error al cargar %s",ROCKETRELEASE);
	if (this->fxSALVATIONARMY == NULL) Log::i(SOUND,"Error al cargar %s",SALVATIONARMY);
	if (this->fxSCALESOFJUSTICE == NULL) Log::i(SOUND,"Error al cargar %s",SCALESOFJUSTICE);
	if (this->fxSHEEPBAA == NULL) Log::i(SOUND,"Error al cargar %s",SHEEPBAA);
	if (this->fxSHOTGUNFIRE == NULL) Log::i(SOUND,"Error al cargar %s",SHOTGUNFIRE);
	if (this->fxSHOTGUNRELOAD == NULL) Log::i(SOUND,"Error al cargar %s",SHOTGUNRELOAD);
	if (this->fxSIZZLE == NULL) Log::i(SOUND,"Error al cargar %s",SIZZLE);
	if (this->fxSKUNKGASLOOP == NULL) Log::i(SOUND,"Error al cargar %s",SKUNKGASLOOP);
	if (this->fxSKUNKSQUEAK == NULL) Log::i(SOUND,"Error al cargar %s",SKUNKSQUEAK);
	if (this->fxSKUNKWALKLOOP == NULL) Log::i(SOUND,"Error al cargar %s",SKUNKWALKLOOP);
	if (this->fxSNOTPLOP == NULL) Log::i(SOUND,"Error al cargar %s",SNOTPLOP);
	if (this->fxSPLASH == NULL) Log::i(SOUND,"Error al cargar %s",SPLASH);
	if (this->fxSPLISH == NULL) Log::i(SOUND,"Error al cargar %s",SPLISH);
	if (this->fxSTARTROUND == NULL) Log::i(SOUND,"Error al cargar %s",STARTROUND);
	if (this->fxSUDDENDEATH == NULL) Log::i(SOUND,"Error al cargar %s",SUDDENDEATH);
	if (this->fxSUPERSHEEPRELEASE == NULL) Log::i(SOUND,"Error al cargar %s",SUPERSHEEPRELEASE);
	if (this->fxSUPERSHEEPWHOOSH == NULL) Log::i(SOUND,"Error al cargar %s",SUPERSHEEPWHOOSH);
	if (this->fxTEAMBOUNCE == NULL) Log::i(SOUND,"Error al cargar %s",TEAMBOUNCE);
	if (this->fxTEAMDROP == NULL) Log::i(SOUND,"Error al cargar %s",TEAMDROP);
	if (this->fxTELEPORT == NULL) Log::i(SOUND,"Error al cargar %s",TELEPORT);
	if (this->fxTHROWPOWERDOWN == NULL) Log::i(SOUND,"Error al cargar %s",THROWPOWERDOWN);
	if (this->fxTHROWPOWERUP == NULL) Log::i(SOUND,"Error al cargar %s",THROWPOWERUP);
	if (this->fxTHROWRELEASE == NULL) Log::i(SOUND,"Error al cargar %s",THROWRELEASE);
	if (this->fxTIMERTICK == NULL) Log::i(SOUND,"Error al cargar %s",TIMERTICK);
	if (this->fxTWANG1 == NULL) Log::i(SOUND,"Error al cargar %s",TWANG1);
	if (this->fxTWANG2 == NULL) Log::i(SOUND,"Error al cargar %s",TWANG2);
	if (this->fxTWANG3 == NULL) Log::i(SOUND,"Error al cargar %s",TWANG3);
	if (this->fxTWANG4 == NULL) Log::i(SOUND,"Error al cargar %s",TWANG4);
	if (this->fxTWANG5 == NULL) Log::i(SOUND,"Error al cargar %s",TWANG5);
	if (this->fxTWANG6 == NULL) Log::i(SOUND,"Error al cargar %s",TWANG6);
	if (this->fxUNDERWATERLOOP == NULL) Log::i(SOUND,"Error al cargar %s",UNDERWATERLOOP);
	if (this->fxUNFREEZE == NULL) Log::i(SOUND,"Error al cargar %s",UNFREEZE);
	if (this->fxUZIFIRE == NULL) Log::i(SOUND,"Error al cargar %s",UZIFIRE);
	if (this->fxVASESMASH == NULL) Log::i(SOUND,"Error al cargar %s",VASESMASH);
	if (this->fxVIKINGAXEIMPACT == NULL) Log::i(SOUND,"Error al cargar %s",VIKINGAXEIMPACT);
	if (this->fxVIKINGAXERELEASE == NULL) Log::i(SOUND,"Error al cargar %s",VIKINGAXERELEASE);
	if (this->fxWALK_COMPRESS == NULL) Log::i(SOUND,"Error al cargar %s",WALK_COMPRESS);
	if (this->fxWALK_EXPAND == NULL) Log::i(SOUND,"Error al cargar %s",WALK_EXPAND);
	if (this->fxWARNINGBEEP == NULL) Log::i(SOUND,"Error al cargar %s",WARNINGBEEP);
	if (this->fxWEAPONHOMING == NULL) Log::i(SOUND,"Error al cargar %s",WEAPONHOMING);
	if (this->fxWORMBURNED == NULL) Log::i(SOUND,"Error al cargar %s",WORMBURNED);
	if (this->fxWORMIMPACT == NULL) Log::i(SOUND,"Error al cargar %s",WORMIMPACT);
	if (this->fxWORMLANDING == NULL) Log::i(SOUND,"Error al cargar %s",WORMLANDING);
	if (this->fxWORMPOP == NULL) Log::i(SOUND,"Error al cargar %s",WORMPOP);
	if (this->fxWORMSELECT == NULL) Log::i(SOUND,"Error al cargar %s",WORMSELECT);
	if (this->fxWORMSPRING == NULL) Log::i(SOUND,"Error al cargar %s",WORMSPRING);

	if (this->fxAMAZING == NULL) Log::i(SOUND,"Error al cargar %s",AMAZING);
	if (this->fxBORING == NULL) Log::i(SOUND,"Error al cargar %s",BORING);
	if (this->fxBRILLIANT == NULL) Log::i(SOUND,"Error al cargar %s",BRILLIANT);
	if (this->fxBUMMER == NULL) Log::i(SOUND,"Error al cargar %s",BUMMER);
	if (this->fxBUNGEE == NULL) Log::i(SOUND,"Error al cargar %s",BUNGEE);
	if (this->fxBYEBYE == NULL) Log::i(SOUND,"Error al cargar %s",BYEBYE);
	if (this->fxCOMEONTHEN == NULL) Log::i(SOUND,"Error al cargar %s",COMEONTHEN);
	if (this->fxCOWARD == NULL) Log::i(SOUND,"Error al cargar %s",COWARD);
	if (this->fxDRAGONPUNCH == NULL) Log::i(SOUND,"Error al cargar %s",DRAGONPUNCH);
	if (this->fxDROP == NULL) Log::i(SOUND,"Error al cargar %s",DROP);
	if (this->fxEXCELLENT == NULL) Log::i(SOUND,"Error al cargar %s",EXCELLENT);
	if (this->fxFATALITY == NULL) Log::i(SOUND,"Error al cargar %s",FATALITY);
	if (this->fxFIRE == NULL) Log::i(SOUND,"Error al cargar %s",FIRE);
	if (this->fxFIREBALL == NULL) Log::i(SOUND,"Error al cargar %s",FIREBALL);
	if (this->fxFIRSTBLOOD == NULL) Log::i(SOUND,"Error al cargar %s",FIRSTBLOOD);
	if (this->fxFLAWLESS == NULL) Log::i(SOUND,"Error al cargar %s",FLAWLESS);
	if (this->fxGOAWAY == NULL) Log::i(SOUND,"Error al cargar %s",GOAWAY);
	if (this->fxGRENADE == NULL) Log::i(SOUND,"Error al cargar %s",FXGRENADE);
	if (this->fxHELLO == NULL) Log::i(SOUND,"Error al cargar %s",HELLO);
	if (this->fxHURRY == NULL) Log::i(SOUND,"Error al cargar %s",HURRY);
	if (this->fxILLGETYOU == NULL) Log::i(SOUND,"Error al cargar %s",ILLGETYOU);
	if (this->fxINCOMING == NULL) Log::i(SOUND,"Error al cargar %s",INCOMING);
	if (this->fxJUMP1 == NULL) Log::i(SOUND,"Error al cargar %s",JUMP1);
	if (this->fxJUMP2 == NULL) Log::i(SOUND,"Error al cargar %s",JUMP2);
	if (this->fxJUSTYOUWAIT == NULL) Log::i(SOUND,"Error al cargar %s",JUSTYOUWAIT);
	if (this->fxKAMIKAZE == NULL) Log::i(SOUND,"Error al cargar %s",KAMIKAZE);
	if (this->fxLAUGH == NULL) Log::i(SOUND,"Error al cargar %s",LAUGH);
	if (this->fxLEAVEMEALONE == NULL) Log::i(SOUND,"Error al cargar %s",LEAVEMEALONE);
	if (this->fxMISSED == NULL) Log::i(SOUND,"Error al cargar %s",MISSED);
	if (this->fxNOOO == NULL) Log::i(SOUND,"Error al cargar %s",NOOO);
	if (this->fxOHDEAR == NULL) Log::i(SOUND,"Error al cargar %s",OHDEAR);
	if (this->fxOINUTTER == NULL) Log::i(SOUND,"Error al cargar %s",OINUTTER);
	if (this->fxOOFF1 == NULL) Log::i(SOUND,"Error al cargar %s",OOFF1);
	if (this->fxOOFF2 == NULL) Log::i(SOUND,"Error al cargar %s",OOFF2);
	if (this->fxOOFF3 == NULL) Log::i(SOUND,"Error al cargar %s",OOFF3);
	if (this->fxOOPS == NULL) Log::i(SOUND,"Error al cargar %s",OOPS);
	if (this->fxORDERS == NULL) Log::i(SOUND,"Error al cargar %s",ORDERS);
	if (this->fxOUCH == NULL) Log::i(SOUND,"Error al cargar %s",OUCH);
	if (this->fxOW1 == NULL) Log::i(SOUND,"Error al cargar %s",OW1);
	if (this->fxOW2 == NULL) Log::i(SOUND,"Error al cargar %s",OW2);
	if (this->fxOW3 == NULL) Log::i(SOUND,"Error al cargar %s",OW3);
	if (this->fxPERFECT == NULL) Log::i(SOUND,"Error al cargar %s",PERFECT);
	if (this->fxREVENGE == NULL) Log::i(SOUND,"Error al cargar %s",REVENGE);
	if (this->fxRUNAWAY == NULL) Log::i(SOUND,"Error al cargar %s",RUNAWAY);
	if (this->fxSTUPID == NULL) Log::i(SOUND,"Error al cargar %s",STUPID);
	if (this->fxTAKECOVER == NULL) Log::i(SOUND,"Error al cargar %s",TAKECOVER);
	if (this->fxTRAITOR == NULL) Log::i(SOUND,"Error al cargar %s",TRAITOR);
	if (this->fxUH_OH == NULL) Log::i(SOUND,"Error al cargar %s",UH_OH);
	if (this->fxVICTORY == NULL) Log::i(SOUND,"Error al cargar %s",VICTORY);
	if (this->fxWATCHTHIS == NULL) Log::i(SOUND,"Error al cargar %s",WATCHTHIS);
	if (this->fxWHATTHE == NULL) Log::i(SOUND,"Error al cargar %s",WHATTHE);
	if (this->fxWOBBLE == NULL) Log::i(SOUND,"Error al cargar %s",WOBBLE);
	if (this->fxYESSIR == NULL) Log::i(SOUND,"Error al cargar %s",YESSIR);
	if (this->fxYOULLREGRETTHAT == NULL) Log::i(SOUND,"Error al cargar %s",YOULLREGRETTHAT);


}

void SoundManager::playMusic(){
	if( Mix_PlayingMusic() == 0 )
	{
		//Play the music
		Mix_PlayMusic( this->music, -1 );
	}
	//If music is being played
	else
	{
		//If the music is paused
		if( Mix_PausedMusic() == 1 )
		{
			//Resume the music
			Mix_ResumeMusic();
		}
		//If the music is playing
		else
		{
			//Pause the music
			Mix_PauseMusic();
		}
	}
}
void SoundManager::close(){
	Mix_FreeMusic( this->music );
	
	Mix_FreeChunk(this->fxAIRSTRIKE);
	Mix_FreeChunk(this->fxARMAGEDDON);
	Mix_FreeChunk(this->fxBANANAIMPACT);
	Mix_FreeChunk(this->fxBASEBALLBATIMPACT);
	Mix_FreeChunk(this->fxBASEBALLBATJINGLE);
	Mix_FreeChunk(this->fxBASEBALLBATRELEASE);
	Mix_FreeChunk(this->fxBLOWTORCH);
	Mix_FreeChunk(this->fxCAMERAPAN);
	Mix_FreeChunk(this->fxCOLLECT);
	Mix_FreeChunk(this->fxCOMMUNICATOR);
	Mix_FreeChunk(this->fxCOUGH1);
	Mix_FreeChunk(this->fxCOUGH2);
	Mix_FreeChunk(this->fxCOUGH3);
	Mix_FreeChunk(this->fxCOUGH4);
	Mix_FreeChunk(this->fxCOUGH5);
	Mix_FreeChunk(this->fxCOUGH6);
	Mix_FreeChunk(this->fxCOWMOO);
	Mix_FreeChunk(this->fxCRATEIMPACT);
	Mix_FreeChunk(this->fxCRATEPOP);
	Mix_FreeChunk(this->fxCROSSIMPACT);
	Mix_FreeChunk(this->fxCROWDPART1);
	Mix_FreeChunk(this->fxCROWDPART2);
	Mix_FreeChunk(this->fxCURSORSELECT);
	Mix_FreeChunk(this->fxDONORCARDAPPEARS);
	Mix_FreeChunk(this->fxDONORCARDCOLLECT);
	Mix_FreeChunk(this->fxDRAGONBALLIMPACT);
	Mix_FreeChunk(this->fxDRAGONBALLRELEASE);
	Mix_FreeChunk(this->fxDRILL);
	Mix_FreeChunk(this->fxDRILLIMPACT);
	Mix_FreeChunk(this->fxEXPLOSION1);
	Mix_FreeChunk(this->fxEXPLOSION2);
	Mix_FreeChunk(this->fxEXPLOSION3);
	Mix_FreeChunk(this->fxFIREPUNCHIMPACT);
	Mix_FreeChunk(this->fxFLAMETHROWERATTACK);
	Mix_FreeChunk(this->fxFLAMETHROWERLOOP);
	Mix_FreeChunk(this->fxFREEZE);
	Mix_FreeChunk(this->fxFRENCHANTHEM);
	Mix_FreeChunk(this->fxFROZENWORMIMPACT);
	Mix_FreeChunk(this->fxFUSE);
	Mix_FreeChunk(this->fxGIRDERIMPACT);
	Mix_FreeChunk(this->fxGRENADEIMPACT);
	Mix_FreeChunk(this->fxHANDGUNFIRE);
	Mix_FreeChunk(this->fxHOLYDONKEY);
	Mix_FreeChunk(this->fxHOLYDONKEYIMPACT);
	Mix_FreeChunk(this->fxHOLYGRENADE);
	Mix_FreeChunk(this->fxHOLYGRENADEIMPACT);
	Mix_FreeChunk(this->fxINDIANANTHEM);
	Mix_FreeChunk(this->fxJETPACKFINISH);
	Mix_FreeChunk(this->fxJETPACKLOOP1);
	Mix_FreeChunk(this->fxJETPACKLOOP2);
	Mix_FreeChunk(this->fxJETPACKSTART);
	Mix_FreeChunk(this->fxKAMIKAZERELEASE);
	Mix_FreeChunk(this->fxKEYCLICK);
	Mix_FreeChunk(this->fxKEYERASE);
	Mix_FreeChunk(this->fxLOADINGTICK);
	Mix_FreeChunk(this->fxLONGBOWIMPACT);
	Mix_FreeChunk(this->fxLONGBOWRELEASE);
	Mix_FreeChunk(this->fxMAGICBULLET);
	Mix_FreeChunk(this->fxMINEARM);
	Mix_FreeChunk(this->fxMINEDUD);
	Mix_FreeChunk(this->fxMINEIMPACT);
	Mix_FreeChunk(this->fxMINETICK);
	Mix_FreeChunk(this->fxMINIGUNFIRE);
	Mix_FreeChunk(this->fxMOLEBOMBDIGGINGLOOP);
	Mix_FreeChunk(this->fxMOLEBOMBSQUEAK);
	Mix_FreeChunk(this->fxMOLEBOMBWALKLOOP);
	Mix_FreeChunk(this->fxMORSE);
	Mix_FreeChunk(this->fxNINJAROPEFIRE);
	Mix_FreeChunk(this->fxNINJAROPEIMPACT);
	Mix_FreeChunk(this->fxNUKEFLASH);
	Mix_FreeChunk(this->fxNUKEPART1);
	Mix_FreeChunk(this->fxNUKEPART2);
	Mix_FreeChunk(this->fxOILDRUMIMPACT);
	Mix_FreeChunk(this->fxOLDWOMAN);
	Mix_FreeChunk(this->fxPAUSETICK);
	Mix_FreeChunk(this->fxPETROL);
	Mix_FreeChunk(this->fxPIGEONCOO);
	Mix_FreeChunk(this->fxRICOCHET);
	Mix_FreeChunk(this->fxROCKETPOWERDOWN);
	Mix_FreeChunk(this->fxROCKETPOWERUP);
	Mix_FreeChunk(this->fxROCKETRELEASE);
	Mix_FreeChunk(this->fxSALVATIONARMY);
	Mix_FreeChunk(this->fxSCALESOFJUSTICE);
	Mix_FreeChunk(this->fxSHEEPBAA);
	Mix_FreeChunk(this->fxSHOTGUNFIRE);
	Mix_FreeChunk(this->fxSHOTGUNRELOAD);
	Mix_FreeChunk(this->fxSIZZLE);
	Mix_FreeChunk(this->fxSKUNKGASLOOP);
	Mix_FreeChunk(this->fxSKUNKSQUEAK);
	Mix_FreeChunk(this->fxSKUNKWALKLOOP);
	Mix_FreeChunk(this->fxSNOTPLOP);
	Mix_FreeChunk(this->fxSPLASH);
	Mix_FreeChunk(this->fxSPLISH);
	Mix_FreeChunk(this->fxSTARTROUND);
	Mix_FreeChunk(this->fxSUDDENDEATH);
	Mix_FreeChunk(this->fxSUPERSHEEPRELEASE);
	Mix_FreeChunk(this->fxSUPERSHEEPWHOOSH);
	Mix_FreeChunk(this->fxTEAMBOUNCE);
	Mix_FreeChunk(this->fxTEAMDROP);
	Mix_FreeChunk(this->fxTELEPORT);
	Mix_FreeChunk(this->fxTHROWPOWERDOWN);
	Mix_FreeChunk(this->fxTHROWPOWERUP);
	Mix_FreeChunk(this->fxTHROWRELEASE);
	Mix_FreeChunk(this->fxTIMERTICK);
	Mix_FreeChunk(this->fxTWANG1);
	Mix_FreeChunk(this->fxTWANG2);
	Mix_FreeChunk(this->fxTWANG3);
	Mix_FreeChunk(this->fxTWANG4);
	Mix_FreeChunk(this->fxTWANG5);
	Mix_FreeChunk(this->fxTWANG6);
	Mix_FreeChunk(this->fxUNDERWATERLOOP);
	Mix_FreeChunk(this->fxUNFREEZE);
	Mix_FreeChunk(this->fxUZIFIRE);
	Mix_FreeChunk(this->fxVASESMASH);
	Mix_FreeChunk(this->fxVIKINGAXEIMPACT);
	Mix_FreeChunk(this->fxVIKINGAXERELEASE);
	Mix_FreeChunk(this->fxWALK_COMPRESS);
	Mix_FreeChunk(this->fxWALK_EXPAND);
	Mix_FreeChunk(this->fxWARNINGBEEP);
	Mix_FreeChunk(this->fxWEAPONHOMING);
	Mix_FreeChunk(this->fxWORMBURNED);
	Mix_FreeChunk(this->fxWORMIMPACT);
	Mix_FreeChunk(this->fxWORMLANDING);
	Mix_FreeChunk(this->fxWORMPOP);
	Mix_FreeChunk(this->fxWORMSELECT);
	Mix_FreeChunk(this->fxWORMSPRING);


	Mix_FreeChunk(this->fxAMAZING);
	Mix_FreeChunk(this->fxBORING);
	Mix_FreeChunk(this->fxBRILLIANT);
	Mix_FreeChunk(this->fxBUMMER);
	Mix_FreeChunk(this->fxBUNGEE);
	Mix_FreeChunk(this->fxBYEBYE);
	Mix_FreeChunk(this->fxCOMEONTHEN);
	Mix_FreeChunk(this->fxCOWARD);
	Mix_FreeChunk(this->fxDRAGONPUNCH);
	Mix_FreeChunk(this->fxDROP);
	Mix_FreeChunk(this->fxEXCELLENT);
	Mix_FreeChunk(this->fxFATALITY);
	Mix_FreeChunk(this->fxFIRE);
	Mix_FreeChunk(this->fxFIREBALL);
	Mix_FreeChunk(this->fxFIRSTBLOOD);
	Mix_FreeChunk(this->fxFLAWLESS);
	Mix_FreeChunk(this->fxGOAWAY);
	Mix_FreeChunk(this->fxGRENADE);
	Mix_FreeChunk(this->fxHELLO);
	Mix_FreeChunk(this->fxHURRY);
	Mix_FreeChunk(this->fxILLGETYOU);
	Mix_FreeChunk(this->fxINCOMING);
	Mix_FreeChunk(this->fxJUMP1);
	Mix_FreeChunk(this->fxJUMP2);
	Mix_FreeChunk(this->fxJUSTYOUWAIT);
	Mix_FreeChunk(this->fxKAMIKAZE);
	Mix_FreeChunk(this->fxLAUGH);
	Mix_FreeChunk(this->fxLEAVEMEALONE);
	Mix_FreeChunk(this->fxMISSED);
	Mix_FreeChunk(this->fxNOOO);
	Mix_FreeChunk(this->fxOHDEAR);
	Mix_FreeChunk(this->fxOINUTTER);
	Mix_FreeChunk(this->fxOOFF1);
	Mix_FreeChunk(this->fxOOFF2);
	Mix_FreeChunk(this->fxOOFF3);
	Mix_FreeChunk(this->fxOOPS);
	Mix_FreeChunk(this->fxORDERS);
	Mix_FreeChunk(this->fxOUCH);
	Mix_FreeChunk(this->fxOW1);
	Mix_FreeChunk(this->fxOW2);
	Mix_FreeChunk(this->fxOW3);
	Mix_FreeChunk(this->fxPERFECT);
	Mix_FreeChunk(this->fxREVENGE);
	Mix_FreeChunk(this->fxRUNAWAY);
	Mix_FreeChunk(this->fxSTUPID);
	Mix_FreeChunk(this->fxTAKECOVER);
	Mix_FreeChunk(this->fxTRAITOR);
	Mix_FreeChunk(this->fxUH_OH);
	Mix_FreeChunk(this->fxVICTORY);
	Mix_FreeChunk(this->fxWATCHTHIS);
	Mix_FreeChunk(this->fxWHATTHE);
	Mix_FreeChunk(this->fxWOBBLE);
	Mix_FreeChunk(this->fxYESSIR);
	Mix_FreeChunk(this->fxYOULLREGRETTHAT);



	Mix_Quit();
}

void SoundManager::playFX(FX i){
	
	Mix_Chunk *fx;

	switch(i){
		case eAIRSTRIKE:fx=this->fxAIRSTRIKE;break;
		case eARMAGEDDON:fx=this->fxARMAGEDDON;break;
		case eBANANAIMPACT:fx=this->fxBANANAIMPACT;break;
		case eBASEBALLBATIMPACT:fx=this->fxBASEBALLBATIMPACT;break;
		case eBASEBALLBATJINGLE:fx=this->fxBASEBALLBATJINGLE;break;
		case eBASEBALLBATRELEASE:fx=this->fxBASEBALLBATRELEASE;break;
		case eBLOWTORCH:fx=this->fxBLOWTORCH;break;
		case eCAMERAPAN:fx=this->fxCAMERAPAN;break;
		case eCOLLECT:fx=this->fxCOLLECT;break;
		case eCOMMUNICATOR:fx=this->fxCOMMUNICATOR;break;
		case eCOUGH1:fx=this->fxCOUGH1;break;
		case eCOUGH2:fx=this->fxCOUGH2;break;
		case eCOUGH3:fx=this->fxCOUGH3;break;
		case eCOUGH4:fx=this->fxCOUGH4;break;
		case eCOUGH5:fx=this->fxCOUGH5;break;
		case eCOUGH6:fx=this->fxCOUGH6;break;
		case eCOWMOO:fx=this->fxCOWMOO;break;
		case eCRATEIMPACT:fx=this->fxCRATEIMPACT;break;
		case eCRATEPOP:fx=this->fxCRATEPOP;break;
		case eCROSSIMPACT:fx=this->fxCROSSIMPACT;break;
		case eCROWDPART1:fx=this->fxCROWDPART1;break;
		case eCROWDPART2:fx=this->fxCROWDPART2;break;
		case eCURSORSELECT:fx=this->fxCURSORSELECT;break;
		case eDONORCARDAPPEARS:fx=this->fxDONORCARDAPPEARS;break;
		case eDONORCARDCOLLECT:fx=this->fxDONORCARDCOLLECT;break;
		case eDRAGONBALLIMPACT:fx=this->fxDRAGONBALLIMPACT;break;
		case eDRAGONBALLRELEASE:fx=this->fxDRAGONBALLRELEASE;break;
		case eDRILL:fx=this->fxDRILL;break;
		case eDRILLIMPACT:fx=this->fxDRILLIMPACT;break;
		case eEXPLOSION1:fx=this->fxEXPLOSION1;break;
		case eEXPLOSION2:fx=this->fxEXPLOSION2;break;
		case eEXPLOSION3:fx=this->fxEXPLOSION3;break;
		case eFIREPUNCHIMPACT:fx=this->fxFIREPUNCHIMPACT;break;
		case eFLAMETHROWERATTACK:fx=this->fxFLAMETHROWERATTACK;break;
		case eFLAMETHROWERLOOP:fx=this->fxFLAMETHROWERLOOP;break;
		case eFREEZE:fx=this->fxFREEZE;break;
		case eFRENCHANTHEM:fx=this->fxFRENCHANTHEM;break;
		case eFROZENWORMIMPACT:fx=this->fxFROZENWORMIMPACT;break;
		case eFUSE:fx=this->fxFUSE;break;
		case eGIRDERIMPACT:fx=this->fxGIRDERIMPACT;break;
		case eGRENADEIMPACT:fx=this->fxGRENADEIMPACT;break;
		case eHANDGUNFIRE:fx=this->fxHANDGUNFIRE;break;
		case eHOLYDONKEY:fx=this->fxHOLYDONKEY;break;
		case eHOLYDONKEYIMPACT:fx=this->fxHOLYDONKEYIMPACT;break;
		case eHOLYGRENADE:fx=this->fxHOLYGRENADE;break;
		case eHOLYGRENADEIMPACT:fx=this->fxHOLYGRENADEIMPACT;break;
		case eINDIANANTHEM:fx=this->fxINDIANANTHEM;break;
		case eJETPACKFINISH:fx=this->fxJETPACKFINISH;break;
		case eJETPACKLOOP1:fx=this->fxJETPACKLOOP1;break;
		case eJETPACKLOOP2:fx=this->fxJETPACKLOOP2;break;
		case eJETPACKSTART:fx=this->fxJETPACKSTART;break;
		case eKAMIKAZERELEASE:fx=this->fxKAMIKAZERELEASE;break;
		case eKEYCLICK:fx=this->fxKEYCLICK;break;
		case eKEYERASE:fx=this->fxKEYERASE;break;
		case eLOADINGTICK:fx=this->fxLOADINGTICK;break;
		case eLONGBOWIMPACT:fx=this->fxLONGBOWIMPACT;break;
		case eLONGBOWRELEASE:fx=this->fxLONGBOWRELEASE;break;
		case eMAGICBULLET:fx=this->fxMAGICBULLET;break;
		case eMINEARM:fx=this->fxMINEARM;break;
		case eMINEDUD:fx=this->fxMINEDUD;break;
		case eMINEIMPACT:fx=this->fxMINEIMPACT;break;
		case eMINETICK:fx=this->fxMINETICK;break;
		case eMINIGUNFIRE:fx=this->fxMINIGUNFIRE;break;
		case eMOLEBOMBDIGGINGLOOP:fx=this->fxMOLEBOMBDIGGINGLOOP;break;
		case eMOLEBOMBSQUEAK:fx=this->fxMOLEBOMBSQUEAK;break;
		case eMOLEBOMBWALKLOOP:fx=this->fxMOLEBOMBWALKLOOP;break;
		case eMORSE:fx=this->fxMORSE;break;
		case eNINJAROPEFIRE:fx=this->fxNINJAROPEFIRE;break;
		case eNINJAROPEIMPACT:fx=this->fxNINJAROPEIMPACT;break;
		case eNUKEFLASH:fx=this->fxNUKEFLASH;break;
		case eNUKEPART1:fx=this->fxNUKEPART1;break;
		case eNUKEPART2:fx=this->fxNUKEPART2;break;
		case eOILDRUMIMPACT:fx=this->fxOILDRUMIMPACT;break;
		case eOLDWOMAN:fx=this->fxOLDWOMAN;break;
		case ePAUSETICK:fx=this->fxPAUSETICK;break;
		case ePETROL:fx=this->fxPETROL;break;
		case ePIGEONCOO:fx=this->fxPIGEONCOO;break;
		case eRICOCHET:fx=this->fxRICOCHET;break;
		case eROCKETPOWERDOWN:fx=this->fxROCKETPOWERDOWN;break;
		case eROCKETPOWERUP:fx=this->fxROCKETPOWERUP;break;
		case eROCKETRELEASE:fx=this->fxROCKETRELEASE;break;
		case eSALVATIONARMY:fx=this->fxSALVATIONARMY;break;
		case eSCALESOFJUSTICE:fx=this->fxSCALESOFJUSTICE;break;
		case eSHEEPBAA:fx=this->fxSHEEPBAA;break;
		case eSHOTGUNFIRE:fx=this->fxSHOTGUNFIRE;break;
		case eSHOTGUNRELOAD:fx=this->fxSHOTGUNRELOAD;break;
		case eSIZZLE:fx=this->fxSIZZLE;break;
		case eSKUNKGASLOOP:fx=this->fxSKUNKGASLOOP;break;
		case eSKUNKSQUEAK:fx=this->fxSKUNKSQUEAK;break;
		case eSKUNKWALKLOOP:fx=this->fxSKUNKWALKLOOP;break;
		case eSNOTPLOP:fx=this->fxSNOTPLOP;break;
		case eSPLASH:fx=this->fxSPLASH;break;
		case eSPLISH:fx=this->fxSPLISH;break;
		case eSTARTROUND:fx=this->fxSTARTROUND;break;
		case eSUDDENDEATH:fx=this->fxSUDDENDEATH;break;
		case eSUPERSHEEPRELEASE:fx=this->fxSUPERSHEEPRELEASE;break;
		case eSUPERSHEEPWHOOSH:fx=this->fxSUPERSHEEPWHOOSH;break;
		case eTEAMBOUNCE:fx=this->fxTEAMBOUNCE;break;
		case eTEAMDROP:fx=this->fxTEAMDROP;break;
		case eTELEPORT:fx=this->fxTELEPORT;break;
		case eTHROWPOWERDOWN:fx=this->fxTHROWPOWERDOWN;break;
		case eTHROWPOWERUP:fx=this->fxTHROWPOWERUP;break;
		case eTHROWRELEASE:fx=this->fxTHROWRELEASE;break;
		case eTIMERTICK:fx=this->fxTIMERTICK;break;
		case eTWANG1:fx=this->fxTWANG1;break;
		case eTWANG2:fx=this->fxTWANG2;break;
		case eTWANG3:fx=this->fxTWANG3;break;
		case eTWANG4:fx=this->fxTWANG4;break;
		case eTWANG5:fx=this->fxTWANG5;break;
		case eTWANG6:fx=this->fxTWANG6;break;
		case eUNDERWATERLOOP:fx=this->fxUNDERWATERLOOP;break;
		case eUNFREEZE:fx=this->fxUNFREEZE;break;
		case eUZIFIRE:fx=this->fxUZIFIRE;break;
		case eVASESMASH:fx=this->fxVASESMASH;break;
		case eVIKINGAXEIMPACT:fx=this->fxVIKINGAXEIMPACT;break;
		case eVIKINGAXERELEASE:fx=this->fxVIKINGAXERELEASE;break;
		case eWALK_COMPRESS:fx=this->fxWALK_COMPRESS;break;
		case eWALK_EXPAND:fx=this->fxWALK_EXPAND;break;
		case eWARNINGBEEP:fx=this->fxWARNINGBEEP;break;
		case eWEAPONHOMING:fx=this->fxWEAPONHOMING;break;
		case eWORMBURNED:fx=this->fxWORMBURNED;break;
		case eWORMIMPACT:fx=this->fxWORMIMPACT;break;
		case eWORMLANDING:fx=this->fxWORMLANDING;break;
		case eWORMPOP:fx=this->fxWORMPOP;break;
		case eWORMSELECT:fx=this->fxWORMSELECT;break;
		case eWORMSPRING:fx=this->fxWORMSPRING;break;

		case eAMAZING:fx=this->fxAMAZING;break;
		case eBORING:fx=this->fxBORING;break;
		case eBRILLIANT:fx=this->fxBRILLIANT;break;
		case eBUMMER:fx=this->fxBUMMER;break;
		case eBUNGEE:fx=this->fxBUNGEE;break;
		case eBYEBYE:fx=this->fxBYEBYE;break;
		case eCOMEONTHEN:fx=this->fxCOMEONTHEN;break;
		case eCOWARD:fx=this->fxCOWARD;break;
		case eDRAGONPUNCH:fx=this->fxDRAGONPUNCH;break;
		case eDROP:fx=this->fxDROP;break;
		case eEXCELLENT:fx=this->fxEXCELLENT;break;
		case eFATALITY:fx=this->fxFATALITY;break;
		case eFIRE:fx=this->fxFIRE;break;
		case eFIREBALL:fx=this->fxFIREBALL;break;
		case eFIRSTBLOOD:fx=this->fxFIRSTBLOOD;break;
		case eFLAWLESS:fx=this->fxFLAWLESS;break;
		case eGOAWAY:fx=this->fxGOAWAY;break;
		case eGRENADE:fx=this->fxGRENADE;break;
		case eHELLO:fx=this->fxHELLO;break;
		case eHURRY:fx=this->fxHURRY;break;
		case eILLGETYOU:fx=this->fxILLGETYOU;break;
		case eINCOMING:fx=this->fxINCOMING;break;
		case eJUMP1:fx=this->fxJUMP1;break;
		case eJUMP2:fx=this->fxJUMP2;break;
		case eJUSTYOUWAIT:fx=this->fxJUSTYOUWAIT;break;
		case eKAMIKAZE:fx=this->fxKAMIKAZE;break;
		case eLAUGH:fx=this->fxLAUGH;break;
		case eLEAVEMEALONE:fx=this->fxLEAVEMEALONE;break;
		case eMISSED:fx=this->fxMISSED;break;
		case eNOOO:fx=this->fxNOOO;break;
		case eOHDEAR:fx=this->fxOHDEAR;break;
		case eOINUTTER:fx=this->fxOINUTTER;break;
		case eOOFF1:fx=this->fxOOFF1;break;
		case eOOFF2:fx=this->fxOOFF2;break;
		case eOOFF3:fx=this->fxOOFF3;break;
		case eOOPS:fx=this->fxOOPS;break;
		case eORDERS:fx=this->fxORDERS;break;
		case eOUCH:fx=this->fxOUCH;break;
		case eOW1:fx=this->fxOW1;break;
		case eOW2:fx=this->fxOW2;break;
		case eOW3:fx=this->fxOW3;break;
		case ePERFECT:fx=this->fxPERFECT;break;
		case eREVENGE:fx=this->fxREVENGE;break;
		case eRUNAWAY:fx=this->fxRUNAWAY;break;
		case eSTUPID:fx=this->fxSTUPID;break;
		case eTAKECOVER:fx=this->fxTAKECOVER;break;
		case eTRAITOR:fx=this->fxTRAITOR;break;
		case eUH_OH:fx=this->fxUH_OH;break;
		case eVICTORY:fx=this->fxVICTORY;break;
		case eWATCHTHIS:fx=this->fxWATCHTHIS;break;
		case eWHATTHE:fx=this->fxWHATTHE;break;
		case eWOBBLE:fx=this->fxWOBBLE;break;
		case eYESSIR:fx=this->fxYESSIR;break;
		case eYOULLREGRETTHAT:fx=this->fxYOULLREGRETTHAT;break;

	}
	Mix_PlayChannel(-1,fx,0);

}


void SoundManager::pAIRSTRIKE(){this->playFX(eAIRSTRIKE);}
void SoundManager::pARMAGEDDON(){this->playFX(eARMAGEDDON);}
void SoundManager::pBANANAIMPACT(){this->playFX(eBANANAIMPACT);}
void SoundManager::pBASEBALLBATIMPACT(){this->playFX(eBASEBALLBATIMPACT);}
void SoundManager::pBASEBALLBATJINGLE(){this->playFX(eBASEBALLBATJINGLE);}
void SoundManager::pBASEBALLBATRELEASE(){this->playFX(eBASEBALLBATRELEASE);}
void SoundManager::pBLOWTORCH(){this->playFX(eBLOWTORCH);}
void SoundManager::pCAMERAPAN(){this->playFX(eCAMERAPAN);}
void SoundManager::pCOLLECT(){this->playFX(eCOLLECT);}
void SoundManager::pCOMMUNICATOR(){this->playFX(eCOMMUNICATOR);}
void SoundManager::pCOUGH1(){this->playFX(eCOUGH1);}
void SoundManager::pCOUGH2(){this->playFX(eCOUGH2);}
void SoundManager::pCOUGH3(){this->playFX(eCOUGH3);}
void SoundManager::pCOUGH4(){this->playFX(eCOUGH4);}
void SoundManager::pCOUGH5(){this->playFX(eCOUGH5);}
void SoundManager::pCOUGH6(){this->playFX(eCOUGH6);}
void SoundManager::pCOWMOO(){this->playFX(eCOWMOO);}
void SoundManager::pCRATEIMPACT(){this->playFX(eCRATEIMPACT);}
void SoundManager::pCRATEPOP(){this->playFX(eCRATEPOP);}
void SoundManager::pCROSSIMPACT(){this->playFX(eCROSSIMPACT);}
void SoundManager::pCROWDPART1(){this->playFX(eCROWDPART1);}
void SoundManager::pCROWDPART2(){this->playFX(eCROWDPART2);}
void SoundManager::pCURSORSELECT(){this->playFX(eCURSORSELECT);}
void SoundManager::pDONORCARDAPPEARS(){this->playFX(eDONORCARDAPPEARS);}
void SoundManager::pDONORCARDCOLLECT(){this->playFX(eDONORCARDCOLLECT);}
void SoundManager::pDRAGONBALLIMPACT(){this->playFX(eDRAGONBALLIMPACT);}
void SoundManager::pDRAGONBALLRELEASE(){this->playFX(eDRAGONBALLRELEASE);}
void SoundManager::pDRILL(){this->playFX(eDRILL);}
void SoundManager::pDRILLIMPACT(){this->playFX(eDRILLIMPACT);}
void SoundManager::pEXPLOSION1(){this->playFX(eEXPLOSION1);}
void SoundManager::pEXPLOSION2(){this->playFX(eEXPLOSION2);}
void SoundManager::pEXPLOSION3(){this->playFX(eEXPLOSION3);}
void SoundManager::pFIREPUNCHIMPACT(){this->playFX(eFIREPUNCHIMPACT);}
void SoundManager::pFLAMETHROWERATTACK(){this->playFX(eFLAMETHROWERATTACK);}
void SoundManager::pFLAMETHROWERLOOP(){this->playFX(eFLAMETHROWERLOOP);}
void SoundManager::pFREEZE(){this->playFX(eFREEZE);}
void SoundManager::pFRENCHANTHEM(){this->playFX(eFRENCHANTHEM);}
void SoundManager::pFROZENWORMIMPACT(){this->playFX(eFROZENWORMIMPACT);}
void SoundManager::pFUSE(){this->playFX(eFUSE);}
void SoundManager::pGIRDERIMPACT(){this->playFX(eGIRDERIMPACT);}
void SoundManager::pGRENADEIMPACT(){this->playFX(eGRENADEIMPACT);}
void SoundManager::pHANDGUNFIRE(){this->playFX(eHANDGUNFIRE);}
void SoundManager::pHOLYDONKEY(){this->playFX(eHOLYDONKEY);}
void SoundManager::pHOLYDONKEYIMPACT(){this->playFX(eHOLYDONKEYIMPACT);}
void SoundManager::pHOLYGRENADE(){this->playFX(eHOLYGRENADE);}
void SoundManager::pHOLYGRENADEIMPACT(){this->playFX(eHOLYGRENADEIMPACT);}
void SoundManager::pINDIANANTHEM(){this->playFX(eINDIANANTHEM);}
void SoundManager::pJETPACKFINISH(){this->playFX(eJETPACKFINISH);}
void SoundManager::pJETPACKLOOP1(){this->playFX(eJETPACKLOOP1);}
void SoundManager::pJETPACKLOOP2(){this->playFX(eJETPACKLOOP2);}
void SoundManager::pJETPACKSTART(){this->playFX(eJETPACKSTART);}
void SoundManager::pKAMIKAZERELEASE(){this->playFX(eKAMIKAZERELEASE);}
void SoundManager::pKEYCLICK(){this->playFX(eKEYCLICK);}
void SoundManager::pKEYERASE(){this->playFX(eKEYERASE);}
void SoundManager::pLOADINGTICK(){this->playFX(eLOADINGTICK);}
void SoundManager::pLONGBOWIMPACT(){this->playFX(eLONGBOWIMPACT);}
void SoundManager::pLONGBOWRELEASE(){this->playFX(eLONGBOWRELEASE);}
void SoundManager::pMAGICBULLET(){this->playFX(eMAGICBULLET);}
void SoundManager::pMINEARM(){this->playFX(eMINEARM);}
void SoundManager::pMINEDUD(){this->playFX(eMINEDUD);}
void SoundManager::pMINEIMPACT(){this->playFX(eMINEIMPACT);}
void SoundManager::pMINETICK(){this->playFX(eMINETICK);}
void SoundManager::pMINIGUNFIRE(){this->playFX(eMINIGUNFIRE);}
void SoundManager::pMOLEBOMBDIGGINGLOOP(){this->playFX(eMOLEBOMBDIGGINGLOOP);}
void SoundManager::pMOLEBOMBSQUEAK(){this->playFX(eMOLEBOMBSQUEAK);}
void SoundManager::pMOLEBOMBWALKLOOP(){this->playFX(eMOLEBOMBWALKLOOP);}
void SoundManager::pMORSE(){this->playFX(eMORSE);}
void SoundManager::pNINJAROPEFIRE(){this->playFX(eNINJAROPEFIRE);}
void SoundManager::pNINJAROPEIMPACT(){this->playFX(eNINJAROPEIMPACT);}
void SoundManager::pNUKEFLASH(){this->playFX(eNUKEFLASH);}
void SoundManager::pNUKEPART1(){this->playFX(eNUKEPART1);}
void SoundManager::pNUKEPART2(){this->playFX(eNUKEPART2);}
void SoundManager::pOILDRUMIMPACT(){this->playFX(eOILDRUMIMPACT);}
void SoundManager::pOLDWOMAN(){this->playFX(eOLDWOMAN);}
void SoundManager::pPAUSETICK(){this->playFX(ePAUSETICK);}
void SoundManager::pPETROL(){this->playFX(ePETROL);}
void SoundManager::pPIGEONCOO(){this->playFX(ePIGEONCOO);}
void SoundManager::pRICOCHET(){this->playFX(eRICOCHET);}
void SoundManager::pROCKETPOWERDOWN(){this->playFX(eROCKETPOWERDOWN);}
void SoundManager::pROCKETPOWERUP(){this->playFX(eROCKETPOWERUP);}
void SoundManager::pROCKETRELEASE(){this->playFX(eROCKETRELEASE);}
void SoundManager::pSALVATIONARMY(){this->playFX(eSALVATIONARMY);}
void SoundManager::pSCALESOFJUSTICE(){this->playFX(eSCALESOFJUSTICE);}
void SoundManager::pSHEEPBAA(){this->playFX(eSHEEPBAA);}
void SoundManager::pSHOTGUNFIRE(){this->playFX(eSHOTGUNFIRE);}
void SoundManager::pSHOTGUNRELOAD(){this->playFX(eSHOTGUNRELOAD);}
void SoundManager::pSIZZLE(){this->playFX(eSIZZLE);}
void SoundManager::pSKUNKGASLOOP(){this->playFX(eSKUNKGASLOOP);}
void SoundManager::pSKUNKSQUEAK(){this->playFX(eSKUNKSQUEAK);}
void SoundManager::pSKUNKWALKLOOP(){this->playFX(eSKUNKWALKLOOP);}
void SoundManager::pSNOTPLOP(){this->playFX(eSNOTPLOP);}
void SoundManager::pSPLASH(){this->playFX(eSPLASH);}
void SoundManager::pSPLISH(){this->playFX(eSPLISH);}
void SoundManager::pSTARTROUND(){this->playFX(eSTARTROUND);}
void SoundManager::pSUDDENDEATH(){this->playFX(eSUDDENDEATH);}
void SoundManager::pSUPERSHEEPRELEASE(){this->playFX(eSUPERSHEEPRELEASE);}
void SoundManager::pSUPERSHEEPWHOOSH(){this->playFX(eSUPERSHEEPWHOOSH);}
void SoundManager::pTEAMBOUNCE(){this->playFX(eTEAMBOUNCE);}
void SoundManager::pTEAMDROP(){this->playFX(eTEAMDROP);}
void SoundManager::pTELEPORT(){this->playFX(eTELEPORT);}
void SoundManager::pTHROWPOWERDOWN(){this->playFX(eTHROWPOWERDOWN);}
void SoundManager::pTHROWPOWERUP(){this->playFX(eTHROWPOWERUP);}
void SoundManager::pTHROWRELEASE(){this->playFX(eTHROWRELEASE);}
void SoundManager::pTIMERTICK(){this->playFX(eTIMERTICK);}
void SoundManager::pTWANG1(){this->playFX(eTWANG1);}
void SoundManager::pTWANG2(){this->playFX(eTWANG2);}
void SoundManager::pTWANG3(){this->playFX(eTWANG3);}
void SoundManager::pTWANG4(){this->playFX(eTWANG4);}
void SoundManager::pTWANG5(){this->playFX(eTWANG5);}
void SoundManager::pTWANG6(){this->playFX(eTWANG6);}
void SoundManager::pUNDERWATERLOOP(){this->playFX(eUNDERWATERLOOP);}
void SoundManager::pUNFREEZE(){this->playFX(eUNFREEZE);}
void SoundManager::pUZIFIRE(){this->playFX(eUZIFIRE);}
void SoundManager::pVASESMASH(){this->playFX(eVASESMASH);}
void SoundManager::pVIKINGAXEIMPACT(){this->playFX(eVIKINGAXEIMPACT);}
void SoundManager::pVIKINGAXERELEASE(){this->playFX(eVIKINGAXERELEASE);}
void SoundManager::pWALK_COMPRESS(){this->playFX(eWALK_COMPRESS);}
void SoundManager::pWALK_EXPAND(){this->playFX(eWALK_EXPAND);}
void SoundManager::pWARNINGBEEP(){this->playFX(eWARNINGBEEP);}
void SoundManager::pWEAPONHOMING(){this->playFX(eWEAPONHOMING);}
void SoundManager::pWORMBURNED(){this->playFX(eWORMBURNED);}
void SoundManager::pWORMIMPACT(){this->playFX(eWORMIMPACT);}
void SoundManager::pWORMLANDING(){this->playFX(eWORMLANDING);}
void SoundManager::pWORMPOP(){this->playFX(eWORMPOP);}
void SoundManager::pWORMSELECT(){this->playFX(eWORMSELECT);}
void SoundManager::pWORMSPRING(){this->playFX(eWORMSPRING);}

void SoundManager::pAMAZING(){this->playFX(eAMAZING);}
void SoundManager::pBORING(){this->playFX(eBORING);}
void SoundManager::pBRILLIANT(){this->playFX(eBRILLIANT);}
void SoundManager::pBUMMER(){this->playFX(eBUMMER);}
void SoundManager::pBUNGEE(){this->playFX(eBUNGEE);}
void SoundManager::pBYEBYE(){this->playFX(eBYEBYE);}
void SoundManager::pCOMEONTHEN(){this->playFX(eCOMEONTHEN);}
void SoundManager::pCOWARD(){this->playFX(eCOWARD);}
void SoundManager::pDRAGONPUNCH(){this->playFX(eDRAGONPUNCH);}
void SoundManager::pDROP(){this->playFX(eDROP);}
void SoundManager::pEXCELLENT(){this->playFX(eEXCELLENT);}
void SoundManager::pFATALITY(){this->playFX(eFATALITY);}
void SoundManager::pFIRE(){this->playFX(eFIRE);}
void SoundManager::pFIREBALL(){this->playFX(eFIREBALL);}
void SoundManager::pFIRSTBLOOD(){this->playFX(eFIRSTBLOOD);}
void SoundManager::pFLAWLESS(){this->playFX(eFLAWLESS);}
void SoundManager::pGOAWAY(){this->playFX(eGOAWAY);}
void SoundManager::pGRENADE(){this->playFX(eGRENADE);}
void SoundManager::pHELLO(){this->playFX(eHELLO);}
void SoundManager::pHURRY(){this->playFX(eHURRY);}
void SoundManager::pILLGETYOU(){this->playFX(eILLGETYOU);}
void SoundManager::pINCOMING(){this->playFX(eINCOMING);}
void SoundManager::pJUMP1(){this->playFX(eJUMP1);}
void SoundManager::pJUMP2(){this->playFX(eJUMP2);}
void SoundManager::pJUSTYOUWAIT(){this->playFX(eJUSTYOUWAIT);}
void SoundManager::pKAMIKAZE(){this->playFX(eKAMIKAZE);}
void SoundManager::pLAUGH(){this->playFX(eLAUGH);}
void SoundManager::pLEAVEMEALONE(){this->playFX(eLEAVEMEALONE);}
void SoundManager::pMISSED(){this->playFX(eMISSED);}
void SoundManager::pNOOO(){this->playFX(eNOOO);}
void SoundManager::pOHDEAR(){this->playFX(eOHDEAR);}
void SoundManager::pOINUTTER(){this->playFX(eOINUTTER);}
void SoundManager::pOOFF1(){this->playFX(eOOFF1);}
void SoundManager::pOOFF2(){this->playFX(eOOFF2);}
void SoundManager::pOOFF3(){this->playFX(eOOFF3);}
void SoundManager::pOOPS(){this->playFX(eOOPS);}
void SoundManager::pORDERS(){this->playFX(eORDERS);}
void SoundManager::pOUCH(){this->playFX(eOUCH);}
void SoundManager::pOW1(){this->playFX(eOW1);}
void SoundManager::pOW2(){this->playFX(eOW2);}
void SoundManager::pOW3(){this->playFX(eOW3);}
void SoundManager::pPERFECT(){this->playFX(ePERFECT);}
void SoundManager::pREVENGE(){this->playFX(eREVENGE);}
void SoundManager::pRUNAWAY(){this->playFX(eRUNAWAY);}
void SoundManager::pSTUPID(){this->playFX(eSTUPID);}
void SoundManager::pTAKECOVER(){this->playFX(eTAKECOVER);}
void SoundManager::pTRAITOR(){this->playFX(eTRAITOR);}
void SoundManager::pUH_OH(){this->playFX(eUH_OH);}
void SoundManager::pVICTORY(){this->playFX(eVICTORY);}
void SoundManager::pWATCHTHIS(){this->playFX(eWATCHTHIS);}
void SoundManager::pWHATTHE(){this->playFX(eWHATTHE);}
void SoundManager::pWOBBLE(){this->playFX(eWOBBLE);}
void SoundManager::pYESSIR(){this->playFX(eYESSIR);}
void SoundManager::pYOULLREGRETTHAT(){this->playFX(eYOULLREGRETTHAT);}
