#version 450 core

layout(binding = 0) uniform sampler2D ColTexture;

in float Intensity;
in vec2 TexCoord;

out vec4 FragColor; // Color that will be used for the fragment

//////////////////////////////////////////////////////////////////
// main()
//////////////////////////////////////////////////////////////////
void main()
{
    vec4 colour = texture(ColTexture, TexCoord.xy); 
    float A;
    if(Intensity >= 0.0 && Intensity < 0.25){
    A = 0.0;
    }
    

    else if(Intensity >= 0.25 && Intensity < 0.5){
    A = 0.25;
    }
    

    else if(Intensity >= 0.5 && Intensity < 0.75){
    A = 0.5;
    }
    

    else if(Intensity >= 0.75){
    A = 0.75;
    }
    

    FragColor = vec4(vec3(colour.xyz * A), 1.0);
}