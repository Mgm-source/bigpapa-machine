struct PS_INPUT
{
    float4 position : SV_Position;
    float3 color : COLOR;
};

struct PS_OUTPUT
{
    float4 color : SV_Target;
};


PS_OUTPUT pixelMain(PS_INPUT input)
{
    PS_OUTPUT output = (PS_OUTPUT) 0;
    output.color = float4(input.color, 1.0);
    return output;
}