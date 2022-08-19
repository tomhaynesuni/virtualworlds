#version 450 core

layout(binding = 0) uniform sampler2D ColTexture;
layout(binding = 2) uniform samplerCube SkyboxTexture;

in float Intensity;
in vec2 TexCoord;
in vec3 rv;

out vec4 FragColor; // Color that will be used for the fragment

//////////////////////////////////////////////////////////////////
// main()
//////////////////////////////////////////////////////////////////
void main()
{
    vec4 colour0 = texture(ColTexture, TexCoord.xy); 
    vec4 colour1 = texture(SkyboxTexture, rv);

   // FragColor = vec4(vec3(colour.xyz * Intensity), 1.0);

    FragColor = vec4(colour0 * colour1);
    //FragColor = vec4(texture(SkyboxTexture, rv).rgb, 1.0);
}