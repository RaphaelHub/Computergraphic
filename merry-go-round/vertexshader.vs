#version 330

uniform mat4 ProjectionMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ModelMatrix;
uniform float lightMode;
uniform vec4 Color;
uniform vec4 intensities;

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Normal;

out vec4 vColor;
out float vlightMode;
out vec3 position_eye;
out vec3 normal_eye;
out mat4 view_mat;
out vec4 colorChange;
out float specular_exponent;
out vec4 vIntensity;

vec3 light_position_world  = vec3 (0.0, 0.0, 20.0);
vec3 light_position_world2  = vec3 (20.0, 0.0, 0.0);

//vec3 Ls = vec3 (1.0, 1.0, 1.0); // white specular colour
float Ls = intensities.x;
//vec3 Ld = vec3 (0.7, 0.7, 0.7); // dull white diffuse light colour
float Ld = intensities.y;
//vec3 La = vec3 (0.2, 0.2, 0.2); // grey ambient colour
float La = intensities.z; 
  
// surface reflectance
vec3 Ks = vec3 (1.0, 1.0, 1.0); // fully reflect specular light
vec3 Kd = vec3 (0.0, 1.0, 0.0); // green diffuse surface reflectance
vec3 Ka = vec3 (1.0, 1.0, 1.0); // fully reflect ambient light



void main() {
	specular_exponent = intensities.w;
	vIntensity = intensities;
	vlightMode = lightMode;
	normal_eye = normalize(Normal);
	position_eye = vec3(ViewMatrix*ModelMatrix*vec4(Position, 1.0));
    gl_Position = ProjectionMatrix * vec4(position_eye, 1.0);
	normal_eye = vec3(ViewMatrix*ModelMatrix * vec4(Normal, 0.0));
	//vColor = vec4(Color.x, Color.y, Color.z, 1.0);
	colorChange = Color;
	view_mat = ViewMatrix;
	
	if(vlightMode > 0.5 && vlightMode < 1.5){
		vec3 Ia = La * Ka;
		
		vec3 light_position_eye = vec3 (ViewMatrix * vec4 (light_position_world, 1.0));
		
		vec3 direction_to_light_eye = normalize(light_position_eye - position_eye);
		vec3 reflection_eye = normalize(reflect(-direction_to_light_eye, normal_eye));
		
		//diffuse light
		float dot_prod = max(dot(direction_to_light_eye, normal_eye), 0.0);	
		vec3 Id = Ld * Kd * dot_prod;
		
		
		//specular light
		float specular_factor = max(dot(reflection_eye, normalize(position_eye)), 0.0);
		specular_factor = pow(specular_factor, specular_exponent);
		vec3 Is = Ls * Ks * specular_factor;
		
		vec3 light1 = Id + Is;

		
		//second light
		light_position_eye = vec3 (ModelMatrix * vec4 (light_position_world2, 1.0));
		
		direction_to_light_eye = normalize(light_position_eye - position_eye);
		reflection_eye = normalize(reflect(-direction_to_light_eye, normal_eye));
		
		//diffuse light
		dot_prod = max(dot(direction_to_light_eye, normal_eye), 0.0);	
		Id = Ld * colorChange.xyz * colorChange.w * dot_prod;	
	
		//specular light
		specular_factor = max(dot(reflection_eye, normalize(position_eye)), 0.0);

		specular_factor = pow(specular_factor, specular_exponent);
		
		
		
		Is = Ls * Ks * specular_factor;
		
		vec3 light2 = Id + Is;	
		
		vColor = vec4(light1 + light2 + Ia, 1.0);
	}
	
	if(vlightMode > 1.5) {
		vColor = vec4(Normal, 1.0);
	}
}
