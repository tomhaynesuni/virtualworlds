#version 450 core

layout(binding = 0) uniform sampler2D ColTexture;

in GS_DATA
{
    float intensity;
    vec2 texCoord;
} gData;

out vec4 FragColor; // Color that will be used for the fragment

//////////////////////////////////////////////////////////////////
// main()
//////////////////////////////////////////////////////////////////
void main()
{
    vec4 colour = texture(ColTexture, gData.texCoord.xy); 

    FragColor = vec4(vec3(colour.xyz * gData.intensity), 1.0);
}