//2.53 Updated to 16th Jan, 2017
#include "../precompiled.h" //always first

#include "ByteCode.h"
#include "CompileError.h"
#include "DataStructs.h"
#include "../zsyssimple.h"
#include <assert.h>
#include <iostream>
#include <cstdlib>

using namespace ZScript;
using std::ostringstream;

string LiteralArgument::toString()
{
    char temp[128];
    string sign = value < 0 ? "-" : "";
    sprintf(temp,"%ld", abs(value)/10000);
    string first = string(temp);
    
    if(value % 10000 == 0)
        return sign + first;
        
    sprintf(temp,"%ld", abs(value)%10000);
    string second = string(temp);
    
    while(second.length() < 4)
        second = "0" + second;
        
    return sign + first + "." + second;
}

string VarArgument::toString()
{
    char temp[128];
    
     switch(ID)
    {
    case SP:
        return "SP";
        
    case DATA:
        return "DATA";
        
    case FFSCRIPT:
        return "FFSCRIPT";
        
    case FCSET:
        return "CSET";
        
    case DELAY:
        return "DELAY";
        
    case FX:
        return "X";
    case FFCID:
	return "FFCID";
        
    case FY:
        return "Y";
        
    case XD:
        return "XD";
        
    case YD:
        return "YD";
        
    case XD2:
        return "XD2";
        
    case YD2:
        return "YD2";
        
    case LINKX:
        return "LINKX";
        
    case LINKY:
        return "LINKY";
        
    case LINKZ:
        return "LINKZ";
        
    case LINKJUMP:
        return "LINKJUMP";
        
    case LINKDIR:
        return "LINKDIR";
        
    case LINKHITDIR:
        return "LINKHITDIR";
        
    case LINKSWORDJINX:
        return "LINKSWORDJINX";
        
    case LINKITEMJINX:
        return "LINKITEMJINX";
        
    case LINKHP:
        return "LINKHP";
        
    case LINKMP:
        return "LINKMP";
        
    case LINKMAXHP:
        return "LINKMAXHP";
        
    case LINKMAXMP:
        return "LINKMAXMP";
        
    case LINKACTION:
        return "LINKACTION";
        
    case LINKHELD:
        return "LINKHELD";
        
    case LINKINVIS:
        return "LINKINVIS";
        
    case LINKINVINC:
        return "LINKINVINC";
        
    case LINKMISCD:
        return "LINKMISCD";
        
    case LINKTILE:
        return "LINKTILE";
        
    case LINKFLIP:
        return "LINKFLIP";
        
    case INPUTSTART:
        return "INPUTSTART";
        
    case INPUTMAP:
        return "INPUTMAP";
        
    case INPUTUP:
        return "INPUTUP";
        
    case INPUTDOWN:
        return "INPUTDOWN";
        
    case INPUTLEFT:
        return "INPUTLEFT";
        
    case INPUTRIGHT:
        return "INPUTRIGHT";
        
    case INPUTA:
        return "INPUTA";
        
    case INPUTB:
        return "INPUTB";
        
    case INPUTL:
        return "INPUTL";
        
    case INPUTR:
        return "INPUTR";
        
    case INPUTEX1:
        return "INPUTEX1";
        
    case INPUTEX2:
        return "INPUTEX2";
        
    case INPUTEX3:
        return "INPUTEX3";
        
    case INPUTEX4:
        return "INPUTEX4";
        
    case INPUTAXISUP:
        return "INPUTAXISUP";
        
    case INPUTAXISDOWN:
        return "INPUTAXISDOWN";
        
    case INPUTAXISLEFT:
        return "INPUTAXISLEFT";
        
    case INPUTAXISRIGHT:
        return "INPUTAXISRIGHT";
        
    case INPUTPRESSSTART:
        return "INPUTPRESSSTART";
        
    case INPUTPRESSMAP:
        return "INPUTPRESSMAP";
        
    case INPUTPRESSUP:
        return "INPUTPRESSUP";
        
    case INPUTPRESSDOWN:
        return "INPUTPRESSDOWN";
        
    case INPUTPRESSLEFT:
        return "INPUTPRESSLEFT";
        
    case INPUTPRESSRIGHT:
        return "INPUTPRESSRIGHT";
        
    case INPUTPRESSA:
        return "INPUTPRESSA";
        
    case INPUTPRESSB:
        return "INPUTPRESSB";
        
    case INPUTPRESSL:
        return "INPUTPRESSL";
        
    case INPUTPRESSR:
        return "INPUTPRESSR";
        
    case INPUTPRESSEX1:
        return "INPUTPRESSEX1";
        
    case INPUTPRESSEX2:
        return "INPUTPRESSEX2";
        
    case INPUTPRESSEX3:
        return "INPUTPRESSEX3";
        
    case INPUTPRESSEX4:
        return "INPUTPRESSEX4";
        
    case INPUTPRESSAXISUP:
        return "PRESSAXISUP";
        
    case INPUTPRESSAXISDOWN:
        return "PRESSAXISDOWN";
        
    case INPUTPRESSAXISLEFT:
        return "PRESSAXISLEFT";
        
    case INPUTPRESSAXISRIGHT:
        return "PRESSAXISRIGHT";
        
    case INPUTMOUSEX:
        return "INPUTMOUSEX";
        
    case INPUTMOUSEY:
        return "INPUTMOUSEY";
        
    case INPUTMOUSEZ:
        return "INPUTMOUSEZ";
        
    case INPUTMOUSEB:
        return "INPUTMOUSEB";
    
    case BUTTONPRESS: return "BUTTONPRESS";
    case BUTTONINPUT: return "BUTTONINPUT";
    case BUTTONHELD: return "BUTTONHELD";
    case KEYPRESS: return "KEYPRESS";
    case READKEY: return "READKEY";
    case JOYPADPRESS: return "JOYPADPRESS";
    
     case LINKINVFRAME:
	return "LINKINVFRAME";
    case LINKCANFLICKER:
	return "LINKCANFLICKER";
    case LINKHURTSFX:
	return "LINKHURTSFX";
    
    case LINKEATEN: return "LINKEATEN";
    
    case LINKITEMB: return "LINKITEMB";

    case LINKITEMA: return "LINKITEMA";
    case SETITEMSLOT: return "SETITEMSLOT";
    case GAMESETB: return "GAMESETB";
    case GAMESETA: return "GAMESETA";
    case LINKUSINGITEM: return "LINKUSINGITEM";
    case LINKUSINGITEMA: return "LINKUSINGITEMA";
    case LINKUSINGITEMB: return "LINKUSINGITEMB";
    
    case SDD:
        return "SDD";
        
    case SCREENFLAGSD:
        return "SCREENFLAGSD";
        
    case SCREENEFLAGSD:
        return "SCREENEFLAGSD";
        
    case COMBODD:
        return "COMBODD";
        
    case COMBOCD:
        return "COMBOCD";
        
    case COMBOFD:
        return "COMBOFD";
        
    case COMBODDM:
        return "COMBODDM";
        
    case COMBOCDM:
        return "COMBOCDM";
        
    case COMBOFDM:
        return "COMBOFDM";
        
    case REFFFC:
        return "REFFFC";
    
    case REFMAPDATA: return "REFMAPDATA";
    case REFSCREENDATA: return "REFSCREENDATA";
    case REFCOMBODATA: return "REFCOMBODATA";
    case REFSPRITEDATA: return "REFSPRITEDATA";
    case REFBITMAP: return "REFBITMAP";
    case REFNPCCLASS: return "REFNPCCLASS";
    
     case REFDMAPDATA: return "REFDMAPDATA";
     case REFSHOPDATA: return "REFSHOPDATA";
     case REFMSGDATA: return "REFMSGDATA";
     case REFNIL: return "REFNIL";
    
     case REFDROPS: return "REFDROPS";
     case REFPONDS: return "REFPONDS";
     case REFWARPRINGS: return "REFWARPRINGS";
     case REFDOORS: return "REFDOORS";
     case REFUICOLOURS: return "REFUICOLOURS";
     case REFRGB: return "REFRGB";
     case REFPALETTE: return "REFPALETTE";
     case REFTUNES: return "REFTUNES";
     case REFPALCYCLE: return "REFPALCYCLE";
     case REFGAMEDATA: return "REFGAMEDATA";
     case REFCHEATS: return "REFCHEATS";
        
    case REFITEM:
        return "REFITEM";
        
    case ITEMCOUNT:
        return "ITEMCOUNT";
        
    case ITEMX:
        return "ITEMX";
        
    case ITEMY:
        return "ITEMY";
        
    case ITEMZ:
        return "ITEMZ";
        
    case ITEMJUMP:
        return "ITEMJUMP";
        
    case ITEMDRAWTYPE:
        return "ITEMDRAWTYPE";
        
    case ITEMID:
        return "ITEMID";
        
    case ITEMTILE:
        return "ITEMTILE";
        
    case ITEMCSET:
        return "ITEMCSET";
        
    case ITEMFLASHCSET:
        return "ITEMFLASHCSET";
        
    case ITEMFRAMES:
        return "ITEMFRAMES";
        
    //This DOES NOT DO what ZScript.txt claims that it does, and needs to be fixed. -Z
    case ITEMFRAME:
        return "ITEMFRAME";
        
    case ITEMASPEED:
        return "ITEMASPEED";
    
    case ITEMACLK:
        return "ITEMACLK";
        
    case ITEMDELAY:
        return "ITEMDELAY";
        
    case ITEMFLASH:
        return "ITEMFLASH";
        
    case ITEMFLIP:
        return "ITEMFLIP";
        
    case ITEMEXTEND:
        return "ITEMEXTEND";
        
    case ITEMPICKUP:
        return "ITEMPICKUP";
        
    case ITEMMISCD:
        return "ITEMMISCD";
        
    case ITEMCLASSFAMILY:
        return "IDATAFAMILY";
        
    case ITEMCLASSFAMTYPE:
        return "IDATALEVEL";
        
    case ITEMCLASSAMOUNT:
        return "IDATAAMOUNT";
        
    case ITEMCLASSMAX:
        return "IDATAMAX";
        
    case ITEMCLASSSETMAX:
        return "IDATASETMAX";
        
    case ITEMCLASSSETGAME:
        return "IDATAKEEP";
        
    case ITEMCLASSCOUNTER:
        return "IDATACOUNTER";
        
    case ITEMCLASSUSESOUND:
        return "IDATAUSESOUND";
        
    case ITEMCLASSPOWER:
        return "IDATAPOWER";
        
    case ITEMCLASSINITDD:
        return "IDATAINITDD";
        
    case REFITEMCLASS:
        return "REFITEMCLASS";
        
    case COMBOID:
        return "COMBOID";
        
    case COMBOTD:
        return "COMBOTD";
        
    case COMBOSD:
        return "COMBOSD";
        
    case COMBOIDM:
        return "COMBOIDM";
        
    case COMBOTDM:
        return "COMBOTDM";
        
    case COMBOSDM:
        return "COMBOSDM";
        
    case GETMIDI:
        return "GETMIDI";
        
    case CURSCR:
        return "CURSCR";
        
    case CURDSCR:
        return "CURDSCR";
        
    case CURMAP:
        return "CURMAP";
        
    case CURDMAP:
        return "CURDMAP";
    case GAMEMAXMAPS: return "GAMEMAXMAPS";
        
    case CURLEVEL:
        return "CURLEVEL";
        
    case GAMEDEATHS:
        return "GAMEDEATHS";
        
    case GAMECHEAT:
        return "GAMECHEAT";
    
    case ZELDAVERSION:
	return "ZELDAVERSION";
    case ZELDABUILD:
	return "ZELDABUILD";
    case ZELDABETA:
	return "ZELDABETA";
    
        
    case GAMETIME:
        return "GAMETIME";
        
    case GAMEHASPLAYED:
        return "GAMEHASPLAYED";
        
    case GAMESTANDALONE:
        return "GAMESTANDALONE";
        
    case GAMETIMEVALID:
        return "GAMETIMEVALID";
        
    case GAMEGUYCOUNT:
        return "GAMEGUYCOUNT";
        
    case GAMECONTSCR:
        return "GAMECONTSCR";
        
    case GAMECONTDMAP:
        return "GAMECONTDMAP";
        
    case GAMEENTRSCR:
        return "GAMEENTRSCR";
        
    case GAMEENTRDMAP:
        return "GAMEENTRDMAP";
        
    case GAMECOUNTERD:
        return "GAMECOUNTERD";
        
    case GAMEMCOUNTERD:
        return "GAMEMCOUNTERD";
        
    case GAMEDCOUNTERD:
        return "GAMEDCOUNTERD";
        
    case GAMEGENERICD:
        return "GAMEGENERICD";
    
    case GAMEMISC:
        return "GAMEMISC";
        
    case GAMEITEMSD:
        return "GAMEITEMSD";
        
    case GAMELITEMSD:
        return "GAMELITEMSD";
        
    case GAMELKEYSD:
        return "GAMELKEYSD";
        
    case SCREENSTATED:
        return "SCREENSTATED";
        
    case SCREENSTATEDD:
        return "SCREENSTATEDD";
        
    case DMAPFLAGSD:
        return "DMAPFLAGSD";
        
    case DMAPLEVELD:
        return "DMAPLEVELD";
    
    case DMAPLEVELPAL:
	return "DMAPLEVELPAL";
        
    case DMAPCOMPASSD:
        return "DMAPCOMPASSD";
        
    case DMAPCONTINUED:
        return "DMAPCONTINUED";
        
    case DMAPMIDID:
        return "DMAPMIDID";
        
    case DMAPOFFSET:
        return "DMAPOFFSET";
        
    case DMAPMAP:
        return "DMAPMAP";
        
    case SDDD:
        return "SDDD";
        
    case SDDDD:
        return "SDDDD";
        
    case GAMECLICKFREEZE:
        return "GAMECLICKFREEZE";
        
    case NOACTIVESUBSC: return "NOACTIVESUBSC"; //Disable active subscreen.
    
    case FFFLAGSD:
        return "FFFLAGSD";
        
    case FFTWIDTH:
        return "FFTWIDTH";
        
    case FFTHEIGHT:
        return "FFTHEIGHT";
        
    case FFCWIDTH:
        return "FFCWIDTH";
        
    case FFCHEIGHT:
        return "FFCHEIGHT";
        
    case FFLINK:
        return "FFLINK";
        
    case FFMISCD:
        return "FFMISCD";
        
    case FFINITDD:
        return "FFINITDD";
        
        /*case FFDD:
        return "FFDD";*/
    case LINKITEMD:
        return "LINKITEMD";
    
    case DISABLEDITEM: return "DISABLEDITEM";
        
    case REFNPC:
        return "REFNPC";
        
    case NPCCOUNT:
        return "NPCCOUNT";
        
    case NPCX:
        return "NPCX";
        
    case NPCY:
        return "NPCY";
        
    case NPCZ:
        return "NPCZ";
        
    case NPCJUMP:
        return "NPCJUMP";
        
    case NPCDIR:
        return "NPCDIR";
        
    case NPCRATE:
        return "NPCRATE";
        
    case NPCHOMING:
        return "NPCHOMING";
        
    case NPCFRAMERATE:
        return "NPCFRAMERATE";
        
    case NPCHALTRATE:
        return "NPCHALTRATE";
        
    case NPCDRAWTYPE:
        return "NPCDRAWTYPE";
        
    case NPCHP:
        return "NPCHP";
        
    case NPCID:
        return "NPCID";
        
    case NPCTYPE:
        return "NPCTYPE";
        
    case NPCDP:
        return "NPCDP";
        
    case NPCWDP:
        return "NPCWDP";
        
    case NPCTILE:
        return "NPCTILE";
        
    case NPCOTILE:
        return "NPCOTILE";
        
    case NPCWEAPON:
        return "NPCWEAPON";
        
    case NPCITEMSET:
        return "NPCITEMSET";
        
    case NPCCSET:
        return "NPCCSET";
        
    case NPCBOSSPAL:
        return "NPCBOSSPAL";
        
    case NPCBGSFX:
        return "NPCBGSFX";
        
    case NPCEXTEND:
        return "NPCEXTEND";
        
    case NPCSTEP:
        return "NPCSTEP";
        
    case NPCDEFENSED:
        return "NPCDEFENSED";
    case NPCSCRDEFENSED: return "NPCSCRDEFENSED";
        
    case NPCMISCD:
        return "NPCMISCD";
        
    case NPCDD:
        return "NPCDD";
        
    case NPCMFLAGS:
        return "NPCMFLAGS";
        
    case NPCCOLLDET:
        return "NPCCOLLDET";
        
    case NPCSTUN:
        return "NPCSTUN";
        
    case NPCHUNGER:
        return "NPCHUNGER";
    
    
    case NPCINVINC:
        return "NPCINVINC";
    case NPCSUPERMAN:
        return "NPCSUPERMAN";
    case NPCHASITEM:
        return "NPCHASITEM";
    case NPCRINGLEAD:
        return "NPCRINGLEAD";
    case NPCSHIELD:
        return "NPCSHIELD";
    
    case NPCFROZEN:
        return "NPCFROZEN";   
    case NPCFROZENTILE:
        return "NPCFROZENTILE";
    case NPCFROZENCSET:
        return "NPCFROZENCSET"; 
    case NPCBEHAVIOUR:
        return "NPCBEHAVIOUR"; 
        
    case SCRDOORD:
        return "SCRDOORD";
        
    case LIT:
        return "LIT";
        
    case WAVY:
        return "WAVY";
        
    case QUAKE:
        return "QUAKE";
        
    case ITEMOTILE:
        return "ITEMOTILE";
        
    case REFLWPN:
        return "REFLWPN";
        
    case LWPNCOUNT:
        return "LWPNCOUNT";
        
    case LWPNX:
        return "LWPNX";
        
    case LWPNY:
        return "LWPNY";
        
    case LWPNZ:
        return "LWPNZ";
        
    case LWPNJUMP:
        return "LWPNJUMP";
        
    case LWPNDIR:
        return "LWPNDIR";
        
    case LWPNANGLE:
        return "LWPNANGLE";
        
    case LWPNSTEP:
        return "LWPNSTEP";
        
    case LWPNFRAMES:
        return "LWPNFRAMES";
        
    case LWPNFRAME:
        return "LWPNFRAME";
        
    case LWPNDRAWTYPE:
        return "LWPNDRAWTYPE";
        
    case LWPNPOWER:
        return "LWPNPOWER";
        
    case LWPNID:
        return "LWPNID";
        
    case LWPNANGULAR:
        return "LWPNANGULAR";
        
    case LWPNBEHIND:
        return "LWPNBEHIND";
        
    case LWPNASPEED:
        return "LWPNASPEED";
        
    case LWPNTILE:
        return "LWPNTILE";
        
    case LWPNFLASHCSET:
        return "LWPNFLASHCSET";
        
    case LWPNDEAD:
        return "LWPNDEAD";
        
    case LWPNCSET:
        return "LWPNCSET";
        
    case LWPNFLASH:
        return "LWPNFLASH";
        
    case LWPNFLIP:
        return "LWPNFLIP";
        
    case LWPNOTILE:
        return "LWPNOTILE";
        
    case LWPNOCSET:
        return "LWPNOCSET";
        
    case LWPNEXTEND:
        return "LWPNEXTEND";
        
    case LWPNCOLLDET:
        return "LWPNCOLLDET";
    
    case LWPNPARENT:
        return "LWPNPARENT";
    case LWPNLEVEL:
        return "LWPNLEVEL";
    case EWPNPARENT:
        return "EWPNPARENT";
        
    case REFEWPN:
        return "REFEWPN";
        
    case EWPNCOUNT:
        return "EWPNCOUNT";
        
    case EWPNX:
        return "EWPNX";
        
    case EWPNY:
        return "EWPNY";
        
    case EWPNZ:
        return "EWPNZ";
        
    case EWPNJUMP:
        return "EWPNJUMP";
        
    case EWPNDIR:
        return "EWPNDIR";
        
    case EWPNANGLE:
        return "EWPNANGLE";
        
    case EWPNSTEP:
        return "EWPNSTEP";
        
    case EWPNFRAMES:
        return "EWPNFRAMES";
        
    case EWPNFRAME:
        return "EWPNFRAME";
        
    case EWPNDRAWTYPE:
        return "EWPNDRAWTYPE";
        
    case EWPNPOWER:
        return "EWPNPOWER";
        
    case EWPNID:
        return "EWPNID";
        
    case EWPNANGULAR:
        return "EWPNANGULAR";
        
    case EWPNBEHIND:
        return "EWPNBEHIND";
        
    case EWPNASPEED:
        return "EWPNASPEED";
        
    case EWPNTILE:
        return "EWPNTILE";
        
    case EWPNFLASHCSET:
        return "EWPNFLASHCSET";
        
    case EWPNDEAD:
        return "EWPNDEAD";
        
    case EWPNCSET:
        return "EWPNCSET";
        
    case EWPNFLASH:
        return "EWPNFLASH";
        
    case EWPNFLIP:
        return "EWPNFLIP";
        
    case EWPNOTILE:
        return "EWPNOTILE";
        
    case EWPNOCSET:
        return "EWPNOCSET";
        
    case EWPNEXTEND:
        return "EWPNEXTEND";
        
    case EWPNCOLLDET:
        return "EWPNCOLLDET";
        
    case SCRIPTRAM:
        return "SCRIPTRAM";
        
    case GLOBALRAM:
        return "GLOBALRAM";
        
    case SCRIPTRAMD:
        return "SCRIPTRAMD";
        
    case GLOBALRAMD:
        return "GLOBALRAMD";
        
    case LWPNHXOFS:
        return "LWPNHXOFS";
        
    case LWPNHYOFS:
        return "LWPNHYOFS";
        
    case LWPNXOFS:
        return "LWPNXOFS";
        
    case LWPNYOFS:
        return "LWPNYOFS";
        
    case LWPNZOFS:
        return "LWPNZOFS";
        
    case LWPNHXSZ:
        return "LWPNHXSZ";
        
    case LWPNHYSZ:
        return "LWPNHYSZ";
        
    case LWPNHZSZ:
        return "LWPNHZSZ";
        
    case LWPNTXSZ:
        return "LWPNTXSZ";
        
    case LWPNTYSZ:
        return "LWPNTYSZ";
        
    case LWPNMISCD:
        return "LWPNMISCD";
        
    case EWPNHXOFS:
        return "EWPNHXOFS";
        
    case EWPNHYOFS:
        return "EWPNHYOFS";
        
    case EWPNXOFS:
        return "EWPNXOFS";
        
    case EWPNYOFS:
        return "EWPNYOFS";
        
    case EWPNZOFS:
        return "EWPNZOFS";
        
    case EWPNHXSZ:
        return "EWPNHXSZ";
        
    case EWPNHYSZ:
        return "EWPNHYSZ";
        
    case EWPNHZSZ:
        return "EWPNHZSZ";
        
    case EWPNTXSZ:
        return "EWPNTXSZ";
        
    case EWPNTYSZ:
        return "EWPNTYSZ";
        
    case EWPNMISCD:
        return "EWPNMISCD";
        
    case NPCHXOFS:
        return "NPCHXOFS";
        
    case NPCHYOFS:
        return "NPCHYOFS";
        
    case NPCXOFS:
        return "NPCXOFS";
        
    case NPCYOFS:
        return "NPCYOFS";
        
    case NPCZOFS:
        return "NPCZOFS";
        
    case NPCHXSZ:
        return "NPCHXSZ";
        
    case NPCHYSZ:
        return "NPCHYSZ";
        
    case NPCHZSZ:
        return "NPCHZSZ";
        
    case NPCTXSZ:
        return "NPCTXSZ";
        
    case NPCTYSZ:
        return "NPCTYSZ";
        
    case ITEMHXOFS:
        return "ITEMHXOFS";
        
    case ITEMHYOFS:
        return "ITEMHYOFS";
        
    case ITEMXOFS:
        return "ITEMXOFS";
        
    case ITEMYOFS:
        return "ITEMYOFS";
        
    case ITEMZOFS:
        return "ITEMZOFS";
        
    case ITEMHXSZ:
        return "ITEMHXSZ";
        
    case ITEMHYSZ:
        return "ITEMHYSZ";
        
    case ITEMHZSZ:
        return "ITEMHZSZ";
        
    case ITEMTXSZ:
        return "ITEMTXSZ";
        
    case ITEMTYSZ:
        return "ITEMTYSZ";
        
    case LINKHXOFS:
        return "LINKHXOFS";
        
    case LINKHYOFS:
        return "LINKHYOFS";
        
    case LINKXOFS:
        return "LINKXOFS";
        
    case LINKYOFS:
        return "LINKYOFS";
        
    case LINKZOFS:
        return "LINKZOFS";
        
    case LINKHXSZ:
        return "LINKHXSZ";
        
    case LINKHYSZ:
        return "LINKHYSZ";
        
    case LINKHZSZ:
        return "LINKHZSZ";
        
    case LINKTXSZ:
        return "LINKTXSZ";
        
    case LINKTYSZ:
        return "LINKTYSZ";
        
    case LINKDRUNK:
        return "LINKDRUNK";
        
    case LINKEQUIP:
        return "LINKEQUIP";
        
    case LINKLADDERX:
        return "LINKLADDERX";
        
    case LINKLADDERY:
        return "LINKLADDERY";
        
    case ROOMTYPE:
        return "ROOMTYPE";
        
    case ROOMDATA:
        return "ROOMDATA";
        
    case PUSHBLOCKX:
        return "PUSHBLOCKX";
        
    case PUSHBLOCKY:
        return "PUSHBLOCKY";
        
    case PUSHBLOCKCOMBO:
        return "PUSHBLOCKCOMBO";
        
    case PUSHBLOCKCSET:
        return "PUSHBLOCKCSET";
        
    case UNDERCOMBO:
        return "UNDERCOMBO";
        
    case UNDERCSET:
        return "UNDERCSET";
    
    //2.6
    case CREATELWPNDX: return "CREATELWPNDX";
    
    //2.54 -Z
/* 2.54 Implemented
    */
    
    
//itemclass / itemdata

    //case IDATAFRAME: return "IDATAFRAME";
    case IDATACOSTCOUNTER: return "IDATACOSTCOUNTER";
    case ITEMCLASSID: return "IDATAID";
    case IDATALTM: return "IDATALTM";
    case IDATAPSCRIPT: return "IDATAPSCRIPT";
    case IDATASCRIPT: return "IDATASCRIPT";
    case IDATAMAGCOST: return "IDATAMAGCOST";
    case IDATAMINHEARTS: return "IDATAMINHEARTS";
    case IDATATILE: return "IDATATILE";
    case IDATAMISC: return "IDATAMISC";    
    case IDATACSET: return "IDATACSET";
    case IDATAFRAMES: return "IDATAFRAMES";
    case IDATAASPEED: return "IDATAASPEED";
    case IDATADELAY: return "IDATADELAY"; 
    case IDATACOMBINE: return "IDATACOMBINE";
    case IDATADOWNGRADE: return "IDATADOWNGRADE";
    case IDATAKEEPOLD: return "IDATAKEEPOLD";
    case IDATARUPEECOST: return "IDATARUPEECOST";
    case IDATAEDIBLE: return "IDATAEDIBLE";
    case IDATAFLAGUNUSED: return "IDATAFLAGUNUSED";
    case IDATAGAINLOWER: return "IDATAGAINLOWER";
    case IDATAPSTRING: return "IDATAPSTRING";
    
    //idata arrays
    case IDATAATTRIB: return "IDATAATTRIB";
    case IDATAFLAGS: return "IDATAFLAGS";
    case IDATASPRITE: return "IDATASPRITE";
        
    case IDATAUSEWPN: return "IDATAUSEWPN";
    case IDATAUSEDEF: return "IDATAUSEDEF";
    case IDATAWRANGE: return "IDATAWRANGE";
    case IDATAMAGICTIMER: return "IDATAMAGICTIMER";
    case IDATAUSEMVT: return "IDATAUSEMVT";
    case IDATADURATION: return "IDATADURATION";
    case IDATADUPLICATES: return "IDATADUPLICATES";
    case IDATADRAWLAYER: return "IDATADRAWLAYER";
    case IDATACOLLECTFLAGS: return "IDATACOLLECTFLAGS";
    case IDATAWEAPONSCRIPT: return "IDATAWEAPONSCRIPT";
    case IDATAMISCD: return "IDATAMISCD";
    case IDATAWEAPHXOFS: return "IDATAWEAPHXOFS";
    case IDATAWEAPHYOFS: return "IDATAWEAPHYOFS";
    case IDATAWEAPHYSZ: return "IDATAWEAPHYSZ";
    case IDATAWEAPHXSZ: return "IDATAWEAPHXSZ";
    case IDATAWEAPHZSZ: return "IDATAWEAPHZSZ";
    case IDATAWEAPXOFS: return "IDATAWEAPXOFS";
    case IDATAWEAPYOFS: return "IDATAWEAPYOFS";
    case IDATAWEAPZOFS: return "IDATAWEAPZOFS";
    case IDATAWPNINITD: return "IDATAWPNINITD";
    
    //Item Sizing
    case IDATAOVERRIDEFLWEAP: return "IDATAOVERRIDEFLWEAP";
    case IDATATILEHWEAP: return "IDATATILEHWEAP";
    case IDATATILEWWEAP: return "IDATATILEWWEAP";
    case IDATAHZSZWEAP: return "IDATAHZSZWEAP";
    case IDATAHYSZWEAP: return "IDATAHYSZWEAP";
    case IDATAHXSZWEAP: return "IDATAHXSZWEAP";
    case IDATADYOFSWEAP: return "IDATADYOFSWEAP";
    case IDATADXOFSWEAP: return "IDATADXOFSWEAP";
    case IDATAHYOFSWEAP: return "IDATAHYOFSWEAP";
    case IDATAHXOFSWEAP: return "IDATAHXOFSWEAP";
    case IDATAOVERRIDEFL: return "IDATAOVERRIDEFL";
    case IDATAPICKUP: return "IDATAPICKUP";
    case IDATATILEH: return "IDATATILEH";
    case IDATATILEW: return "IDATATILEW";
    case IDATAHZSZ: return "IDATAHZSZ";
    case IDATAHYSZ: return "IDATAHYSZ";
    case IDATAHXSZ: return "IDATAHXSZ";
    case IDATADYOFS: return "IDATADYOFS";
    case IDATADXOFS: return "IDATADXOFS";
    case IDATAHYOFS: return "IDATAHYOFS";
    case IDATAHXOFS: return "IDATAHXOFS";
    
    case NPCWEAPSPRITE: return "NPCWEAPSPRITE";
    
    //Debug->
    
    case DEBUGREFFFC: return "DEBUGREFFFC";
    case DEBUGREFITEM: return "DEBUGREFITEM";
    case DEBUGREFNPC: return "DEBUGREFNPC";
    case DEBUGREFITEMDATA: return "DEBUGREFITEMDATA";
    case DEBUGREFLWEAPON: return "DEBUGREFLWEAPON";
    case DEBUGREFEWEAPON: return "DEBUGREFEWEAPON";
    case DEBUGSP: return "DEBUGSP";
    case DEBUGGDR: return "DEBUGGDR";
    
    case LWPNRANGE: return "LWPNRANGE";
    
    case SETSCREENDOOR: return "SETSCREENDOOR";
    case SETSCREENENEMY: return "SETSCREENENEMY";
    case SCREENWIDTH: return "SCREENWIDTH";
    case SCREENHEIGHT: return "SCREENHEIGHT";
    case SCREENVIEWX: return "SCREENVIEWX";
    case SCREENVIEWY: return "SCREENVIEWY";
    case SCREENGUY: return "SCREENGUY";
    case SCREENSTRING: return "SCREENSTRING";
    case SCREENROOM: return "SCREENROOM";
    case SCREENENTX: return "SCREENENTX";
    case SCREENENTY: return "SCREENENTY";
    case SCREENITEM: return "SCREENITEM";
    case SCREENUNDCMB: return "SCREENUNDCMB";
    case SCREENUNDCST: return "SCREENUNDCST";
    case SCREENCATCH: return "SCREENCATCH";
    case SETSCREENLAYOP: return "SETSCREENLAYOP";
    case SETSCREENSECCMB: return "SETSCREENSECCMB";
    case SETSCREENSECCST: return "SETSCREENSECCST";
    case SETSCREENSECFLG: return "SETSCREENSECFLG";
    case SETSCREENLAYMAP: return "SETSCREENLAYMAP";
    case SETSCREENLAYSCR: return "SETSCREENLAYSCR";
    case SETSCREENPATH: return "SETSCREENPATH";
    case SETSCREENWARPRX: return "SETSCREENWARPRX";
    case SETSCREENWARPRY: return "SETSCREENWARPRY";
    
    case GAMENUMMESSAGES: return "GAMENUMMESSAGES";
    case GAMESUBSCHEIGHT: return "GAMESUBSCHEIGHT";
    case GAMEPLAYFIELDOFS: return "GAMEPLAYFIELDOFS";
    case PASSSUBOFS: return "PASSSUBOFS";
    
    case LINKBIGHITBOX: return "LINKBIGHITBOX";
    case LINKDIAG: return "LINKDIAG";
    
    //NPCData
    
	//three inputs no return (function-only)
	case SETNPCDATASCRIPTDEF: return "SETNPCDATASCRIPTDEF";
	case SETNPCDATADEFENSE: return "SETNPCDATADEFENSE";
	case SETNPCDATASIZEFLAG: return "SETNPCDATASIZEFLAG";
	case SETNPCDATAATTRIBUTE: return "SETNPCDATAATTRIBUTE";
    
    //ComboData
    
    //three inputs no return (function-only)
	case SCDBLOCKWEAPON: return "SCDBLOCKWEAPON";
	case SCDEXPANSION: return "SCDEXPANSION";
	case SCDSTRIKEWEAPONS: return "SCDSTRIKEWEAPONS";
	
	//Game Over Screen
	case SETGAMEOVERELEMENT: return "SETGAMEOVERELEMENT";
	case SETGAMEOVERSTRING: return "SETGAMEOVERSTRING";
	
	//Input->Mouse[]
	case MOUSEARR: return "MOUSEARR";
	
	
	//DataTypes
	
	//spritedata sd->
	case SPRITEDATATILE: return "SPRITEDATATILE";
	case SPRITEDATAMISC: return "SPRITEDATAMISC";
	case SPRITEDATACSETS: return "SPRITEDATACSETS";
	case SPRITEDATAFRAMES: return "SPRITEDATAFRAMES";
	case SPRITEDATASPEED: return "SPRITEDATASPEED";
	case SPRITEDATATYPE: return "SPRITEDATATYPE";
	
	//npcdata nd->
	case NPCDATATILE: return "NPCDATATILE";
	case NPCDATAHEIGHT: return "NPCDATAHEIGHT";
	case NPCDATAFLAGS: return "NPCDATAFLAGS";
	case NPCDATAFLAGS2: return "NPCDATAFLAGS2";
	case NPCDATAHITSFX: return "NPCDATAHITSFX";
	case NPCDATAWIDTH: return "NPCDATAWIDTH";
	case NPCDATASTILE: return "NPCDATASTILE";
	case NPCDATASWIDTH: return "NPCDATASWIDTH";
	case NPCDATASHEIGHT: return "NPCDATASHEIGHT";
	case NPCDATAETILE: return "NPCDATAETILE";
	case NPCDATAEWIDTH: return "NPCDATAEWIDTH";
	case NPCDATAEHEIGHT: return "NPCDATAEHEIGHT";
	case NPCDATAHP: return "NPCDATAHP";
	case NPCDATAFAMILY: return "NPCDATAFAMILY";
	case NPCDATACSET: return "NPCDATACSET";
	case NPCDATAANIM: return "NPCDATAANIM";
	case NPCDATAEANIM: return "NPCDATAEANIM";
	case NPCDATAFRAMERATE: return "NPCDATAFRAMERATE";
	case NPCDATAEFRAMERATE: return "NPCDATAEFRAMERATE";
	case NPCDATATOUCHDAMAGE: return "NPCDATATOUCHDAMAGE";
	case NPCDATAWEAPONDAMAGE: return "NPCDATAWEAPONDAMAGE";
	case NPCDATAWEAPON: return "NPCDATAWEAPON";
	case NPCDATARANDOM: return "NPCDATARANDOM";
	case NPCDATAHALT: return "NPCDATAHALT";
	case NPCDATASTEP: return "NPCDATASTEP";
	case NPCDATAHOMING: return "NPCDATAHOMING";
	case NPCDATAHUNGER: return "NPCDATAHUNGER";
	case NPCDATADROPSET: return "NPCDATADROPSET";
	case NPCDATABGSFX: return "NPCDATABGSFX";
	case NPCDATADEATHSFX: return "NPCDATADEATHSFX";
	case NPCDATAXOFS: return "NPCDATAXOFS";
	case NPCDATAYOFS: return "NPCDATAYOFS";
	case NPCDATAZOFS: return "NPCDATAZOFS";
	case NPCDATAHXOFS: return "NPCDATAHXOFS";
	case NPCDATAHYOFS: return "NPCDATAHYOFS";
	case NPCDATAHITWIDTH: return "NPCDATAHITWIDTH";
	case NPCDATAHITHEIGHT: return "NPCDATAHITHEIGHT";
	case NPCDATAHITZ: return "NPCDATAHITZ";
	case NPCDATATILEWIDTH: return "NPCDATATILEWIDTH";
	case NPCDATATILEHEIGHT: return "NPCDATATILEHEIGHT";
	case NPCDATAWPNSPRITE: return "NPCDATAWPNSPRITE";
	case NPCDATADEFENSE: return "NPCDATADEFENSE";
	case NPCDATASIZEFLAG: return "NPCDATASIZEFLAG";
	case NPCDATAATTRIBUTE: return "NPCDATAATTRIBUTE";
	case NPCDATASHIELD: return "NPCDATASHIELD";
	case NPCDATAFROZENTILE: return "NPCDATAFROZENTILE";
	case NPCDATAFROZENCSET: return "NPCDATAFROZENCSET";
	case NPCDATABEHAVIOUR: return "NPCDATABEHAVIOUR";
		
	case MAPDATAVALID: return "MAPDATAVALID";
	case MAPDATAGUY: return "MAPDATAGUY";
	case MAPDATASTRING: return "MAPDATASTRING";
	case MAPDATAROOM: return "MAPDATAROOM";
	case MAPDATAITEM: return "MAPDATAITEM";
	case MAPDATAHASITEM: return "MAPDATAHASITEM";
	case MAPDATATILEWARPTYPE: return "MAPDATATILEWARPTYPE";
	case MAPDATATILEWARPOVFLAGS: return "MAPDATATILEWARPOVFLAGS";
	case MAPDATADOORCOMBOSET: return "MAPDATADOORCOMBOSET";
	case MAPDATAWARPRETX: return "MAPDATAWARPRETX";
	case MAPDATAWARPRETY: return "MAPDATAWARPRETY";
	case MAPDATAWARPRETURNC: return "MAPDATAWARPRETURNC";
	case MAPDATASTAIRX: return "MAPDATASTAIRX";
	case MAPDATASTAIRY: return "MAPDATASTAIRY";
	case MAPDATACOLOUR: return "MAPDATACOLOUR";
	case MAPDATAENEMYFLAGS: return "MAPDATAENEMYFLAGS";
	case MAPDATADOOR: return "MAPDATADOOR";
	case MAPDATATILEWARPDMAP: return "MAPDATATILEWARPDMAP";
	case MAPDATATILEWARPSCREEN: return "MAPDATATILEWARPSCREEN";
	case MAPDATAEXITDIR: return "MAPDATAEXITDIR";
	case MAPDATAENEMY: return "MAPDATAENEMY";
	case MAPDATAPATTERN: return "MAPDATAPATTERN";
	case MAPDATASIDEWARPTYPE: return "MAPDATASIDEWARPTYPE";
	case MAPDATASIDEWARPOVFLAGS: return "MAPDATASIDEWARPOVFLAGS";
	case MAPDATAWARPARRIVALX: return "MAPDATAWARPARRIVALX";
	case MAPDATAWARPARRIVALY: return "MAPDATAWARPARRIVALY";
	case MAPDATAPATH: return "MAPDATAPATH";
	case MAPDATASIDEWARPSC: return "MAPDATASIDEWARPSC";
	case MAPDATASIDEWARPDMAP: return "MAPDATASIDEWARPDMAP";
	case MAPDATASIDEWARPINDEX: return "MAPDATASIDEWARPINDEX";
	case MAPDATAUNDERCOMBO: return "MAPDATAUNDERCOMBO";
	case MAPDATAUNDERCSET: return "MAPDATAUNDERCSET";
	case MAPDATACATCHALL: return "MAPDATACATCHALL";
	case MAPDATAFLAGS: return "MAPDATAFLAGS";
	case MAPDATACSENSITIVE: return "MAPDATACSENSITIVE";
	case MAPDATANORESET: return "MAPDATANORESET";
	case MAPDATANOCARRY: return "MAPDATANOCARRY";
	case MAPDATALAYERMAP: return "MAPDATALAYERMAP";
	case MAPDATALAYERSCREEN: return "MAPDATALAYERSCREEN";
	case MAPDATALAYEROPACITY: return "MAPDATALAYEROPACITY";
	case MAPDATATIMEDWARPTICS: return "MAPDATATIMEDWARPTICS";
	case MAPDATANEXTMAP: return "MAPDATANEXTMAP";
	case MAPDATANEXTSCREEN: return "MAPDATANEXTSCREEN";
	case MAPDATASECRETCOMBO: return "MAPDATASECRETCOMBO";
	case MAPDATASECRETCSET: return "MAPDATASECRETCSET";
	case MAPDATASECRETFLAG: return "MAPDATASECRETFLAG";
	case MAPDATAVIEWX: return "MAPDATAVIEWX";
	case MAPDATAVIEWY: return "MAPDATAVIEWY";
	case MAPDATASCREENWIDTH: return "MAPDATASCREENWIDTH";
	case MAPDATASCREENHEIGHT: return "MAPDATASCREENHEIGHT";
	case MAPDATAENTRYX: return "MAPDATAENTRYX";
	case MAPDATAENTRYY: return "MAPDATAENTRYY";
	case MAPDATANUMFF: return "MAPDATANUMFF";
	case MAPDATAFFDATA: return "MAPDATAFFDATA";
	case MAPDATAFFCSET: return "MAPDATAFFCSET";
	case MAPDATAFFDELAY: return "MAPDATAFFDELAY";
	case MAPDATAFFX: return "MAPDATAFFX";
	case MAPDATAFFY: return "MAPDATAFFY";
	case MAPDATAFFXDELTA: return "MAPDATAFFXDELTA";
	case MAPDATAFFYDELTA: return "MAPDATAFFYDELTA";
	case MAPDATAFFXDELTA2: return "MAPDATAFFXDELTA2";
	case MAPDATAFFYDELTA2: return "MAPDATAFFYDELTA2";
	case MAPDATAFFFLAGS: return "MAPDATAFFFLAGS";
	case MAPDATAFFWIDTH: return "MAPDATAFFWIDTH";
	case MAPDATAFFHEIGHT: return "MAPDATAFFHEIGHT";
	case MAPDATAFFLINK: return "MAPDATAFFLINK";
	case MAPDATAFFSCRIPT: return "MAPDATAFFSCRIPT";
	case MAPDATAINTID: return "MAPDATAINTID"; //needs to be a function; [32][10]
	case MAPDATAINITA: return "MAPDATAINITA"; //needs to be a function [32][2]
	case MAPDATAFFINITIALISED: return "MAPDATAFFINITIALISED";
	case MAPDATASCRIPTENTRY: return "MAPDATASCRIPTENTRY";
	case MAPDATASCRIPTOCCUPANCY: return "MAPDATASCRIPTOCCUPANCY";
	case MAPDATASCRIPTEXIT: return "MAPDATASCRIPTEXIT";
	case MAPDATAOCEANSFX: return "MAPDATAOCEANSFX";
	case MAPDATABOSSSFX: return "MAPDATABOSSSFX";
	case MAPDATASECRETSFX: return "MAPDATASECRETSFX";
	case MAPDATAHOLDUPSFX: return "MAPDATAHOLDUPSFX";
	case MAPDATASCREENMIDI: return "MAPDATASCREENMIDI";
	case MAPDATALENSLAYER: return "MAPDATALENSLAYER";
	
	case MAPDATACOMBODD: return "MAPDATACOMBODD";
	case MAPDATACOMBOCD: return "MAPDATACOMBOCD";
	case MAPDATACOMBOFD: return "MAPDATACOMBOFD";
	case MAPDATACOMBOTD: return "MAPDATACOMBOTD";
	case MAPDATACOMBOID: return "MAPDATACOMBOID";
	case MAPDATACOMBOSD: return "MAPDATACOMBOSD";
	
	
	
	case MAPDATAMISCD: return "MAPDATAMISCD";
	case MAPDATASCREENSTATED: return "MAPDATASCREENSTATED";
	case MAPDATASCREENFLAGSD: return "MAPDATASCREENFLAGSD";
	case MAPDATASCREENEFLAGSD: return "MAPDATASCREENEFLAGSD";
	
		
	case SCREENDATAVALID: return "SCREENDATAVALID";
	case SCREENDATAGUY: return "SCREENDATAGUY";
	case SCREENDATASTRING: return "SCREENDATASTRING";
	case SCREENDATAROOM: return "SCREENDATAROOM";
	case SCREENDATAITEM: return "SCREENDATAITEM";
	case SCREENDATAHASITEM: return "SCREENDATAHASITEM";
	case SCREENDATATILEWARPTYPE: return "SCREENDATATILEWARPTYPE";
	case SCREENDATATILEWARPOVFLAGS: return "SCREENDATATILEWARPOVFLAGS";
	case SCREENDATADOORCOMBOSET: return "SCREENDATADOORCOMBOSET";
	case SCREENDATAWARPRETX: return "SCREENDATAWARPRETX";
	case SCREENDATAWARPRETY: return "SCREENDATAWARPRETY";
	case SCREENDATAWARPRETURNC: return "SCREENDATAWARPRETURNC";
	case SCREENDATASTAIRX: return "SCREENDATASTAIRX";
	case SCREENDATASTAIRY: return "SCREENDATASTAIRY";
	case SCREENDATACOLOUR: return "SCREENDATACOLOUR";
	case SCREENDATAENEMYFLAGS: return "SCREENDATAENEMYFLAGS";
	case SCREENDATADOOR: return "SCREENDATADOOR";
	case SCREENDATATILEWARPDMAP: return "SCREENDATATILEWARPDMAP";
	case SCREENDATATILEWARPSCREEN: return "SCREENDATATILEWARPSCREEN";
	case SCREENDATAEXITDIR: return "SCREENDATAEXITDIR";
	case SCREENDATAENEMY: return "SCREENDATAENEMY";
	case SCREENDATAPATTERN: return "SCREENDATAPATTERN";
	case SCREENDATASIDEWARPTYPE: return "SCREENDATASIDEWARPTYPE";
	case SCREENDATASIDEWARPOVFLAGS: return "SCREENDATASIDEWARPOVFLAGS";
	case SCREENDATAWARPARRIVALX: return "SCREENDATAWARPARRIVALX";
	case SCREENDATAWARPARRIVALY: return "SCREENDATAWARPARRIVALY";
	case SCREENDATAPATH: return "SCREENDATAPATH";
	case SCREENDATASIDEWARPSC: return "SCREENDATASIDEWARPSC";
	case SCREENDATASIDEWARPDMAP: return "SCREENDATASIDEWARPDMAP";
	case SCREENDATASIDEWARPINDEX: return "SCREENDATASIDEWARPINDEX";
	case SCREENDATAUNDERCOMBO: return "SCREENDATAUNDERCOMBO";
	case SCREENDATAUNDERCSET: return "SCREENDATAUNDERCSET";
	case SCREENDATACATCHALL: return "SCREENDATACATCHALL";
	case SCREENDATAFLAGS: return "SCREENDATAFLAGS";
	case SCREENDATACSENSITIVE: return "SCREENDATACSENSITIVE";
	case SCREENDATANORESET: return "SCREENDATANORESET";
	case SCREENDATANOCARRY: return "SCREENDATANOCARRY";
	case SCREENDATALAYERMAP: return "SCREENDATALAYERMAP";
	case SCREENDATALAYERSCREEN: return "SCREENDATALAYERSCREEN";
	case SCREENDATALAYEROPACITY: return "SCREENDATALAYEROPACITY";
	case SCREENDATATIMEDWARPTICS: return "SCREENDATATIMEDWARPTICS";
	case SCREENDATANEXTMAP: return "SCREENDATANEXTMAP";
	case SCREENDATANEXTSCREEN: return "SCREENDATANEXTSCREEN";
	case SCREENDATASECRETCOMBO: return "SCREENDATASECRETCOMBO";
	case SCREENDATASECRETCSET: return "SCREENDATASECRETCSET";
	case SCREENDATASECRETFLAG: return "SCREENDATASECRETFLAG";
	case SCREENDATAVIEWX: return "SCREENDATAVIEWX";
	case SCREENDATAVIEWY: return "SCREENDATAVIEWY";
	case SCREENDATASCREENWIDTH: return "SCREENDATASCREENWIDTH";
	case SCREENDATASCREENHEIGHT: return "SCREENDATASCREENHEIGHT";
	case SCREENDATAENTRYX: return "SCREENDATAENTRYX";
	case SCREENDATAENTRYY: return "SCREENDATAENTRYY";
	case SCREENDATANUMFF: return "SCREENDATANUMFF";
	case SCREENDATAFFDATA: return "SCREENDATAFFDATA";
	case SCREENDATAFFCSET: return "SCREENDATAFFCSET";
	case SCREENDATAFFDELAY: return "SCREENDATAFFDELAY";
	case SCREENDATAFFX: return "SCREENDATAFFX";
	case SCREENDATAFFY: return "SCREENDATAFFY";
	case SCREENDATAFFXDELTA: return "SCREENDATAFFXDELTA";
	case SCREENDATAFFYDELTA: return "SCREENDATAFFYDELTA";
	case SCREENDATAFFXDELTA2: return "SCREENDATAFFXDELTA2";
	case SCREENDATAFFYDELTA2: return "SCREENDATAFFYDELTA2";
	case SCREENDATAFFFLAGS: return "SCREENDATAFFFLAGS";
	case SCREENDATAFFWIDTH: return "SCREENDATAFFWIDTH";
	case SCREENDATAFFHEIGHT: return "SCREENDATAFFHEIGHT";
	case SCREENDATAFFLINK: return "SCREENDATAFFLINK";
	case SCREENDATAFFSCRIPT: return "SCREENDATAFFSCRIPT";
	case SCREENDATAINTID: return "SCREENDATAINTID"; //needs to be a function; [32][10]
	case SCREENDATAINITA: return "SCREENDATAINITA"; //needs to be a function [32][2]
	case SCREENDATAFFINITIALISED: return "SCREENDATAFFINITIALISED";
	case SCREENDATASCRIPTENTRY: return "SCREENDATASCRIPTENTRY";
	case SCREENDATASCRIPTOCCUPANCY: return "SCREENDATASCRIPTOCCUPANCY";
	case SCREENDATASCRIPTEXIT: return "SCREENDATASCRIPTEXIT";
	case SCREENDATAOCEANSFX: return "SCREENDATAOCEANSFX";
	case SCREENDATABOSSSFX: return "SCREENDATABOSSSFX";
	case SCREENDATASECRETSFX: return "SCREENDATASECRETSFX";
	case SCREENDATAHOLDUPSFX: return "SCREENDATAHOLDUPSFX";
	case SCREENDATASCREENMIDI: return "SCREENDATASCREENMIDI";
	case SCREENDATALENSLAYER: return "SCREENDATALENSLAYER";
	
	case LINKSCRIPTTILE: return "LINKSCRIPTTILE";
	case LINKSCRIPFLIP: return "LINKSCRIPFLIP";
	case MAPDATAITEMX: return "MAPDATAITEMX";
	case MAPDATAITEMY: return "MAPDATAITEMY";
	case SCREENDATAITEMX: return "SCREENDATAITEMX";
	case SCREENDATAITEMY: return "SCREENDATAITEMY";
	
	case MAPDATAFFEFFECTWIDTH: return "MAPDATAFFEFFECTWIDTH";
	case MAPDATAFFEFFECTHEIGHT: return "MAPDATAFFEFFECTHEIGHT";
	case SCREENDATAFFEFFECTWIDTH: return "SCREENDATAFFEFFECTWIDTH";
	case SCREENDATAFFEFFECTHEIGHT: return "SCREENDATAFFEFFECTHEIGHT";
	case LOADMAPDATA: return "LOADMAPDATA";
	case CREATEBITMAP: return "CREATEBITMAP";
	case SHOPDATANAME: return "SHOPDATANAME";
	case SHOPDATAITEM: return "SHOPDATAITEM";
	case SHOPDATAHASITEM: return "SHOPDATAHASITEM";
	case SHOPDATAPRICE: return "SHOPDATAPRICE";
	case SHOPDATASTRING: return "SHOPDATASTRING";
	
	case AUDIOVOLUME: return "AUDIOVOLUME";
	case AUDIOPAN: return "AUDIOPAN";
	
	case MESSAGEDATANEXT: return "MESSAGEDATANEXT";
	case MESSAGEDATATILE: return "MESSAGEDATATILE";
	case MESSAGEDATACSET: return "MESSAGEDATACSET";
	case MESSAGEDATATRANS: return "MESSAGEDATATRANS";
	case MESSAGEDATAFONT: return "MESSAGEDATAFONT";
	case MESSAGEDATAX: return "MESSAGEDATAX";
	case MESSAGEDATAY: return "MESSAGEDATAY";
	case MESSAGEDATAW: return "MESSAGEDATAW";
	case MESSAGEDATAH: return "MESSAGEDATAH";
	case MESSAGEDATASFX: return "MESSAGEDATASFX";
	case MESSAGEDATALISTPOS: return "MESSAGEDATALISTPOS";
	case MESSAGEDATAVSPACE: return "MESSAGEDATAVSPACE";
	case MESSAGEDATAHSPACE: return "MESSAGEDATAHSPACE";
	case MESSAGEDATAFLAGS: return "MESSAGEDATAFLAGS";
	
	case DMAPDATAMAP: return "DMAPDATAMAP";
	case DMAPDATALEVEL: return "DMAPDATALEVEL";
	case DMAPDATAOFFSET: return "DMAPDATAOFFSET";
	case DMAPDATACOMPASS: return "DMAPDATACOMPASS";
	case DMAPDATAPALETTE: return "DMAPDATAPALETTE";
	case DMAPDATAMIDI: return "DMAPDATAMIDI";
	case DMAPDATACONTINUE: return "DMAPDATACONTINUE";
	case DMAPDATATYPE: return "DMAPDATATYPE";
	case DMAPDATAGRID: return "DMAPDATAGRID";
	case DMAPDATAMINIMAPTILE: return "DMAPDATAMINIMAPTILE";
	case DMAPDATAMINIMAPCSET: return "DMAPDATAMINIMAPCSET";
	case DMAPDATALARGEMAPTILE: return "DMAPDATALARGEMAPTILE";
	case DMAPDATALARGEMAPCSET: return "DMAPDATALARGEMAPCSET";
	case DMAPDATAMUISCTRACK: return "DMAPDATAMUISCTRACK";
	case DMAPDATASUBSCRA: return "DMAPDATASUBSCRA";
	case DMAPDATASUBSCRP: return "DMAPDATASUBSCRP";
	case DMAPDATADISABLEDITEMS: return "DMAPDATADISABLEDITEMS";
	case DMAPDATAFLAGS: return "DMAPDATAFLAGS";
	
	case ITEMPSTRING: return "ITEMPSTRING";
	case ITEMPSTRINGFLAGS: return "ITEMPSTRINGFLAGS";
	case ITEMOVERRIDEFLAGS: return "ITEMOVERRIDEFLAGS";
	
	
	case LINKPUSH: return "LINKPUSH";
	case LINKSTUN: return "LINKSTUN";
	case TYPINGMODE: return "TYPINGMODE";
//	case DMAPDATAGRAVITY: return "DMAPDATAGRAVITY";
//	case DMAPDATAJUMPLAYER: return "DMAPDATAJUMPLAYER";


	//newcombo struct
	case COMBODTILE: return "COMBODTILE";
	case COMBODFLIP: return "COMBODFLIP";
	case COMBODWALK: return "COMBODWALK";
	case COMBODTYPE: return "COMBODTYPE";
	case COMBODCSET: return "COMBODCSET";
	case COMBODFOO: return "COMBODFOO";
	case COMBODFRAMES: return "COMBODFRAMES";
	case COMBODNEXTD: return "COMBODNEXTD";
	case COMBODNEXTC: return "COMBODNEXTC";
	case COMBODFLAG: return "COMBODFLAG";
	case COMBODSKIPANIM: return "COMBODSKIPANIM";
	case COMBODNEXTTIMER: return "COMBODNEXTTIMER";
	case COMBODAKIMANIMY: return "COMBODAKIMANIMY";
	case COMBODANIMFLAGS: return "COMBODANIMFLAGS";
	case COMBODEXPANSION: return "COMBODEXPANSION";
	case COMBODATTRIBUTES: return "COMBODATTRIBUTES";
	case COMBODUSRFLAGS: return "COMBODUSRFLAGS";
	case COMBODTRIGGERFLAGS: return "COMBODTRIGGERFLAGS";
	case COMBODTRIGGERLEVEL: return "COMBODTRIGGERLEVEL";

	//comboclass struct
	case COMBODNAME: return "COMBODNAME";
	case COMBODBLOCKNPC: return "COMBODBLOCKNPC";
	case COMBODBLOCKHOLE: return "COMBODBLOCKHOLE";
	case COMBODBLOCKTRIG: return "COMBODBLOCKTRIG";
	case COMBODBLOCKWEAPON: return "COMBODBLOCKWEAPON";
	case COMBODCONVXSPEED: return "COMBODCONVXSPEED";
	case COMBODCONVYSPEED: return "COMBODCONVYSPEED";
	case COMBODSPAWNNPC: return "COMBODSPAWNNPC";
	case COMBODSPAWNNPCWHEN: return "COMBODSPAWNNPCWHEN";
	case COMBODSPAWNNPCCHANGE: return "COMBODSPAWNNPCCHANGE";
	case COMBODDIRCHANGETYPE: return "COMBODDIRCHANGETYPE";
	case COMBODDISTANCECHANGETILES: return "COMBODDISTANCECHANGETILES";
	case COMBODDIVEITEM: return "COMBODDIVEITEM";
	case COMBODDOCK: return "COMBODDOCK";
	case COMBODFAIRY: return "COMBODFAIRY";
	case COMBODFFATTRCHANGE: return "COMBODFFATTRCHANGE";
	case COMBODFOORDECOTILE: return "COMBODFOORDECOTILE";
	case COMBODFOORDECOTYPE: return "COMBODFOORDECOTYPE";
	case COMBODHOOKSHOTPOINT: return "COMBODHOOKSHOTPOINT";
	case COMBODLADDERPASS: return "COMBODLADDERPASS";
	case COMBODLOCKBLOCK: return "COMBODLOCKBLOCK";
	case COMBODLOCKBLOCKCHANGE: return "COMBODLOCKBLOCKCHANGE";
	case COMBODMAGICMIRROR: return "COMBODMAGICMIRROR";
	case COMBODMODHPAMOUNT: return "COMBODMODHPAMOUNT";
	case COMBODMODHPDELAY: return "COMBODMODHPDELAY";
	case COMBODMODHPTYPE: return "COMBODMODHPTYPE";
	case COMBODNMODMPAMOUNT: return "COMBODNMODMPAMOUNT";
	case COMBODMODMPDELAY: return "COMBODMODMPDELAY";
	case COMBODMODMPTYPE: return "COMBODMODMPTYPE";
	case COMBODNOPUSHBLOCK: return "COMBODNOPUSHBLOCK";
	case COMBODOVERHEAD: return "COMBODOVERHEAD";
	case COMBODPLACENPC: return "COMBODPLACENPC";
	case COMBODPUSHDIR: return "COMBODPUSHDIR";
	case COMBODPUSHWAIT: return "COMBODPUSHWAIT";
	case COMBODPUSHHEAVY: return "COMBODPUSHHEAVY";
	case COMBODPUSHED: return "COMBODPUSHED";
	case COMBODRAFT: return "COMBODRAFT";
	case COMBODRESETROOM: return "COMBODRESETROOM";
	case COMBODSAVEPOINTTYPE: return "COMBODSAVEPOINTTYPE";
	case COMBODSCREENFREEZETYPE: return "COMBODSCREENFREEZETYPE";
	case COMBODSECRETCOMBO: return "COMBODSECRETCOMBO";
	case COMBODSINGULAR: return "COMBODSINGULAR";
	case COMBODSLOWWALK: return "COMBODSLOWWALK";
	case COMBODSTATUETYPE: return "COMBODSTATUETYPE";
	case COMBODSTEPTYPE: return "COMBODSTEPTYPE";
	case COMBODSTEPCHANGEINTO: return "COMBODSTEPCHANGEINTO";
	case COMBODSTRIKEWEAPONS: return "COMBODSTRIKEWEAPONS";
	case COMBODSTRIKEREMNANTS: return "COMBODSTRIKEREMNANTS";
	case COMBODSTRIKEREMNANTSTYPE: return "COMBODSTRIKEREMNANTSTYPE";
	case COMBODSTRIKECHANGE: return "COMBODSTRIKECHANGE";
	case COMBODSTRIKEITEM: return "COMBODSTRIKEITEM";
	case COMBODTOUCHITEM: return "COMBODTOUCHITEM";
	case COMBODTOUCHSTAIRS: return "COMBODTOUCHSTAIRS";
	case COMBODTRIGGERTYPE: return "COMBODTRIGGERTYPE";
	case COMBODTRIGGERSENS: return "COMBODTRIGGERSENS";
	case COMBODWARPTYPE: return "COMBODWARPTYPE";
	case COMBODWARPSENS: return "COMBODWARPSENS";
	case COMBODWARPDIRECT: return "COMBODWARPDIRECT";
	case COMBODWARPLOCATION: return "COMBODWARPLOCATION";
	case COMBODWATER: return "COMBODWATER";
	case COMBODWHISTLE: return "COMBODWHISTLE";
	case COMBODWINGAME: return "COMBODWINGAME";
	case COMBODBLOCKWPNLEVEL: return "COMBODBLOCKWPNLEVEL";
	case LINKHITBY: return "LINKHITBY";
	case LINKDEFENCE: return "LINKDEFENCE";
	case NPCHITBY: return "NPCHITBY";
	case NPCISCORE: return "NPCISCORE";
	case NPCSCRIPTUID: return "NPCSCRIPTUID";
	case LWEAPONSCRIPTUID: return "LWEAPONSCRIPTUID";
	case EWEAPONSCRIPTUID: return "EWEAPONSCRIPTUID";
	case ITEMSCRIPTUID: return "ITEMSCRIPTUID";
	case DMAPDATASIDEVIEW: return "DMAPDATASIDEVIEW";
	
	
	case DONULL: return "DONULL";
	case DEBUGD: return "DEBUGD";
	case GETPIXEL: return "GETPIXEL";
	case DOUNTYPE: return "DOUNTYPE";
	case LINKTILEMOD: return "LINKTILEMOD";
	case NPCINITD: return "NPCINITD";
	
	case NPCCOLLISION: return "NPCCOLLISION";
	case NPCLINEDUP: return "NPCLINEDUP";
	case NPCDATAINITD: return "NPCDATAINITD";
	case NPCDATASCRIPT: return "NPCDATASCRIPT";
	case NPCMATCHINITDLABEL: return "NPCMATCHINITDLABEL";
	//lweapon scripts
	case LWPNSCRIPT: return "LWPNSCRIPT";
	case LWPNINITD: return "LWPNINITD";
	case ITEMFAMILY: return "ITEMFAMILY";
	case ITEMLEVEL: return "ITEMLEVEL";
	
	case EWPNSCRIPT: return "EWPNSCRIPT";
	case EWPNINITD: return "EWPNINITD";
	case NPCSCRIPT: return "NPCSCRIPT";
	case DMAPSCRIPT: return "DMAPSCRIPT";
	case DMAPINITD: return "DMAPINITD";
	case SCREENSCRIPT: return "SCREENSCRIPT";
	case SCREENINITD: return "SCREENINITD";
	case LINKINITD: return "LINKINITD";
	case NPCDATAWEAPONINITD: return "NPCDATAWEAPONINITD";
	case NPCDATAWEAPONSCRIPT: return "NPCDATAWEAPONSCRIPT";
	
	case NPCSCRIPTTILE: return "NPCSCRIPTTILE";
	case NPCSCRIPTFLIP: return "NPCSCRIPTFLIP";
	case LWPNSCRIPTTILE: return "LWPNSCRIPTTILE";
	case LWPNSCRIPTFLIP: return "LWPNSCRIPTFLIP";
	case EWPNSCRIPTTILE: return "EWPNSCRIPTTILE";
	case EWPNSCRIPTFLIP: return "EWPNSCRIPTFLIP";
	
	case LINKENGINEANIMATE: return "LINKENGINEANIMATE";
	case NPCENGINEANIMATE: return "NPCENGINEANIMATE";
	case LWPNENGINEANIMATE: return "LWPNENGINEANIMATE";
	case EWPNENGINEANIMATE: return "EWPNENGINEANIMATE";
	
	case SKIPCREDITS: return "SKIPCREDITS";
	case SKIPF6: return "SKIPF6";
	case LWPNUSEWEAPON: return "LWPNUSEWEAPON";
	case LWPNUSEDEFENCE: return "LWPNUSEDEFENCE";

	case LWPNROTATION: return "LWPNROTATION";
	case EWPNROTATION: return "EWPNROTATION";
	case NPCROTATION: return "NPCROTATION";
	case ITEMROTATION: return "ITEMROTATION";
	case LINKROTATION: return "LINKROTATION";
	
	case LWPNSCALE: return "LWPNSCALE";
	case EWPNSCALE: return "EWPNSCALE";
	case NPCSCALE: return "NPCSCALE";
	case ITEMSCALE: return "ITEMSCALE";
	case LINKSCALE: return "LINKSCALE";
	case ITEMSPRITESCRIPT: return "ITEMSPRITESCRIPT";
	case FFRULE: return "FFRULE";
	case NUMDRAWS: return "NUMDRAWS";
	case MAXDRAWS: return "MAXDRAWS";
	case BITMAPWIDTH: return "BITMAPWIDTH";
	case BITMAPHEIGHT: return "BITMAPHEIGHT";
	case ALLOCATEBITMAPR: return "ALLOCATEBITMAPR";
	case KEYMODIFIERS: return "KEYMODIFIERS";
	case SIMULATEKEYPRESS: return "SIMULATEKEYPRESS";
	case KEYBINDINGS: return "KEYBINDINGS";
	
	case MAPDATASCRIPT: return "MAPDATASCRIPT";
	
	case MAPDATAINITDARRAY: return "MAPDATAINITDARRAY";
	
	
	
    default:
    {
        sprintf(temp, "d%d", ID);
        return string(temp);
    }
    }
}

