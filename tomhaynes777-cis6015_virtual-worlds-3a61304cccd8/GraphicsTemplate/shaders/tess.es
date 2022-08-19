#version 450 core

layout (triangles, equal_spacing, ccw) in;

layout (location = 4) uniform mat4          projMatrix;
layout (location = 5) uniform mat4          viewMatrix;

in TCSData {
  vec2    texCoord;
  float   intensity;
  vec3    normal;
  vec3    worldPos;
} inData[];

out TESData {
  vec2    texCoord;
  float   intensity;
  vec3    normal;
  vec3    worldPos;
} outData;

vec2 interpolate2D(vec2 v0, vec2 v1, vec2 v2)
{
    return vec2(gl_TessCoord.x) * v0 + vec2(gl_TessCoord.y) * v1 + vec2(gl_TessCoord.z) * v2;
}

vec3 interpolate3D(vec3 v0, vec3 v1, vec3 v2)
{
    return vec3(gl_TessCoord.x) * v0 + vec3(gl_TessCoord.y) * v1 + vec3(gl_TessCoord.z) * v2;
}

void main() {

    outData.texCoord = interpolate2D(inData[0].texCoord, inData[1].texCoord, inData[2].texCoord);
    outData.intensity = inData[0].intensity;
    outData.normal = interpolate3D(inData[0].normal, inData[1].normal, inData[2].normal);
    outData.normal = normalize(outData.normal);
    outData.worldPos = interpolate3D(inData[0].worldPos, inData[1].worldPos, inData[2].worldPos);

    vec3 pos = interpolate3D(inData[0].worldPos.xyz, inData[1].worldPos.xyz, inData[2].worldPos.xyz);

    gl_Position = projMatrix * viewMatrix * vec4(pos, 1.0f);
}