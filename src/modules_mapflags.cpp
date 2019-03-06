
const char map_flag_cats[mfMAX][256]
{
	"mfNONE","mfPUSHUD","mfPUSH4","mfWHISTLE","mfBCANDLE","mfARROW","mfBOMB","mfFAIRY","mfRAFT","mfSTATUE_SECRET","mfSTATUE_ITEM","mfSBOMB","mfRAFT_BRANCH","mfDIVE_ITEM","mfLENSMARKER","mfWINGAME",
	"mfSECRETS01","mfSECRETS02","mfSECRETS03","mfSECRETS04","mfSECRETS05","mfSECRETS06","mfSECRETS07","mfSECRETS08","mfSECRETS09","mfSECRETS10","mfSECRETS11","mfSECRETS12","mfSECRETS13","mfSECRETS14","mfSECRETS15","mfSECRETS16",
	"mfTRAP_H","mfTRAP_V","mfTRAP_4","mfTRAP_LR","mfTRAP_UD","mfENEMY0","mfENEMY1","mfENEMY2","mfENEMY3","mfENEMY4","mfENEMY5","mfENEMY6","mfENEMY7","mfENEMY8","mfENEMY9","mfPUSHLR",
	"mfPUSHU","mfPUSHD","mfPUSHL","mfPUSHR","mfPUSHUDNS","mfPUSHLRNS","mfPUSH4NS","mfPUSHUNS","mfPUSHDNS","mfPUSHLNS","mfPUSHRNS","mfPUSHUDINS","mfPUSHLRINS","mfPUSH4INS","mfPUSHUINS","mfPUSHDINS",
	"mfPUSHLINS","mfPUSHRINS","mfBLOCKTRIGGER","mfNOBLOCKS","mfBRANG","mfMBRANG","mfFBRANG","mfSARROW","mfGARROW","mfRCANDLE","mfWANDFIRE","mfDINSFIRE","mfWANDMAGIC","mfREFMAGIC","mfREFFIREBALL","mfSWORD",
	"mfWSWORD","mfMSWORD","mfXSWORD","mfSWORDBEAM","mfWSWORDBEAM","mfMSWORDBEAM","mfXSWORDBEAM","mfGRAPPLE","mfWAND","mfHAMMER","mfSTRIKE","mfBLOCKHOLE","mfMAGICFAIRY","mfALLFAIRY","mfSINGLE","mfSINGLE16",
	"mfNOENEMY","mfNOGROUNDENEMY","mfSCRIPT1","mfSCRIPT2","mfSCRIPT3","mfSCRIPT4","mfSCRIPT5","mfRAFT_BOUNCE","mfPUSHED","mfSCRIPT6","mfSCRIPT7","mfSCRIPT8","mfSCRIPT9","mfSCRIPT10","mfSCRIPT11","mfSCRIPT12",
	"mfSCRIPT13","mfSCRIPT14","mfSCRIPT15","mfSCRIPT16","mfSCRIPT17","mfSCRIPT18","mfSCRIPT19","mfSCRIPT20","mfPITHOLE","mfPITFALLFLOOR","mfLAVA","mfICE","mfICEDAMAGE","mfDAMAGE1","mfDAMAGE2","mfDAMAGE4",
	"mfDAMAGE8","mfDAMAGE16","mfDAMAGE32","mfFREEZEALL","mfFREZEALLANSFFCS","mfFREEZEFFCSOLY","mfSCRITPTW1TRIG","mfSCRITPTW2TRIG","mfSCRITPTW3TRIG","mfSCRITPTW4TRIG","mfSCRITPTW5TRIG","mfSCRITPTW6TRIG","mfSCRITPTW7TRIG","mfSCRITPTW8TRIG","mfSCRITPTW9TRIG","mfSCRITPTW10TRIG",
	"mfTROWEL","mfTROWELNEXT","mfTROWELSPECIALITEM","mfSLASHPOT","mfLIFTPOT","mfLIFTORSLASH","mfLIFTROCK","mfLIFTROCKHEAVY","mfDROPITEM","mfSPECIALITEM","mfDROPKEY","mfDROPLKEY","mfDROPCOMPASS","mfDROPMAP","mfDROPBOSSKEY","mfSPAWNNPC",
	"mfSWITCHHOOK","mf161","mf162","mf163","mf164","mf165","mf166","mf167","mf168","mf169","mf170","mf171","mf172","mf173","mf174","mf175",
	"mf176","mf177","mf178","mf179","mf180","mf181","mf182","mf183","mf184","mf185","mf186","mf187","mf188","mf189","mf190","mf191",
	"mf192","mf193","mf194","mf195","mf196","mf197","mf198","mf199","mf200","mf201","mf202","mf203","mf204","mf205","mf206","mf207",
	"mf208","mf209","mf210","mf211","mf212","mf213","mf214","mf215","mf216","mf217","mf218","mf219","mf220","mf221","mf222","mf223",
	"mf224","mf225","mf226","mf227","mf228","mf229","mf230","mf231","mf232","mf233","mf234","mf235","mf236","mf237","mf238","mf239",
	"mf240","mf241","mf242","mf243","mf244","mf245","mf246","mf247","mf248","mf249","mf250","mf251","mf252","mf253","mf254","mfEXTENDED"
}