string GlobalArgument::toString()
{
    char temp[40];
    sprintf(temp, "gd%d", ID);
    return string(temp);
}

string LabelArgument::toString()
{
    if(!haslineno)
    {
        char temp[40];
        sprintf(temp, "l%d", ID);
        return string(temp);
    }
    else
    {
        char temp[40];
        sprintf(temp, "%d", lineno);
        return string(temp);
    }
}

string LabelArgument::toStringSetV()
{
    if(!haslineno)
    {
        char temp[40];
        sprintf(temp, "l%d", ID);
        return string(temp);
    }
    else
    {
        char temp[40];
        sprintf(temp, "%.4f", lineno * 0.0001f);
        return string(temp);
    }
}

string OSetTrue::toString()
{
    return "SETTRUE " + getArgument()->toString();
}

string OSetTrueI::toString()
{
    return "SETTRUEI " + getArgument()->toString();
}

string OSetFalse::toString()
{
    return "SETFALSE " + getArgument()->toString();
}

string OSetFalseI::toString()
{
    return "SETFALSEI " + getArgument()->toString();
}

string OSetMore::toString()
{
    return "SETMORE " + getArgument()->toString();
}

string OSetMoreI::toString()
{
    return "SETMOREI " + getArgument()->toString();
}

string OSetLess::toString()
{
    return "SETLESS " + getArgument()->toString();
}

