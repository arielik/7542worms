#pragma once

#ifndef __COSNTANTES__H_
#define __COSNTANTES__H_

#define TIME_STEP 30.0

#define MENU_WIDTH  140
#define USER_BAR_HEIGHT 80

#define WORM_WIDTH 30
#define WORM_HEIGHT 30

#define MODEL_WORM_WIDTH 2
#define MODEL_WORM_HEIGHT 2.75

#define SPRITES_WIDTH 48
#define SPRITES_HEIGHT 48

#define ELEM_WIDTH 10
#define ELEM_HEIGHT 10

#define LOGIC_UNITS 100

#define DELTA 20 // delta del scroll
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define ALIGN_SPRITE 50
#define ARROW_Y_POS 15

#define CONFIG_IMAGES 6

#define BACKGROUND "background"
#define ARROW_BUTTON "arrow"
#define SAVE_BUTTON "save"
#define EXIT_BUTTON "exit"
#define LOAD_BACK_BUTTON "loadButton"

#define DEFAULT_YAML_LEVEL "res/levels/clienteyaml.yaml"
#define DEFAULT_YAML_SERVER "res/levels/level.yaml"
#define CONFIG_FILE "config/config.yaml"

#define PI 3.14159265

#define WORM_LIFE 100

/* ************************ Constantes referidas a armamento ************************ */

#define SHOOT_POWER 0.2
#define MAX_TIME_POWER 3
#define MAX_POWER 100

#define BANANA_TIME 4
#define GRENADE_TIME 4
#define HOLY_TIME 3
#define BANANITA_TIME 3
#define DYNAMITE_TIME 3
#define SHEEP_TIME 10

#define SHEEP_SPEED 3
#define SHEEP_FORCE 170

#define BAZOOKA_X_FACTOR 1.7
#define BANANITA_Y_FACTOR 2

#define AIR_STRIKE_Y 80
#define BURRO_Y 80



#define TURN_DURATION 60


/****************************************************************************************************/
/** Archivo de configuracion que reune todos los valores constantes que se utilizan en el proyecto **/
/****************************************************************************************************/

/** 1 Unidad logica equivale a 10 pixels*/
#define ESCALA_UL2PX  10

/**************************** Log ****************************/
#define LOG_RUTA "./DI_Log.txt"
#define LOG_MAX_LINE_SIZE 512

// Para setear el uso del archivo de log
#define LOG_ESCRITURA LOG_ON  // <<< Acá se setea, se puede poner LOG_OFF o LOG_ON
#define LOG_OFF 0
#define LOG_ON 1

/**************************** SDL ****************************/


/*********************CONTROLES EN PANTALLA ******************/
#define DEFAULT_FONT "./src/utils/Fonts/verdana.ttf"

/**************************** YAML ***************************/

#define YAML_RUTA_ARCHIVO_JUEGO "./config/juego.yaml"
#define YAML_RUTA_ARCHIVO_CONEXION "./config/conexion.yaml"
#define YAML_RUTA_DIRECTORIO_IMG "./img/"
#define YAML_RUTA_DIRECTORIO_JUEGOS "./config/"

#define YAML_STRING_VACIO ""
#define YAML_ERROR_INT -1

#define YAML_TIPO_STRING "Cadena de caracteres"
#define YAML_TIPO_INT "Entero"

#define YAML_DEAFAULT_PANTALLA_ALTO 600
#define YAML_DEAFAULT_PANTALLA_ANCHO 800
#define YAML_DEAFAULT_VEL_PERSONAJE 100
#define YAML_DEAFAULT_MARGEN_SCROLL 20
#define YAML_DEAFAULT_NOMBRE "default"
#define YAML_DEAFAULT_RUTA_IMAGEN "default.png"
#define YAML_DEAFAULT_ANCHO_BASE 1
#define YAML_DEAFAULT_ALTO_BASE 1
#define YAML_DEAFAULT_PIXEL_REF_X 0
#define YAML_DEAFAULT_PIXEL_REF_Y 0
#define YAML_DEAFAULT_FPS 15
#define YAML_DEAFAULT_DELAY 1
#define YAML_DEAFAULT_ALTO_NIVEL 100
#define YAML_DEAFAULT_ANCHO_NIVEL 100

