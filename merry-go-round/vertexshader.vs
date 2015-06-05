#version 330

uniform mat4 ProjectionMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ModelMatrix;

uniform vec3 LightPos;

in vec4 Position;
in vec4 Color;
in vec3 Normal;

out vec4 vColor;

void main()
{
	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(
		Position.x, Position.y, Position.z, 1.0);
	vec3 modelViewVertex = vec3(ProjectionMatrix * ViewMatrix * ModelMatrix *
		Position);
	vec3 modelViewNormal = vec3(ViewMatrix * ModelMatrix * vec4(Normal, 0.0));
	
	float distance = length(LightPos - modelViewVertex);

	// lighting from light to vertex
	vec3 lightVector = normalize(LightPos - modelViewVertex);

	float diffuse = max(dot(modelViewNormal, lightVector), 0.1);

	// adjust light to on distance
	diffuse = diffuse * (1.0 / (1.0 + (0.25 * distance * distance)));

	// Interpolated across the triangle.
	vColor = Color * diffuse;
}
