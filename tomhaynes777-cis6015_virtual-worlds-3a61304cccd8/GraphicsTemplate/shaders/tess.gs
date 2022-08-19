#version 450 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

layout (location = 8) uniform float bWireframe;

noperspective out vec3 gDist;

out TGSData {
  vec2    texCoord;
  float   intensity;
  vec3    normal;
  vec3    worldPos;
} outData;

in TESData {
  vec2    texCoord;
  float   intensity;
  vec3    normal;
  vec3    worldPos;
} inData[];

void main()
{
	if(bWireframe >= 0.1)
	{
		vec2 p0 = vec2(800,600) * gl_in[0].gl_Position.xy/gl_in[0].gl_Position.w;
		vec2 p1 = vec2(800,600) * gl_in[1].gl_Position.xy/gl_in[0].gl_Position.w;
		vec2 p2 = vec2(800,600) * gl_in[2].gl_Position.xy/gl_in[0].gl_Position.w;

		vec2 v0=p2-p1;
		vec2 v1=p2-p0;
		vec2 v2=p1-p2;
		float area = abs(v1.x*v2.y - v1.y * v2.x);

		gDist = vec3(area/length(v0),0,0);
		gl_Position = gl_in[0].gl_Position;
		EmitVertex();

		gDist = vec3(0,area/length(v1),0);
		gl_Position = gl_in[1].gl_Position;
		EmitVertex();

		gDist = vec3(0,0,area/length(v2));
		gl_Position = gl_in[2].gl_Position;
		EmitVertex();

		EndPrimitive();
	}
	else
	{
		for(int i = 0; i < 3; i++) 
		{ 
			gl_Position = gl_in[i].gl_Position;

			outData.texCoord = inData[i].texCoord;
			outData.intensity = inData[i].intensity;
			outData.normal = inData[i].normal;
			outData.worldPos = inData[i].worldPos;

			EmitVertex();
		}	
	}
}