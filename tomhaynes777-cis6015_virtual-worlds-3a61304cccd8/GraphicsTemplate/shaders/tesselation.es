#version 460

// We'll do coordinate transforms for each tessellated vertex here
layout (location = 3) uniform mat4          modelMatrix;
layout (location = 4) uniform mat4          projMatrix;
layout (location = 5) uniform mat4          viewMatrix;

layout (quads, equal_spacing, ccw) in;

in ControlPoint {

  float   Intensity;
  vec2    texCoord;
  
} inControlPoints[];

out TessVertex {
  float   Intensity;
  vec2    texCoord;
} outputVertex;



void main() {
  float u = gl_TessCoord.x;
  float v = gl_TessCoord.y;

  float w0 = (1.0f - u) * (1.0f - v);
  float w1 = u * (1.0f - v);
  float w2 = u * v;
  float w3 = (1.0f - u) * v;

  outputVertex.Intensity = inControlPoints[0].Intensity * w0 + 
                        inControlPoints[1].Intensity * w1 +
                        inControlPoints[2].Intensity * w2 + 
	                    inControlPoints[3].Intensity * w3;
  
  outputVertex.texCoord = inControlPoints[0].texCoord * w0 +
                          inControlPoints[1].texCoord * w1 +
                          inControlPoints[2].texCoord * w2 +
                          inControlPoints[3].texCoord * w3;
  
  vec3 pos = gl_in[0].gl_Position.xyz * w0 +
             gl_in[1].gl_Position.xyz * w1 + 
             gl_in[2].gl_Position.xyz * w2 +
             gl_in[3].gl_Position.xyz * w3;
             
  gl_Position = projMatrix * viewMatrix * modelMatrix * vec4(pos, 1.0f);

}
