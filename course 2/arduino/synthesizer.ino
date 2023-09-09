#include <Keypad.h>

const byte ROWS = 4; 
const byte COLS = 4; 

char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

bool val = false;
int h = 1;

byte rowPins[ROWS] = {12, 11, 10, 9}; 
byte colPins[COLS] = {8, 7, 6, 5}; 

Keypad keypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

const int sinus[1024] 
{
  0x800,0x80d,0x819,0x826,0x832,0x83f,0x84b,0x858,0x865,0x871,
  0x87e,0x88a,0x897,0x8a3,0x8b0,0x8bc,0x8c9,0x8d5,0x8e2,0x8ee,
  0x8fb,0x907,0x914,0x920,0x92d,0x939,0x946,0x952,0x95e,0x96b,
  0x977,0x984,0x990,0x99c,0x9a9,0x9b5,0x9c1,0x9cd,0x9da,0x9e6,
  0x9f2,0x9fe,0xa0a,0xa17,0xa23,0xa2f,0xa3b,0xa47,0xa53,0xa5f,
  0xa6b,0xa77,0xa83,0xa8f,0xa9b,0xaa7,0xab3,0xabe,0xaca,0xad6,
  0xae2,0xaed,0xaf9,0xb05,0xb10,0xb1c,0xb28,0xb33,0xb3f,0xb4a,
  0xb56,0xb61,0xb6c,0xb78,0xb83,0xb8e,0xb9a,0xba5,0xbb0,0xbbb,
  0xbc6,0xbd1,0xbdc,0xbe7,0xbf2,0xbfd,0xc08,0xc13,0xc1e,0xc29,
  0xc33,0xc3e,0xc49,0xc53,0xc5e,0xc68,0xc73,0xc7d,0xc88,0xc92,
  0xc9c,0xca7,0xcb1,0xcbb,0xcc5,0xccf,0xcd9,0xce3,0xced,0xcf7,
  0xd01,0xd0b,0xd14,0xd1e,0xd28,0xd31,0xd3b,0xd44,0xd4e,0xd57,
  0xd60,0xd6a,0xd73,0xd7c,0xd85,0xd8e,0xd97,0xda0,0xda9,0xdb2,
  0xdbb,0xdc4,0xdcc,0xdd5,0xdde,0xde6,0xdef,0xdf7,0xdff,0xe08,
  0xe10,0xe18,0xe20,0xe28,0xe30,0xe38,0xe40,0xe48,0xe50,0xe57,
  0xe5f,0xe67,0xe6e,0xe76,0xe7d,0xe84,0xe8c,0xe93,0xe9a,0xea1,
  0xea8,0xeaf,0xeb6,0xebd,0xec3,0xeca,0xed1,0xed7,0xede,0xee4,
  0xeea,0xef1,0xef7,0xefd,0xf03,0xf09,0xf0f,0xf15,0xf1b,0xf21,
  0xf26,0xf2c,0xf31,0xf37,0xf3c,0xf42,0xf47,0xf4c,0xf51,0xf56,
  0xf5b,0xf60,0xf65,0xf6a,0xf6e,0xf73,0xf78,0xf7c,0xf81,0xf85,
  0xf89,0xf8d,0xf91,0xf95,0xf99,0xf9d,0xfa1,0xfa5,0xfa9,0xfac,
  0xfb0,0xfb3,0xfb7,0xfba,0xfbd,0xfc0,0xfc3,0xfc6,0xfc9,0xfcc,
  0xfcf,0xfd2,0xfd4,0xfd7,0xfd9,0xfdc,0xfde,0xfe0,0xfe2,0xfe4,
  0xfe6,0xfe8,0xfea,0xfec,0xfee,0xfef,0xff1,0xff2,0xff4,0xff5,
  0xff6,0xff8,0xff9,0xffa,0xffb,0xffc,0xffc,0xffd,0xffe,0xffe,
  0xfff,0xfff,0xfff,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,0x1000,
  0xfff,0xfff,0xffe,0xffe,0xffd,0xffd,0xffc,0xffb,0xffa,0xff9,
  0xff8,0xff7,0xff6,0xff5,0xff3,0xff2,0xff0,0xfef,0xfed,0xfeb,
  0xfe9,0xfe7,0xfe5,0xfe3,0xfe1,0xfdf,0xfdd,0xfda,0xfd8,0xfd5,
  0xfd3,0xfd0,0xfcd,0xfcb,0xfc8,0xfc5,0xfc2,0xfbf,0xfbb,0xfb8,
  0xfb5,0xfb1,0xfae,0xfaa,0xfa7,0xfa3,0xf9f,0xf9b,0xf97,0xf93,
  0xf8f,0xf8b,0xf87,0xf83,0xf7e,0xf7a,0xf75,0xf71,0xf6c,0xf67,
  0xf63,0xf5e,0xf59,0xf54,0xf4f,0xf4a,0xf44,0xf3f,0xf3a,0xf34,
  0xf2f,0xf29,0xf23,0xf1e,0xf18,0xf12,0xf0c,0xf06,0xf00,0xefa,
  0xef4,0xeee,0xee7,0xee1,0xeda,0xed4,0xecd,0xec7,0xec0,0xeb9,
  0xeb2,0xeab,0xea4,0xe9d,0xe96,0xe8f,0xe88,0xe81,0xe79,0xe72,
  0xe6a,0xe63,0xe5b,0xe54,0xe4c,0xe44,0xe3c,0xe34,0xe2c,0xe24,
  0xe1c,0xe14,0xe0c,0xe04,0xdfb,0xdf3,0xdea,0xde2,0xdd9,0xdd1,
  0xdc8,0xdbf,0xdb7,0xdae,0xda5,0xd9c,0xd93,0xd8a,0xd81,0xd78,
  0xd6e,0xd65,0xd5c,0xd52,0xd49,0xd40,0xd36,0xd2c,0xd23,0xd19,
  0xd0f,0xd06,0xcfc,0xcf2,0xce8,0xcde,0xcd4,0xcca,0xcc0,0xcb6,
  0xcac,0xca1,0xc97,0xc8d,0xc82,0xc78,0xc6e,0xc63,0xc59,0xc4e,
  0xc43,0xc39,0xc2e,0xc23,0xc18,0xc0e,0xc03,0xbf8,0xbed,0xbe2,
  0xbd7,0xbcc,0xbc1,0xbb6,0xbaa,0xb9f,0xb94,0xb89,0xb7d,0xb72,
  0xb67,0xb5b,0xb50,0xb44,0xb39,0xb2d,0xb22,0xb16,0xb0b,0xaff,
  0xaf3,0xae8,0xadc,0xad0,0xac4,0xab9,0xaad,0xaa1,0xa95,0xa89,
  0xa7d,0xa71,0xa65,0xa59,0xa4d,0xa41,0xa35,0xa29,0xa1d,0xa11,
  0xa04,0x9f8,0x9ec,0x9e0,0x9d4,0x9c7,0x9bb,0x9af,0x9a2,0x996,
  0x98a,0x97d,0x971,0x965,0x958,0x94c,0x93f,0x933,0x927,0x91a,
  0x90e,0x901,0x8f5,0x8e8,0x8dc,0x8cf,0x8c3,0x8b6,0x8aa,0x89d,
  0x891,0x884,0x877,0x86b,0x85e,0x852,0x845,0x839,0x82c,0x81f,
  0x813,0x806,0x7fa,0x7ed,0x7e1,0x7d4,0x7c7,0x7bb,0x7ae,0x7a2,
  0x795,0x789,0x77c,0x76f,0x763,0x756,0x74a,0x73d,0x731,0x724,
  0x718,0x70b,0x6ff,0x6f2,0x6e6,0x6d9,0x6cd,0x6c1,0x6b4,0x6a8,
  0x69b,0x68f,0x683,0x676,0x66a,0x65e,0x651,0x645,0x639,0x62c,
  0x620,0x614,0x608,0x5fc,0x5ef,0x5e3,0x5d7,0x5cb,0x5bf,0x5b3,
  0x5a7,0x59b,0x58f,0x583,0x577,0x56b,0x55f,0x553,0x547,0x53c,
  0x530,0x524,0x518,0x50d,0x501,0x4f5,0x4ea,0x4de,0x4d3,0x4c7,
  0x4bc,0x4b0,0x4a5,0x499,0x48e,0x483,0x477,0x46c,0x461,0x456,
  0x44a,0x43f,0x434,0x429,0x41e,0x413,0x408,0x3fd,0x3f2,0x3e8,
  0x3dd,0x3d2,0x3c7,0x3bd,0x3b2,0x3a7,0x39d,0x392,0x388,0x37e,
  0x373,0x369,0x35f,0x354,0x34a,0x340,0x336,0x32c,0x322,0x318,
  0x30e,0x304,0x2fa,0x2f1,0x2e7,0x2dd,0x2d4,0x2ca,0x2c0,0x2b7,
  0x2ae,0x2a4,0x29b,0x292,0x288,0x27f,0x276,0x26d,0x264,0x25b,
  0x252,0x249,0x241,0x238,0x22f,0x227,0x21e,0x216,0x20d,0x205,
  0x1fc,0x1f4,0x1ec,0x1e4,0x1dc,0x1d4,0x1cc,0x1c4,0x1bc,0x1b4,
  0x1ac,0x1a5,0x19d,0x196,0x18e,0x187,0x17f,0x178,0x171,0x16a,
  0x163,0x15c,0x155,0x14e,0x147,0x140,0x139,0x133,0x12c,0x126,
  0x11f,0x119,0x112,0x10c,0x106,0x100,0xfa,0xf4,0xee,0xe8,
  0xe2,0xdd,0xd7,0xd1,0xcc,0xc6,0xc1,0xbc,0xb6,0xb1,
  0xac,0xa7,0xa2,0x9d,0x99,0x94,0x8f,0x8b,0x86,0x82,
  0x7d,0x79,0x75,0x71,0x6d,0x69,0x65,0x61,0x5d,0x59,
  0x56,0x52,0x4f,0x4b,0x48,0x45,0x41,0x3e,0x3b,0x38,
  0x35,0x33,0x30,0x2d,0x2b,0x28,0x26,0x23,0x21,0x1f,
  0x1d,0x1b,0x19,0x17,0x15,0x13,0x11,0x10,0xe,0xd,
  0xb,0xa,0x9,0x8,0x7,0x6,0x5,0x4,0x3,0x3,
  0x2,0x2,0x1,0x1,0x0,0x0,0x0,0x0,0x0,0x0,
  0x0,0x1,0x1,0x1,0x2,0x2,0x3,0x4,0x4,0x5,
  0x6,0x7,0x8,0xa,0xb,0xc,0xe,0xf,0x11,0x12,
  0x14,0x16,0x18,0x1a,0x1c,0x1e,0x20,0x22,0x24,0x27,
  0x29,0x2c,0x2e,0x31,0x34,0x37,0x3a,0x3d,0x40,0x43,
  0x46,0x49,0x4d,0x50,0x54,0x57,0x5b,0x5f,0x63,0x67,
  0x6b,0x6f,0x73,0x77,0x7b,0x7f,0x84,0x88,0x8d,0x92,
  0x96,0x9b,0xa0,0xa5,0xaa,0xaf,0xb4,0xb9,0xbe,0xc4,
  0xc9,0xcf,0xd4,0xda,0xdf,0xe5,0xeb,0xf1,0xf7,0xfd,
  0x103,0x109,0x10f,0x116,0x11c,0x122,0x129,0x12f,0x136,0x13d,
  0x143,0x14a,0x151,0x158,0x15f,0x166,0x16d,0x174,0x17c,0x183,
  0x18a,0x192,0x199,0x1a1,0x1a9,0x1b0,0x1b8,0x1c0,0x1c8,0x1d0,
  0x1d8,0x1e0,0x1e8,0x1f0,0x1f8,0x201,0x209,0x211,0x21a,0x222,
  0x22b,0x234,0x23c,0x245,0x24e,0x257,0x260,0x269,0x272,0x27b,
  0x284,0x28d,0x296,0x2a0,0x2a9,0x2b2,0x2bc,0x2c5,0x2cf,0x2d8,
  0x2e2,0x2ec,0x2f5,0x2ff,0x309,0x313,0x31d,0x327,0x331,0x33b,
  0x345,0x34f,0x359,0x364,0x36e,0x378,0x383,0x38d,0x398,0x3a2,
  0x3ad,0x3b7,0x3c2,0x3cd,0x3d7,0x3e2,0x3ed,0x3f8,0x403,0x40e,
  0x419,0x424,0x42f,0x43a,0x445,0x450,0x45b,0x466,0x472,0x47d,
  0x488,0x494,0x49f,0x4aa,0x4b6,0x4c1,0x4cd,0x4d8,0x4e4,0x4f0,
  0x4fb,0x507,0x513,0x51e,0x52a,0x536,0x542,0x54d,0x559,0x565,
  0x571,0x57d,0x589,0x595,0x5a1,0x5ad,0x5b9,0x5c5,0x5d1,0x5dd,
  0x5e9,0x5f6,0x602,0x60e,0x61a,0x626,0x633,0x63f,0x64b,0x657,
  0x664,0x670,0x67c,0x689,0x695,0x6a2,0x6ae,0x6ba,0x6c7,0x6d3,
  0x6e0,0x6ec,0x6f9,0x705,0x712,0x71e,0x72b,0x737,0x744,0x750,
  0x75d,0x769,0x776,0x782,0x78f,0x79b,0x7a8,0x7b5,0x7c1,0x7ce,
  0x7da,0x7e7,0x7f3,0x800
};

