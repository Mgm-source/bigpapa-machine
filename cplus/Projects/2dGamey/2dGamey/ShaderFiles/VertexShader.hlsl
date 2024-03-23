struct VS_INPUT
{
    float4 position : POSITION;
    float3 color : COLOR;
};

struct VS_OUTPUT
{
    float4 position : SV_POSITION;
    float3 color : COLOR;
};

cbuffer VS_CONSTANT : register(b0)
{
    row_major float4x4 m_world;
    row_major float4x4 m_view;
    row_major float4x4 m_screen;
    unsigned int m_time;
};

VS_OUTPUT vertexMain(VS_INPUT input)
{
    VS_OUTPUT output = (VS_OUTPUT) 0;
    //world space
    output.position = mul(input.position,m_world);
    
    // view space
    output.position = mul(output.position, m_view);
                         
    // screen space      
    output.position = mul(output.position, m_screen);
    
    output.color = input.color;
    
    return output;
}