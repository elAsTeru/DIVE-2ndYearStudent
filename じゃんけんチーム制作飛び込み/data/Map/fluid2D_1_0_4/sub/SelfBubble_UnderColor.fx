//���ʉ��I�u�W�F�N�g�p�V�F�[�_
//MRT0�F�@��
shared texture UnderNormal: RENDERCOLORTARGET;
//MRT1�F���W
shared texture UnderPos: RENDERCOLORTARGET;
//�[�x�X�e���V��
shared texture UnderDepthBuffer : RENDERDEPTHSTENCILTARGET;



//�e�N�X�`����
#define TEXNAME "../Texture/NormalBase.png"

//�e�N�X�`��������
#define TEXSPLIT 1

// �\�[�g��L���ɂ���Ȃ�1
// �K�v�Ȃ��������r���Ă݂����Ƃ���0
#define SORT_ENABLE 1

// �p�[�e�B�N���̍ő�\�����A�ő��65536
// 4096,16384�𒴂���ƃ\�[�g�����̊֌W�Œi�K�I�ɏd���Ȃ�̂Œ���
#define PARTICLE_COUNT 65536

//�����������x
float MinSpd = 0.0f;
//�ő��]���x
float RotationSpdMax = 10;

// �F(�e�N�X�`���̐F�ɏ�Z)
float4 ParticleColor = float4(1,1,1,1);



// ���Z�F(RGB)
//���F������
//�E�F������
float3 AddColorByLife[2] = { float3(0,0,0),float3(0,0,0)};
//�F�ω����x
float AddColorPower = 20;
//�@�������_�ɂ����Z�̗}��
float AddColorEyeAddjust = 1;

//�p�[�e�B�N���o�Ղ�
float CoefProbable = 0.002;

//���ˑ��x�ő�l
float ShotSpd = 0.025;
//���ˑ��x�����_�����Z�l
float RndSpd = 0.025;

//���ˎ������_���p�x(1.0��360�x����)
float ShotRand = 1;
//�����_�����ˊp�x��炬��
float RndShotYuragi = 0.5;
//�����_�����ˊp�x��炬���x
float RndShotYuragiSpd = 10;

//�����ӏ������_����XYZ
float3 PosRand = float3(0,0,0);

//�����ő�l
float Life = 10;

//���������_�����Z�l
float RndLife = 0.1;

//�d��
float3 Grv = float3(0,-0.025,0);

//���ˎ��̌���
float3 CollisionDrag = float3(1,1,1)*0.1;
//���ˎ��̎��������i0�Ŗ��� 1.0�ő�����)
float CollisionLifeDown = 0;

//���ڐG���̃����_���p�x�ύX��
float CollisionRandSp = 0.25;

//�ڐG���̃����_���p�x�Ό���
float CollisionRandPl = 0.25;

//�X�N���[���ڐG���̃����_���p�x�Ό���
float CollisionRandSS = 0.1;

//��肻���x
float Attract = 1;

//����t�����A���x������
float StickDownSpd = 0.9;
//����t�����A�d�͕����ւ̂�������x�i0�œ����Ȃ��j
float StickFallSpd = 0;
//����t�����A��������͌�����
float StickFallLife = 2;

//��C��R
float AirDrag = 0.92;

//�����_����炬��
float RndYuragi = 0;

//������l
float Scale = 1;
//�傫�������_�����Z�l
float RandScale = 0.5;

float ScaleByLife[3] = {0,1,0.8};

//�傫���ω����x
float ScalePower = 16;

//�_�ŗ�(0�œ_�ł��Ȃ��B1���ő�j
float Flick = 0;
//�_�ő��x
float FlickSpd = 1.0;

// �����蔻��
#define SSBOUNCE	1		// �����蔻���L���ɂ���
float BounceFactor = 0;		// �Փˎ��̒��˕Ԃ藦�B0�`1
float FrictionFactor = 1.0;		// �Փˎ��̌������B1�Ō������Ȃ��B
float IgnoreDpethOffset = 10;		// �\�ʂ�肱��ȏ��̃p�[�e�B�N���͏Փ˂𖳎�����


