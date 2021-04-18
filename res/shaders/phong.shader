#shader vertex
#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1)in vec3 normVec;

out vec3 NormVec;
out vec3 FragPos;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

void main()
{
    gl_Position = proj * view * model * vec4(position,1.0);
    FragPos = vec3(model * vec4(position , 1.0f));
    NormVec = mat3(transpose(inverse(model))) * normVec;
};

#shader fragment
#version 330 core

#define NR_POINT_LIGHTS 4
#define NR_DIR_LIGHTS 1

struct Material{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct PointLight{
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct DirLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

layout(location = 0)out vec4 FragColor;

in vec3 NormVec;
in vec3 FragPos;

uniform float a_constant;
uniform float a_linear;
uniform float a_quadratic;

uniform vec3 viewPos;
uniform Material material;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform DirLight dirLights[NR_DIR_LIGHTS];

vec3 calcDirLight(DirLight source, vec3 normal, vec3 viewDir)
{
    //ambient lighting
    vec3 ambient = material.ambient * source.ambient;
    
    //diffuse lighting
    vec3 lightDir = normalize(-source.direction);
    vec3 norm = normalize(normal);
    float diff = max(0.0, dot(norm, lightDir));
    vec3 diffuse = source.diffuse * (material.diffuse * diff);

    //specular lighting
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = source.specular * (spec * material.specular);

    return (ambient + diffuse + specular);
}

vec3 calcPointLight(PointLight source , vec3 normal , vec3 position , vec3 viewDir)
{
    float distance = length(source.position - position);
    float attenuation = 1.0 / (a_constant + a_linear * distance + a_quadratic * distance * distance);

    // ambient lighting
    vec3 ambient = material.ambient * source.ambient;

    //diffuse lighting
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(source.position - position);
    float diff = max(0.0 , dot(norm , lightDir));
    vec3 diffuse = source.diffuse * (material.diffuse * diff);

    //specular strength
    vec3 reflectDir = reflect(-lightDir , norm);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(norm, halfwayDir), 0.0), material.shininess);
    vec3 specular = source.specular * (spec * material.specular);    

    return (ambient + diffuse + specular) * attenuation;
}

void main()
{

    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 result = vec3(0.0f);

    for(int i = 0 ; i < NR_POINT_LIGHTS ; i++)
    {
        result += calcPointLight(pointLights[i] , NormVec , FragPos , viewDir);
    }
    for (int i = 0; i < NR_DIR_LIGHTS; i++)
    {
        result += calcDirLight(dirLights[i] , NormVec , viewDir);
    }

    float gamma = 2.2;
    result.rgb = pow(result.rgb, vec3(1.0 / gamma));

    FragColor = vec4(result , 1.0f);
};