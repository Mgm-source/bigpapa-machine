struct PS_INPUT
{
    float4 position : SV_Position;
    float3 color : COLOR;
    float3 color2 : COLOR2;
};

struct PS_OUTPUT
{
    float4 color : SV_Target;
};

cbuffer VS_CONSTANT : register(b0)
{
    unsigned int m_time;
};

PS_OUTPUT pixelMain(PS_INPUT input)
{
    PS_OUTPUT output = (PS_OUTPUT) 0;
    output.color = float4(lerp(input.color, input.color2, (sin(m_time / 10000.0f) + 1.0f) / 2.0f), 1);
    return output;
}