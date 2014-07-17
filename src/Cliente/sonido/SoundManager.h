#ifndef __SOUND_MANAGER__
#define __SOUND_MANAGER__
#include <SDL_mixer.h>
#include "../../utils/Constantes/Constantes.h"
#include <map>
#include <SDL.h>
#include "../../utils/Log.h"

enum FX {	eAIRSTRIKE,
			eARMAGEDDON,
			eBANANAIMPACT,
			eBASEBALLBATIMPACT,
			eBASEBALLBATJINGLE,
			eBASEBALLBATRELEASE,
			eBLOWTORCH,
			eCAMERAPAN,
			eCOLLECT,
			eCOMMUNICATOR,
			eCOUGH1,
			eCOUGH2,
			eCOUGH3,
			eCOUGH4,
			eCOUGH5,
			eCOUGH6,
			eCOWMOO,
			eCRATEIMPACT,
			eCRATEPOP,
			eCROSSIMPACT,
			eCROWDPART1,
			eCROWDPART2,
			eCURSORSELECT,
			eDONORCARDAPPEARS,
			eDONORCARDCOLLECT,
			eDRAGONBALLIMPACT,
			eDRAGONBALLRELEASE,
			eDRILL,
			eDRILLIMPACT,
			eEXPLOSION1,
			eEXPLOSION2,
			eEXPLOSION3,
			eFIREPUNCHIMPACT,
			eFLAMETHROWERATTACK,
			eFLAMETHROWERLOOP,
			eFREEZE,
			eFRENCHANTHEM,
			eFROZENWORMIMPACT,
			eFUSE,
			eGIRDERIMPACT,
			eGRENADEIMPACT,
			eHANDGUNFIRE,
			eHOLYDONKEY,
			eHOLYDONKEYIMPACT,
			eHOLYGRENADE,
			eHOLYGRENADEIMPACT,
			eINDIANANTHEM,
			eJETPACKFINISH,
			eJETPACKLOOP1,
			eJETPACKLOOP2,
			eJETPACKSTART,
			eKAMIKAZERELEASE,
			eKEYCLICK,
			eKEYERASE,
			eLOADINGTICK,
			eLONGBOWIMPACT,
			eLONGBOWRELEASE,
			eMAGICBULLET,
			eMINEARM,
			eMINEDUD,
			eMINEIMPACT,
			eMINETICK,
			eMINIGUNFIRE,
			eMOLEBOMBDIGGINGLOOP,
			eMOLEBOMBSQUEAK,
			eMOLEBOMBWALKLOOP,
			eMORSE,
			eNINJAROPEFIRE,
			eNINJAROPEIMPACT,
			eNUKEFLASH,
			eNUKEPART1,
			eNUKEPART2,
			eOILDRUMIMPACT,
			eOLDWOMAN,
			ePAUSETICK,
			ePETROL,
			ePIGEONCOO,
			eRICOCHET,
			eROCKETPOWERDOWN,
			eROCKETPOWERUP,
			eROCKETRELEASE,
			eSALVATIONARMY,
			eSCALESOFJUSTICE,
			eSHEEPBAA,
			eSHOTGUNFIRE,
			eSHOTGUNRELOAD,
			eSIZZLE,
			eSKUNKGASLOOP,
			eSKUNKSQUEAK,
			eSKUNKWALKLOOP,
			eSNOTPLOP,
			eSPLASH,
			eSPLISH,
			eSTARTROUND,
			eSUDDENDEATH,
			eSUPERSHEEPRELEASE,
			eSUPERSHEEPWHOOSH,
			eTEAMBOUNCE,
			eTEAMDROP,
			eTELEPORT,
			eTHROWPOWERDOWN,
			eTHROWPOWERUP,
			eTHROWRELEASE,
			eTIMERTICK,
			eTWANG1,
			eTWANG2,
			eTWANG3,
			eTWANG4,
			eTWANG5,
			eTWANG6,
			eUNDERWATERLOOP,
			eUNFREEZE,
			eUZIFIRE,
			eVASESMASH,
			eVIKINGAXEIMPACT,
			eVIKINGAXERELEASE,
			eWALK_COMPRESS,
			eWALK_EXPAND,
			eWARNINGBEEP,
			eWEAPONHOMING,
			eWORMBURNED,
			eWORMIMPACT,
			eWORMLANDING,
			eWORMPOP,
			eWORMSELECT,
			eWORMSPRING,