// (������)��Ԃ̗�������`����֐�
// ���q�ʒuParticlePos�ɂ������C�̗�����L�q���܂��B
// �߂�l��0�ȊO�̎��̓I�u�W�F�N�g�������Ȃ��Ă����q����o���܂��B
// ���x��R�W����ResistFactor>0�łȂ��Ɨ��q�̓����ɉe����^���܂���B
float3 VelocityField(float3 ParticlePos)
{
   float3 vel = float3( 0.0, 0.0, 0.0 );
   return vel;
}

float NowScaleByLife(float t)
{
	float ret = 0;
	if(t > 0.5)
	{
		ret = lerp(ScaleByLife[1],ScaleByLife[0],(t-0.5)*2);
	}else{
		ret = lerp(ScaleByLife[2],ScaleByLife[1],t*2);
	}
	return ret;
}

//================================================================================================//
#include "../function/rotate.fxsub"
// �p�����[�^�錾

#if(PARTICLE_COUNT>65536)
	#error �p�[�e�B�N���̏�����I�[�o�[���Ă��܂��I
#elif(PARTICLE_COUNT>16384)
	#define TEX_SIZE 256
#elif(PARTICLE_COUNT>4096)
	#define TEX_SIZE 128
#else
	#define TEX_SIZE 64
#endif

int count = PARTICLE_COUNT;


float3 LightAmbient : AMBIENT < string Object = "Light"; >;
float3 CameraPosition	: POSITION  < string Object = "Camera"; >;
float3 LightDirection	: DIRECTION < string Object = "Light"; >;


//------------------------------------------------------------------------------------------------//
// �J�����̃p�����[�^

// ���@�ϊ��s��
float4x4 ViewMatrix		: VIEW;
float4x4 WorldViewMatrix		: WORLDVIEW;
float4x4 WVP		: WORLDVIEWPROJECTION;
float4x4 ViewProjMatrix				: VIEWPROJECTION;
float4x4 ProjMatrix				: PROJECTION;
float4x4 WorldMatrix : WORLD;
float4x4 LightViewProjMatrix : VIEWPROJECTION < string Object = "Light"; >;
float4x4 LightWorldViewProjMatrix : WORLDVIEWPROJECTION < string Object = "Light"; >;

//------------------------------------------------------------------------------------------------//
// �e�N�X�`���ƃT���v��

texture BaseTex< string ResourceName = TEXNAME; >;
sampler BaseSamp = sampler_state {
	texture = <BaseTex>;
	MINFILTER = ANISOTROPIC;
	MAGFILTER = ANISOTROPIC;
	MIPFILTER = LINEAR;
	MAXANISOTROPY = 16;
	AddressU = WRAP;
	AddressV = WRAP;
};

//�����e�N�X�`��
texture2D rndtex < string ResourceName = "../function/random512x512.bmp"; >;
sampler rnd = sampler_state {
	texture = <rndtex>;
	FILTER = NONE;
};
sampler rnd_linear = sampler_state {
	texture = <rndtex>;
	FILTER = LINEAR;
};

//�����e�N�X�`���T�C�Y
#define RNDTEX_WIDTH  512
#define RNDTEX_HEIGHT 512

float Random(float p)
{
    return frac(sin(dot(normalize(float2(p,p*13.456)), float2(12.9898,78.233))) * 43758.5453);
}

