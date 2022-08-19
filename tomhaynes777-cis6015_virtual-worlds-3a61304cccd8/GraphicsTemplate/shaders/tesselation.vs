#version 450 core

layout (location = 0) in vec3               vertexPos_VS;	  	// Position in attribute location 0
layout (location = 1) in vec2               texCoord_VS;
layout (location = 2) in vec3               vertexNormal_VS;

layout (location = 3) uniform mat4          modelMatrix;
layout (location = 4) uniform mat4          projMatrix;
layout (location = 5) uniform mat4          viewMatrix;

layout (location = 6) uniform vec3          gCP;
layout (location = 7) uniform vec3          lightPosition;
layout (location = 8) uniform mat4          mvpMatrix;

out vPoint
{
    vec4 colour;
    vec2 texCoord;
}   outvPoints;

//out float Intensity;
//out vec2 TexCoord;



//////////////////////////////////////////////////////////////////
// main()
//////////////////////////////////////////////////////////////////
void main()
{    

    outvPoints.texCoord    = texCoord_VS;
    outvPoints.colour = vec4(1.0, 1.0, 1.0, 1.0);

    gl_Position = vec4(vertexPos_VS, 1.0);
}