string OSetLessI::toString()
{
    return "SETLESSI " + getArgument()->toString();
}

string OSetImmediate::toString()
{
	ostringstream oss;
	oss << "SETV " << getFirstArgument()->toString() << ",";
	Argument* second = getSecondArgument();
	if (LabelArgument* label = dynamic_cast<LabelArgument*>(second))
		oss << label->toStringSetV();
	else
		oss << second->toString();
	return oss.str();
}

string OSetRegister::toString()
{
    return "SETR " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}

string OAddImmediate::toString()
{
    return "ADDV " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}

string OAddRegister::toString()
{
    return "ADDR " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}

string OSubImmediate::toString()
{
    return "SUBV " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}

string OSubRegister::toString()
{
    return "SUBR " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}

string OMultImmediate::toString()
{
    return "MULTV " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}


string OMultRegister::toString()
{
    return "MULTR " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}

string ODivImmediate::toString()
{
    return "DIVV " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}

string ODivRegister::toString()
{
    return "DIVR " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}

string OCompareImmediate::toString()
{
    return "COMPAREV " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}

string OCompareRegister::toString()
{
    return "COMPARER " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}

string OWaitframe::toString()
{
    return "WAITFRAME";
}

string OWaitdraw::toString()
{
    return "WAITDRAW";
}

