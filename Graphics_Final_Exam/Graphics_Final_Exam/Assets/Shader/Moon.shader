#vertex

#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in vec4 vertexColor;


uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat4 inverseModel;

out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoord;

void main()
{
	gl_Position = projection * view * model * vec4(position, 1);
	TexCoord = vec2(texCoord.x, texCoord.y);
	
	vec4 worlNormal = inverseModel * vec4(normal, 1.0f);
	Normal = normalize(worlNormal.xyz);
	FragPos = vec3(model * vec4(position, 1.0f));
};


#fragment

#version 330 core

out vec4 color;
in vec3 Normal;
in vec2 TexCoord;
in vec3 FragPos;

uniform float emissionStrength;
uniform vec4 solidColor;
uniform sampler2D texture_diffuse;

void main()
{
	vec4 diffuseColor = texture(texture_diffuse, TexCoord);
	vec4 result = diffuseColor * solidColor;
	result.xyz = result.xyz + vec3(1) * emissionStrength;
    color = vec4(result.xyz, 1.0);
};