mfNONE,
mfPUSHUD,
mfPUSH4,
mfWHISTLE,
mfBCANDLE,
mfARROW,
mfBOMB,
mfFAIRY,
mfRAFT,
mfSTATUE_SECRET,
mfSTATUE_ITEM,
mfSBOMB,
mfRAFT_BRANCH,
mfDIVE_ITEM,
mfLENSMARKER,
mfWINGAME,
mfSECRETS01,
mfSECRETS02,
mfSECRETS03,
mfSECRETS04,
mfSECRETS05,
mfSECRETS06,
mfSECRETS07,
mfSECRETS08,
mfSECRETS09,
mfSECRETS10,
mfSECRETS11,
mfSECRETS12,
mfSECRETS13,
mfSECRETS14,
mfSECRETS15,
mfSECRETS16,
mfTRAP_H,
mfTRAP_V,
mfTRAP_4,
mfTRAP_LR,
mfTRAP_UD,
mfENEMY0,
mfENEMY1,
mfENEMY2,
mfENEMY3,
mfENEMY4,
mfENEMY5,
mfENEMY6,
mfENEMY7,
mfENEMY8,
mfENEMY9,
mfPUSHLR,
mfPUSHU,
mfPUSHD,
mfPUSHL,
mfPUSHR,
mfPUSHUDNS,
mfPUSHLRNS,
mfPUSH4NS,
mfPUSHUNS,
mfPUSHDNS,
mfPUSHLNS,
mfPUSHRNS,
mfPUSHUDINS,
mfPUSHLRINS,
mfPUSH4INS,
mfPUSHUINS,
mfPUSHDINS,
mfPUSHLINS,
mfPUSHRINS,
mfBLOCKTRIGGER,
mfNOBLOCKS,
mfBRANG,
mfMBRANG,
mfFBRANG,
mfSARROW,
mfGARROW,
mfRCANDLE,
mfWANDFIRE,
mfDINSFIRE,
mfWANDMAGIC,
mfREFMAGIC,
mfREFFIREBALL,
mfSWORD,
mfWSWORD,
mfMSWORD,
mfXSWORD,
mfSWORDBEAM,
mfWSWORDBEAM,
mfMSWORDBEAM,
mfXSWORDBEAM,
mfGRAPPLE,
mfWAND,
mfHAMMER,
mfSTRIKE,
mfBLOCKHOLE,
mfMAGICFAIRY,
mfALLFAIRY,
mfSINGLE,
mfSINGLE16,
mfNOENEMY,
mfNOGROUNDENEMY,
mfSCRIPT1,
mfSCRIPT2,
mfSCRIPT3,
mfSCRIPT4,
mfSCRIPT5,
mfRAFT_BOUNCE,
mfPUSHED,
mfSCRIPT6,
mfSCRIPT7,
mfSCRIPT8,
mfSCRIPT9,
mfSCRIPT10,
mfSCRIPT11,
mfSCRIPT12,
mfSCRIPT13,
mfSCRIPT14,
mfSCRIPT15,
mfSCRIPT16,
mfSCRIPT17,
mfSCRIPT18,
mfSCRIPT19,
mfSCRIPT20,
mfPITHOLE,
mfPITFALLFLOOR,
mfLAVA,
mfICE,
mfICEDAMAGE,
mfDAMAGE1,
mfDAMAGE2,
mfDAMAGE4,
mfDAMAGE8,
mfDAMAGE16,
mfDAMAGE32,
mfFREEZEALL,
mfFREZEALLANSFFCS,
mfFREEZEFFCSOLY,
mfSCRITPTW1TRIG,
mfSCRITPTW2TRIG,
mfSCRITPTW3TRIG,
mfSCRITPTW4TRIG,
mfSCRITPTW5TRIG,
mfSCRITPTW6TRIG,
mfSCRITPTW7TRIG,
mfSCRITPTW8TRIG,
mfSCRITPTW9TRIG,
mfSCRITPTW10TRIG,
mfTROWEL,
mfTROWELNEXT,
mfTROWELSPECIALITEM,
mfSLASHPOT,
mfLIFTPOT,
mfLIFTORSLASH,
mfLIFTROCK,
mfLIFTROCKHEAVY,
mfDROPITEM,
mfSPECIALITEM,
mfDROPKEY,
mfDROPLKEY,
mfDROPCOMPASS,
mfDROPMAP,
mcDROPBOSSKEY,
mfSPAWNNPC,
mfSWITCHHOOK,
mf161,
mf162,
mf163,
mf164,
mf165,
mf166,
mf167,
mf168,
mf169,
mf170,
mf171,
mf172,
mf173,
mf174,
mf175,
mf176,
mf177,
mf178,
mf179,
mf180,
mf181,
mf182,
mf183,
mf184,
mf185,
mf186,
mf187,
mf188,
mf189,
mf190,
mf191,
mf192,
mf193,
mf194,
mf195,
mf196,
mf197,
mf198,
mf199,
mf200,
mf201,
mf202,
mf203,
mf204,
mf205,
mf206,
mf207,
mf208,
mf209,
mf210,
mf211,
mf212,
mf213,
mf214,
mf215,
mf216,
mf217,
mf218,
mf219,
mf220,
mf221,
mf222,
mf223,
mf224,
mf225,
mf226,
mf227,
mf228,
mf229,
mf230,
mf231,
mf232,
mf233,
mf234,
mf235,
mf236,
mf237,
mf238,
mf239,
mf240,
mf241,
mf242,
mf243,
mf244,
mf245,
mf246,
mf247,
mf248,
mf249,
mf250,
mf251,
mf252,
mf253,
mf254,
mfEXTENDED,