//�����擾
float4 getRandom(float rindex)
{
	float2 tpos = float2(rindex % RNDTEX_WIDTH, trunc(rindex / RNDTEX_WIDTH));
	tpos += float2(0.5,0.5);
	tpos /= float2(RNDTEX_WIDTH, RNDTEX_HEIGHT);
	return tex2Dlod(rnd, float4(tpos,0,1));
}
float4 getRandom_calc(float rindex)
{
	return float4(Random(rindex*123.456),Random(rindex*234.567),Random(rindex*345.678),Random(rindex*456.789));
}
float4 getRandomLinear(float rindex)
{
	float2 tpos = float2(rindex % RNDTEX_WIDTH, trunc(rindex / RNDTEX_WIDTH));
	tpos += float2(0.5,0.5);
	tpos /= float2(RNDTEX_WIDTH, RNDTEX_HEIGHT);
	return tex2Dlod(rnd_linear, float4(tpos,0,1));
}
//�\�t�g�p�[�e�B�N���G���W���p�[�x�e�N�X�`��
shared texture2D SPE_DepthTex : RENDERCOLORTARGET;
sampler2D SPE_DepthSamp = sampler_state {
	texture = <SPE_DepthTex>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = NONE;
	AddressU  = CLAMP;
	AddressV = CLAMP;
};
// �p�[�e�B�N�����W��ۑ�����e�N�X�`��
shared texture2D ParticlePosTex_SB1 : RENDERCOLORTARGET;
sampler2D ParticlePosSamp = sampler_state {
	texture = <ParticlePosTex_SB1>;
	Filter = NONE;
	AddressU = CLAMP; AddressV = CLAMP;
};
// �p�[�e�B�N�����x�Ǝ�����ۑ�����e�N�X�`��
shared texture2D ParticleVecTex_SB1 : RENDERCOLORTARGET;
sampler2D ParticleVecSamp = sampler_state {
	texture = <ParticleVecTex_SB1>;
	Filter = NONE;
	AddressU = CLAMP; AddressV = CLAMP;
};
// �ڐG���ƖڕW�p�x
shared texture2D ParticleNormTex_SB1 : RENDERCOLORTARGET;
sampler2D ParticleNormSamp = sampler_state {
	texture = <ParticleNormTex_SB1>;
	Filter = NONE;
	AddressU = CLAMP; AddressV = CLAMP;
};

bool     parthf;   // �p�[�X�y�N�e�B�u�t���O
#define SKII1    1500
#define SKII2    8000
#define Toon     3

// �V���h�E�o�b�t�@�̃T���v���B"register(s0)"�Ȃ̂�MMD��s0���g���Ă��邩��
sampler DefSampler : register(s0);

//------------------------------------------------------------------------------------------------//
// �\�t�g�p�[�e�B�N���G���W���̃p�����[�^

//�\�t�g�p�[�e�B�N���G���W���g�p�t���O
bool use_spe : CONTROLOBJECT < string name = "SoftParticleEngine.x"; >;


//------------------------------------------------------------------------------------------------//
// �o�C�g�j�b�N�\�[�g�Ɋւ���p�����[�^


//------------------------------------------------------------------------------------------------//
// ���̑��̃p�����[�^�E�֐�

float time : TIME; //�o�ߎ���
float elapsed_time : ELAPSEDTIME;
static float Dt = (elapsed_time < 0.2f) ? clamp(elapsed_time, 0.001f, 1.0f/15.0f) : 1.0f/30.0f;

float Tr : CONTROLOBJECT < string name = "(self)"; string item = "Tr"; >;
float Si : CONTROLOBJECT < string name = "(self)"; string item = "Si"; >;

float Script : STANDARDSGLOBAL <
	string ScriptOutput = "color";
	string ScriptClass = "sceneorobject";
	string ScriptOrder = "standard";
> = 0.8;

float RndScale(int id)
{
	float4 rnd = getRandom_calc(id);
	
	return rnd.r;
}

// �p�[�e�B�N���̍��W�Ɠ����x������
float4 EffectPosColor(int id)
{
	float3 Pos;

	float index = id;

	// �����_���z�u
	float4 base_pos = getRandom(index) - 0.5;

	// �����x���v�Z
	float alpha = 1;
	
	return float4(base_pos.xyz,alpha);
}

// �e�N�X�`�����W����C���f�b�N�X�����߂�
int TexToIndex(float2 tex, int size, float offset){
	int index = (int)round(tex.x*size-offset)+(int)round(tex.y*size-offset)*size;
	return index;
}

