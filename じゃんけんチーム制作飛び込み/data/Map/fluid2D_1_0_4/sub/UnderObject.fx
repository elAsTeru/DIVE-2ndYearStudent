//���ʉ��I�u�W�F�N�g�p�V�F�[�_
//MRT0�F�@��
shared texture UnderNormal: RENDERCOLORTARGET;
//MRT1�F���W
shared texture UnderPos: RENDERCOLORTARGET;
//�[�x�X�e���V��
shared texture UnderDepthBuffer : RENDERDEPTHSTENCILTARGET;

#define OBJECT_TEC(name, mmdpass, tex, sphere, toon)\
technique name<\
	string MMDPass = mmdpass; \
	bool UseTexture = tex; \
	bool UseSphereMap = sphere; \
	bool UseToon = toon; \
	string Script = \
		"RenderColorTarget0=;" \
		"RenderColorTarget1=UnderPos;" \
		"RenderDepthStencilTarget0=UnderDepthBuffer;" \
		"Pass=DrawObject;" \
	;\
	> { \
	pass DrawObject { \
		AlphaBlendEnable	= true; \
		AlphaTestEnable		= true; \
		ZEnable				= true; \
		ZWriteEnable		= true; \
		VertexShader = compile vs_3_0 Basic_VS(tex, sphere, toon); \
		PixelShader = compile ps_3_0 Basic_PS(tex, sphere, toon); \
	} \
}

float4 EgColor;
// �p�����[�^�錾

// ���@�ϊ��s��
float4x4 WorldViewProjMatrix      : WORLDVIEWPROJECTION;
float4x4 WorldMatrix              : WORLD;
float4x4 ViewMatrix               : VIEW;
float4x4 LightWorldViewProjMatrix : WORLDVIEWPROJECTION < string Object = "Light"; >;

float3   LightDirection    : DIRECTION < string Object = "Light"; >;
float3   CameraPosition    : POSITION  < string Object = "Camera"; >;

// �}�e���A���F
float4   MaterialDiffuse   : DIFFUSE  < string Object = "Geometry"; >;
float3   MaterialAmbient   : AMBIENT  < string Object = "Geometry"; >;
float3   MaterialEmmisive  : EMISSIVE < string Object = "Geometry"; >;
float3   MaterialSpecular  : SPECULAR < string Object = "Geometry"; >;
float    SpecularPower     : SPECULARPOWER < string Object = "Geometry"; >;
float3   MaterialToon      : TOONCOLOR;
float4   EdgeColor         : EDGECOLOR;
float4   GroundShadowColor : GROUNDSHADOWCOLOR;
// ���C�g�F
float3   LightDiffuse      : DIFFUSE   < string Object = "Light"; >;
float3   LightAmbient      : AMBIENT   < string Object = "Light"; >;
float3   LightSpecular     : SPECULAR  < string Object = "Light"; >;
static float4 DiffuseColor  = MaterialDiffuse  * float4(LightDiffuse, 1.0f);
static float3 AmbientColor  = MaterialAmbient  * LightAmbient + MaterialEmmisive;
static float3 SpecularColor = MaterialSpecular * LightSpecular;

// �e�N�X�`���ގ����[�t�l
float4   TextureAddValue   : ADDINGTEXTURE;
float4   TextureMulValue   : MULTIPLYINGTEXTURE;
float4   SphereAddValue    : ADDINGSPHERETEXTURE;
float4   SphereMulValue    : MULTIPLYINGSPHERETEXTURE;

bool	 use_subtexture;    // �T�u�e�N�X�`���t���O

bool     parthf;   // �p�[�X�y�N�e�B�u�t���O
bool     transp;   // �������t���O
bool	 spadd;    // �X�t�B�A�}�b�v���Z�����t���O
#define SKII1    1500
#define SKII2    8000
#define Toon     3


// �I�u�W�F�N�g�̃e�N�X�`��
texture ObjectTexture: MATERIALTEXTURE;
sampler ObjTexSampler = sampler_state {
    texture = <ObjectTexture>;
    MINFILTER = LINEAR;
    MAGFILTER = LINEAR;
    MIPFILTER = LINEAR;
    ADDRESSU  = WRAP;
    ADDRESSV  = WRAP;
};

// �X�t�B�A�}�b�v�̃e�N�X�`��
texture ObjectSphereMap: MATERIALSPHEREMAP;
sampler ObjSphareSampler = sampler_state {
    texture = <ObjectSphereMap>;
    MINFILTER = LINEAR;
    MAGFILTER = LINEAR;
    MIPFILTER = LINEAR;
    ADDRESSU  = WRAP;
    ADDRESSV  = WRAP;
};

