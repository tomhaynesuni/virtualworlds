#version 450 core
layout (triangles) in;	  	// Position in attribute location 0
layout (triangle_strip, max_vertices = 3) out;

in VS_DATA
{
  float Intensity;
  vec2 TexCoord;
} inData[];

//out GS_DATA
//{
//  float intensity;
//  vec2 texCoord;
//} gsData;

out float Intensity;
out vec2 TexCoord;


//////////////////////////////////////////////////////////////////
// main()
//////////////////////////////////////////////////////////////////
void main() 
{
    for( int i=0; i<3; i++ )
    {
        // pass through
        Intensity = inData[i].Intensity; 
        TexCoord = inData[i].TexCoord;
        gl_Position = gl_in[i].gl_Position; 
        EmitVertex();
    }  
}