			eAMAZING,
			eBORING,
			eBRILLIANT,
			eBUMMER,
			eBUNGEE,
			eBYEBYE,
			eCOMEONTHEN,
			eCOWARD,
			eDRAGONPUNCH,
			eDROP,
			eEXCELLENT,
			eFATALITY,
			eFIRE,
			eFIREBALL,
			eFIRSTBLOOD,
			eFLAWLESS,
			eGOAWAY,
			eGRENADE,
			eHELLO,
			eHURRY,
			eILLGETYOU,
			eINCOMING,
			eJUMP1,
			eJUMP2,
			eJUSTYOUWAIT,
			eKAMIKAZE,
			eLAUGH,
			eLEAVEMEALONE,
			eMISSED,
			eNOOO,
			eOHDEAR,
			eOINUTTER,
			eOOFF1,
			eOOFF2,
			eOOFF3,
			eOOPS,
			eORDERS,
			eOUCH,
			eOW1,
			eOW2,
			eOW3,
			ePERFECT,
			eREVENGE,
			eRUNAWAY,
			eSTUPID,
			eTAKECOVER,
			eTRAITOR,
			eUH_OH,
			eVICTORY,
			eWATCHTHIS,
			eWHATTHE,
			eWOBBLE,
			eYESSIR,
			eYOULLREGRETTHAT,


         };