// �C���f�b�N�X����e�N�X�`�����W�����߂�
float2 IndexToTex(int index, int size, float offset){
	float2 tex;
	tex.x = (index%size+offset)/size;
	tex.y = (index/size+offset)/size;
	return tex;
}



//------------------------------------------------------------------------------------------------//
// �p�[�e�B�N���{�̂̕`��

/* ���_�V�F�[�_�[�p�\���� */
struct PTCL_VS_OUTPUT
{
	float4 Pos		: POSITION;		// �ˉe�ϊ����W
	float2 Tex		: TEXCOORD0;	// �e�N�X�`��
	float indexF	: TEXCOORD1;	// �p�[�e�B�N���̃C���f�b�N�X
	float Alpha		: TEXCOORD2;	// �p�[�e�B�N���̓����x
	float4 VPos		: TEXCOORD3;	// �r���[���W
	float3 Normal	: TEXCOORD4;
	float4 ScrPos	: TEXCOORD5;	// �X�N���[�����W
	float3 WPos		: TEXCOORD6;
	float4 pPos		: TEXCOORD7;
	float4 pVec	 	: TEXCOORD8;
	float4 ZCalcTex : TEXCOORD9;
};

float4x4 ViewMatrixInverse        : VIEWINVERSE;
static float3x3 BillboardMatrix = {
    normalize(ViewMatrixInverse[0].xyz),
    normalize(ViewMatrixInverse[1].xyz),
    normalize(ViewMatrixInverse[2].xyz),
};
float4x4 WorldViewProjMatrix      : WORLDVIEWPROJECTION;

