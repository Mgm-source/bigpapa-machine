struct PS_INPUT
{
    float4 position : SV_Position;
    float3 color : COLOR;
};

struct PS_OUTPUT
{
    float4 color : SV_Target;
};

cbuffer VS_CONSTANT : register(b1)
{
    row_major float4x4 m_world;
    row_major float4x4 m_view;
    row_major float4x4 m_screen;
    unsigned int m_time;
};

Texture2D my_texture;
SamplerState my_Sampler;

PS_OUTPUT pixelMain(PS_INPUT input)
{
    PS_OUTPUT output = (PS_OUTPUT) 0;
    output.color = my_texture.Sample(my_Sampler, input.color.xy);
    
    return output;
}