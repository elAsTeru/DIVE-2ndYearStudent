//�~���[�[�x�p�V�F�[�_

#define OBJECT_TEC(name, mmdpass, tex, sphere, toon)\
technique name<\
	string MMDPass = mmdpass; \
	bool UseTexture = tex; \
	bool UseSphereMap = sphere; \
	bool UseToon = toon; \
	string Script = \
		"RenderColorTarget0=;" \
		"RenderDepthStencilTarget0=;" \
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

////////////////////////////////////////////////////////////////////////////////////////////////
//
//  MWF_Object.fx ver0.0.2  ���f���������`��
//  ( MirrorWF.fx ����Ăяo����܂��D�I�t�X�N���[���`��p)
//  �쐬: �j��P( ���͉��P����Mirror.fx, full.fx,���� )
//
////////////////////////////////////////////////////////////////////////////////////////////////
// �A�N�Z�ɑg�ݍ��ޏꍇ�͂�����K�X�ύX���Ă��������D
float3 MirrorPos = float3( 0.0, 0.0, 0.0 );    // ���[�J�����W�n�ɂ����鋾�ʏ�̔C�ӂ̍��W(�A�N�Z���_���W�̈�_)
float3 MirrorNormal = float3( 0.0, 1.0, 0.0 ); // ���[�J�����W�n�ɂ����鋾�ʂ̖@���x�N�g��

///////////////////////////////////////////////////////////////////////////////////////////////

// ���[�J�����W�n�ɂ����鋾���ʒu�ւ̕ϊ�
static float3 n = normalize(MirrorNormal);
static float4x4 MirrorMatrix = { 1.0f-2.0f*n.x*n.x, -2.0f*n.x*n.y,      -2.0f*n.x*n.z,      0.0f,
                                -2.0f*n.x*n.y,       1.0f-2.0f*n.y*n.y, -2.0f*n.y*n.z,      0.0f,
                                -2.0f*n.x*n.z,      -2.0f*n.y*n.z,       1.0f-2.0f*n.z*n.z, 0.0f,
                                 MirrorPos.x,        MirrorPos.y,        MirrorPos.z,       1.0f};
float4 TransMirrorPos( float4 Pos ){
    Pos = float4(Pos.xyz - MirrorPos, 1.0f);
    Pos = mul( Pos, MirrorMatrix ); // �����ϊ�
    return Pos;
}

// ���[���h�ϊ��s�����ŁA�t�s����v�Z����B
// - �s�񂪁A���{�X�P�[�����O�A��]�A���s�ړ������܂܂Ȃ����Ƃ�O������Ƃ���B
float4x4 InverseWorldMatrix(float4x4 mat) {
    float scaling = length(mat._11_12_13);
    float scaling_inv = 1.0 / (scaling * scaling);

    float3x3 mat3x3_inv = transpose((float3x3)mat) * scaling_inv;
    return float4x4( mat3x3_inv[0], 0, 
                     mat3x3_inv[1], 0, 
                     mat3x3_inv[2], 0, 
                     -mul(mat._41_42_43, mat3x3_inv), 1 );
}

// ���ʍ��W�ϊ��p�����[�^
float4x4 MirrorWorldMatrix: CONTROLOBJECT < string Name = "(OffscreenOwner)"; >; // ���ʃA�N�Z�̃��[���h�ϊ��s��
static float4x4 InvMirrorWorldMatrix = InverseWorldMatrix(MirrorWorldMatrix);    // ���ʃA�N�Z�̃��[���h�ϊ��t�s��

// Obj���W�ϊ��s��
float4x4 WorldViewProjMatrix      : WORLDVIEWPROJECTION;
float4x4 WorldMatrix              : WORLD;
float4x4 ViewMatrix               : VIEW;
float4x4 ViewProjMatrix           : VIEWPROJECTION;
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
// ���C�g�F
float3   LightDiffuse      : DIFFUSE   < string Object = "Light"; >;
float3   LightAmbient      : AMBIENT   < string Object = "Light"; >;
float3   LightSpecular     : SPECULAR  < string Object = "Light"; >;
static float4 DiffuseColor  = MaterialDiffuse  * float4(LightDiffuse, 1.0f);
static float3 AmbientColor  = MaterialAmbient  * LightAmbient + MaterialEmmisive;
static float3 SpecularColor = MaterialSpecular * LightSpecular;

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
};

// �X�t�B�A�}�b�v�̃e�N�X�`��
texture ObjectSphereMap: MATERIALSPHEREMAP;
sampler ObjSphareSampler = sampler_state {
    texture = <ObjectSphereMap>;
    MINFILTER = LINEAR;
    MAGFILTER = LINEAR;
};

// MMD�{����sampler���㏑�����Ȃ����߂̋L�q�ł��B�폜�s�B
sampler MMDSamp0 : register(s0);
sampler MMDSamp1 : register(s1);
sampler MMDSamp2 : register(s2);

////////////////////////////////////////////////////////////////////////////////////////////////
// �֊s�`��

struct VS_OUTPUT0 {
    float4 Pos        : POSITION;    // �ˉe�ϊ����W
    float4 VPos       : TEXCOORD1;   // �������f���̃��[���h���W
    float4 WPos		  : TEXCOORD2;
    float4 VCamera    : TEXCOORD3;   // �J�����Ƌ��ʂ̑��΍��W
};

