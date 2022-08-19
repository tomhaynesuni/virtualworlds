#version 450 core

layout(binding = 0) uniform sampler2D ColTexture;

in TessVertex {

  float Intensity;
  vec2    texCoord;
  
} inputVertex;

//in float Intensity;
//in vec2 TexCoord;

out vec4 FragColor; // Color that will be used for the fragment

//////////////////////////////////////////////////////////////////
// main()
//////////////////////////////////////////////////////////////////
void main()
{
    vec4 colour = texture(ColTexture, inputVertex.texCoord.xy); 

    FragColor = vec4(vec3(colour.xyz * inputVertex.Intensity), 1.0);
    //FragColor = vec4(vec3(1.0, 1.0, 1.0), 1.0);
}