// �g�D�[���}�b�v�̃e�N�X�`��
texture ObjectToonTexture: MATERIALTOONTEXTURE;
sampler ObjToonSampler = sampler_state {
    texture = <ObjectToonTexture>;
    MINFILTER = LINEAR;
    MAGFILTER = LINEAR;
    MIPFILTER = NONE;
    ADDRESSU  = CLAMP;
    ADDRESSV  = CLAMP;
};


struct PS_OUTPUT {
	float4 Normal : COLOR0;
	float4 Pos : COLOR1;
};


///////////////////////////////////////////////////////////////////////////////////////////////
// �I�u�W�F�N�g�`��i�Z���t�V���h�EOFF�j

struct VS_OUTPUT {
    float4 Pos        : POSITION;    // �ˉe�ϊ����W
    float2 Tex        : TEXCOORD1;   // �e�N�X�`��
    float3 Normal     : TEXCOORD2;   // �@��
    float3 Eye        : TEXCOORD3;   // �J�����Ƃ̑��Έʒu
    float2 SpTex      : TEXCOORD4;	 // �X�t�B�A�}�b�v�e�N�X�`�����W
    float3 WPos		  : TEXCOORD5;
    float4 Color      : COLOR0;      // �f�B�t���[�Y�F
    float3 Specular   : COLOR1;      // �X�y�L�����F
};

// ���_�V�F�[�_
VS_OUTPUT Basic_VS(float4 Pos : POSITION, float3 Normal : NORMAL, float2 Tex : TEXCOORD0, float2 Tex2 : TEXCOORD1, uniform bool useTexture, uniform bool useSphereMap, uniform bool useToon)
{
    VS_OUTPUT Out = (VS_OUTPUT)0;
    
    // �J�������_�̃��[���h�r���[�ˉe�ϊ�
    Out.Pos = mul( Pos, WorldViewProjMatrix );
    Out.WPos = mul( Pos,WorldMatrix);
    // �J�����Ƃ̑��Έʒu
    Out.Eye = CameraPosition - mul( Pos, WorldMatrix );
    // ���_�@��
    Out.Normal = normalize( mul( Normal, (float3x3)WorldMatrix ) );
    
    // �f�B�t���[�Y�F�{�A���r�G���g�F �v�Z
    Out.Color.rgb = AmbientColor;
    if ( !useToon ) {
        Out.Color.rgb += max(0,dot( Out.Normal, -LightDirection )) * DiffuseColor.rgb;
    }
    Out.Color.a = DiffuseColor.a;
    Out.Color = saturate( Out.Color );
    
    // �e�N�X�`�����W
    Out.Tex = Tex;
    
    if ( useSphereMap ) {
		if ( use_subtexture ) {
			// PMX�T�u�e�N�X�`�����W
			Out.SpTex = Tex2;
	    } else {
	        // �X�t�B�A�}�b�v�e�N�X�`�����W
	        float2 NormalWV = mul( Out.Normal, (float3x3)ViewMatrix );
	        Out.SpTex.x = NormalWV.x * 0.5f + 0.5f;
	        Out.SpTex.y = NormalWV.y * -0.5f + 0.5f;
	    }
    }
    
    // �X�y�L�����F�v�Z
    float3 HalfVector = normalize( normalize(Out.Eye) + -LightDirection );
    Out.Specular = pow( max(0,dot( HalfVector, Out.Normal )), SpecularPower ) * SpecularColor;
    
    return Out;
}
//�G�b�W�p���_�V�F�[�_
VS_OUTPUT Edge_VS(float4 Pos : POSITION, float3 Normal : NORMAL, float2 Tex : TEXCOORD0, float2 Tex2 : TEXCOORD1, uniform bool useTexture, uniform bool useSphereMap, uniform bool useToon)
{
    VS_OUTPUT Out = (VS_OUTPUT)0;

    // �J�������_�̃��[���h�r���[�ˉe�ϊ�
    Out.Pos = mul( Pos, WorldViewProjMatrix );
    Out.WPos = mul( Pos,WorldMatrix);
    // �J�����Ƃ̑��Έʒu
    Out.Eye = CameraPosition - mul( Pos, WorldMatrix );
    // ���_�@��
    Out.Normal = normalize( mul( Normal, (float3x3)WorldMatrix ) );
    
    // �f�B�t���[�Y�F�{�A���r�G���g�F �v�Z
    Out.Color.rgb = AmbientColor;
    if ( !useToon ) {
        Out.Color.rgb += max(0,dot( Out.Normal, -LightDirection )) * DiffuseColor.rgb;
    }
    Out.Color.a = DiffuseColor.a;
    Out.Color = saturate( Out.Color );
    
    // �e�N�X�`�����W
    Out.Tex = Tex;
    
    if ( useSphereMap ) {
		if ( use_subtexture ) {
			// PMX�T�u�e�N�X�`�����W
			Out.SpTex = Tex2;
	    } else {
	        // �X�t�B�A�}�b�v�e�N�X�`�����W
	        float2 NormalWV = mul( Out.Normal, (float3x3)ViewMatrix );
	        Out.SpTex.x = NormalWV.x * 0.5f + 0.5f;
	        Out.SpTex.y = NormalWV.y * -0.5f + 0.5f;
	    }
    }
    
    // �X�y�L�����F�v�Z
    float3 HalfVector = normalize( normalize(Out.Eye) + -LightDirection );
    Out.Specular = pow( max(0,dot( HalfVector, Out.Normal )), SpecularPower ) * SpecularColor;
    
    return Out;
}