/* ���_�V�F�[�_�[ */
PTCL_VS_OUTPUT PtclMain_VS(float4 Pos : POSITION, float2 Tex : TEXCOORD0)
{
	// ������
	PTCL_VS_OUTPUT Out = (PTCL_VS_OUTPUT)0;
	
	// Z�l�����Ƃɂ����C���f�b�N�X
	int indexZ = int(round(Pos.z));
	
	// �\�[�g��̃C���f�b�N�X���擾
	int index = indexZ;//(int)round(tex2Dlod(SortSamp, float4(IndexToTex(indexZ,TEX_SIZE,0.5),0,1)).g);
	
	// �p�[�e�B�N���̃r���[���W�Ɠ����x���擾���Ĉړ�
	float2 PtclTex = IndexToTex(index,TEX_SIZE,0.5);
	float4 PtclData = tex2Dlod(ParticlePosSamp,float4(PtclTex,0,1));
	float4 VecData = tex2Dlod(ParticleVecSamp,float4(PtclTex,0,1));
	float4 NormData = tex2Dlod(ParticleNormSamp,float4(PtclTex,0,1));
	
	Out.Pos = float4(Pos.xy,0,1);
	
	Out.Normal = float3(Pos.xy,-1);
	Out.Normal = normalize(Out.Normal);
	
	float3 PtclPos = PtclData.rgb;
	float fLife = saturate(VecData.a / Life);
	float PtclAlpha = 1 * (1-pow(1-fLife,4));
	
	
	float3 Prev = PtclPos - VecData.xyz*2;
	float3 Now = PtclPos;
	
	//�J�����x�N�g��
	float3 Eye = CameraPosition - lerp(Prev,Now,0.5);
	
	Scale -= RandScale * getRandom_calc(index*1.234).x;
	float FixScale = Scale * NowScaleByLife(pow(saturate(VecData.a/Life),ScalePower));
	
	float4 rndR = getRandom_calc(index*123.456);
		
	//�r���{�[�h����
	Out.Pos.xy *= FixScale;
		
	float3 posbase = Out.Pos.xyz;
	float3 normbase = Out.Normal.xyz;
	float Sc = (RndScale(index));
	if(Sc > 0.995) Sc *= 1.5;
	/*
	//Out.Pos.xy *= Sc*Si;
	// �p�[�e�B�N���ɉ�]��^����
	float rot_z = rndR.x*2*3.1415;
	float3x3 RotationZ = {
		{cos(rot_z), sin(rot_z), 0},
		{-sin(rot_z), cos(rot_z), 0},
		{0, 0, 1},
	};
	float3x3 RevRotationZ = {
		{cos(-rot_z), sin(-rot_z), 0},
		{-sin(-rot_z), cos(-rot_z), 0},
		{0, 0, 1},
	};
	
	Out.Pos.xyz = mul( Out.Pos.xyz, RotationZ );
	Out.Normal.xyz = mul( Out.Normal, RotationZ);
	*/
	/*
	Out.Pos.xyz = RotY_vec(Out.Pos.xyz,rndR.y*2*3.1415 + time*rndR.z*RotationSpdMax);
	Out.Normal.xyz = RotY_vec(Out.Normal.xyz,rndR.y*2*3.1415);
	
	Out.Pos.xyz = RotX_vec(Out.Pos.xyz,rndR.z*2*3.1415 + time*rndR.x*RotationSpdMax);
	Out.Normal.xyz = RotX_vec(Out.Normal.xyz,rndR.z*2*3.1415);
	*/
	
	Out.Pos.xyz = mul( Out.Pos, BillboardMatrix);
	Out.Normal.xyz = mul( Out.Normal, BillboardMatrix);
		
	float3x3 ColTargetMatrix = {
	    normalize(float3(1,0,0)),
	    normalize(getRandom_calc(index*123.456).xyz),
	    normalize(-NormData.xyz),
	};
	ColTargetMatrix[0] = cross(ColTargetMatrix[1],ColTargetMatrix[2]);
	ColTargetMatrix[1] = cross(ColTargetMatrix[0],ColTargetMatrix[2]);
	
	
	Out.Pos.xyz = lerp(Out.Pos.xyz,mul( posbase, ColTargetMatrix),NormData.a);
	Out.Normal.xyz = lerp(Out.Normal.xyz,mul( normbase, ColTargetMatrix),NormData.a);
	
	Out.Pos.xyz += NormData.xyz*NormData.a*0.05;
	Out.Pos.xyz += Now;

	
	Out.WPos = Out.Pos.xyz;
	
	
	// �r���[���W���R�s�[
	Out.VPos = mul(Out.Pos,ViewMatrix);
	// �ˉe�ϊ����s��(���W�̓��[���h�r���[�ϊ��ς݂ł��邽��)
	Out.ZCalcTex = mul( Out.Pos, LightViewProjMatrix );
	Out.Pos = mul( Out.Pos, ViewProjMatrix );
	// �X�N���[�����W���R�s�[
	Out.ScrPos = Out.Pos;
	
	// �e�N�X�`�����W
	Out.Tex = Tex;
	
	Out.indexF = (float)index;
	Out.Alpha = PtclAlpha;
	Out.pPos = PtclData;
	Out.pVec = VecData;
	
	// �ő�\�����𒴂������͔�\���ɂ���
	Out.Pos.z += (indexZ > count) ? 2 : 0;
	//Out.Pos.z += (NormData.a < 0.5) ? 2 : 0;
	//Out.Pos = mul(Pos,WorldViewProjMatrix);
	return Out;
}
float3x3 compute_tangent_frame(float3 Normal, float3 View, float2 UV)
{
  float3 dp1 = ddx(View);
  float3 dp2 = ddy(View);
  float2 duv1 = ddx(UV);
  float2 duv2 = ddy(UV);

  float3x3 M = float3x3(dp1, dp2, cross(dp1, dp2));
  float2x3 inverseM = float2x3(cross(M[1], M[2]), cross(M[2], M[0]));
  float3 Tangent = mul(float2(duv1.x, duv2.x), inverseM);
  float3 Binormal = mul(float2(duv1.y, duv2.y), inverseM);

  return float3x3(normalize(Tangent), normalize(Binormal), Normal);
}
struct PS_OUTPUT {
	float4 Normal : COLOR0;
	float4 Pos : COLOR1;
};

