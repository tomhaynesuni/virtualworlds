#version 450 core

layout (location = 0) in vec3               vertexPos_VS;	  	// Position in attribute location 0
layout (location = 1) in vec2               texCoord_VS;
layout (location = 2) in vec3               vertexNormal_VS;

layout (location = 3) uniform mat4          modelMatrix;
layout (location = 4) uniform mat4          projMatrix;
layout (location = 5) uniform mat4          viewMatrix;

layout (location = 6) uniform vec3          gCP;
layout (location = 7) uniform vec3          lightPosition;
layout (location = 8) uniform float         bWireframe;

out vPoint
{
    float Intensity;
    vec2 texCoord;
}   outvPoints;

//out float Intensity;
//out vec2 TexCoord;



//////////////////////////////////////////////////////////////////
// main()
//////////////////////////////////////////////////////////////////
void main()
{    

   // outvPoints.texCoord    = texCoord_VS;
   //outvPoints.colour = vec4(1.0, 1.0, 1.0, 1.0);

   // gl_Position = vec4(vertexPos_VS, 1.0);

    vec3 mpos   = (modelMatrix * vec4(vertexPos_VS, 1.0)).xyz;

     outvPoints.texCoord    = texCoord_VS;
    
    vec3 Normal 	   = (modelMatrix * vec4(vertexNormal_VS, 0.0)).xyz;     
    vec3 N = normalize(Normal);

    vec3 lightDir  = lightPosition - mpos;
    vec3 L = normalize(lightDir);

    outvPoints.Intensity = dot(N, L);

    gl_Position =  vec4(vertexPos_VS, 1.0);
}