// �s�N�Z���V�F�[�_
PS_OUTPUT Basic_PS(VS_OUTPUT IN, uniform bool useTexture, uniform bool useSphereMap, uniform bool useToon) : COLOR0
{
	PS_OUTPUT Out = (PS_OUTPUT)0;
	
    float4 Color = IN.Color;
    if ( useTexture ) {
        // �e�N�X�`���K�p
        Color *= tex2D( ObjTexSampler, IN.Tex );
    }
    if ( useSphereMap ) {
        // �X�t�B�A�}�b�v�K�p
        float4 TexColor = tex2D(ObjSphareSampler,IN.SpTex);
        if(spadd) Color.rgb += TexColor.rgb;
        else      Color.rgb *= TexColor.rgb;
        Color.a *= TexColor.a;
    }
    
    if ( useToon ) {
        // �g�D�[���K�p
        float LightNormal = dot( IN.Normal, -LightDirection );
        Color *= tex2D(ObjToonSampler, float2(0, 0.5 - LightNormal * 0.5) );
    }
    
	Out.Normal = float4(IN.Normal,Color.a > 0.9);
	Out.Pos = float4(IN.WPos,Color.a > 0.9);
	return Out;
}
technique ZplotTec < string MMDPass = "zplot"; > {}
//technique EdgeTec < string MMDPass = "edge"; > {}

technique EdgeTec < string MMDPass = "edge";
string Script = 
	"RenderColorTarget0=;" 
	"RenderColorTarget1=UnderPos;" 
	"RenderDepthStencilTarget0=UnderDepthBuffer;" 
	"Pass=DrawObject;" 
;
> { 
	pass DrawObject {
        AlphaBlendEnable = FALSE;
        AlphaTestEnable  = FALSE;
        
		VertexShader = compile vs_3_0 Edge_VS(false, false, false);
		PixelShader = compile ps_3_0 Basic_PS(false, false, false);
	}
}

technique ShadowTec < string MMDPass = "shadow"; > {}


OBJECT_TEC(MainTec0, "object", false, false, false)
OBJECT_TEC(MainTec1, "object", true, false, false)
OBJECT_TEC(MainTec2, "object", false, true, false)
OBJECT_TEC(MainTec3, "object", true, true, false)
OBJECT_TEC(MainTec4, "object", false, false, true)
OBJECT_TEC(MainTec5, "object", true, false, true)
OBJECT_TEC(MainTec6, "object", false, true, true)
OBJECT_TEC(MainTec7, "object", true, true, true)

OBJECT_TEC(MainTecBS0, "object_ss", false, false, false)
OBJECT_TEC(MainTecBS1, "object_ss", true, false, false)
OBJECT_TEC(MainTecBS2, "object_ss", false, true, false)
OBJECT_TEC(MainTecBS3, "object_ss", true, true, false)
OBJECT_TEC(MainTecBS4, "object_ss", false, false, true)
OBJECT_TEC(MainTecBS5, "object_ss", true, false, true)
OBJECT_TEC(MainTecBS6, "object_ss", false, true, true)
OBJECT_TEC(MainTecBS7, "object_ss", true, true, true)

///////////////////////////////////////////////////////////////////////////////////////////////
