////////////////////////////////////////////////////////////////////////////////////////////////
//
//  �x���V�e�B�}�b�v �o�̓G�t�F�N�g
//  ����F���ڂ�
//  MME 0.27���K�v�ł�
//  �����E���p�Ƃ����R�ł�
//
////////////////////////////////////////////////////////////////////////////////////////////////


// �w�i�܂œ��߂�����臒l��ݒ肵�܂�
float TransparentThreshold = 0.5;

// ���ߔ���Ƀe�N�X�`���̓��ߓx���g�p���܂��B1�ŗL���A0�Ŗ���
#define TRANS_TEXTURE  1

float3 CameraPosition	: POSITION  < string Object = "Camera"; >;
////////////////////////////////////////////////////////////////////////////////////////////////
//Clone�A�g�@�\

//Clone�̃p�����[�^�ǂݍ��ݎw��
#define CLONE_PARAMINCLUDE

//�ȉ��̃R�����g�A�E�g���O���A�N���[���G�t�F�N�g�t�@�C�������w��
//include "Clone.fx"


//�_�~�[�ϐ��E�֐��錾
#ifndef CLONE_MIPMAPTEX_SIZE
int CloneIndex = 0; //���[�v�ϐ�
int CloneCount = 1; //������
float4 ClonePos(float4 Pos) { return Pos; }
#endif

////////////////////////////////////////////////////////////////////////////////////////////////


// ���@�ϊ��s��
float4x4 WorldViewProjMatrix      : WORLDVIEWPROJECTION;
float4x4 WorldMatrix              : WORLD;
float4x4 WorldViewMatrix          : WORLDVIEW;
float4x4 ProjectionMatrix         : PROJECTION;
float4x4 ViewProjMatrix           : VIEWPROJECTION;


bool use_texture;  //�e�N�X�`���̗L��

// �}�e���A���F
float4 MaterialDiffuse   : DIFFUSE  < string Object = "Geometry"; >;

// �X�N���[���T�C�Y
float2 ViewportSize : VIEWPORTPIXELSIZE;
static float ViewportAspect = ViewportSize.x / ViewportSize.y;


#if TRANS_TEXTURE!=0
    // �I�u�W�F�N�g�̃e�N�X�`��
    texture ObjectTexture: MATERIALTEXTURE;
    sampler ObjTexSampler = sampler_state
    {
        texture = <ObjectTexture>;
        MINFILTER = LINEAR;
        MAGFILTER = LINEAR;
    };
    
    
    // MMD�{����sampler���㏑�����Ȃ����߂̋L�q�ł��B�폜�s�B
    sampler MMDSamp0 : register(s0);
    sampler MMDSamp1 : register(s1);
    sampler MMDSamp2 : register(s2);
    
#endif



//26�����_�܂őΉ�
#define VPBUF_WIDTH  512
#define VPBUF_HEIGHT 512

//���_���W�o�b�t�@�T�C�Y
static float2 VPBufSize = float2(VPBUF_WIDTH, VPBUF_HEIGHT);

static float2 VPBufOffset = float2(0.5 / VPBUF_WIDTH, 0.5 / VPBUF_HEIGHT);


//���_���Ƃ̃��[���h���W���L�^
texture DepthBuffer : RenderDepthStencilTarget <
   int Width=VPBUF_WIDTH;
   int Height=VPBUF_HEIGHT;
    string Format = "D24S8";
>;
texture VertexPosBufTex : RenderColorTarget
<
    int Width=VPBUF_WIDTH;
    int Height=VPBUF_HEIGHT;
    bool AntiAlias = false;
    int Miplevels = 1;
    string Format="A32B32G32R32F";
