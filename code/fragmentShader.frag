#version 330 core
out vec4 FragColor;
in vec3 normal;
in vec3 ourPosition;
in vec3 ourColor;
in vec2 TexCoords;
uniform sampler2D texture0;
uniform sampler2D texture1;
//uniform vec3 objectColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
in vec3 fragPos;

struct Material
{
//vec3 ambient;
//vec3 diffuse;
//vec3 specular;
sampler2D diffuse;
sampler2D specular;
sampler2D emission;
float shininess;//反光度
};

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
	 float constant;
    float linear;
    float quadratic;
};
struct DirLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  
struct PointLight {
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  
#define NR_POINT_LIGHTS 4
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform DirLight dirLight;
uniform Light light;
uniform Material material;

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
void main()
{
   vec3 norm=normalize(normal);
   vec3 viewDir=normalize(viewPos-fragPos);
   float distance    = length(light.position - fragPos);
   float attenuation = 1.0 / (light.constant + light.linear * distance + 
                light.quadratic * (distance * distance));
   vec3 lightDir=normalize(light.position-fragPos);
   vec3 refletDir=reflect(-lightDir,norm);
   float spec=pow(max(dot(viewDir,refletDir),0.0),material.shininess);
   float diff= max(dot(norm,lightDir),0.0);
   vec3 diffuse=diff*light.diffuse*vec3(texture(material.diffuse,TexCoords));
   vec3 ambient=vec3(texture(material.diffuse, TexCoords))*light.ambient;
   //这个32是高光的反光度(Shininess)。一个物体的反光度越高，反射光的能力越强，散射得越少，高光点就会越小。
   vec3 specular=vec3(texture(material.specular, TexCoords))*spec*light.specular;
   vec3 emission=vec3(texture(material.emission,TexCoords));
   ambient  *= attenuation; 
   diffuse  *= attenuation;
   specular *= attenuation;
   vec3 result= (ambient+diffuse+specular);
   //FragColor = mix(texture(texture0,TexCoord),texture(texture1,TexCoord),0.5f);//mix是两个纹理图片的融合
   FragColor = vec4(result,1.0);
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // 漫反射着色
    float diff = max(dot(normal, lightDir), 0.0);
    // 镜面光着色
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // 合并结果
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    return (ambient + diffuse + specular);
}
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // 漫反射着色
    float diff = max(dot(normal, lightDir), 0.0);
    // 镜面光着色
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // 衰减
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + 
                 light.quadratic * (distance * distance));    
    // 合并结果
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}