class SoundManager
{
private:
	Mix_Chunk* fxAIRSTRIKE;
	Mix_Chunk* fxARMAGEDDON;
	Mix_Chunk* fxBANANAIMPACT;
	Mix_Chunk* fxBASEBALLBATIMPACT;
	Mix_Chunk* fxBASEBALLBATJINGLE;
	Mix_Chunk* fxBASEBALLBATRELEASE;
	Mix_Chunk* fxBLOWTORCH;
	Mix_Chunk* fxCAMERAPAN;
	Mix_Chunk* fxCOLLECT;
	Mix_Chunk* fxCOMMUNICATOR;
	Mix_Chunk* fxCOUGH1;
	Mix_Chunk* fxCOUGH2;
	Mix_Chunk* fxCOUGH3;
	Mix_Chunk* fxCOUGH4;
	Mix_Chunk* fxCOUGH5;
	Mix_Chunk* fxCOUGH6;
	Mix_Chunk* fxCOWMOO;
	Mix_Chunk* fxCRATEIMPACT;
	Mix_Chunk* fxCRATEPOP;
	Mix_Chunk* fxCROSSIMPACT;
	Mix_Chunk* fxCROWDPART1;
	Mix_Chunk* fxCROWDPART2;
	Mix_Chunk* fxCURSORSELECT;
	Mix_Chunk* fxDONORCARDAPPEARS;
	Mix_Chunk* fxDONORCARDCOLLECT;
	Mix_Chunk* fxDRAGONBALLIMPACT;
	Mix_Chunk* fxDRAGONBALLRELEASE;
	Mix_Chunk* fxDRILL;
	Mix_Chunk* fxDRILLIMPACT;
	Mix_Chunk* fxEXPLOSION1;
	Mix_Chunk* fxEXPLOSION2;
	Mix_Chunk* fxEXPLOSION3;
	Mix_Chunk* fxFIREPUNCHIMPACT;
	Mix_Chunk* fxFLAMETHROWERATTACK;
	Mix_Chunk* fxFLAMETHROWERLOOP;
	Mix_Chunk* fxFREEZE;
	Mix_Chunk* fxFRENCHANTHEM;
	Mix_Chunk* fxFROZENWORMIMPACT;
	Mix_Chunk* fxFUSE;
	Mix_Chunk* fxGIRDERIMPACT;
	Mix_Chunk* fxGRENADEIMPACT;
	Mix_Chunk* fxHANDGUNFIRE;
	Mix_Chunk* fxHOLYDONKEY;
	Mix_Chunk* fxHOLYDONKEYIMPACT;
	Mix_Chunk* fxHOLYGRENADE;
	Mix_Chunk* fxHOLYGRENADEIMPACT;
	Mix_Chunk* fxINDIANANTHEM;
	Mix_Chunk* fxJETPACKFINISH;
	Mix_Chunk* fxJETPACKLOOP1;
	Mix_Chunk* fxJETPACKLOOP2;
	Mix_Chunk* fxJETPACKSTART;
	Mix_Chunk* fxKAMIKAZERELEASE;
	Mix_Chunk* fxKEYCLICK;
	Mix_Chunk* fxKEYERASE;
	Mix_Chunk* fxLOADINGTICK;
	Mix_Chunk* fxLONGBOWIMPACT;
	Mix_Chunk* fxLONGBOWRELEASE;
	Mix_Chunk* fxMAGICBULLET;
	Mix_Chunk* fxMINEARM;
	Mix_Chunk* fxMINEDUD;
	Mix_Chunk* fxMINEIMPACT;
	Mix_Chunk* fxMINETICK;
	Mix_Chunk* fxMINIGUNFIRE;
	Mix_Chunk* fxMOLEBOMBDIGGINGLOOP;
	Mix_Chunk* fxMOLEBOMBSQUEAK;
	Mix_Chunk* fxMOLEBOMBWALKLOOP;
	Mix_Chunk* fxMORSE;
	Mix_Chunk* fxNINJAROPEFIRE;
	Mix_Chunk* fxNINJAROPEIMPACT;
	Mix_Chunk* fxNUKEFLASH;
	Mix_Chunk* fxNUKEPART1;
	Mix_Chunk* fxNUKEPART2;
	Mix_Chunk* fxOILDRUMIMPACT;
	Mix_Chunk* fxOLDWOMAN;
	Mix_Chunk* fxPAUSETICK;
	Mix_Chunk* fxPETROL;
	Mix_Chunk* fxPIGEONCOO;
	Mix_Chunk* fxRICOCHET;
	Mix_Chunk* fxROCKETPOWERDOWN;
	Mix_Chunk* fxROCKETPOWERUP;
	Mix_Chunk* fxROCKETRELEASE;
	Mix_Chunk* fxSALVATIONARMY;
	Mix_Chunk* fxSCALESOFJUSTICE;
	Mix_Chunk* fxSHEEPBAA;
	Mix_Chunk* fxSHOTGUNFIRE;
	Mix_Chunk* fxSHOTGUNRELOAD;
	Mix_Chunk* fxSIZZLE;
	Mix_Chunk* fxSKUNKGASLOOP;
	Mix_Chunk* fxSKUNKSQUEAK;
	Mix_Chunk* fxSKUNKWALKLOOP;
	Mix_Chunk* fxSNOTPLOP;
	Mix_Chunk* fxSPLASH;
	Mix_Chunk* fxSPLISH;
	Mix_Chunk* fxSTARTROUND;
	Mix_Chunk* fxSUDDENDEATH;
	Mix_Chunk* fxSUPERSHEEPRELEASE;
	Mix_Chunk* fxSUPERSHEEPWHOOSH;
	Mix_Chunk* fxTEAMBOUNCE;
	Mix_Chunk* fxTEAMDROP;
	Mix_Chunk* fxTELEPORT;
	Mix_Chunk* fxTHROWPOWERDOWN;
	Mix_Chunk* fxTHROWPOWERUP;
	Mix_Chunk* fxTHROWRELEASE;
	Mix_Chunk* fxTIMERTICK;
	Mix_Chunk* fxTWANG1;
	Mix_Chunk* fxTWANG2;
	Mix_Chunk* fxTWANG3;
	Mix_Chunk* fxTWANG4;
	Mix_Chunk* fxTWANG5;
	Mix_Chunk* fxTWANG6;
	Mix_Chunk* fxUNDERWATERLOOP;
	Mix_Chunk* fxUNFREEZE;
	Mix_Chunk* fxUZIFIRE;
	Mix_Chunk* fxVASESMASH;
	Mix_Chunk* fxVIKINGAXEIMPACT;
	Mix_Chunk* fxVIKINGAXERELEASE;
	Mix_Chunk* fxWALK_COMPRESS;
	Mix_Chunk* fxWALK_EXPAND;
	Mix_Chunk* fxWARNINGBEEP;
	Mix_Chunk* fxWEAPONHOMING;
	Mix_Chunk* fxWORMBURNED;
	Mix_Chunk* fxWORMIMPACT;
	Mix_Chunk* fxWORMLANDING;
	Mix_Chunk* fxWORMPOP;
	Mix_Chunk* fxWORMSELECT;
	Mix_Chunk* fxWORMSPRING;