const int wave[1024] 
{
  0x0,0x10,0x20,0x30,0x40,0x4f,0x5f,0x6f,0x7e,0x8e,
  0x9d,0xac,0xbc,0xcb,0xda,0xe9,0xf8,0x107,0x116,0x125,
  0x134,0x143,0x152,0x160,0x16f,0x17d,0x18c,0x19a,0x1a9,0x1b7,
  0x1c5,0x1d4,0x1e2,0x1f0,0x1fe,0x20c,0x21a,0x228,0x236,0x243,
  0x251,0x25f,0x26c,0x27a,0x287,0x295,0x2a2,0x2b0,0x2bd,0x2ca,
  0x2d7,0x2e5,0x2f2,0x2ff,0x30c,0x319,0x325,0x332,0x33f,0x34c,
  0x359,0x365,0x372,0x37e,0x38b,0x397,0x3a4,0x3b0,0x3bc,0x3c9,
  0x3d5,0x3e1,0x3ed,0x3f9,0x405,0x411,0x41d,0x429,0x435,0x440,
  0x44c,0x458,0x464,0x46f,0x47b,0x486,0x492,0x49d,0x4a8,0x4b4,
  0x4bf,0x4ca,0x4d6,0x4e1,0x4ec,0x4f7,0x502,0x50d,0x518,0x523,
  0x52e,0x538,0x543,0x54e,0x559,0x563,0x56e,0x578,0x583,0x58d,
  0x598,0x5a2,0x5ad,0x5b7,0x5c1,0x5cb,0x5d6,0x5e0,0x5ea,0x5f4,
  0x5fe,0x608,0x612,0x61c,0x626,0x630,0x639,0x643,0x64d,0x657,
  0x660,0x66a,0x673,0x67d,0x686,0x690,0x699,0x6a3,0x6ac,0x6b5,
  0x6bf,0x6c8,0x6d1,0x6da,0x6e3,0x6ed,0x6f6,0x6ff,0x708,0x711,
  0x71a,0x722,0x72b,0x734,0x73d,0x746,0x74e,0x757,0x760,0x768,
  0x771,0x779,0x782,0x78a,0x793,0x79b,0x7a4,0x7ac,0x7b4,0x7bd,
  0x7c5,0x7cd,0x7d5,0x7de,0x7e6,0x7ee,0x7f6,0x7fe,0x806,0x80e,
  0x816,0x81e,0x826,0x82d,0x835,0x83d,0x845,0x84c,0x854,0x85c,
  0x863,0x86b,0x873,0x87a,0x882,0x889,0x891,0x898,0x89f,0x8a7,
  0x8ae,0x8b5,0x8bd,0x8c4,0x8cb,0x8d2,0x8da,0x8e1,0x8e8,0x8ef,
  0x8f6,0x8fd,0x904,0x90b,0x912,0x919,0x920,0x927,0x92d,0x934,
  0x93b,0x942,0x949,0x94f,0x956,0x95d,0x963,0x96a,0x970,0x977,
  0x97e,0x984,0x98b,0x991,0x997,0x99e,0x9a4,0x9ab,0x9b1,0x9b7,
  0x9bd,0x9c4,0x9ca,0x9d0,0x9d6,0x9dc,0x9e3,0x9e9,0x9ef,0x9f5,
  0x9fb,0xa01,0xa07,0xa0d,0xa13,0xa19,0xa1f,0xa25,0xa2a,0xa30,
  0xa36,0xa3c,0xa42,0xa47,0xa4d,0xa53,0xa58,0xa5e,0xa64,0xa69,
  0xa6f,0xa74,0xa7a,0xa7f,0xa85,0xa8a,0xa90,0xa95,0xa9b,0xaa0,
  0xaa5,0xaab,0xab0,0xab5,0xabb,0xac0,0xac5,0xaca,0xad0,0xad5,
  0xada,0xadf,0xae4,0xae9,0xaee,0xaf4,0xaf9,0xafe,0xb03,0xb08,
  0xb0d,0xb12,0xb16,0xb1b,0xb20,0xb25,0xb2a,0xb2f,0xb34,0xb38,
  0xb3d,0xb42,0xb47,0xb4b,0xb50,0xb55,0xb59,0xb5e,0xb63,0xb67,
  0xb6c,0xb70,0xb75,0xb7a,0xb7e,0xb83,0xb87,0xb8c,0xb90,0xb94,
  0xb99,0xb9d,0xba2,0xba6,0xbaa,0xbaf,0xbb3,0xbb7,0xbbc,0xbc0,
  0xbc4,0xbc8,0xbcd,0xbd1,0xbd5,0xbd9,0xbdd,0xbe1,0xbe5,0xbea,
  0xbee,0xbf2,0xbf6,0xbfa,0xbfe,0xc02,0xc06,0xc0a,0xc0e,0xc12,
  0xc16,0xc1a,0xc1d,0xc21,0xc25,0xc29,0xc2d,0xc31,0xc34,0xc38,
  0xc3c,0xc40,0xc44,0xc47,0xc4b,0xc4f,0xc52,0xc56,0xc5a,0xc5d,
  0xc61,0xc65,0xc68,0xc6c,0xc6f,0xc73,0xc77,0xc7a,0xc7e,0xc81,
  0xc85,0xc88,0xc8c,0xc8f,0xc92,0xc96,0xc99,0xc9d,0xca0,0xca3,
  0xca7,0xcaa,0xcad,0xcb1,0xcb4,0xcb7,0xcbb,0xcbe,0xcc1,0xcc4,
  0xcc8,0xccb,0xcce,0xcd1,0xcd4,0xcd8,0xcdb,0xcde,0xce1,0xce4,
  0xce7,0xcea,0xced,0xcf0,0xcf4,0xcf7,0xcfa,0xcfd,0xd00,0xd03,
  0xd06,0xd09,0xd0c,0xd0f,0xd11,0xd14,0xd17,0xd1a,0xd1d,0xd20,
  0xd23,0xd26,0xd29,0xd2b,0xd2e,0xd31,0xd34,0xd37,0xd39,0xd3c,
  0xd3f,0xd42,0xd44,0xd47,0xd4a,0xd4d,0xd4f,0xd52,0xd55,0xd57,
  0xd5a,0xd5d,0xd5f,0xd62,0xd65,0xd67,0xd6a,0xd6c,0xd6f,0xd71,
  0xd74,0xd77,0xd79,0xd7c,0xd7e,0xd81,0xd83,0xd86,0xd88,0xd8b,
  0xd8d,0xd8f,0xd92,0xd94,0xd97,0xd99,0xd9c,0xd9e,0xda0,0xda3,
  0xda5,0xda7,0xdaa,0xdac,0xdae,0xdb1,0xdb3,0xdb5,0xdb8,0xdba,
  0xdbc,0xdbe,0xdc1,0xdc3,0xdc5,0xdc7,0xdca,0xdcc,0xdce,0xdd0,
  0xdd2,0xdd5,0xdd7,0xdd9,0xddb,0xddd,0xddf,0xde1,0xde4,0xde6,
  0xde8,0xdea,0xdec,0xdee,0xdf0,0xdf2,0xdf4,0xdf6,0xdf8,0xdfa,
  0xdfc,0xdfe,0xe00,0xe02,0xe04,0xe06,0xe08,0xe0a,0xe0c,0xe0e,
  0xe10,0xe12,0xe14,0xe16,0xe18,0xe1a,0xe1c,0xe1e,0xe1f,0xe21,
  0xe23,0xe25,0xe27,0xe29,0xe2b,0xe2c,0xe2e,0xe30,0xe32,0xe34,
  0xe35,0xe37,0xe39,0xe3b,0xe3d,0xe3e,0xe40,0xe42,0xe44,0xe45,
  0xe47,0xe49,0xe4a,0xe4c,0xe4e,0xe50,0xe51,0xe53,0xe55,0xe56,
  0xe58,0xe5a,0xe5b,0xe5d,0xe5e,0xe60,0xe62,0xe63,0xe65,0xe67,
  0xe68,0xe6a,0xe6b,0xe6d,0xe6f,0xe70,0xe72,0xe73,0xe75,0xe76,
  0xe78,0xe79,0xe7b,0xe7c,0xe7e,0xe7f,0xe81,0xe82,0xe84,0xe85,
  0xe87,0xe88,0xe8a,0xe8b,0xe8d,0xe8e,0xe90,0xe91,0xe92,0xe94,
  0xe95,0xe97,0xe98,0xe9a,0xe9b,0xe9c,0xe9e,0xe9f,0xea0,0xea2,
  0xea3,0xea5,0xea6,0xea7,0xea9,0xeaa,0xeab,0xead,0xeae,0xeaf,
  0xeb1,0xeb2,0xeb3,0xeb5,0xeb6,0xeb7,0xeb8,0xeba,0xebb,0xebc,
  0xebd,0xebf,0xec0,0xec1,0xec2,0xec4,0xec5,0xec6,0xec7,0xec9,
  0xeca,0xecb,0xecc,0xecd,0xecf,0xed0,0xed1,0xed2,0xed3,0xed5,
  0xed6,0xed7,0xed8,0xed9,0xeda,0xedb,0xedd,0xede,0xedf,0xee0,
  0xee1,0xee2,0xee3,0xee5,0xee6,0xee7,0xee8,0xee9,0xeea,0xeeb,
  0xeec,0xeed,0xeee,0xeef,0xef0,0xef2,0xef3,0xef4,0xef5,0xef6,
  0xef7,0xef8,0xef9,0xefa,0xefb,0xefc,0xefd,0xefe,0xeff,0xf00,
  0xf01,0xf02,0xf03,0xf04,0xf05,0xf06,0xf07,0xf08,0xf09,0xf0a,
  0xf0b,0xf0c,0xf0d,0xf0e,0xf0e,0xf0f,0xf10,0xf11,0xf12,0xf13,
  0xf14,0xf15,0xf16,0xf17,0xf18,0xf19,0xf1a,0xf1a,0xf1b,0xf1c,
  0xf1d,0xf1e,0xf1f,0xf20,0xf21,0xf22,0xf22,0xf23,0xf24,0xf25,
  0xf26,0xf27,0xf28,0xf28,0xf29,0xf2a,0xf2b,0xf2c,0xf2d,0xf2d,
  0xf2e,0xf2f,0xf30,0xf31,0xf31,0xf32,0xf33,0xf34,0xf35,0xf35,
  0xf36,0xf37,0xf38,0xf39,0xf39,0xf3a,0xf3b,0xf3c,0xf3c,0xf3d,
  0xf3e,0xf3f,0xf40,0xf40,0xf41,0xf42,0xf42,0xf43,0xf44,0xf45,
  0xf45,0xf46,0xf47,0xf48,0xf48,0xf49,0xf4a,0xf4a,0xf4b,0xf4c,
  0xf4d,0xf4d,0xf4e,0xf4f,0xf4f,0xf50,0xf51,0xf51,0xf52,0xf53,
  0xf53,0xf54,0xf55,0xf55,0xf56,0xf57,0xf57,0xf58,0xf59,0xf59,
  0xf5a,0xf5b,0xf5b,0xf5c,0xf5d,0xf5d,0xf5e,0xf5f,0xf5f,0xf60,
  0xf60,0xf61,0xf62,0xf62,0xf63,0xf64,0xf64,0xf65,0xf65,0xf66,
  0xf67,0xf67,0xf68,0xf68,0xf69,0xf6a,0xf6a,0xf6b,0xf6b,0xf6c,
  0xf6c,0xf6d,0xf6e,0xf6e,0xf6f,0xf6f,0xf70,0xf70,0xf71,0xf72,
  0xf72,0xf73,0xf73,0xf74,0xf74,0xf75,0xf75,0xf76,0xf76,0xf77,
  0xf78,0xf78,0xf79,0xf79,0xf7a,0xf7a,0xf7b,0xf7b,0xf7c,0xf7c,
  0xf7d,0xf7d,0xf7e,0xf7e,0xf7f,0xf7f,0xf80,0xf80,0xf81,0xf81,
  0xf82,0xf82,0xf83,0xf83,0xf84,0xf84,0xf85,0xf85,0xf86,0xf86,
  0xf87,0xf87,0xf88,0xf88,0xf89,0xf89,0xf89,0xf8a,0xf8a,0xf8b,
  0xf8b,0xf8c,0xf8c,0xf8d,0xf8d,0xf8e,0xf8e,0xf8e,0xf8f,0xf8f,
  0xf90,0xf90,0xf91,0xf91,0xf92,0xf92,0xf92,0xf93,0xf93,0xf94,
  0xf94,0xf94,0xf95,0xf95,0xf96,0xf96,0xf97,0xf97,0xf97,0xf98,
  0xf98,0xf99,0xf99,0xf99,0xf9a,0xf9a,0xf9b,0xf9b,0xf9b,0xf9c,
  0xf9c,0xf9d,0xf9d,0xf9d,0xf9e,0xf9e,0xf9f,0xf9f,0xf9f,0xfa0,
  0xfa0,0xfa0,0xfa1,0xfa1,0xfa2,0xfa2,0xfa2,0xfa3,0xfa3,0xfa3,
  0xfa4,0xfa4,0xfa4,0xfa5,0xfa5,0xfa5,0xfa6,0xfa6,0xfa7,0xfa7,
  0xfa7,0xfa8,0xfa8,0xfa8,0xfa9,0xfa9,0xfa9,0xfaa,0xfaa,0xfaa,
  0xfab,0xfab,0xfab,0xfac,0xfac,0xfac,0xfad,0xfad,0xfad,0xfae,
  0xfae,0xfae,0xfaf,0xfaf,0xfaf,0xfb0,0xfb0,0xfb0,0xfb0,0xfb1,
  0xfb1,0xfb1,0xfb2,0xfb2,0xfb2,0xfb3,0xfb3,0xfb3,0xfb3,0xfb4,
  0xfb4,0xfb4,0xfb5,0xfb5
};