string ONoOp::toString()
{
	return "NOP";
}

string OCastBoolI::toString()
{
	return "CASTBOOLI " + getArgument()->toString();
}

string OCastBoolF::toString()
{
	return "CASTBOOLF " + getArgument()->toString();
}

//I would like to add a Jump instruction tot he parser, which would be 'GOTOLABEL' -Z
string OGotoImmediate::toString()
{
    return "GOTO " + getArgument()->toString();
}

string OGotoTrueImmediate::toString()
{
    return "GOTOTRUE " + getArgument()->toString();
}

string OGotoFalseImmediate::toString()
{
    return "GOTOFALSE " + getArgument()->toString();
}

string OGotoMoreImmediate::toString()
{
    return "GOTOMORE " + getArgument()->toString();
}

string OGotoLessImmediate::toString()
{
    return "GOTOLESS " + getArgument()->toString();
}

string OPushRegister::toString()
{
    return "PUSHR " + getArgument()->toString();
}

string OPushImmediate::toString()
{
	ostringstream oss;
	oss << "PUSHV ";
	Argument* arg = getArgument();
	if (LabelArgument* label = dynamic_cast<LabelArgument*>(arg))
		oss << label->toStringSetV();
	else
		oss << arg->toString();
	return oss.str();
    return "PUSHV " + getArgument()->toString();
}

