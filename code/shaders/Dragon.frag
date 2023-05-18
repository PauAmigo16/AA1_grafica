#version 330

in vec4 frag_Normal;
in vec4 FragPos;
out vec4 out_Color;

uniform mat4 mv_Mat;
uniform mat4 objMat;
uniform vec4 color;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform float lightIntensity;
uniform vec3 camPos;
uniform float brightness;
uniform float kAmbient;
uniform float kDiffuse;
uniform float kSpecular;

void main() {
	//ambient
	vec4 ambient = color * lightColor;

	//Diffuse
	vec3 surfacePos = vec3(objMat * FragPos);
	vec3 ligthDir = lightPos - surfacePos;
	vec3 lightDirNorm = normalize(ligthDir); 
	vec3 normal = normalize(frag_Normal.xyz);
	float dotNormLight = clamp(dot(normal, lightDirNorm), 0.f, 1.f);
	float dist = max(0.001f, length(ligthDir));
	vec4 diffuse = color * lightColor * dotNormLight * (lightIntensity / (4.f*3.141592*dist*dist));

	//Specular
	vec3 lightDirMirror = reflect(lightDirNorm, normal);
	vec3 camDir = normalize(surfacePos - camPos);
	float DotCamReflection = max(dot(camDir, lightDirMirror), 0.f);
	vec4 specular = lightColor * pow(DotCamReflection, brightness) * (lightIntensity / (4.f * 3.141592*dist*dist));
	
	//Result
	out_Color = ambient * kAmbient + diffuse * kDiffuse + specular * kSpecular;
}