	Mix_Chunk* fxAMAZING;
	Mix_Chunk* fxBORING;
	Mix_Chunk* fxBRILLIANT;
	Mix_Chunk* fxBUMMER;
	Mix_Chunk* fxBUNGEE;
	Mix_Chunk* fxBYEBYE;
	Mix_Chunk* fxCOMEONTHEN;
	Mix_Chunk* fxCOWARD;
	Mix_Chunk* fxDRAGONPUNCH;
	Mix_Chunk* fxDROP;
	Mix_Chunk* fxEXCELLENT;
	Mix_Chunk* fxFATALITY;
	Mix_Chunk* fxFIRE;
	Mix_Chunk* fxFIREBALL;
	Mix_Chunk* fxFIRSTBLOOD;
	Mix_Chunk* fxFLAWLESS;
	Mix_Chunk* fxGOAWAY;
	Mix_Chunk* fxGRENADE;
	Mix_Chunk* fxHELLO;
	Mix_Chunk* fxHURRY;
	Mix_Chunk* fxILLGETYOU;
	Mix_Chunk* fxINCOMING;
	Mix_Chunk* fxJUMP1;
	Mix_Chunk* fxJUMP2;
	Mix_Chunk* fxJUSTYOUWAIT;
	Mix_Chunk* fxKAMIKAZE;
	Mix_Chunk* fxLAUGH;
	Mix_Chunk* fxLEAVEMEALONE;
	Mix_Chunk* fxMISSED;
	Mix_Chunk* fxNOOO;
	Mix_Chunk* fxOHDEAR;
	Mix_Chunk* fxOINUTTER;
	Mix_Chunk* fxOOFF1;
	Mix_Chunk* fxOOFF2;
	Mix_Chunk* fxOOFF3;
	Mix_Chunk* fxOOPS;
	Mix_Chunk* fxORDERS;
	Mix_Chunk* fxOUCH;
	Mix_Chunk* fxOW1;
	Mix_Chunk* fxOW2;
	Mix_Chunk* fxOW3;
	Mix_Chunk* fxPERFECT;
	Mix_Chunk* fxREVENGE;
	Mix_Chunk* fxRUNAWAY;
	Mix_Chunk* fxSTUPID;
	Mix_Chunk* fxTAKECOVER;
	Mix_Chunk* fxTRAITOR;
	Mix_Chunk* fxUH_OH;
	Mix_Chunk* fxVICTORY;
	Mix_Chunk* fxWATCHTHIS;
	Mix_Chunk* fxWHATTHE;
	Mix_Chunk* fxWOBBLE;
	Mix_Chunk* fxYESSIR;
	Mix_Chunk* fxYOULLREGRETTHAT;

	Mix_Music* music;

	void playFX(FX);

public:

	static SoundManager & Instance(){
			static SoundManager theSoundManager;
			return theSoundManager;
	}

	void init();

	

	void close();

	/*musica de fondo*/
	void playMusic();