>;
sampler VertexPosBuf = sampler_state
{
   Texture = (VertexPosBufTex);
   ADDRESSU = CLAMP;
   ADDRESSV = CLAMP;
   MAGFILTER = NONE;
   MINFILTER = NONE;
   MIPFILTER = NONE;
};
texture VertexPosBufTex2 : RenderColorTarget
<
    int Width=VPBUF_WIDTH;
    int Height=VPBUF_HEIGHT;
    bool AntiAlias = false;
    int Miplevels = 1;
    string Format="A32B32G32R32F";
>;
sampler VertexPosBuf2 = sampler_state
{
   Texture = (VertexPosBufTex2);
   ADDRESSU = CLAMP;
   ADDRESSV = CLAMP;
   MAGFILTER = NONE;
   MINFILTER = NONE;
   MIPFILTER = NONE;
};


//���[���h�r���[�ˉe�s��Ȃǂ̋L�^

#define INFOBUFSIZE 16

texture DepthBufferMB : RenderDepthStencilTarget <
   int Width=INFOBUFSIZE;
   int Height=1;
    string Format = "D24S8";
>;
texture MatrixBufTex : RenderColorTarget
<
    int Width=INFOBUFSIZE;
    int Height=1;
    bool AntiAlias = false;
    int Miplevels = 1;
    string Format="A32B32G32R32F";
>;

float4 MatrixBufArray[INFOBUFSIZE] : TEXTUREVALUE <
    string TextureName = "MatrixBufTex";
>;

//�O�t���[���̃��[���h�s��
static float4x4 lastWorldMatrix = float4x4(MatrixBufArray[0], MatrixBufArray[1], MatrixBufArray[2], MatrixBufArray[3]);

//�O�t���[���̃r���[�ˉe�s��
static float4x4 lastViewMatrix = float4x4(MatrixBufArray[4], MatrixBufArray[5], MatrixBufArray[6], MatrixBufArray[7]);



//�t���[���̋L�^���u���b�N���邩�ǂ���
bool MotionBlockerEnable  : CONTROLOBJECT < string name = "LockMotion.x"; >;
bool CameraBlockerEnable  : CONTROLOBJECT < string name = "LockCamera.x"; >;


#ifdef MIKUMIKUMOVING
    static float4x4 lastMatrix = mul(WorldMatrix, lastViewMatrix);
#else
    static float4x4 lastMatrix = mul(lastWorldMatrix, lastViewMatrix);
#endif


//����
float ftime : TIME<bool SyncInEditMode=true;>;
float stime : TIME<bool SyncInEditMode=false;>;

//�o���t���[�����ǂ���
//�O��Ăяo������0.5s�ȏ�o�߂��Ă������\���������Ɣ��f
static float last_ftime = MatrixBufArray[8].y;
static float last_stime = MatrixBufArray[8].x;
static bool Appear = (abs(last_stime - stime) > 0.5);


////////////////////////////////////////////////////////////////////////////////////////////////
//MMM�Ή�

#ifdef MIKUMIKUMOVING
    
    #define GETPOS MMM_SkinnedPosition(IN.Pos, IN.BlendWeight, IN.BlendIndices, IN.SdefC, IN.SdefR0, IN.SdefR1)
    
    int voffset : VERTEXINDEXOFFSET;
    
#else
    
    struct MMM_SKINNING_INPUT{
        float4 Pos : POSITION;
        float2 Tex : TEXCOORD0;
        float4 AddUV1 : TEXCOORD1;
        float4 AddUV2 : TEXCOORD2;
        float4 AddUV3 : TEXCOORD3;
        int Index     : _INDEX;
    };
    
    #define GETPOS (IN.Pos)
    
    const int voffset = 0;
    
#endif

////////////////////////////////////////////////////////////////////////////////////////////////
//�ėp�֐�

//W�t���X�N���[�����W��P���X�N���[�����W��
float3 ScreenPosRasterize(float4 ScreenPos){
    return ScreenPos.xyz / ScreenPos.w;
    
}

