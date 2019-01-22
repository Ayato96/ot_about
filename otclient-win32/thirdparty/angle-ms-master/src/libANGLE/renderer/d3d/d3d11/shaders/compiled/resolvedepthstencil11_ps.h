#if 0
//
// Generated by Microsoft (R) HLSL Shader Compiler 6.3.9600.16384
//
//
// Resource Bindings:
//
// Name                                 Type  Format         Dim Slot Elements
// ------------------------------ ---------- ------- ----------- ---- --------
// Depth                             texture   float        2dMS    0        1
// Stencil                           texture   uint2        2dMS    1        1
//
//
//
// Input signature:
//
// Name                 Index   Mask Register SysValue  Format   Used
// -------------------- ----- ------ -------- -------- ------- ------
// SV_Position              0   xyzw        0      POS   float       
// TEXCOORD                 0   xy          1     NONE   float   xy  
//
//
// Output signature:
//
// Name                 Index   Mask Register SysValue  Format   Used
// -------------------- ----- ------ -------- -------- ------- ------
// SV_Target                0   xy          0   TARGET   float   xy  
//
ps_4_1
dcl_globalFlags refactoringAllowed
dcl_resource_texture2dms(0) (float,float,float,float) t0
dcl_resource_texture2dms(0) (uint,uint,uint,uint) t1
dcl_input_ps linear v1.xy
dcl_output o0.xy
dcl_temps 1
resinfo_uint r0.xy, l(0), t0.xyzw
utof r0.xy, r0.xyxx
mul r0.xy, r0.xyxx, v1.xyxx
ftou r0.xy, r0.xyxx
mov r0.zw, l(0,0,0,0)
ldms r0.z, r0.xyzw, t1.xzyw, l(0)
ldms r0.x, r0.xyww, t0.xyzw, l(0)
mov o0.x, r0.x
utof o0.y, r0.z
ret 
// Approximately 10 instruction slots used
#endif

const BYTE g_PS_ResolveDepthStencil[] = {
    68,  88,  66,  67,  229, 191, 254, 12,  10,  19,  181, 162, 222, 203, 244, 146, 104, 226, 195,
    177, 1,   0,   0,   0,   40,  3,   0,   0,   5,   0,   0,   0,   52,  0,   0,   0,   216, 0,
    0,   0,   48,  1,   0,   0,   100, 1,   0,   0,   172, 2,   0,   0,   82,  68,  69,  70,  156,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   2,   0,   0,   0,   28,  0,   0,   0,
    1,   4,   255, 255, 0,   1,   0,   0,   106, 0,   0,   0,   92,  0,   0,   0,   2,   0,   0,
    0,   5,   0,   0,   0,   6,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,
    0,   0,   1,   0,   0,   0,   98,  0,   0,   0,   2,   0,   0,   0,   4,   0,   0,   0,   6,
    0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   5,   0,   0,   0,
    68,  101, 112, 116, 104, 0,   83,  116, 101, 110, 99,  105, 108, 0,   77,  105, 99,  114, 111,
    115, 111, 102, 116, 32,  40,  82,  41,  32,  72,  76,  83,  76,  32,  83,  104, 97,  100, 101,
    114, 32,  67,  111, 109, 112, 105, 108, 101, 114, 32,  54,  46,  51,  46,  57,  54,  48,  48,
    46,  49,  54,  51,  56,  52,  0,   73,  83,  71,  78,  80,  0,   0,   0,   2,   0,   0,   0,
    8,   0,   0,   0,   56,  0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   3,   0,   0,
    0,   0,   0,   0,   0,   15,  0,   0,   0,   68,  0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   3,   0,   0,   0,   1,   0,   0,   0,   3,   3,   0,   0,   83,  86,  95,  80,  111,
    115, 105, 116, 105, 111, 110, 0,   84,  69,  88,  67,  79,  79,  82,  68,  0,   171, 171, 171,
    79,  83,  71,  78,  44,  0,   0,   0,   1,   0,   0,   0,   8,   0,   0,   0,   32,  0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   3,   0,   0,   0,   0,   0,   0,   0,   3,   12,
    0,   0,   83,  86,  95,  84,  97,  114, 103, 101, 116, 0,   171, 171, 83,  72,  68,  82,  64,
    1,   0,   0,   65,  0,   0,   0,   80,  0,   0,   0,   106, 8,   0,   1,   88,  32,  0,   4,
    0,   112, 16,  0,   0,   0,   0,   0,   85,  85,  0,   0,   88,  32,  0,   4,   0,   112, 16,
    0,   1,   0,   0,   0,   68,  68,  0,   0,   98,  16,  0,   3,   50,  16,  16,  0,   1,   0,
    0,   0,   101, 0,   0,   3,   50,  32,  16,  0,   0,   0,   0,   0,   104, 0,   0,   2,   1,
    0,   0,   0,   61,  16,  0,   7,   50,  0,   16,  0,   0,   0,   0,   0,   1,   64,  0,   0,
    0,   0,   0,   0,   70,  126, 16,  0,   0,   0,   0,   0,   86,  0,   0,   5,   50,  0,   16,
    0,   0,   0,   0,   0,   70,  0,   16,  0,   0,   0,   0,   0,   56,  0,   0,   7,   50,  0,
    16,  0,   0,   0,   0,   0,   70,  0,   16,  0,   0,   0,   0,   0,   70,  16,  16,  0,   1,
    0,   0,   0,   28,  0,   0,   5,   50,  0,   16,  0,   0,   0,   0,   0,   70,  0,   16,  0,
    0,   0,   0,   0,   54,  0,   0,   8,   194, 0,   16,  0,   0,   0,   0,   0,   2,   64,  0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   46,  0,
    0,   9,   66,  0,   16,  0,   0,   0,   0,   0,   70,  14,  16,  0,   0,   0,   0,   0,   134,
    125, 16,  0,   1,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   0,   46,  0,   0,   9,
    18,  0,   16,  0,   0,   0,   0,   0,   70,  15,  16,  0,   0,   0,   0,   0,   70,  126, 16,
    0,   0,   0,   0,   0,   1,   64,  0,   0,   0,   0,   0,   0,   54,  0,   0,   5,   18,  32,
    16,  0,   0,   0,   0,   0,   10,  0,   16,  0,   0,   0,   0,   0,   86,  0,   0,   5,   34,
    32,  16,  0,   0,   0,   0,   0,   42,  0,   16,  0,   0,   0,   0,   0,   62,  0,   0,   1,
    83,  84,  65,  84,  116, 0,   0,   0,   10,  0,   0,   0,   1,   0,   0,   0,   0,   0,   0,
    0,   2,   0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   2,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   2,   0,   0,   0,   0,   0,   0,   0,   3,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0};