// �����G�b�W���_�V�F�[�_
VS_OUTPUT0 MirrorEdge_VS(float4 Pos : POSITION)
{
    VS_OUTPUT0 Out = (VS_OUTPUT0)0;

    // ���[���h���W�ϊ�
    Pos = mul( Pos, WorldMatrix );
	Out.WPos = Pos;

    // �����ʒu�ւ̍��W�ϊ�
    Pos = mul( Pos, InvMirrorWorldMatrix );
    Pos = TransMirrorPos( Pos ); // �����ϊ�
    Out.VPos = Pos;
    Pos = mul( Pos, MirrorWorldMatrix );

    // �J�������_�̃r���[�ˉe�ϊ�
    Out.Pos = mul( Pos, ViewProjMatrix );
    Out.Pos.x *= -1.0f; // �|���S�������Ԃ�Ȃ��悤�ɍ��E���]�ɂ��ĕ`��

    // �J�����̋��ʂɑ΂��鑊�΍��W
    Out.VCamera = mul( float4(CameraPosition, 1.0f), InvMirrorWorldMatrix );

    return Out;
}

// �s�N�Z���V�F�[�_
float4 Edge_PS(VS_OUTPUT0 IN) : COLOR
{
    // �֊s�F�œh��Ԃ�
    float4 Color = EdgeColor;

    // ���ʂ̗����ɂ��镔�ʂ͋����\�����Ȃ�
    if(dot((float3)IN.VPos-MirrorPos, MirrorNormal)*dot((float3)IN.VCamera-MirrorPos, MirrorNormal) >= 0.0f) Color.a = 0.0f;

    float3 Eye = CameraPosition - IN.WPos.xyz;
    return float4(length(Eye),0,0,Color.a);
}

// �֊s�`��p�e�N�j�b�N
technique EdgeTec < string MMDPass = "edge"; > {
    pass DrawMirrorEdge {
        AlphaBlendEnable = TRUE;
        AlphaTestEnable  = TRUE;
        SrcBlend = SRCALPHA;
        DestBlend = INVSRCALPHA;
        VertexShader = compile vs_2_0 MirrorEdge_VS();
        PixelShader  = compile ps_2_0 Edge_PS();
    }
}

// �e�`��p�e�N�j�b�N
technique ShadowTec < string MMDPass = "shadow"; > {}


///////////////////////////////////////////////////////////////////////////////////////////////
// �I�u�W�F�N�g�`��i�Z���t�V���h�EOFF�j

struct VS_OUTPUT {
    float4 Pos        : POSITION;    // �ˉe�ϊ����W
    float2 Tex        : TEXCOORD1;   // �e�N�X�`��
    float3 Normal     : TEXCOORD2;   // �@��
    float3 Eye        : TEXCOORD3;   // �J�����Ƃ̑��Έʒu
    float2 SpTex      : TEXCOORD4;   // �X�t�B�A�}�b�v�e�N�X�`�����W
    float4 VPos       : TEXCOORD5;   // �������f���̃��[���h���W
    float4 VCamera    : TEXCOORD6;   // �J�����Ƌ��ʂ̑��΍��W
    float4 WPos		  : TEXCOORD7;
    float4 Color      : COLOR0;      // �f�B�t���[�Y�F
};

// ���_�V�F�[�_
VS_OUTPUT Basic_VS(float4 Pos : POSITION, float3 Normal : NORMAL, float2 Tex : TEXCOORD0, uniform bool useTexture, uniform bool useSphereMap, uniform bool useToon)
{
    VS_OUTPUT Out = (VS_OUTPUT)0;

    // ���[���h���W�ϊ�
    Pos = mul( Pos, WorldMatrix );
	Out.WPos = Pos;

    // �J�����Ƃ̑��Έʒu(����������������Ă��邱�Ƃ��l��)
    Out.Eye = CameraPosition - Pos;
    // �����ʒu�ւ̍��W�ϊ�
    Pos = mul( Pos, InvMirrorWorldMatrix );
    Pos = TransMirrorPos( Pos ); // �����ϊ�
    Out.VPos = Pos;
    Pos = mul( Pos, MirrorWorldMatrix );

    // �J�������_�̃r���[�ˉe�ϊ�
    Out.Pos = mul( Pos, ViewProjMatrix );
    Out.Pos.x *= -1.0f; // �|���S�������Ԃ�Ȃ��悤�ɍ��E���]�ɂ��ĕ`��

    // �J�����̋��ʂɑ΂��鑊�΍��W
    Out.VCamera = mul( float4(CameraPosition, 1.0f), InvMirrorWorldMatrix );

    // ���_�@��(����������������Ă��邱�Ƃ��l��)
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
        // �X�t�B�A�}�b�v�e�N�X�`�����W
        float2 NormalWV = mul( Out.Normal, (float3x3)ViewMatrix );
        Out.SpTex.x = NormalWV.x * 0.5f + 0.5f;
        Out.SpTex.y = NormalWV.y * -0.5f + 0.5f;
    }

    return Out;
}

// �s�N�Z���V�F�[�_
float4 Basic_PS(VS_OUTPUT IN, uniform bool useTexture, uniform bool useSphereMap, uniform bool useToon) : COLOR0
{
    // �X�y�L�����F�v�Z
    float3 HalfVector = normalize( normalize(IN.Eye) + -LightDirection );
    float3 Specular = pow( max(0,dot( HalfVector, normalize(IN.Normal) )), SpecularPower ) * SpecularColor;

    float4 Color = IN.Color;
    if ( useTexture ) {
        // �e�N�X�`���K�p
        Color *= tex2D( ObjTexSampler, IN.Tex );
    }

    // ���ʂ̗����ɂ��镔�ʂ͋����\�����Ȃ�
    if(dot((float3)IN.VPos-MirrorPos, MirrorNormal)*dot((float3)IN.VCamera-MirrorPos, MirrorNormal) >= 0.0f) Color.a = 0.0f;


    float3 Eye = CameraPosition - IN.WPos.xyz;
    return float4(length(Eye),0,0,Color.a);
}

// Z�l�v���b�g�p�e�N�j�b�N
technique ZplotTec < string MMDPass = "zplot"; > {}

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
