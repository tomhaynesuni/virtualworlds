#version 450 core

layout(binding = 0) uniform sampler2D ColTexture;
layout (location = 8) uniform float bWireframe;

const vec4 wire_color = vec4(1.0, 1.0, 1.0, 1.0);
const vec4 fill_color = vec4(0.0, 0.0, 0.0, 0.0);

in TGSData 
{
  vec2    texCoord;
  float   intensity;
  vec3    normal;
  vec3    worldPos;
} inData;

noperspective in vec3 gDist;

out vec4 FragColor; //Color that will be used for the fragment


void main()
{
    float d = min(gDist[0],min(gDist[1],gDist[2]));
	float i = exp2(-2*d*d);

    vec4 colour = texture(ColTexture, inData.texCoord.xy);
    vec4 wireFrameColour = i * wire_color + (1.0 - i) * fill_color;

    if(bWireframe <= 0.1){FragColor = vec4(vec3(colour.xyz * inData.intensity), 1.0);} //Set the model to normal
    else{FragColor = wireFrameColour;} //Set the model to wireframe
}