//���_���W�o�b�t�@�擾
float4 getVertexPosBuf(float index)
{
    float4 Color;
    float2 tpos = float2(index % VPBUF_WIDTH, trunc(index / VPBUF_WIDTH));
    tpos += float2(0.5, 0.5);
    tpos /= float2(VPBUF_WIDTH, VPBUF_HEIGHT);
    Color = tex2Dlod(VertexPosBuf2, float4(tpos,0,0));
    return Color;
}

////////////////////////////////////////////////////////////////////////////////////////////////

struct VS_OUTPUT
{
    float4 Pos        : POSITION;    // �ˉe�ϊ����W
    float2 Tex        : TEXCOORD0;   // UV
    float4 LastPos    : TEXCOORD1;
    float4 CurrentPos : TEXCOORD2;
    
};

VS_OUTPUT Velocity_VS(MMM_SKINNING_INPUT IN , uniform bool useToon)
{
    VS_OUTPUT Out = (VS_OUTPUT)0;
    
    if(useToon){
        Out.LastPos = ClonePos(getVertexPosBuf((float)(IN.Index + voffset)));
    }
    
    float4 pos = GETPOS;
    pos = ClonePos(pos);
    
    Out.CurrentPos = pos;
    
    Out.Pos = mul( Out.LastPos, WorldViewProjMatrix );
    
    #if TRANS_TEXTURE!=0
        Out.Tex = IN.Tex; //�e�N�X�`��UV
    #endif
    
    return Out;
}


float4 Velocity_PS( VS_OUTPUT IN , uniform bool useToon , uniform bool isEdge) : COLOR0
{
    float4 lastPos, ViewPos;
    
    if(useToon){
        lastPos = mul( IN.LastPos, lastWorldMatrix );
        ViewPos = mul( IN.CurrentPos, WorldMatrix );
    }else{
        lastPos = mul( IN.CurrentPos, lastWorldMatrix );
        ViewPos = mul( IN.CurrentPos, WorldMatrix );
    }
    
    float alpha = MaterialDiffuse.a;
    
    //�[�x
    float mb_depth = ViewPos.z;
    //float mb_depth = ViewPos.z / ViewPos.w;
    
    #if TRANS_TEXTURE!=0
        if(use_texture){
            alpha *= tex2D(ObjTexSampler,IN.Tex).a;
        }
    #endif
    
    //���x�Z�o
    float3 Velocity = ScreenPosRasterize(ViewPos) - ScreenPosRasterize(lastPos);

    
    //�o�����A���x�L�����Z��
    //Velocity *= !Appear || MotionBlockerEnable || CameraBlockerEnable;
    
    //���x��F�Ƃ��ďo��
    //Velocity = Velocity * 0.25 + 0.5;
    
    alpha = (alpha >= TransparentThreshold);
    
    
    float4 Color = float4(Velocity*1, length(lastPos.xyz - CameraPosition));
    
    //return float4(10,0,0,1);
    return Color;
    
}


/////////////////////////////////////////////////////////////////////////////////////
//���o�b�t�@�̍쐬

struct VS_OUTPUT2 {
    float4 Pos: POSITION;
    float2 texCoord: TEXCOORD0;
};


VS_OUTPUT2 DrawMatrixBuf_VS(float4 Pos: POSITION, float2 Tex: TEXCOORD) {
    VS_OUTPUT2 Out;
    
    Out.Pos = Pos;
    Out.texCoord = Tex;
    return Out;
}

float4 DrawMatrixBuf_PS(float2 texCoord: TEXCOORD0) : COLOR {
    
    int dindex = (int)((texCoord.x * INFOBUFSIZE) + 0.2); //�e�N�Z���ԍ�
    float4 Color;
    
    if(dindex < 4){
        Color = MotionBlockerEnable ? lastWorldMatrix[(int)dindex] : WorldMatrix[(int)dindex]; //�s����L�^
        
    }else if(dindex < 8){
        Color = CameraBlockerEnable ? lastViewMatrix[(int)dindex - 4] : ViewProjMatrix[(int)dindex - 4];
        
    }else{
        Color = float4(stime, ftime, 0.5, 1);
    }
    
    return Color;
}