string OPopRegister::toString()
{
    return "POP " + getArgument()->toString();
}

string OLoadIndirect::toString()
{
    return "LOADI " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}

string OStoreIndirect::toString()
{
    return "STOREI " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}

string OQuit::toString()
{
    return "QUIT";
}

string OGotoRegister::toString()
{
    return "GOTOR " + getArgument()->toString();
}

string OAndImmediate::toString()
{
    return "ANDV " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}

string OAndRegister::toString()
{
    return "ANDR " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}

string OOrImmediate::toString()
{
    return "ORV " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}

string OOrRegister::toString()
{
    return "ORR " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}

string OXorImmediate::toString()
{
    return "XORV " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}

string OXorRegister::toString()
{
    return "XORR " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}

string OSinRegister::toString()
{
    return "SINR " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}

string OCosRegister::toString()
{
    return "COSR " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}

string OTanRegister::toString()
{
    return "TANR " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}

string Ostrlen::toString()
{
    return "STRINGLENGTH " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}

string OATanRegister::toString()
{
    return "ARCTANR " + getArgument()->toString();
}

string OArcCosRegister::toString()
{
    return "ARCCOSR " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}

string OArcSinRegister::toString()
{
    return "ARCSINR " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}

string OMinRegister::toString()
{
    return "MINR " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}

string OMaxRegister::toString()
{
    return "MAXR " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}

string OPowRegister::toString()
{
    return "POWERR " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}

string OInvPowRegister::toString()
{
    return "IPOWERR " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}

string OFactorial::toString()
{
    return "FACTORIAL " + getArgument()->toString();
}

string OAbsRegister::toString()
{
    return "ABS " + getArgument()->toString();
}

string OLog10Register::toString()
{
    return "LOG10 " + getArgument()->toString();
}

string OLogERegister::toString()
{
    return "LOGE " + getArgument()->toString();
}

string OArraySize::toString()
{
    return "ARRAYSIZE " + getArgument()->toString();
}


string OArraySizeF::toString()
{
    return "ARRAYSIZEF " + getArgument()->toString();
}
string OArraySizeN::toString()
{
    return "ARRAYSIZEN " + getArgument()->toString();
}
string OArraySizeE::toString()
{
    return "ARRAYSIZEE " + getArgument()->toString();
}
string OArraySizeL::toString()
{
    return "ARRAYSIZEL " + getArgument()->toString();
}
string OArraySizeB::toString()
{
    return "ARRAYSIZEB " + getArgument()->toString();
}
string OArraySizeI::toString()
{
    return "ARRAYSIZEI " + getArgument()->toString();
}
string OArraySizeID::toString()
{
    return "ARRAYSIZEID " + getArgument()->toString();
}


string OCalcSplineRegister::toString()
{
    return "CALCSPLINER" + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}

string OSetColorRegister::toString()
{
    return "SETCOLORR";
}

string OSetDepthRegister::toString()
{
    return "SETDEPTHR";
}

string OCollisionRectRegister::toString()
{
    return "COLLISIONRECTR" + getArgument()->toString();
}

string OCollisionBoxRegister::toString()
{
    return "COLLISIONBOXR" + getArgument()->toString();
}

string OLShiftImmediate::toString()
{
    return "LSHIFTV " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}

string OLShiftRegister::toString()
{
    return "LSHIFTR " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}

string ORShiftImmediate::toString()
{
    return "RSHIFTV " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}

string ORShiftRegister::toString()
{
    return "RSHIFTR " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}

string OModuloImmediate::toString()
{
    return "MODV " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}

string OModuloRegister::toString()
{
    return "MODR " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}

string ONot::toString()
{
    return "BITNOT " + getArgument()->toString();
}

string OTraceRegister::toString()
{
    return "TRACER " + getArgument()->toString();
}

string OTrace2Register::toString()
{
    return "TRACE2R " + getArgument()->toString();
}

string OTrace3::toString()
{
    return "TRACE3";
}

string OTrace4::toString()
{
    return "TRACE4";
}

string OTrace5Register::toString()
{
    return "TRACE5";
}

string OTrace6Register::toString()
{
    return "TRACE6 " + getArgument()->toString();
}


string ORandRegister::toString()
{
    return "RNDR " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}

string OCheckTrig::toString()
{
    return "CHECKTRIG";
}

string OWarp::toString()
{
    return "WARPR " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}

string OPitWarp::toString()
{
    return "PITWARPR " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}

string OSqrtRegister::toString()
{
    return "SQROOTR " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}

string OCreateItemRegister::toString()
{
    return "CREATEITEMR " + getArgument()->toString();
}

string OCreateNPCRegister::toString()
{
    return "CREATENPCR " + getArgument()->toString();
}

string OCreateLWpnRegister::toString()
{
    return "CREATELWEAPONR " + getArgument()->toString();
}

string OCreateEWpnRegister::toString()
{
    return "CREATEEWEAPONR " + getArgument()->toString();
}

string OLoadItemRegister::toString()
{
    return "LOADITEMR " + getArgument()->toString();
}

string OLoadItemDataRegister::toString()
{
    return "LOADITEMDATAR " + getArgument()->toString();
}

//New Types

string OLoadShopDataRegister::toString()
{
    return "LOADSHOPR " + getArgument()->toString();
}
string OLoadInfoShopDataRegister::toString()
{
    return "LOADINFOSHOPR " + getArgument()->toString();
}
string OLoadMessageDataRegister::toString()
{
    return "LOADMESSAGEDATAR " + getArgument()->toString();
}

string OLoadDMapDataRegister::toString()
{
    return "LOADDMAPDATAR " + getArgument()->toString();
}

string ODMapDataGetNameRegister::toString()
{
    return "DMAPDATAGETNAMER " + getArgument()->toString();
}

string ODMapDataSetNameRegister::toString()
{
    return "DMAPDATASETNAMER " + getArgument()->toString();
}

string ODMapDataGetTitleRegister::toString()
{
    return "DMAPDATAGETTITLER " + getArgument()->toString();
}

string ODMapDataSetTitleRegister::toString()
{
    return "DMAPDATASETTITLER " + getArgument()->toString();
}

string ODMapDataGetIntroRegister::toString()
{
    return "DMAPDATAGETINTROR " + getArgument()->toString();
}

string ODMapDataSetIntroRegister::toString()
{
    return "DMAPDATANSETITROR " + getArgument()->toString();
}

string ODMapDataGetMusicRegister::toString()
{
    return "DMAPDATAGETMUSICR " + getArgument()->toString();
}

string ODMapDataSetMusicRegister::toString()
{
    return "DMAPDATASETMUSICR " + getArgument()->toString();
}

string OMessageDataSetStringRegister::toString()
{
    return "MESSAGEDATASETSTRINGR " + getArgument()->toString();
}
string OMessageDataGetStringRegister::toString()
{
    return "MESSAGEDATAGETSTRINGR " + getArgument()->toString();
}
string OLoadNPCDataRegister::toString()
{
    return "LOADNPCDATAR " + getArgument()->toString();
}
string OLoadComboDataRegister::toString()
{
    return "LOADCOMBODATAR " + getArgument()->toString();
}
string OLoadMapDataRegister::toString()
{
    return "LOADMAPDATAR " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}
