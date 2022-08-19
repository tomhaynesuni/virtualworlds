#version 450 core
layout (triangles) in;	  	// Position in attribute location 0
layout (line_strip, max_vertices = 4) out;

in VS_DATA
{
  float Intensity;
  vec2 TexCoord;
} inData[];

out GS_DATA
{
  float intensity;
  vec2 texCoord;
} gsData;


//////////////////////////////////////////////////////////////////
// main()
//////////////////////////////////////////////////////////////////
void main() 
{

	for(int i=0; i<3; i++){
		gl_Position = gl_in[i].gl_Position;
		gsData.intensity = inData[i].Intensity;
		gsData.texCoord = inData[i].TexCoord;
		EmitVertex();
		//EndPrimitive();
	}
	gl_Position = gl_in[0].gl_Position;
		gsData.intensity = inData[0].Intensity;
		gsData.texCoord = inData[0].TexCoord;
		EmitVertex();
		EndPrimitive();
}