/////////////////////////////////////////////////////////////////////////////////////
//���_���W�o�b�t�@�̍쐬

struct VS_OUTPUT3 {
    float4 Pos: POSITION;
    float4 BasePos: TEXCOORD0;
};

VS_OUTPUT3 DrawVertexBuf_VS(MMM_SKINNING_INPUT IN)
{
    VS_OUTPUT3 Out;
    
    float findex = (float)(IN.Index + voffset);
    float2 tpos = 0;
    tpos.x = modf(findex / VPBUF_WIDTH, tpos.y);
    tpos.y /= VPBUF_HEIGHT;
    
    //�o�b�t�@�o��
    Out.Pos.xy = (tpos * 2 - 1) * float2(1,-1); //�e�N�X�`�����W�����_���W�ϊ�
    Out.Pos.zw = float2(0, 1);
    
    Out.Pos.x += MotionBlockerEnable * -100; //�L�^�̉�
    
    //���X�^���C�Y�Ȃ��Ńs�N�Z���V�F�[�_�ɓn��
    Out.BasePos = GETPOS;
    
    return Out;
}

float4 DrawVertexBuf_PS( VS_OUTPUT3 IN ) : COLOR0
{
    //���W��F�Ƃ��ďo��
    return IN.BasePos;
}

/////////////////////////////////////////////////////////////////////////////////////
//���_���W�o�b�t�@�̃R�s�[

VS_OUTPUT2 CopyVertexBuf_VS(float4 Pos: POSITION, float2 Tex: TEXCOORD) {
   VS_OUTPUT2 Out;
  
   Out.Pos = Pos;
   Out.texCoord = Tex + VPBufOffset;
   return Out;
}

float4 CopyVertexBuf_PS(float2 texCoord: TEXCOORD0) : COLOR {
   return tex2D(VertexPosBuf, texCoord);
}

/////////////////////////////////////////////////////////////////////////////////////


float4 ClearColor = {0,0,0,1};
float ClearDepth  = 1.0;


// �I�u�W�F�N�g�`��p�e�N�j�b�N

stateblock PMD_State = stateblock_state
{
    
    DestBlend = InvSrcAlpha; SrcBlend = SrcAlpha; //���Z�����̃L�����Z��
    AlphaBlendEnable = false;
    AlphaTestEnable = true;
    
    VertexShader = compile vs_3_0 Velocity_VS(true);
    PixelShader  = compile ps_3_0 Velocity_PS(true, false);
};

stateblock Edge_State = stateblock_state
{
    
    DestBlend = InvSrcAlpha; SrcBlend = SrcAlpha; //���Z�����̃L�����Z��
    AlphaBlendEnable = false;
    AlphaTestEnable = true;
    
    VertexShader = compile vs_3_0 Velocity_VS(true);
    PixelShader  = compile ps_3_0 Velocity_PS(true, true);
};


stateblock Accessory_State = stateblock_state
{
    
    DestBlend = InvSrcAlpha; SrcBlend = SrcAlpha; //���Z�����̃L�����Z��
    AlphaBlendEnable = false;
    AlphaTestEnable = true;
    
    VertexShader = compile vs_3_0 Velocity_VS(false);
    PixelShader  = compile ps_3_0 Velocity_PS(false, false);
};

stateblock makeMatrixBufState = stateblock_state
{
    AlphaBlendEnable = false;
    AlphaTestEnable = false;
    VertexShader = compile vs_3_0 DrawMatrixBuf_VS();
    PixelShader  = compile ps_3_0 DrawMatrixBuf_PS();
};