string OLoadSpriteDataRegister::toString()
{
    return "LOADSPRITEDATAR " + getArgument()->toString();
}
string OLoadScreenDataRegister::toString()
{
    return "LOADSCREENDATAR " + getArgument()->toString();
}
string OLoadBitmapDataRegister::toString()
{
    return "LOADBITMAPDATAR " + getArgument()->toString();
}

string OLoadNPCRegister::toString()
{
    return "LOADNPCR " + getArgument()->toString();
}

string OLoadLWpnRegister::toString()
{
    return "LOADLWEAPONR " + getArgument()->toString();
}

string OLoadEWpnRegister::toString()
{
    return "LOADEWEAPONR " + getArgument()->toString();
}
string OAdjustVolumeRegister::toString()
{
    return "ADJUSTVOLUMER " + getArgument()->toString();
}
string OAdjustSFXVolumeRegister::toString()
{
    return "ADJUSTSFXVOLUMER " + getArgument()->toString();
}
string OPlaySoundRegister::toString()
{
    return "PLAYSOUNDR " + getArgument()->toString();
}

string OPlayMIDIRegister::toString()
{
    return "PLAYMIDIR " + getArgument()->toString();
}

string OPlayEnhancedMusic::toString()
{
    return "PLAYENHMUSIC " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}

string OPlayEnhancedMusicEx::toString()
{
    return "PLAYENHMUSICEX " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}

string OGetEnhancedMusicPos::toString()
{
    return "GETENHMUSICPOS " + getArgument()->toString();
}

string OSetEnhancedMusicPos::toString()
{
    return "SETENHMUSICPOS " + getArgument()->toString();
}

string OSetEnhancedMusicSpeed::toString()
{
    return "SETENHMUSICSPEED " + getArgument()->toString();
}

string OGetDMapMusicFilename::toString()
{
    return "GETMUSICFILE " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}

string OGetNPCDataInitDLabel::toString()
{
    return "NPCGETINITDLABEL " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}

string OGetDMapMusicTrack::toString()
{
    return "GETMUSICTRACK " + getArgument()->toString();
}

// Audio->
string OEndSoundRegister::toString()
{
    return "ENDSOUNDR " + getArgument()->toString();
}


string OContinueSFX::toString()
{
    return "CONTINUESFX " + getArgument()->toString();
}

string OPauseSoundRegister::toString()
{
    return "PAUSESOUNDR " + getArgument()->toString();
}

string OPauseMusic::toString()
{
    return "PAUSEMUSIC";
}
string OResumeMusic::toString()
{
    return "RESUMEMUSIC";
}

string OResumeSoundRegister::toString()
{
    return "RESUMESOUNDR " + getArgument()->toString();
}

//END Audio

string OSetDMapEnhancedMusic::toString()
{
    return "SETDMAPENHMUSIC";
}

string OGetSaveName::toString()
{
    return "GETSAVENAME " + getArgument()->toString();
}

string OSetSaveName::toString()
{
    return "SETSAVENAME " + getArgument()->toString();
}

string OGetDMapName::toString()
{
    return "GETDMAPNAME " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}

string OGetDMapTitle::toString()
{
    return "GETDMAPTITLE " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}

string OGetDMapIntro::toString()
{
    return "GETDMAPINTRO " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}


string OSetDMapName::toString()
{
    return "SETDMAPNAME " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}

string OSetDMapTitle::toString()
{
    return "SETDMAPTITLE " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}

string OSetDMapIntro::toString()
{
    return "SETDMAPINTRO " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}

string OGetItemName::toString()
{
    return "ITEMNAME " + getArgument()->toString();
}

string OGetNPCName::toString()
{
    return "NPCNAME " + getArgument()->toString();
}

string OGetMessage::toString()
{
    return "GETMESSAGE " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}


string OSetMessage::toString()
{
    return "SETMESSAGE " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}

string OClearSpritesRegister::toString()
{
    return "CLEARSPRITESR " + getArgument()->toString();
}

string ORectangleRegister::toString()
{
    return "RECT";
}

string OCircleRegister::toString()
{
    return "CIRCLE";
}

string OArcRegister::toString()
{
    return "ARC";
}

string OEllipseRegister::toString()
{
    return "ELLIPSE";
}

string OLineRegister::toString()
{
    return "LINE";
}

string OSplineRegister::toString()
{
    return "SPLINE";
}

string OPutPixelRegister::toString()
{
    return "PUTPIXEL";
}

string OPutPixelArrayRegister::toString()
{
    return "PIXELARRAYR";
}

string OPutTileArrayRegister::toString()
{
    return "TILEARRAYR";
}

string OPutLinesArrayRegister::toString()
{
    return "LINESARRAY";
}

string ODrawCharRegister::toString()
{
    return "DRAWCHAR";
}

string ODrawIntRegister::toString()
{
    return "DRAWINT";
}

string ODrawTileRegister::toString()
{
    return "DRAWTILE";
}

string ODrawComboRegister::toString()
{
    return "DRAWCOMBO";
}

string OFastTileRegister::toString()
{
    return "FASTTILE";
}

string OFastComboRegister::toString()
{
    return "FASTCOMBO";
}

string OFastComboArrayRegister::toString()
{
    return "COMBOARRAYR";
}

string ODrawStringRegister::toString()
{
    return "DRAWSTRING";
}

string ODrawBitmapRegister::toString()
{
    return "DRAWBITMAP";
}

string ODrawBitmapExRegister::toString()
{
    return "BITMAPEXR";
}

string OSetRenderTargetRegister::toString()
{
    return "SETRENDERTARGET";
}

string OSetDepthBufferRegister::toString()
{
    return "SETDEPTHB";
}

string OGetDepthBufferRegister::toString()
{
    return "GETDEPTHB";
}

string OSetColorBufferRegister::toString()
{
    return "SETCOLORB";
}

string OGetColorBufferRegister::toString()
{
    return "GETCOLORB";
}

string OQuadRegister::toString()
{
    return "QUAD";
}

string OTriangleRegister::toString()
{
    return "TRIANGLE";
}


string OQuad3DRegister::toString()
{
    return "QUAD3D";
}

string OTriangle3DRegister::toString()
{
    return "TRIANGLE3D";
}

string ODrawLayerRegister::toString()
{
    return "DRAWLAYER";
}

string ODrawScreenRegister::toString()
{
    return "DRAWSCREEN";
}

string OMessageRegister::toString()
{
    return "MSGSTRR " + getArgument()->toString();
}

string OIsSolid::toString()
{
    return "ISSOLID " + getArgument()->toString();
}

string OIsSolidMapdata::toString()
{
    return "MAPDATAISSOLID " + getArgument()->toString();
}

string OSetSideWarpRegister::toString()
{
    return "SETSIDEWARP";
}

string OGetSideWarpDMap::toString()
{
    return "GETSIDEWARPDMAP " + getArgument()->toString();
}

string OGetSideWarpScreen::toString()
{
    return "GETSIDEWARPSCR " + getArgument()->toString();
}

string OGetSideWarpType::toString()
{
    return "GETSIDEWARPTYPE " + getArgument()->toString();
}

string OGetTileWarpDMap::toString()
{
    return "GETTILEWARPDMAP " + getArgument()->toString();
}

string OGetTileWarpScreen::toString()
{
    return "GETTILEWARPSCR " + getArgument()->toString();
}

string OGetTileWarpType::toString()
{
    return "GETTILEWARPTYPE " + getArgument()->toString();
}

string OSetTileWarpRegister::toString()
{
    return "SETTILEWARP";
}

string OLayerScreenRegister::toString()
{
    return "LAYERSCREEN " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}

string OLayerMapRegister::toString()
{
    return "LAYERMAP " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}

string OTriggerSecrets::toString()
{
    return "SECRETS";
}

string OIsValidItem::toString()
{
    return "ISVALIDITEM " + getArgument()->toString();
}

string OIsValidNPC::toString()
{
    return "ISVALIDNPC " + getArgument()->toString();
}

string OCopyTileRegister::toString()
{
    return "COPYTILERR " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}

string Ostrcpy::toString()
{
    return "STRINGCOPY " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}

string OOverlayTileRegister::toString()
{
    return "OVERLAYTILERR " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}

string OSwapTileRegister::toString()
{
    return "SWAPTILERR " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}

string OClearTileRegister::toString()
{
    return "CLEARTILER " + getArgument()->toString();
}

string OIsValidLWpn::toString()
{
    return "ISVALIDLWPN " + getArgument()->toString();
}

string OIsValidEWpn::toString()
{
    return "ISVALIDEWPN " + getArgument()->toString();
}

string OUseSpriteLWpn::toString()
{
    return "LWPNUSESPRITER " + getArgument()->toString();
}

string OUseSpriteEWpn::toString()
{
    return "EWPNUSESPRITER " + getArgument()->toString();
}

string OAllocateMemRegister::toString()
{
    return "ALLOCATEMEMR " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}

string OAllocateMemImmediate::toString()
{
    return "ALLOCATEMEMV " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}

string OAllocateGlobalMemImmediate::toString()
{
    return "ALLOCATEGMEMV " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}

string OAllocateGlobalMemRegister::toString()
{
    return "ALLOCATEGMEMR " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}

string ODeallocateMemRegister::toString()
{
    return "DEALLOCATEMEMR " + getArgument()->toString();
}

string ODeallocateMemImmediate::toString()
{
    return "DEALLOCATEMEMV " + getArgument()->toString();
}

string OSave::toString()
{
    return "SAVE";
}

string OGetScreenFlags::toString()
{
    return "GETSCREENFLAGS " + getArgument()->toString();
}

string OGetScreenEFlags::toString()
{
    return "GETSCREENEFLAGS " + getArgument()->toString();
}

string OEnd::toString()
{
    return "GAMEEND";
}

string OGameContinue::toString()
{
    return "GAMECONTINUE";
}

string OShowF6Screen::toString()
{
    return "SHOWF6SCREEN";
}

string OComboTile::toString()
{
    return "COMBOTILE " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}

string OBreakShield::toString()
{
    return "BREAKSHIELD " + getArgument()->toString();
}

string OShowSaveScreen::toString()
{
    return "SAVESCREEN " + getArgument()->toString();
}

string OShowSaveQuitScreen::toString()
{
    return "SAVEQUITSCREEN";
}

string OSelectAWeaponRegister::toString()
{
    return "SELECTAWPNR " + getArgument()->toString();
}

string OSelectBWeaponRegister::toString()
{
    return "SELECTBWPNR " + getArgument()->toString();
}

string OGetFFCScript::toString()
{
    return "GETFFCSCRIPT " + getArgument()->toString();
}

//2.54

string OGreyscaleOn::toString()
{
    return "GREYSCALEON";
}

string OGreyscaleOff::toString()
{
    return "GREYSCALEOFF";
}

string OZapIn::toString()
{
    return "ZAPIN";
}

string OZapOut::toString()
{
    return "ZAPOUT";
}

//These need to be unary opcodes that accept bool linkvisible. 
string OWavyIn::toString()
{
    return "WAVYIN";
}

string OWavyOut::toString()
{
    return "WAVYOUT";
}

string OOpenWipe::toString()
{
    return "OPENWIPE";
}

//Game->GetItemScript(int ptr[])
string OGetItemScript::toString()
{
    return "GETITEMSCRIPT " + getArgument()->toString();
}


string OGetLWeaponPointer::toString()
{
    return "LWPNARRPTR " + getArgument()->toString();
}

string OSetLWeaponPointer::toString()
{
    return "LWPNARRPTR2 " + getArgument()->toString();
}

string OGetEWeaponPointer::toString()
{
    return "EWPNARRPTR " + getArgument()->toString();
}

string OSetEWeaponPointer::toString()
{
    return "EWPNARRPTR2 " + getArgument()->toString();
}

string OGetItemPointer::toString()
{
    return "ITEMARRPTR " + getArgument()->toString();
}

string OSetItemPointer::toString()
{
    return "ITEMARRPTR2 " + getArgument()->toString();
}

string OGetItemDataPointer::toString()
{
    return "IDATAARRPTR " + getArgument()->toString();
}

string OSetItemDataPointer::toString()
{
    return "IDATAARRPTR2 " + getArgument()->toString();
}

string OGetFFCPointer::toString()
{
    return "FFCARRPTR " + getArgument()->toString();
}

string OSetFFCPointer::toString()
{
    return "FFCARRPTR2 " + getArgument()->toString();
}

string OGetBoolPointer::toString()
{
    return "BOOLARRPTR " + getArgument()->toString();
}

string OSetBoolPointer::toString()
{
    return "BOOLARRPTR2 " + getArgument()->toString();
}

string OGetNPCPointer::toString()
{
    return "NPCARRPTR " + getArgument()->toString();
}

string OSetNPCPointer::toString()
{
    return "NPCARRPTR2 " + getArgument()->toString();
}


string OGetScreenDoor::toString()
{
    return "GETSCREENDOOR " + getArgument()->toString();
}

string OGetScreenEnemy::toString()
{
    return "GETSCREENENEMY " + getArgument()->toString();
}


string OGetScreenLayerOpacity::toString()
{
    return "GETSCREENLAYOP " + getArgument()->toString();
}

string OGetScreenSecretCombo::toString()
{
    return "GETSCREENSECCMB " + getArgument()->toString();
}

string OGetScreenSecretCSet::toString()
{
    return "GETSCREENSECCST " + getArgument()->toString();
}

string OGetScreenSecretFlag::toString()
{
    return "GETSCREENSECFLG " + getArgument()->toString();
}

string OGetScreenLayerMap::toString()
{
    return "GETSCREENLAYMAP " + getArgument()->toString();
}

string OGetScreenLayerScreen::toString()
{
    return "GETSCREENLAYSCR " + getArgument()->toString();
}

string OGetScreenPath::toString()
{
    return "GETSCREENPATH " + getArgument()->toString();
}

string OGetScreenWarpReturnX::toString()
{
    return "GETSCREENWARPRX " + getArgument()->toString();
}

string OGetScreenWarpReturnY::toString()
{
    return "GETSCREENWARPRY " + getArgument()->toString();
}

string OTriggerSecretRegister::toString()
{
    return "TRIGGERSECRETR " + getArgument()->toString();
}

string OBMPPolygonRegister::toString()
{
    return "BMPPOLYGONR";
}

string OPolygonRegister::toString()
{
    return "POLYGONR";
}

string OChangeFFCScriptRegister::toString()
{
    return "CHANGEFFSCRIPTR " + getArgument()->toString();
}


//NPCData

