string description = "Basic 2d sprite";

//------------------------------------
float4x4 worldViewProj : WorldViewProjection;
int frameNumber : FrameNumber; 
float frameWidth : FrameWidth;

texture colorTexture : ColorTexture
<
	string ResourceName = "photo.dds";
>;

float4 materialDiffuse : Diffuse
<
    string UIWidget = "Surface Color";
    string Space = "material";
> = {1.0f, 1.0f, 1.0f, 1.0f};

float4 white = {1.0f, 1.0f, 1.0f, 1.0f};

//------------------------------------
struct vertexInput {
    float3 position				: POSITION;
};

struct vertexOutput {
    float4 hPosition		: POSITION;
    float2 texCoordDiffuse	: TEXCOORD0;
};


//------------------------------------
vertexOutput VS_TransformAndFrame(vertexInput IN) 
{
    vertexOutput OUT;
    OUT.hPosition = mul( float4(IN.position.xyz , 1.0) , worldViewProj);
    OUT.texCoordDiffuse.xy = (IN.position.xy + 0.5);
    OUT.texCoordDiffuse.x = OUT.texCoordDiffuse.x*frameWidth+frameWidth*frameNumber;
    return OUT;
}


//------------------------------------
sampler TextureSampler = sampler_state 
{
    texture = <colorTexture>;
    AddressU  = CLAMP;        
    AddressV  = CLAMP;
    AddressW  = CLAMP;
    MIPFILTER = LINEAR;
    MINFILTER = LINEAR;
    MAGFILTER = LINEAR;
};


//-----------------------------------
float4 PS_Sample( vertexOutput IN): COLOR
{
  float4 diffuseTexture = tex2D( TextureSampler, IN.texCoordDiffuse );
  return materialDiffuse * diffuseTexture;
}

//float4 PS_white( vertexOutput IN): COLOR0
//{
//  return white;
//}

//-----------------------------------
technique q1
{
    pass p0 
    {		
		VertexShader = compile vs_1_1 VS_TransformAndFrame();
		PixelShader  = compile ps_1_1 PS_Sample();
    }
}