	/*FX*/
	void pAIRSTRIKE();
	void pARMAGEDDON();
	void pBANANAIMPACT();
	void pBASEBALLBATIMPACT();
	void pBASEBALLBATJINGLE();
	void pBASEBALLBATRELEASE();
	void pBLOWTORCH();
	void pCAMERAPAN();
	void pCOLLECT();
	void pCOMMUNICATOR();
	void pCOUGH1();
	void pCOUGH2();
	void pCOUGH3();
	void pCOUGH4();
	void pCOUGH5();
	void pCOUGH6();
	void pCOWMOO();
	void pCRATEIMPACT();
	void pCRATEPOP();
	void pCROSSIMPACT();
	void pCROWDPART1();
	void pCROWDPART2();
	void pCURSORSELECT();
	void pDONORCARDAPPEARS();
	void pDONORCARDCOLLECT();
	void pDRAGONBALLIMPACT();
	void pDRAGONBALLRELEASE();
	void pDRILL();
	void pDRILLIMPACT();
	void pEXPLOSION1();
	void pEXPLOSION2();
	void pEXPLOSION3();
	void pFIREPUNCHIMPACT();
	void pFLAMETHROWERATTACK();
	void pFLAMETHROWERLOOP();
	void pFREEZE();
	void pFRENCHANTHEM();
	void pFROZENWORMIMPACT();
	void pFUSE();
	void pGIRDERIMPACT();
	void pGRENADEIMPACT();
	void pHANDGUNFIRE();
	void pHOLYDONKEY();
	void pHOLYDONKEYIMPACT();
	void pHOLYGRENADE();
	void pHOLYGRENADEIMPACT();
	void pINDIANANTHEM();
	void pJETPACKFINISH();
	void pJETPACKLOOP1();
	void pJETPACKLOOP2();
	void pJETPACKSTART();
	void pKAMIKAZERELEASE();
	void pKEYCLICK();
	void pKEYERASE();
	void pLOADINGTICK();
	void pLONGBOWIMPACT();
	void pLONGBOWRELEASE();
	void pMAGICBULLET();
	void pMINEARM();
	void pMINEDUD();
	void pMINEIMPACT();
	void pMINETICK();
	void pMINIGUNFIRE();
	void pMOLEBOMBDIGGINGLOOP();
	void pMOLEBOMBSQUEAK();
	void pMOLEBOMBWALKLOOP();
	void pMORSE();
	void pNINJAROPEFIRE();
	void pNINJAROPEIMPACT();
	void pNUKEFLASH();
	void pNUKEPART1();
	void pNUKEPART2();
	void pOILDRUMIMPACT();
	void pOLDWOMAN();
	void pPAUSETICK();
	void pPETROL();
	void pPIGEONCOO();
	void pRICOCHET();
	void pROCKETPOWERDOWN();
	void pROCKETPOWERUP();
	void pROCKETRELEASE();
	void pSALVATIONARMY();
	void pSCALESOFJUSTICE();
	void pSHEEPBAA();
	void pSHOTGUNFIRE();
	void pSHOTGUNRELOAD();
	void pSIZZLE();
	void pSKUNKGASLOOP();
	void pSKUNKSQUEAK();
	void pSKUNKWALKLOOP();
	void pSNOTPLOP();
	void pSPLASH();
	void pSPLISH();
	void pSTARTROUND();
	void pSUDDENDEATH();
	void pSUPERSHEEPRELEASE();
	void pSUPERSHEEPWHOOSH();
	void pTEAMBOUNCE();
	void pTEAMDROP();
	void pTELEPORT();
	void pTHROWPOWERDOWN();
	void pTHROWPOWERUP();
	void pTHROWRELEASE();
	void pTIMERTICK();
	void pTWANG1();
	void pTWANG2();
	void pTWANG3();
	void pTWANG4();
	void pTWANG5();
	void pTWANG6();
	void pUNDERWATERLOOP();
	void pUNFREEZE();
	void pUZIFIRE();
	void pVASESMASH();
	void pVIKINGAXEIMPACT();
	void pVIKINGAXERELEASE();
	void pWALK_COMPRESS();
	void pWALK_EXPAND();
	void pWARNINGBEEP();
	void pWEAPONHOMING();
	void pWORMBURNED();
	void pWORMIMPACT();
	void pWORMLANDING();
	void pWORMPOP();
	void pWORMSELECT();
	void pWORMSPRING();


	void pAMAZING();
	void pBORING();
	void pBRILLIANT();
	void pBUMMER();
	void pBUNGEE();
	void pBYEBYE();
	void pCOMEONTHEN();
	void pCOWARD();
	void pDRAGONPUNCH();
	void pDROP();
	void pEXCELLENT();
	void pFATALITY();
	void pFIRE();
	void pFIREBALL();
	void pFIRSTBLOOD();
	void pFLAWLESS();
	void pGOAWAY();
	void pGRENADE();
	void pHELLO();
	void pHURRY();
	void pILLGETYOU();
	void pINCOMING();
	void pJUMP1();
	void pJUMP2();
	void pJUSTYOUWAIT();
	void pKAMIKAZE();
	void pLAUGH();
	void pLEAVEMEALONE();
	void pMISSED();
	void pNOOO();
	void pOHDEAR();
	void pOINUTTER();
	void pOOFF1();
	void pOOFF2();
	void pOOFF3();
	void pOOPS();
	void pORDERS();
	void pOUCH();
	void pOW1();
	void pOW2();
	void pOW3();
	void pPERFECT();
	void pREVENGE();
	void pRUNAWAY();
	void pSTUPID();
	void pTAKECOVER();
	void pTRAITOR();
	void pUH_OH();
	void pVICTORY();
	void pWATCHTHIS();
	void pWHATTHE();
	void pWOBBLE();
	void pYESSIR();
	void pYOULLREGRETTHAT();
};



#endif /* defined(__SOUND_MANAGER__) */