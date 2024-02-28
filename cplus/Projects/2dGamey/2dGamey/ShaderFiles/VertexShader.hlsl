struct VS_INPUT
{
    float3 position : POSITION;
    float3 position2 : POSITION1;
    float3 color : COLOR;
};

struct VS_OUTPUT
{
    float4 position : SV_POSITION;
    float3 color : COLOR;
    float3 color2 : COLOR2;
};

cbuffer VS_CONSTANT : register(b0)
{
    unsigned int m_time;
};

VS_OUTPUT vertexMain(VS_INPUT input)
{
    VS_OUTPUT output = (VS_OUTPUT) 0;
    output.position = float4(lerp(input.position, input.position2, (sin(m_time / 10000.0f) + 1.0f) / 2.0f), 1);
    output.color = input.color;
    output.color2 = input.position2;
    return output;
}