stateblock makeVertexBufState = stateblock_state
{
    DestBlend = InvSrcAlpha; SrcBlend = SrcAlpha; //���Z�����̃L�����Z��
    FillMode = POINT;
    CullMode = NONE;
    ZEnable = false;
    AlphaBlendEnable = false;
    AlphaTestEnable = false;
    
    VertexShader = compile vs_3_0 DrawVertexBuf_VS();
    PixelShader  = compile ps_3_0 DrawVertexBuf_PS();
};

stateblock copyVertexBufState = stateblock_state
{
    AlphaBlendEnable = false;
    AlphaTestEnable = false;
    VertexShader = compile vs_3_0 CopyVertexBuf_VS();
    PixelShader  = compile ps_3_0 CopyVertexBuf_PS();
};

////////////////////////////////////////////////////////////////////////////////////////////////

technique MainTec0_0 < 
    string MMDPass = "object"; 
    bool UseToon = true;
    string Subset = "0"; 
    string Script =
        
        "RenderColorTarget=MatrixBufTex;"
        "RenderDepthStencilTarget=DepthBufferMB;"
        "Pass=DrawMatrixBuf;"
        
        "RenderColorTarget=VertexPosBufTex2;"
        "RenderDepthStencilTarget=DepthBuffer;"
        "Pass=CopyVertexBuf;"
        
        "RenderColorTarget=;"
        "RenderDepthStencilTarget=;"
        "LoopByCount=CloneCount;"
        "LoopGetIndex=CloneIndex;"
            "Pass=DrawObject;"
        "LoopEnd=;"
        
        "RenderColorTarget=VertexPosBufTex;"
        "RenderDepthStencilTarget=DepthBuffer;"
        "Pass=DrawVertexBuf;"
        
    ;
> {
    pass DrawMatrixBuf < string Script = "Draw=Buffer;";>   { StateBlock = (makeMatrixBufState); }
    pass DrawObject    < string Script = "Draw=Geometry;";> { StateBlock = (PMD_State);  }
    pass DrawVertexBuf < string Script = "Draw=Geometry;";> { StateBlock = (makeVertexBufState); }
    pass CopyVertexBuf < string Script = "Draw=Buffer;";>   { StateBlock = (copyVertexBufState); }
    
}


technique MainTec0_1 < 
    string MMDPass = "object"; 
    bool UseToon = true;
    string Script =
        
        "RenderColorTarget=;"
        "RenderDepthStencilTarget=;"
        "LoopByCount=CloneCount;"
        "LoopGetIndex=CloneIndex;"
            "Pass=DrawObject;"
        "LoopEnd=;"
        
        "RenderColorTarget=VertexPosBufTex;"
        "RenderDepthStencilTarget=DepthBuffer;"
        "Pass=DrawVertexBuf;"
        
    ;
> {
    pass DrawObject    < string Script = "Draw=Geometry;";> { StateBlock = (PMD_State);  }
    pass DrawVertexBuf < string Script = "Draw=Geometry;";> { StateBlock = (makeVertexBufState); }
    
}

technique MainTec1 < 
    string MMDPass = "object"; 
    bool UseToon = false;
    string Script =
        
        "RenderColorTarget=MatrixBufTex;"
        "RenderDepthStencilTarget=DepthBufferMB;"
        "Pass=DrawMatrixBuf;"
        
        "RenderColorTarget=;"
        "RenderDepthStencilTarget=;"
        "LoopByCount=CloneCount;"
        "LoopGetIndex=CloneIndex;"
            "Pass=DrawObject;"
        "LoopEnd=;"
        
    ;
> {
    pass DrawObject    < string Script = "Draw=Geometry;";> { StateBlock = (Accessory_State);  }
    pass DrawMatrixBuf < string Script = "Draw=Buffer;";>   { StateBlock = (makeMatrixBufState); }
    
}

////////////////////////////////////////////////////////////////////////////////////////////////