/* �s�N�Z���V�F�[�_�[ */
float4 PtclMain_PS( PTCL_VS_OUTPUT IN) : COLOR0
{
	float3 BaseColor = float3(0.25,0.25,0.25);
	float3 AddColor1 = float3(1,0.5,0)*2;
	float3 AddColor2 = float3(0.8,0,1)*2;
	
	int index = (int)round(IN.indexF);
	
	float2 tex = IN.Tex*(1.0/TEXSPLIT);
	
	tex.x += (index%TEXSPLIT)*(1.0/TEXSPLIT);
	tex.y += ((index/TEXSPLIT)%TEXSPLIT)*(1.0/TEXSPLIT);
	
	float4 Color = tex2D( BaseSamp, tex );
	float3 Eye = CameraPosition - IN.WPos;
	
	float3x3 tangentFrame = compute_tangent_frame(IN.Normal, -normalize(Eye), IN.Tex);
	float4 NormalColor = Color*2;	
	NormalColor = NormalColor.rgba;
	NormalColor.a = 1;
	
	float3 normal = normalize(mul(NormalColor - 1.0f, tangentFrame));
	
	
	float2 ScTex = IN.ScrPos.xyz/IN.ScrPos.w;
	ScTex = ScTex*float2(0.5,-0.5)+float2(0.5,0.5);
	Color.rgb = 1;
	Color.a *= saturate(IN.Alpha);
	float4 LastColor;
	
	LastColor.rgb = Color.rgb;
	LastColor.a = Color.a * ParticleColor.a;
	
	//----�����v�Z
	LastColor.rgb *= LightAmbient+0.7;
	
	float nd = saturate(dot(normal,-LightDirection)*0.25+0.75);
	
	//TOON//
	//nd = saturate(dot(normal,-LightDirection));
	//nd = smoothstep(0.4,0.41,nd);
	//nd = saturate(nd+0.5);
	
	LastColor.rgb *= nd;
	LastColor.rgb *= ParticleColor;
	
	//LastColor.a = smoothstep(0,0.1,LastColor.a);
	
	float fLife = (IN.pVec.a/Life);
	
	float ed = saturate(dot(normal,normalize(Eye)));
	
	LastColor.rgb += lerp(AddColorByLife[1],AddColorByLife[0],pow(fLife,AddColorPower))*saturate(lerp(1,ed,AddColorEyeAddjust));
	LastColor.r = 1;
	float3 HalfVector = normalize( normalize(Eye) + -LightDirection );
    float3 Specular = pow( max(0,dot( HalfVector, normalize(normal) )), 4 );
	LastColor.g = Specular;
	LastColor.b = nd;
	LastColor.rgb *= saturate(LastColor.a);	
	
	
	if(use_spe)
	{
		// �J��������̋���!!
		float dep = length(IN.VPos);
		float scrdep = tex2D(SPE_DepthSamp,ScTex).r;
		
		dep = length(dep-scrdep);
		dep = smoothstep(0,Si*0.1,dep);
		LastColor.a *= dep;
	}
	
	if(IN.indexF == 0) Color = 0;
	
	return LastColor;
}

//------------------------------------------------------------------------------------------------//
// �e�N�j�b�N�ƃp�X

float4 ClearColor = {0,0,0,1};
float ClearDepth  = 1.0;

technique MainTec < string MMDPass = "object";
	string Script = 
		// �p�[�e�B�N���̕\��
		"RenderColorTarget0=;"
		"RenderColorTarget1=;"
		"RenderDepthStencilTarget0=;"
		"Pass=DrawParticle;"
		;
 > {
	pass DrawParticle{
		CULLMODE = NONE;
		AlphaBlendEnable	= true;
		AlphaTestEnable		= true;
		ZEnable				= true;
		ZWriteEnable		= true;
		VertexShader = compile vs_3_0 PtclMain_VS();
		PixelShader  = compile ps_3_0 PtclMain_PS();
	}
}

technique ZplotTec < string MMDPass = "zplot"; > {}
technique EdgeTec < string MMDPass = "edge"; > {}
technique ShadowTec < string MMDPass = "shadow"; > {}


//================================================================================================//
