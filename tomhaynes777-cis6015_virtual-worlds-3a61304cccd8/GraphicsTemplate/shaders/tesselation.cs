#version 460 core

layout(vertices = 4) out;

in vPoint
{
    vec4 colour;
    vec2 texCoord;
}
invPoints[];

out ControlPoint
{
    vec4 colour;
    vec2 texCoord;
}
outControlPoints[];


void main()
{

    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position; // and then set tessellation levels
                                                                              // Calculate edge tessellation factors for quad
    outControlPoints[gl_InvocationID].colour = invPoints[gl_InvocationID].colour;
    outControlPoints[gl_InvocationID].texCoord = invPoints[gl_InvocationID].texCoord;
    gl_TessLevelOuter[0] = 3.0f;
    gl_TessLevelOuter[1] = 7.0f;
    gl_TessLevelOuter[2] = 11.0f;
    gl_TessLevelOuter[3] = 15.0f;

    // Calculate internal tessellation factors along u and v in quad domain
    gl_TessLevelInner[0] = 15.0f;
    gl_TessLevelInner[1] = 15.0f;

}