technique MainTec0_0SS < 
    string MMDPass = "object_ss"; 
    bool UseToon = true;
    string Subset = "0"; 
    string Script =
        
        "RenderColorTarget=MatrixBufTex;"
        "RenderDepthStencilTarget=DepthBufferMB;"
        "Pass=DrawMatrixBuf;"
        
        "RenderColorTarget=VertexPosBufTex2;"
        "RenderDepthStencilTarget=DepthBuffer;"
        "Pass=CopyVertexBuf;"
        
        "RenderColorTarget=;"
        "RenderDepthStencilTarget=;"
        "LoopByCount=CloneCount;"
        "LoopGetIndex=CloneIndex;"
            "Pass=DrawObject;"
        "LoopEnd=;"
        
        "RenderColorTarget=VertexPosBufTex;"
        "RenderDepthStencilTarget=DepthBuffer;"
        "Pass=DrawVertexBuf;"
        
    ;
> {
    pass DrawMatrixBuf < string Script = "Draw=Buffer;";>   { StateBlock = (makeMatrixBufState); }
    pass DrawObject    < string Script = "Draw=Geometry;";> { StateBlock = (PMD_State);  }
    pass DrawVertexBuf < string Script = "Draw=Geometry;";> { StateBlock = (makeVertexBufState); }
    pass CopyVertexBuf < string Script = "Draw=Buffer;";>   { StateBlock = (copyVertexBufState); }
    
}


technique MainTec0_1SS < 
    string MMDPass = "object_ss"; 
    bool UseToon = true;
    string Script =
        
        "RenderColorTarget=;"
        "RenderDepthStencilTarget=;"
        "LoopByCount=CloneCount;"
        "LoopGetIndex=CloneIndex;"
            "Pass=DrawObject;"
        "LoopEnd=;"
        
        "RenderColorTarget=VertexPosBufTex;"
        "RenderDepthStencilTarget=DepthBuffer;"
        "Pass=DrawVertexBuf;"
        
    ;
> {
    pass DrawObject    < string Script = "Draw=Geometry;";> { StateBlock = (PMD_State);  }
    pass DrawVertexBuf < string Script = "Draw=Geometry;";> { StateBlock = (makeVertexBufState); }
    
}

technique MainTec1SS < 
    string MMDPass = "object_ss"; 
    bool UseToon = false;
    string Script =
        
        "RenderColorTarget=MatrixBufTex;"
        "RenderDepthStencilTarget=DepthBufferMB;"
        "Pass=DrawMatrixBuf;"
        
        "RenderColorTarget=;"
        "RenderDepthStencilTarget=;"
        "LoopByCount=CloneCount;"
        "LoopGetIndex=CloneIndex;"
            "Pass=DrawObject;"
        "LoopEnd=;"
        
    ;
> {
    pass DrawObject    < string Script = "Draw=Geometry;";> { StateBlock = (Accessory_State);  }
    pass DrawMatrixBuf < string Script = "Draw=Buffer;";>   { StateBlock = (makeMatrixBufState); }
    
}

////////////////////////////////////////////////////////////////////////////////////////////////
// �֊s�`��

technique EdgeTec < string MMDPass = "edge";
    string Script =
        
        "RenderColorTarget=;"
        "RenderDepthStencilTarget=;"
        "LoopByCount=CloneCount;"
        "LoopGetIndex=CloneIndex;"
            "Pass=DrawObject;"
        "LoopEnd=;"
        
    ;
> {
    pass DrawObject < string Script = "Draw=Geometry;";> { StateBlock = (Edge_State);  }
    
}

///////////////////////////////////////////////////////////////////////////////////////////////
// �e�i��Z���t�V���h�E�j�`��

// �e�Ȃ�
technique ShadowTec < string MMDPass = "shadow"; > {
    
}

///////////////////////////////////////////////////////////////////////////////////////////////
// �Z���t�V���h�E�pZ�l�v���b�g

// Z�l�v���b�g�p�e�N�j�b�N
technique ZplotTec < string MMDPass = "zplot"; > {
    
}

///////////////////////////////////////////////////////////////////////////////////////////////