string ONDataBaseTile::toString()
{
    return "GETNPCDATATILE " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataEHeight::toString()
{
    return "GETNPCDATAEHEIGHT " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}

string ONDataFlags::toString()
{
    return "GETNPCDATAFLAGS " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataFlags2::toString()
{
    return "GETNPCDATAFLAGS2 " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataWidth::toString()
{
    return "GETNPCDATAWIDTH " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataHeight::toString()
{
    return "GETNPCDATAHEIGHT " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataTile::toString()
{
    return "GETNPCDATASTILE " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataSWidth::toString()
{
    return "GETNPCDATASWIDTH " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataSHeight::toString()
{
    return "GETNPCDATASHEIGHT " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataETile::toString()
{
    return "GETNPCDATAETILE " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataEWidth::toString()
{
    return "GETNPCDATAEWIDTH " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataHP::toString()
{
    return "GETNPCDATAHP " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataFamily::toString()
{
    return "GETNPCDATAFAMILY " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataCSet::toString()
{
    return "GETNPCDATACSET " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataAnim::toString()
{
    return "GETNPCDATAANIM " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataEAnim::toString()
{
    return "GETNPCDATAEANIM " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataFramerate::toString()
{
    return "GETNPCDATAFRAMERATE " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataEFramerate::toString()
{
    return "GETNPCDATAEFRAMERATE " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataTouchDamage::toString()
{
    return "GETNPCDATATOUCHDMG " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataWeaponDamage::toString()
{
    return "GETNPCDATAWPNDAMAGE " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataWeapon::toString()
{
    return "GETNPCDATAWEAPON " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataRandom::toString()
{
    return "GETNPCDATARANDOM " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataHalt::toString()
{
    return "GETNPCDATAHALT " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataStep::toString()
{
    return "GETNPCDATASTEP " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataHoming::toString()
{
    return "GETNPCDATAHOMING " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataHunger::toString()
{
    return "GETNPCDATAHUNGER " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataropset::toString()
{
    return "GETNPCDATADROPSET " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataBGSound::toString()
{
    return "GETNPCDATABGSFX " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataHitSound::toString()
{
    return "GETNPCDATAHITSFX " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataDeathSound::toString()
{
    return "GETNPCDATADEATHSFX " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataXofs::toString()
{
    return "GETNPCDATAXOFS " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataYofs::toString()
{
    return "GETNPCDATAYOFS " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataZofs::toString()
{
    return "GETNPCDATAZOFS " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataHitXOfs::toString()
{
    return "GETNPCDATAHXOFS " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataHYOfs::toString()
{
    return "GETNPCDATAHYOFS " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataHitWidth::toString()
{
    return "GETNPCDATAHITWIDTH " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataHitHeight::toString()
{
    return "GETNPCDATAHITHEIGHT " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataHitZ::toString()
{
    return "GETNPCDATAHITZ " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataTileWidth::toString()
{
    return "GETNPCDATATILEWIDTH " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataTileHeight::toString()
{
    return "GETNPCDATATILEHEIGHT " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataWeapSprite::toString()
{
    return "GETNPCDATAWPNSPRITE " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}

//two inputs, one return
string ONDataScriptDef::toString()
{
    return "GETNPCDATASCRIPTDEF " + getArgument()->toString();
}
//two inputs, one return
string ONDataDefense::toString()
{
    return "GETNPCDATADEFENSE " + getArgument()->toString();
}
//two inputs, one return
string ONDataSizeFlag::toString()
{
    return "GETNPCDATASIZEFLAG " + getArgument()->toString();
}
//two inputs, one return
string ONDatattributes::toString()
{
    return "GETNPCDATAATTRIBUTE " + getArgument()->toString();
}

string ONDataSetBaseTile::toString()
{
    return "SETNPCDATATILE " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataSetEHeight::toString()
{
    return "SETNPCDATAEHEIGHT " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}

string ONDataSetFlags::toString()
{
    return "SETNPCDATAFLAGS " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataSetFlags2::toString()
{
    return "SETNPCDATAFLAGS2 " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataSetWidth::toString()
{
    return "SETNPCDATAWIDTH " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataSetHeight::toString()
{
    return "SETNPCDATAHEIGHT " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataSetTile::toString()
{
    return "SETNPCDATASTILE " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataSetSWidth::toString()
{
    return "SETNPCDATASWIDTH " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataSetSHeight::toString()
{
    return "SETNPCDATASHEIGHT " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataSetETile::toString()
{
    return "SETNPCDATAETILE " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataSetEWidth::toString()
{
    return "SETNPCDATAEWIDTH " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataSetHP::toString()
{
    return "SETNPCDATAHP " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataSetFamily::toString()
{
    return "SETNPCDATAFAMILY " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataSetCSet::toString()
{
    return "SETNPCDATACSET " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataSetAnim::toString()
{
    return "SETNPCDATAANIM " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataSetEAnim::toString()
{
    return "SETNPCDATAEANIM " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataSetFramerate::toString()
{
    return "SETNPCDATAFRAMERATE " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataSetEFramerate::toString()
{
    return "SETNPCDATAEFRAMERATE " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataSetTouchDamage::toString()
{
    return "SETNPCDATATOUCHDMG " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataSetWeaponDamage::toString()
{
    return "SETNPCDATAWPNDAMAGE " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataSetWeapon::toString()
{
    return "SETNPCDATAWEAPON " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataSetRandom::toString()
{
    return "SETNPCDATARANDOM " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataSetHalt::toString()
{
    return "SETNPCDATAHALT " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataSetStep::toString()
{
    return "SETNPCDATASTEP " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataSetHoming::toString()
{
    return "SETNPCDATAHOMING " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataSetHunger::toString()
{
    return "SETNPCDATAHUNGER " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataSetropset::toString()
{
    return "SETNPCDATADROPSET " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataSetBGSound::toString()
{
    return "SETNPCDATABGSFX " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataSetHitSound::toString()
{
    return "SETNPCDATAHITSFX " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataSetDeathSound::toString()
{
    return "SETNPCDATADEATHSFX " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataSetXofs::toString()
{
    return "SETNPCDATAXOFS " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataSetYofs::toString()
{
    return "SETNPCDATAYOFS " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataSetZofs::toString()
{
    return "SETNPCDATAZOFS " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataSetHitXOfs::toString()
{
    return "SETNPCDATAHXOFS " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataSetHYOfs::toString()
{
    return "SETNPCDATAHYOFS " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataSetHitWidth::toString()
{
    return "SETNPCDATAHITWIDTH " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataSetHitHeight::toString()
{
    return "SETNPCDATAHITHEIGHT " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataSetHitZ::toString()
{
    return "SETNPCDATAHITZ " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataSetTileWidth::toString()
{
    return "SETNPCDATATILEWIDTH " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataSetTileHeight::toString()
{
    return "SETNPCDATATILEHEIGHT " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string ONDataSetWeapSprite::toString()
{
    return "SETNPCDATAWPNSPRITE " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}

//ComboData

string OCDataBlockEnemy::toString()
{
    return "GCDBLOCKENEM " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCDataBlockHole::toString()
{
    return "GCDBLOCKHOLE " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCDataBlockTrig::toString()
{
    return "GCDBLOCKTRIG " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCDataConveyX::toString()
{
    return "GCDCONVEYSPDX " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCDataConveyY::toString()
{
    return "GCDCONVEYSPDY " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCDataCreateNPC::toString()
{
    return "GCDCREATEENEM " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCDataCreateEnemW::toString()
{
    return "GCDCREATEENEMWH " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCDataCreateEnemC::toString()
{
    return "GCDCREATEENEMCH " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCDataDirch::toString()
{
    return "GCDDIRCHTYPE " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCDataDistTiles::toString()
{
    return "GCDDISTCHTILES " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCDataDiveItem::toString()
{
    return "GCDDIVEITEM " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCDataDock::toString()
{
    return "GCDDOCK " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCDataFairy::toString()
{
    return "GCDFAIRY " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCDataAttrib::toString()
{
    return "GCDFFCOMBOATTRIB " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCDataDecoTile::toString()
{
    return "GCDFOOTDECOTILE " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}

string OCDataLadderPass::toString()
{
    return "GCDLADDERPASS " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataLadderPass::toString()
{
    return "SCDLADDERPASS " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}


string OCDataDecoType::toString()
{
    return "GCDFOOTDECOTYPE " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCDataHookshotGrab::toString()
{
    return "GCDHOOKSHOTGRAB " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCDataLockBlock::toString()
{
    return "GCDLOCKBLOCKTYPE " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCDataLockBlockChange::toString()
{
    return "GCDLOCKBLOCKCHANGE " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCDataMagicMirror::toString()
{
    return "GCDMAGICMIRRORTYPE " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCDataModHP::toString()
{
    return "GCDMODIFYHPAMOUNT " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCDataModHPDelay::toString()
{
    return "GCDMODIFYHPDELAY " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCDataModHpType::toString()
{
    return "GCDMODIFYHPTYPE " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCDataModMP::toString()
{
    return "GCDMODIFYMPAMOUNT " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCDataMpdMPDelay::toString()
{
    return "GCDMODIFYMPDELAY " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCDataModMPType::toString()
{
    return "GCDMODIFYMPTYPE " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCDataNoPush::toString()
{
    return "GCDNOPUSHBLOCKS " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCDataOverhead::toString()
{
    return "GCDOVERHEAD " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCDataEnemyLoc::toString()
{
    return "GCDPLACEENEMY " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCDataPushDir::toString()
{
    return "GCDPUSHDIR " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCDataPushWeight::toString()
{
    return "GCDPUSHWEIGHT " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCDataPushWait::toString()
{
    return "GCDPUSHWAIT " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCDataPushed::toString()
{
    return "GCDPUSHED " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCDataRaft::toString()
{
    return "GCDRAFT " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCDataResetRoom::toString()
{
    return "GCDRESETROOM " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCDataSavePoint::toString()
{
    return "GCDSAVEPOINT " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCDataFreeezeScreen::toString()
{
    return "GCDSCREENFREEZE " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCDataSecretCombo::toString()
{
    return "GCDSECRETCOMBO " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCDataSingular::toString()
{
    return "GCDSINGULAR " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCDataSlowMove::toString()
{
    return "GCDSLOWMOVE " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCDataStatue::toString()
{
    return "GCDSTATUE " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCDataStepType::toString()
{
    return "GCDSTEPTYPE " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCDataSteoChange::toString()
{
    return "GCDSTEPCHANGETO " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCDataStrikeRem::toString()
{
    return "GCDSTRIKEREMNANTS " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCDataStrikeRemType::toString()
{
    return "GCDSTRIKEREMNANTSTYPE " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCDataStrikeChange::toString()
{
    return "GCDSTRIKECHANGE " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCDataStrikeChangeItem::toString()
{
    return "GCDSTRIKECHANGEITEM " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCDataTouchItem::toString()
{
    return "GCDTOUCHITEM " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCDataTouchStairs::toString()
{
    return "GCDTOUCHSTAIRS " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCDataTriggerType::toString()
{
    return "GCDTRIGGERTYPE " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCDataTriggerSens::toString()
{
    return "GCDTRIGGERSENS " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCDataWarpType::toString()
{
    return "GCDWARPTYPE " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCDataWarpSens::toString()
{
    return "GCDWARPSENS " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCDataWarpDirect::toString()
{
    return "GCDWARPDIRECT " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCDataWarpLoc::toString()
{
    return "GCDWARPLOCATION " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCDataWater::toString()
{
    return "GCDWATER " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}

string OCDataWinGame::toString()
{
    return "GCDWINGAME " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCDataWhistle::toString()
{
    return "GCDWHISTLE " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCDataWeapBlockLevel::toString()
{
    return "GCDBLOCKWEAPLVL " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCDataTile::toString()
{
    return "GCDTILE " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCDataFlip::toString()
{
    return "GCDFLIP " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCDataWalkability::toString()
{
    return "GCDWALK " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCDataType::toString()
{
    return "GCDTYPE " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCDataCSets::toString()
{
    return "GCDCSETS " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCDataFoo::toString()
{
    return "GCDFOO " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCDataFrames::toString()
{
    return "GCDFRAMES " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCDataSpeed::toString()
{
    return "GCDSPEED " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCDataNext::toString()
{
    return "GCDNEXTCOMBO " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCDataNextCSet::toString()
{
    return "GCDNEXTCSET " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCDataFlag::toString()
{
    return "GCDFLAG " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCDataSkipAnim::toString()
{
    return "GCDSKIPANIM " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCDataTimer::toString()
{
    return "GCDNEXTTIMER " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCDataAnimY::toString()
{
    return "GCDSKIPANIMY " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCDataAnimFlags::toString()
{
    return "GCDANIMFLAGS " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}

string OCDataBlockWeapon::toString()
{
    return "GCDBLOCKWEAPON " + getArgument()->toString();
}
string OCDataExpansion::toString()
{
    return "GCDEXPANSION " + getArgument()->toString();
}
string OCDataStrikeWeapon::toString()
{
    return "GCDSTRIKEWEAPONS " + getArgument()->toString();
}

string OCSetDataBlockEnemy::toString()
{
    return "SCDBLOCKENEM " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataBlockHole::toString()
{
    return "SCDBLOCKHOLE " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataBlockTrig::toString()
{
    return "SCDBLOCKTRIG " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataConveyX::toString()
{
    return "SCDCONVEYSPDX " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataConveyY::toString()
{
    return "SCDCONVEYSPDY " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataCreateNPC::toString()
{
    return "SCDCREATEENEM " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataCreateEnemW::toString()
{
    return "SCDCREATEENEMWH " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataCreateEnemC::toString()
{
    return "SCDCREATEENEMCH " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataDirch::toString()
{
    return "SCDDIRCHTYPE " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataDistTiles::toString()
{
    return "SCDDISTCHTILES " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataDiveItem::toString()
{
    return "SCDDIVEITEM " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataDock::toString()
{
    return "SCDDOCK " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataFairy::toString()
{
    return "SCDFAIRY " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataAttrib::toString()
{
    return "SCDFFCOMBOATTRIB " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataDecoTile::toString()
{
    return "SCDFOOTDECOTILE " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataDecoType::toString()
{
    return "SCDFOOTDECOTYPE " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataHookshotGrab::toString()
{
    return "SCDHOOKSHOTGRAB " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataLockBlock::toString()
{
    return "SCDLOCKBLOCKTYPE " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataLockBlockChange::toString()
{
    return "SCDLOCKBLOCKCHANGE " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataMagicMirror::toString()
{
    return "SCDMAGICMIRRORTYPE " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataModHP::toString()
{
    return "SCDMODIFYHPAMOUNT " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataModHPDelay::toString()
{
    return "SCDMODIFYHPDELAY " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataModHpType::toString()
{
    return "SCDMODIFYHPTYPE " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataModMP::toString()
{
    return "SCDMODIFYMPAMOUNT " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataMpdMPDelay::toString()
{
    return "SCDMODIFYMPDELAY " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataModMPType::toString()
{
    return "SCDMODIFYMPTYPE " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataNoPush::toString()
{
    return "SCDNOPUSHBLOCKS " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataOverhead::toString()
{
    return "SCDOVERHEAD " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataEnemyLoc::toString()
{
    return "SCDPLACEENEMY " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataPushDir::toString()
{
    return "SCDPUSHDIR " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataPushWeight::toString()
{
    return "SCDPUSHWEIGHT " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataPushWait::toString()
{
    return "SCDPUSHWAIT " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataPushed::toString()
{
    return "SCDPUSHED " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataRaft::toString()
{
    return "SCDRAFT " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataResetRoom::toString()
{
    return "SCDRESETROOM " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataSavePoint::toString()
{
    return "SCDSAVEPOINT " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataFreeezeScreen::toString()
{
    return "SCDSCREENFREEZE " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataSecretCombo::toString()
{
    return "SCDSECRETCOMBO " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataSingular::toString()
{
    return "SCDSINGULAR " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataSlowMove::toString()
{
    return "SCDSLOWMOVE " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataStatue::toString()
{
    return "SCDSTATUE " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataStepType::toString()
{
    return "SCDSTEPTYPE " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataSteoChange::toString()
{
    return "SCDSTEPCHANGETO " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataStrikeRem::toString()
{
    return "SCDSTRIKEREMNANTS " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataStrikeRemType::toString()
{
    return "SCDSTRIKEREMNANTSTYPE " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataStrikeChange::toString()
{
    return "SCDSTRIKECHANGE " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataStrikeChangeItem::toString()
{
    return "SCDSTRIKECHANGEITEM " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataTouchItem::toString()
{
    return "SCDTOUCHITEM " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataTouchStairs::toString()
{
    return "SCDTOUCHSTAIRS " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataTriggerType::toString()
{
    return "SCDTRIGGERTYPE " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataTriggerSens::toString()
{
    return "SCDTRIGGERSENS " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataWarpType::toString()
{
    return "SCDWARPTYPE " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataWarpSens::toString()
{
    return "SCDWARPSENS " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataWarpDirect::toString()
{
    return "SCDWARPDIRECT " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataWarpLoc::toString()
{
    return "SCDWARPLOCATION " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataWater::toString()
{
    return "SCDWATER " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataWhistle::toString()
{
    return "SCDWHISTLE " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataWeapBlockLevel::toString()
{
    return "SCDBLOCKWEAPLVL " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataTile::toString()
{
    return "SCDTILE " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataFlip::toString()
{
    return "SCDFLIP " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataWalkability::toString()
{
    return "SCDWALK " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataType::toString()
{
    return "SCDTYPE " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataCSets::toString()
{
    return "SCDCSETS " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataFoo::toString()
{
    return "SCDFOO " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataFrames::toString()
{
    return "SCDFRAMES " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataSpeed::toString()
{
    return "SCDSPEED " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataNext::toString()
{
    return "SCDNEXTCOMBO " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataNextCSet::toString()
{
    return "SCDNEXTCSET " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataFlag::toString()
{
    return "SCDFLAG " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataSkipAnim::toString()
{
    return "SCDSKIPANIM " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataTimer::toString()
{
    return "SCDNEXTTIMER " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataAnimY::toString()
{
    return "SCDSKIPANIMY " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OCSetDataAnimFlags::toString()
{
    return "SCDANIMFLAGS " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}

string OCSetDataWinGame::toString()
{
    return "SCDWINGAME " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}

//SpriteData
string OSDataTile::toString()
{
    return "GETSPRITEDATATILE " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OSDataMisc::toString()
{
    return "GETSPRITEDATAMISC " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OSDataCSets::toString()
{
    return "GETSPRITEDATACGETS " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OSDataFrames::toString()
{
    return "GETSPRITEDATAFRAMES " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OSDataSpeed::toString()
{
    return "GETSPRITEDATASPEED " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OSDataType::toString()
{
    return "GETSPRITEDATATYPE " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}

string OSSetDataTile::toString()
{
    return "SETSPRITEDATATILE " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OSSetDataMisc::toString()
{
    return "SETSPRITEDATAMISC " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OSSetDataCSets::toString()
{
    return "SETSPRITEDATACGETS " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OSSetDataFrames::toString()
{
    return "SETSPRITEDATAFRAMES " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OSSetDataSpeed::toString()
{
    return "SETSPRITEDATASPEED " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OSSetDataType::toString()
{
    return "SETSPRITEDATATYPE " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}

//Continue Screen Settings
string OSSetContinueScreen::toString()
{
    return "SETCONTINUESCREEN " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}
string OSSetContinueString::toString()
{
    return "SETCONTINUESTRING " + getFirstArgument()->toString() + "," +  getSecondArgument()->toString();
}

//Visual effects with one bool arg.

string OWavyR::toString()
{
    return "FXWAVYR " + getArgument()->toString();
}

string OZapR::toString()
{
    return "FXZAPR " + getArgument()->toString();
}

string OGreyscaleR::toString()
{
    return "GREYSCALER " + getArgument()->toString();
}

string OMonochromeR::toString()
{
    return "MONOCHROMER " + getArgument()->toString();
}

string OClearTint::toString()
{
    return "CLEARTINT";
}

string OTintR::toString()
{
    return "TINT";
}

string OMonoHueR::toString()
{
    return "MONOHUE";
}

//Bitmap commands

string OBMPRectangleRegister::toString()
{
    return "BMPRECTR";
}

string OBMPCircleRegister::toString()
{
    return "BMPCIRCLER";
}

string OBMPArcRegister::toString()
{
    return "BMPARCR";
}

string OBMPEllipseRegister::toString()
{
    return "BMPELLIPSER";
}

string OBMPLineRegister::toString()
{
    return "BMPLINER";
}

string OBMPSplineRegister::toString()
{
    return "BMPBMPSPLINER";
}

string OBMPPutPixelRegister::toString()
{
    return "BMPPUTPIXELR";
}

string OBMPDrawCharRegister::toString()
{
    return "BMPDRAWCHARR";
}

string OBMPDrawIntRegister::toString()
{
    return "BMPDRAWINTR";
}

string OBMPDrawTileRegister::toString()
{
    return "BMPDRAWTILER";
}

string OBMPDrawComboRegister::toString()
{
    return "BMPDRAWCOMBOR";
}

string OBMPFastTileRegister::toString()
{
    return "BMPFASTTILER";
}

string OBMPFastComboRegister::toString()
{
    return "BMPFASTCOMBOR";
}

string OBMPDrawStringRegister::toString()
{
    return "BMPDRAWSTRINGR";
}

string OBMPDrawBitmapExRegister::toString()
{
    return "BMPBLIT";
}
string OBMPBlitTO::toString()
{
    return "BMPBLITTO";
}

string OBMPGetPixel::toString()
{
    return "BITMAPGETPIXEL";
}
string OBMPMode7::toString()
{
    return "BMPMODE7";
}

string OBMPQuadRegister::toString()
{
    return "BMPQUADR";
}

string OBMPTriangleRegister::toString()
{
    return "BMPTRIANGLER";
}


string OBMPQuad3DRegister::toString()
{
    return "BMPQUAD3DR";
}

string OBMPTriangle3DRegister::toString()
{
    return "BMPTRIANGLE3DR";
}

string OBMPDrawLayerRegister::toString()
{
    return "BMPDRAWLAYERR";
}

string OBMPDrawScreenRegister::toString()
{
    return "BMPDRAWSCREENR";
}

string OLinkWarpExRegister::toString()
{
    return "LINKWARPEXR " + getArgument()->toString();
}

string OLinkExplodeRegister::toString()
{
    return "LINKEXPLODER " + getArgument()->toString();
}


string OGetSystemRTCRegister::toString()
{
    return "GETRTCTIMER " + getArgument()->toString();
}


string ONPCExplodeRegister::toString()
{
    return "NPCEXPLODER " + getArgument()->toString();
}
string OLWeaponExplodeRegister::toString()
{
    return "LWEAPONEXPLODER " + getArgument()->toString();
}
string OEWeaponExplodeRegister::toString()
{
    return "EWEAPONEXPLODER " + getArgument()->toString();
}
string OItemExplodeRegister::toString()
{
    return "ITEMEXPLODER " + getArgument()->toString();
}

string ORunItemScript::toString()
{
    return "RUNITEMSCRIPT " + getArgument()->toString();
}

//new npc-> functions for npc scripts
string ONPCDead::toString()
{
    return "NPCDEAD " + getArgument()->toString();
}
string ONPCCanSlide::toString()
{
    return "NPCCANSLIDE " + getArgument()->toString();
}
string ONPCSlide::toString()
{
    return "NPCSLIDE " + getArgument()->toString();
}
string ONPCBreatheFire::toString()
{
    return "NPCFIREBREATH " + getArgument()->toString();
}
string ONPCNewDir8::toString()
{
    return "NPCNEWDIR8 " + getArgument()->toString();
}
string ONPCRemove::toString()
{
    return "NPCKICKBUCKET " + getArgument()->toString();
}
string ONPCStopSFX::toString()
{
    return "NPCSTOPBGSFX " + getArgument()->toString();
}
string ONPCAttack::toString()
{
    return "NPCATTACK " + getArgument()->toString();
}
string ONPCNewDir::toString()
{
    return "NPCNEWDIR " + getArgument()->toString();
}
string ONPCConstWalk::toString()
{
    return "NPCCONSTWALK " + getArgument()->toString();
}
string ONPCConstWalk8::toString()
{
    return "NPCCONSTWALK8 " + getArgument()->toString();
}
string ONPCVarWalk::toString()
{
    return "NPCVARWALK " + getArgument()->toString();
}
string ONPCVarWalk8::toString()
{
    return "NPCVARWALK8 " + getArgument()->toString();
}
string ONPCHaltWalk::toString()
{
    return "NPCHALTWALK " + getArgument()->toString();
}
string ONPCHaltWalk8::toString()
{
    return "NPCHALTWALK8 " + getArgument()->toString();
}
string ONPCFloatWalk::toString()
{
    return "NPCFLOATWALK " + getArgument()->toString();
}
string ONPCLinkInRange::toString()
{
    return "NPCLINKINRANGE " + getArgument()->toString();
}
string ONPCAdd::toString()
{
    return "NPCADD " + getArgument()->toString();
}
string ONPCCanMove::toString()
{
    return "NPCCANMOVE " + getArgument()->toString();
}
string ONPCHitWith::toString()
{
    return "NPCHITWITH " + getArgument()->toString();
}

string OGetNPCDataName::toString()
{
    return "NPCDATAGETNAME " + getArgument()->toString();
}

string OAllocateBitmap::toString()
{
    return "ALLOCATEBITMAP " + getArgument()->toString();
}

string OClearBitmap::toString()
{
    return "CLEARBITMAP";
}

string ORegenerateBitmap::toString()
{
    return "REGENERATEBITMAP";
}

string OReadBitmap::toString()
{
    return "READBITMAP";
}
string OWriteBitmap::toString()
{
    return "WRITEBITMAP";
}

string OIsValidBitmap::toString()
{
    return "ISVALIDBITMAP " + getArgument()->toString();
}


string OBMPDrawScreenSolidRegister::toString()
{
    return "BMPDRAWSCREENSOLIDR";
}

string OBMPDrawScreenSolid2Register::toString()
{
    return "BMPDRAWSCREENSOLID2R";
}
string OBMPDrawScreenComboFRegister::toString()
{
    return "BMPDRAWSCREENCOMBOFR";
}
string OBMPDrawScreenComboIRegister::toString()
{
    return "BMPDRAWSCREENCOMBOIR";
}
string OBMPDrawScreenComboTRegister::toString()
{
    return "BMPDRAWSCREENCOMBOTR";
}
string OGraphicsGetpixel::toString()
{
    return "GRAPHICSGETPIXEL " + getArgument()->toString();
}

string OBMPDrawScreenSolidityRegister::toString()
{
    return "BMPDRAWLAYERSOLIDITYR";
}
string OBMPDrawScreenSolidMaskRegister::toString()
{
    return "BMPDRAWLAYERSOLIDR";
}
string OBMPDrawScreenCTypeRegister::toString()
{
    return "BMPDRAWLAYERCTYPER";
}
string OBMPDrawScreenCFlagRegister::toString()
{
    return "BMPDRAWLAYERCFLAGR";
}
string OBMPDrawScreenCIFlagRegister::toString()
{
    return "BMPDRAWLAYERCIFLAGR";
}


string OStrCmp::toString()
{
    return "STRINGCOMPARE " + getArgument()->toString();
}


string OStrNCmp::toString()
{
    return "STRINGNCOMPARE " + getArgument()->toString();
}

//based on Ostrcpy
string oARRAYCOPY::toString()
{
    return "ARRAYCOPY " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}

/*to do 
  //1 INPUT, NO RETURN 
     { "REMCHR",                2,   0,   0,   0},
     { "STRINGUPPERLOWER",                2,   0,   0,   0},
     { "STRINGLOWERUPPER",                2,   0,   0,   0},
     { "STRINGCONVERTCASE",                2,   0,   0,   0},
     */

//1 inp, 1 ret, baseds on STRINGLENGTH / Ostrlen

string Oxlen::toString()
{
    return "XLEN " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}
string Oxtoi::toString()
{
    return "XTOI " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}
string Oilen::toString()
{
    return "ILEN " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}
string Oatoi::toString()
{
    return "ATOI " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}

//2 inp, 1 ret, based on STRINGCOMPARE / OStrCmp

string Ostrcspn::toString()
{
    return "STRCSPN " + getArgument()->toString();
}

string Ostrstr::toString()
{
    return "STRSTR " + getArgument()->toString();
}

string Oxtoa::toString()
{
    return "XTOA " + getArgument()->toString();
}

string Oitoa::toString()
{
    return "ITOA " + getArgument()->toString();
}

string Ostrcat::toString()
{
    return "STRCAT " + getArgument()->toString();
}

string Ostrspn::toString()
{
    return "STRSPN " + getArgument()->toString();
}
string Ostrchr::toString()
{
    return "STRCHR " + getArgument()->toString();
}

string Ostrrchr::toString()
{
    return "STRRCHR " + getArgument()->toString();
}
string Oxlen2::toString()
{
    return "XLEN2 " + getArgument()->toString();
}

string Oxtoi2::toString()
{
    return "XTOI2 " + getArgument()->toString();
}
string Oilen2::toString()
{
    return "ILEN2 " + getArgument()->toString();
}
string Oatoi2::toString()
{
    return "ATOI2 " + getArgument()->toString();
}
string Oremchr2::toString()
{
    return "REMCHR2 " + getArgument()->toString();
}


/*to do
  //3 INPUT 1 RET 
    { "XTOA3",		       1,   0,   0,   0},
    { "STRCATF",		       1,   0,   0,   0},
    { "ITOA3",		       1,   0,   0,   0},
    { "STRSTR3",		       1,   0,   0,   0},
    { "REMNCHR3",		       1,   0,   0,   0},
    { "STRCAT3",		       1,   0,   0,   0},
    { "STRNCAT3",		       1,   0,   0,   0},
    { "STRCHR3",		       1,   0,   0,   0},
    { "STRRCHR3",		       1,   0,   0,   0},
    { "STRSPN3",		       1,   0,   0,   0},
    { "STRCSPN3",		       1,   0,   0,   0},
    
*/








string Ouppertolower::toString()
{
    return "UPPERTOLOWER " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}
string Olowertoupper::toString()
{
    return "LOWERTOUPPER " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}
string Oconvertcase::toString()
{
    return "CONVERTCASE " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}

//Game->GetByString functions
//similar to Oconvertcase

string OGETNPCSCRIPT::toString()
{
    return "GETNPCSCRIPT " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}
string OGETLWEAPONSCRIPT::toString()
{
    return "GETLWEAPONSCRIPT " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}
string OGETEWEAPONSCRIPT::toString()
{
    return "GETEWEAPONSCRIPT " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}
string OGETHEROSCRIPT::toString()
{
    return "GETHEROSCRIPT " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}
string OGETGLOBALSCRIPT::toString()
{
    return "GETGLOBALSCRIPT " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}
string OGETDMAPSCRIPT::toString()
{
    return "GETDMAPSCRIPT " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}
string OGETSCREENSCRIPT::toString()
{
    return "GETSCREENSCRIPT " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}
string OGETSPRITESCRIPT::toString()
{
    return "GETSPRITESCRIPT " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}
string OGETUNTYPEDSCRIPT::toString()
{
    return "GETUNTYPEDSCRIPT " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}
string OGETSUBSCREENSCRIPT::toString()
{
    return "GETSUBSCREENSCRIPT " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}
string OGETNPCBYNAME::toString()
{
    return "GETNPCBYNAME " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}
string OGETITEMBYNAME::toString()
{
    return "GETITEMBYNAME " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}
string OGETCOMBOBYNAME::toString()
{
    return "GETCOMBOBYNAME " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}
string OGETDMAPBYNAME::toString()
{
    return "GETDMAPBYNAME " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}



string OReturn::toString()
{
	return "RETURN";
}


//////////////////////////////////////////////////////////////////////////////////////