#define YAML_PANTALLA_ALTO_TOPE_MINIMO 1
#define YAML_PANTALLA_ALTO_TOPE_MAXIMO 1080
#define YAML_PANTALLA_ANCHO_TOPE_MINIMO 1
#define YAML_PANTALLA_ANCHO_TOPE_MAXIMO 1920
#define YAML_VELOCIDAD_PERSONAJE_TOPE_MINIMO 0
#define YAML_VELOCIDAD_PERSONAJE_TOPE_MAXIMO 5000
#define YAML_MARGEN_SCROLL_TOPE_MINIMO 1
#define YAML_PERSONAJE_LONGITUD_MAXIMA 50
#define YAML_FPS_TOPE_MAXIMO 99
#define YAML_DELAY_TOPE_MAXIMO 99
#define YAML_CANTIDAD_OBLIGATORIA_DE_ANIMACIONES_PROTAGONISTA 24


/**************************** LOG2 ***************************/


/**************************** HANDLE CONTOUR ***************************/
#define HC_OFFSET 1000
#define HC_ERROR_1 /*1001*/ "Existen Lineas superpuestas"
#define HC_ERROR_2 /*1002*/ "Los puntos no esta en orde horario"
#define HC_ERROR_3 /*1003*/ "Existen Lineas superpuestas y ademas los puntos no esta en orde antihorario"
#define HC_ERROR_4 /*1004*/ "Error desconocido"
#define HC_INFO_VAL  "INICIANDO PROCESAMIENTO DE POLIGONOS"
#define HC_TRACE_VAL  "Chequeando la validacion del contorno"
#define HC_TRACE_RDP  "Procesando la eliminacion de puntos en el contorno"
#define HC_TRACE_SHAPES  "Procesando las formas para los poligonos"
#define HC_TRACE_MAX_VERTEX  "Procesando separacion de puntos por poligono"


/**************************** HANDLE CONTOUR ***************************/

/**************************** HANDLE PLAYER ***************************/
#define HP_OFFSET 2000
#define HP_ERROR_1 /*2001*/ "El nivel no admite mas jugadores"
#define HP_ERROR_2 /*2002*/ "Ocurrio un error al intentar agregar un jugador"
/**************************** HANDLE PLAYER ***************************/



/**************************** SOUNDS ***************************/
//#define MUSICAFONDO "./res/sounds/fondo.wav"
#define MUSICAFONDO ""