void generate(double coef, bool val, int h)
{
   for(int tmr = 0; tmr < 100*coef; ++tmr)
   {             
    for(int i = 0; i < 1024; i+=h*coef)
    {            
      if (val)
        analogWrite(DAC1, sinus[i]);                   
      else 
        analogWrite(DAC1, wave[i]);
    }
  }
}

void setup()
{
 analogWriteResolution(12);
 
 pinMode (8, OUTPUT);
 pinMode (7, OUTPUT);
 pinMode (6, OUTPUT);
 pinMode (5, OUTPUT);
  
 pinMode (12, INPUT); 
 digitalWrite(12, HIGH);
 pinMode (11, INPUT);
 digitalWrite(11, HIGH);
 pinMode (10, INPUT);
 digitalWrite(10, HIGH);
 pinMode (9, INPUT);
 digitalWrite(9, HIGH);
 
 pinMode(DAC1, OUTPUT);
}


void loop()
{
  char key = keypad.getKey();
  switch (key)
  {
    default:
      break;
    case '1':
      generate(1, val, h);
      break;
    case '2':
      generate(2, val, h);
      break;
    case '3':
      generate(3, val, h);
      break;
    case '4':
      generate(4, val, h);
      break;
    case '5':
      generate(5, val, h);
      break;
    case '6':
      generate(6, val, h);
      break;
    case '7':
      generate(7, val, h);
      break;
    case '8':
      generate(8, val, h);
      break;
    case '9':
      generate(9, val, h);
      break;
    case 'A':
      val = !val;
      break;
    case 'B':
      if (h < 10)
        ++h;
      else 
        h = 1;
      break;
  }
}