#version 450 core
layout(vertices = 3) out;
layout(location = 5) uniform mat4          viewMatrix;

in TVertexData
{
    vec2 texCoord;
    float intensity;
    vec3 normal;
    vec3 worldPos;
}
inData[];

out TCSData
{
    vec2 texCoord;
    float intensity;
    vec3 normal;
    vec3 worldPos;
}
outData[];



float GetTessLevel(float Distance0, float Distance1)
{
    float AvgDistance = (Distance0 + Distance1) / 2.0;

    if (AvgDistance <= 2.0)
    {
        return 5.0;
    }
    else if (AvgDistance <= 6.0)
    {
        return 3.0;
    }
    else if (AvgDistance <= 12.0)
    {
        return 2.0;
    }
    else
    {
        return 1.0;
    }
}

void main()
{
    vec3 gEyeWorldPos = vec3(viewMatrix[3][0], viewMatrix[3][1], viewMatrix[3][2]);
    gEyeWorldPos *= 1.0;

    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;

    outData[gl_InvocationID].texCoord = inData[gl_InvocationID].texCoord;
    outData[gl_InvocationID].intensity = inData[gl_InvocationID].intensity;
    outData[gl_InvocationID].normal = inData[gl_InvocationID].normal;
    outData[gl_InvocationID].worldPos = inData[gl_InvocationID].worldPos;

    // Calculate the distance from the camera to the three control points
    float EyeToVertexDistance0 = distance(gEyeWorldPos, inData[0].worldPos);
    float EyeToVertexDistance1 = distance(gEyeWorldPos, inData[1].worldPos);
    float EyeToVertexDistance2 = distance(gEyeWorldPos, inData[2].worldPos);

    // Calculate the tessellation levels
    gl_TessLevelOuter[0] = GetTessLevel(EyeToVertexDistance1, EyeToVertexDistance2);
    gl_TessLevelOuter[1] = GetTessLevel(EyeToVertexDistance2, EyeToVertexDistance0);
    gl_TessLevelOuter[2] = GetTessLevel(EyeToVertexDistance0, EyeToVertexDistance1);
    gl_TessLevelInner[0] = gl_TessLevelOuter[2];
}
