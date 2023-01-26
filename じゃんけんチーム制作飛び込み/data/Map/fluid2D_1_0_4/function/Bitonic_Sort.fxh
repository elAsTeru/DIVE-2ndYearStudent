//================================================================================================//
// Bitonic_Sort�p�w�b�_�t�@�C��
// ���� : ����
// 
// �p�[�e�B�N����Z�\�[�g���s�����߂̃w�b�_�t�@�C���ł�
//================================================================================================//

// �e�N�X�`�����W����C���f�b�N�X�����߂�
int Sort_TexToIndex(float2 tex, int size, float offset){
	int index = (int)round(tex.x*size-offset)+(int)round(tex.y*size-offset)*size;
	return index;
}

// �C���f�b�N�X����e�N�X�`�����W�����߂�
float2 Sort_IndexToTex(int index, int size, float offset){
	float2 tex;
	tex.x = (index%size+offset)/size;
	tex.y = (index/size+offset)/size;
	return tex;
}

/* ���_�V�F�[�_�[�p�̍\���� */
struct SORT_VS_OUTPUT
{
	float4 Pos : POSITION;	// ���_���W
	float2 Tex : TEXCOORD0;	// �e�N�X�`�����W
};

/* ���_�V�F�[�_�[ */
SORT_VS_OUTPUT Sort_VS( float4 Pos : POSITION, float4 Tex : TEXCOORD0)
{
	SORT_VS_OUTPUT Out = (SORT_VS_OUTPUT)0;
	
	Out.Pos = Pos;
	Out.Tex = Tex.xy + float2(0.5,0.5)/BS_TEX_SIZE;
	
	return Out;
}

/* �s�N�Z���V�F�[�_�[ */
float4 Sort_PS(SORT_VS_OUTPUT IN, uniform int Level, uniform int Step, uniform sampler2D samp) : COLOR
{
	float4 Data = float4(1,1,1,1);
	float2 tex1 = IN.Tex;
	
	int index1 = Sort_TexToIndex(tex1, BS_TEX_SIZE, 0.5);
	
	// �����A�~�����؂�ւ��Ԋu
	int orderWidth = pow(2,Level+1);
	int orderDir = ((index1/orderWidth)%2 == 1) ? -1 : 1;
	
	// ����ւ����s���Ԋu
	int swapWidth = ( Level<Step )? 0 : pow(2,Level-Step);
	int swapDir = ((index1/swapWidth)%2 == 1) ? -1 : 1;
	
	// ��r�Ώۂ̃C���f�b�N�X�ƃe�N�X�`�����W
	int index2 = index1 + swapDir*swapWidth;
	float2 tex2 = Sort_IndexToTex(index2, BS_TEX_SIZE, 0.5);
	
	// �s�N�Z���̏����擾
	float4 n1 = tex2D(samp, tex1);
	float4 n2 = tex2D(samp, tex2);
	
	// ���������߂ĕK�v�Ȃ�Γ���ւ�
	int d = orderDir*swapDir*BS_ORDER;
	Data = ( n1.x*d > n2.x*d ) ? n1 : n2;
	
	return Data;
}

int BS_LoopCount[] = 
	{ 1,  1,  2,  2,  3,  3,  4,  4,  5,  5,  6,  6,  7,  7,  8,  8,
	  9,  9, 10, 10, 11, 11, 12, 12, 13, 13, 14, 14, 15, 15, 16, 16 };
int BS_Step = 0;

// �p�X�̒�`
#define BITONIC_SORT_PASSES_N(_level)												\
	pass Sort_##_level##_0 <  string Script= "Draw=Buffer;"; >{						\
		ALPHATESTENABLE = FALSE;													\
		ALPHABLENDENABLE = FALSE;													\
		VertexShader = compile vs_3_0 Sort_VS();									\
		PixelShader = compile ps_3_0 Sort_PS((_level),2*BS_Step,SortSamp);			\
	}																				\
	pass Sort_##_level##_1 <  string Script= "Draw=Buffer;"; >{						\
		ALPHATESTENABLE = FALSE;													\
		ALPHABLENDENABLE = FALSE;													\
		VertexShader = compile vs_3_0 Sort_VS();									\
		PixelShader = compile ps_3_0 Sort_PS((_level), 2*BS_Step+1,SortSampSub);	\
	}

// �X�N���v�g�̒�`
#define BITONIC_SORT_SCRIPTS_N(_level)					\
	"LoopByCount=BS_LoopCount["#_level"];"				\
	"LoopGetIndex=BS_Step;"								\
		"RenderColorTarget0=SortTexSub;"				\
		"RenderDepthStencilTarget=Sort_DepthBuffer;"	\
		"Clear=Color; Clear=Depth;"						\
		"Pass=Sort_"#_level"_0;"						\
		"RenderColorTarget0=SortTex;"					\
		"RenderDepthStencilTarget=Sort_DepthBuffer;"	\
		"Clear=Color; Clear=Depth;"						\
		"Pass=Sort_"#_level"_1;"						\
	"LoopEnd=;"
	
//================================================================================================//
