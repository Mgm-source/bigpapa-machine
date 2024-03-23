struct PS_INPUT
{
    float4 position : SV_Position;
    float3 color : COLOR;
};

struct PS_OUTPUT
{
    float4 color : SV_Target;
};

cbuffer VS_CONSTANT : register(b0)
{
    row_major float4x4 m_world;
    row_major float4x4 m_view;
    row_major float4x4 m_screen;
    unsigned int m_time;
};

PS_OUTPUT pixelMain(PS_INPUT input)
{
    PS_OUTPUT output = (PS_OUTPUT) 0;
    output.color = float4(input.color, 1);
    return output;
}