#define AIRSTRIKE "./res/sounds/audio_sfx/Airstrike.wav"
#define ARMAGEDDON "./res/sounds/audio_sfx/Armageddon.wav"
#define BANANAIMPACT "./res/sounds/audio_sfx/BananaImpact.wav"
#define BASEBALLBATIMPACT "./res/sounds/audio_sfx/BaseBallBatImpact.wav"
#define BASEBALLBATJINGLE "./res/sounds/audio_sfx/BaseBallBatJingle.wav"
#define BASEBALLBATRELEASE "./res/sounds/audio_sfx/BaseBallBatRelease.wav"
#define BLOWTORCH "./res/sounds/audio_sfx/BlowTorch.wav"
#define CAMERAPAN "./res/sounds/audio_sfx/CameraPan.wav"
#define COLLECT "./res/sounds/audio_sfx/Collect.wav"
#define COMMUNICATOR "./res/sounds/audio_sfx/Communicator.wav"
#define COUGH1 "./res/sounds/audio_sfx/COUGH1.WAV"
#define COUGH2 "./res/sounds/audio_sfx/Cough2.wav"
#define COUGH3 "./res/sounds/audio_sfx/Cough3.wav"
#define COUGH4 "./res/sounds/audio_sfx/Cough4.wav"
#define COUGH5 "./res/sounds/audio_sfx/COUGH5.WAV"
#define COUGH6 "./res/sounds/audio_sfx/Cough6.wav"
#define COWMOO "./res/sounds/audio_sfx/CowMoo.wav"
#define CRATEIMPACT "./res/sounds/audio_sfx/CrateImpact.wav"
#define CRATEPOP "./res/sounds/audio_sfx/cratepop.wav"
#define CROSSIMPACT "./res/sounds/audio_sfx/CrossImpact.wav"
#define CROWDPART1 "./res/sounds/audio_sfx/CrowdPart1.wav"
#define CROWDPART2 "./res/sounds/audio_sfx/CrowdPart2.wav"
#define CURSORSELECT "./res/sounds/audio_sfx/CursorSelect.wav"
#define DONORCARDAPPEARS "./res/sounds/audio_sfx/DonorCardAppears.wav"
#define DONORCARDCOLLECT "./res/sounds/audio_sfx/DonorCardCollect.wav"
#define DRAGONBALLIMPACT "./res/sounds/audio_sfx/DragonBallImpact.wav"
#define DRAGONBALLRELEASE "./res/sounds/audio_sfx/DragonBallRelease.wav"
#define DRILL "./res/sounds/audio_sfx/DRILL.WAV"
#define DRILLIMPACT "./res/sounds/audio_sfx/DrillImpact.wav"
#define EXPLOSION1 "./res/sounds/audio_sfx/Explosion1.wav"
#define EXPLOSION2 "./res/sounds/audio_sfx/Explosion2.wav"
#define EXPLOSION3 "./res/sounds/audio_sfx/Explosion3.WAV"
#define FIREPUNCHIMPACT "./res/sounds/audio_sfx/FirePunchImpact.wav"
#define FLAMETHROWERATTACK "./res/sounds/audio_sfx/FlameThrowerAttack.wav"
#define FLAMETHROWERLOOP "./res/sounds/audio_sfx/FlameThrowerLoop.wav"
#define FREEZE "./res/sounds/audio_sfx/Freeze.wav"
#define FRENCHANTHEM "./res/sounds/audio_sfx/FrenchAnthem.wav"
#define FROZENWORMIMPACT "./res/sounds/audio_sfx/FrozenWormImpact.wav"
#define FUSE "./res/sounds/audio_sfx/FUSE.WAV"
#define GIRDERIMPACT "./res/sounds/audio_sfx/GIRDERIMPACT.WAV"
#define GRENADEIMPACT "./res/sounds/audio_sfx/GRENADEIMPACT.WAV"
#define HANDGUNFIRE "./res/sounds/audio_sfx/HANDGUNFIRE.WAV"
#define HOLYDONKEY "./res/sounds/audio_sfx/HOLYDONKEY.WAV"
#define HOLYDONKEYIMPACT "./res/sounds/audio_sfx/HOLYDONKEYIMPACT.WAV"
#define HOLYGRENADE "./res/sounds/audio_sfx/HOLYGRENADE.WAV"
#define HOLYGRENADEIMPACT "./res/sounds/audio_sfx/HOLYGRENADEIMPACT.WAV"
#define INDIANANTHEM "./res/sounds/audio_sfx/IndianAnthem.wav"
#define JETPACKFINISH "./res/sounds/audio_sfx/JetPackFinish.wav"
#define JETPACKLOOP1 "./res/sounds/audio_sfx/JetPackLoop1.wav"
#define JETPACKLOOP2 "./res/sounds/audio_sfx/JetPackLoop2.wav"
#define JETPACKSTART "./res/sounds/audio_sfx/JetPackStart.wav"
#define KAMIKAZERELEASE "./res/sounds/audio_sfx/KAMIKAZERELEASE.WAV"
#define KEYCLICK "./res/sounds/audio_sfx/KEYCLICK.WAV"
#define KEYERASE "./res/sounds/audio_sfx/KEYERASE.WAV"
#define LOADINGTICK "./res/sounds/audio_sfx/LoadingTick.wav"
#define LONGBOWIMPACT "./res/sounds/audio_sfx/LongBowImpact.wav"
#define LONGBOWRELEASE "./res/sounds/audio_sfx/LongBowRelease.wav"
#define MAGICBULLET "./res/sounds/audio_sfx/MAGICBULLET.WAV"
#define MINEARM "./res/sounds/audio_sfx/MineArm.wav"
#define MINEDUD "./res/sounds/audio_sfx/MINEDUD.WAV"
#define MINEIMPACT "./res/sounds/audio_sfx/MINEIMPACT.WAV"
#define MINETICK "./res/sounds/audio_sfx/MINETICK.WAV"
#define MINIGUNFIRE "./res/sounds/audio_sfx/MiniGunFire.wav"
#define MOLEBOMBDIGGINGLOOP "./res/sounds/audio_sfx/MoleBombDiggingLoop.wav"
#define MOLEBOMBSQUEAK "./res/sounds/audio_sfx/MoleBombSqueak.wav"
#define MOLEBOMBWALKLOOP "./res/sounds/audio_sfx/MoleBombWalkLoop.wav"
#define MORSE "./res/sounds/audio_sfx/Morse.wav"
#define NINJAROPEFIRE "./res/sounds/audio_sfx/NinjaRopeFire.wav"
#define NINJAROPEIMPACT "./res/sounds/audio_sfx/NinjaRopeImpact.wav"
#define NUKEFLASH "./res/sounds/audio_sfx/NukeFlash.wav"
#define NUKEPART1 "./res/sounds/audio_sfx/NUKEPART1.WAV"
#define NUKEPART2 "./res/sounds/audio_sfx/NUKEPART2.WAV"
#define OILDRUMIMPACT "./res/sounds/audio_sfx/OilDrumImpact.wav"
#define OLDWOMAN "./res/sounds/audio_sfx/OLDWOMAN.WAV"
#define PAUSETICK "./res/sounds/audio_sfx/PAUSETICK.WAV"
#define PETROL "./res/sounds/audio_sfx/PETROL.WAV"
#define PIGEONCOO "./res/sounds/audio_sfx/PIGEONCOO.WAV"
#define RICOCHET "./res/sounds/audio_sfx/RICOCHET.WAV"
#define ROCKETPOWERDOWN "./res/sounds/audio_sfx/ROCKETPOWERDOWN.wav"
#define ROCKETPOWERUP "./res/sounds/audio_sfx/ROCKETPOWERUP.WAV"
#define ROCKETRELEASE "./res/sounds/audio_sfx/ROCKETRELEASE.WAV"
#define SALVATIONARMY "./res/sounds/audio_sfx/SALVATIONARMY.WAV"
#define SCALESOFJUSTICE "./res/sounds/audio_sfx/ScalesOfJustice.wav"
#define SHEEPBAA "./res/sounds/audio_sfx/SHEEPBAA.WAV"
#define SHOTGUNFIRE "./res/sounds/audio_sfx/ShotGunFire.wav"
#define SHOTGUNRELOAD "./res/sounds/audio_sfx/SHOTGUNRELOAD.WAV"
#define SIZZLE "./res/sounds/audio_sfx/SIZZLE.WAV"
#define SKUNKGASLOOP "./res/sounds/audio_sfx/SkunkGasLoop.wav"
#define SKUNKSQUEAK "./res/sounds/audio_sfx/SkunkSqueak.wav"
#define SKUNKWALKLOOP "./res/sounds/audio_sfx/SkunkWalkLoop.wav"
#define SNOTPLOP "./res/sounds/audio_sfx/SNOTPLOP.WAV"
#define SPLASH "./res/sounds/audio_sfx/Splash.wav"
#define SPLISH "./res/sounds/audio_sfx/Splish.wav"
#define STARTROUND "./res/sounds/audio_sfx/StartRound.wav"
#define SUDDENDEATH "./res/sounds/audio_sfx/SUDDENDEATH.WAV"
#define SUPERSHEEPRELEASE "./res/sounds/audio_sfx/SUPERSHEEPRELEASE.WAV"
#define SUPERSHEEPWHOOSH "./res/sounds/audio_sfx/SUPERSHEEPWHOOSH.WAV"
#define TEAMBOUNCE "./res/sounds/audio_sfx/TEAMBOUNCE.WAV"
#define TEAMDROP "./res/sounds/audio_sfx/TeamDrop.wav"
#define TELEPORT "./res/sounds/audio_sfx/TELEPORT.WAV"
#define THROWPOWERDOWN "./res/sounds/audio_sfx/THROWPOWERDOWN.wav"
#define THROWPOWERUP "./res/sounds/audio_sfx/THROWPOWERUP.WAV"
#define THROWRELEASE "./res/sounds/audio_sfx/THROWRELEASE.WAV"
#define TIMERTICK "./res/sounds/audio_sfx/TIMERTICK.WAV"
#define TWANG1 "./res/sounds/audio_sfx/TWANG1.WAV"
#define TWANG2 "./res/sounds/audio_sfx/TWANG2.WAV"
#define TWANG3 "./res/sounds/audio_sfx/TWANG3.WAV"
#define TWANG4 "./res/sounds/audio_sfx/TWANG4.WAV"
#define TWANG5 "./res/sounds/audio_sfx/TWANG5.WAV"
#define TWANG6 "./res/sounds/audio_sfx/TWANG6.WAV"
#define UNDERWATERLOOP "./res/sounds/audio_sfx/UnderWaterLoop.wav"
#define UNFREEZE "./res/sounds/audio_sfx/UnFreeze.wav"
#define UZIFIRE "./res/sounds/audio_sfx/UZIFIRE.WAV"
#define VASESMASH "./res/sounds/audio_sfx/VASESMASH.WAV"
#define VIKINGAXEIMPACT "./res/sounds/audio_sfx/VikingAxeImpact.wav"
#define VIKINGAXERELEASE "./res/sounds/audio_sfx/VikingAxeRelease.wav"
#define WALK_COMPRESS "./res/sounds/audio_sfx/Walk_Compress.wav"
#define WALK_EXPAND "./res/sounds/audio_sfx/Walk_Expand.wav"
#define WARNINGBEEP "./res/sounds/audio_sfx/WARNINGBEEP.WAV"
#define WEAPONHOMING "./res/sounds/audio_sfx/WEAPONHOMING.WAV"
#define WORMBURNED "./res/sounds/audio_sfx/WORMBURNED.WAV"
#define WORMIMPACT "./res/sounds/audio_sfx/WORMIMPACT.WAV"
#define WORMLANDING "./res/sounds/audio_sfx/WormLanding.wav"
#define WORMPOP "./res/sounds/audio_sfx/WORMPOP.WAV"
#define WORMSELECT "./res/sounds/audio_sfx/WORMSELECT.WAV"
#define WORMSPRING "./res/sounds/audio_sfx/WORMSPRING.WAV"

