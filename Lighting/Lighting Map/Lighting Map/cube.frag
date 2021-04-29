#version 330 core
struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    vec3 emit;
    float shininess;
};

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

out vec4 FragColor;

uniform Material material;
uniform Light light;

uniform vec3 viewPos;

void main()
{
    // Ambient
    vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;

    // Diffuse
    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);

    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;

    // Specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);  // shininess is shininess
    vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;
    //vec3 specular = light.specular * spec * (vec3(1.0) - texture(material.specular, TexCoords).rgb);

    vec3 emit = material.emit * texture(material.emission, TexCoords).rgb;

    vec3 result = ambient + diffuse + specular + emit;
    FragColor = vec4(result, 1.0);
}