#define AMAZING "./res/sounds/audio_vox/AMAZING.WAV"
#define BORING "./res/sounds/audio_vox/BORING.WAV"
#define BRILLIANT "./res/sounds/audio_vox/BRILLIANT.WAV"
#define BUMMER "./res/sounds/audio_vox/BUMMER.WAV"
#define BUNGEE "./res/sounds/audio_vox/BUNGEE.WAV"
#define BYEBYE "./res/sounds/audio_vox/BYEBYE.WAV"
#define COMEONTHEN "./res/sounds/audio_vox/COMEONTHEN.WAV"
#define COWARD "./res/sounds/audio_vox/COWARD.WAV"
#define DRAGONPUNCH "./res/sounds/audio_vox/DRAGONPUNCH.WAV"
#define DROP "./res/sounds/audio_vox/DROP.WAV"
#define EXCELLENT "./res/sounds/audio_vox/EXCELLENT.WAV"
#define FATALITY "./res/sounds/audio_vox/FATALITY.WAV"
#define FIRE "./res/sounds/audio_vox/FIRE.WAV"
#define FIREBALL "./res/sounds/audio_vox/FIREBALL.WAV"
#define FIRSTBLOOD "./res/sounds/audio_vox/FIRSTBLOOD.WAV"
#define FLAWLESS "./res/sounds/audio_vox/FLAWLESS.WAV"
#define GOAWAY "./res/sounds/audio_vox/GOAWAY.WAV"
#define FXGRENADE "./res/sounds/audio_vox/GRENADE.WAV"
#define HELLO "./res/sounds/audio_vox/HELLO.WAV"
#define HURRY "./res/sounds/audio_vox/HURRY.WAV"
#define ILLGETYOU "./res/sounds/audio_vox/ILLGETYOU.WAV"
#define INCOMING "./res/sounds/audio_vox/INCOMING.WAV"
#define JUMP1 "./res/sounds/audio_vox/JUMP1.WAV"
#define JUMP2 "./res/sounds/audio_vox/JUMP2.WAV"
#define JUSTYOUWAIT "./res/sounds/audio_vox/JUSTYOUWAIT.WAV"
#define KAMIKAZE "./res/sounds/audio_vox/KAMIKAZE.WAV"
#define LAUGH "./res/sounds/audio_vox/LAUGH.WAV"
#define LEAVEMEALONE "./res/sounds/audio_vox/LEAVEMEALONE.WAV"
#define MISSED "./res/sounds/audio_vox/MISSED.WAV"
#define NOOO "./res/sounds/audio_vox/NOOO.WAV"
#define OHDEAR "./res/sounds/audio_vox/OHDEAR.WAV"
#define OINUTTER "./res/sounds/audio_vox/OINUTTER.WAV"
#define OOFF1 "./res/sounds/audio_vox/OOFF1.WAV"
#define OOFF2 "./res/sounds/audio_vox/OOFF2.WAV"
#define OOFF3 "./res/sounds/audio_vox/OOFF3.WAV"
#define OOPS "./res/sounds/audio_vox/OOPS.WAV"
#define ORDERS "./res/sounds/audio_vox/ORDERS.WAV"
#define OUCH "./res/sounds/audio_vox/OUCH.WAV"
#define OW1 "./res/sounds/audio_vox/OW1.WAV"
#define OW2 "./res/sounds/audio_vox/OW2.WAV"
#define OW3 "./res/sounds/audio_vox/OW3.WAV"
#define PERFECT "./res/sounds/audio_vox/PERFECT.WAV"
#define REVENGE "./res/sounds/audio_vox/REVENGE.WAV"
#define RUNAWAY "./res/sounds/audio_vox/RUNAWAY.WAV"
#define STUPID "./res/sounds/audio_vox/STUPID.WAV"
#define TAKECOVER "./res/sounds/audio_vox/TAKECOVER.WAV"
#define TRAITOR "./res/sounds/audio_vox/TRAITOR.WAV"
#define UH_OH "./res/sounds/audio_vox/UH_OH.WAV"
#define VICTORY "./res/sounds/audio_vox/VICTORY.WAV"
#define WATCHTHIS "./res/sounds/audio_vox/WATCHTHIS.WAV"
#define WHATTHE "./res/sounds/audio_vox/WHATTHE.WAV"
#define WOBBLE "./res/sounds/audio_vox/WOBBLE.WAV"
#define YESSIR "./res/sounds/audio_vox/YESSIR.WAV"
#define YOULLREGRETTHAT "./res/sounds/audio_vox/YOULLREGRETTHAT.WAV"

/**************************** SOUNDS ***************************/


/**************************** FONTS ****************************/
#define ARIAL16 "res/images/arial16.png"

#define ARIAL12 "res/images/arial12.png"

/***************************************************************/


#define LOG_PATH "./LOG"

#endif /*__COSNTANTES__H_*/