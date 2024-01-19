#include "foxshaderprogram.h"
#include "foxlighting.h"

#include <QOpenGLShaderProgram>
#include <QVector3D>
#include <QObject>

// Ĭ����Ⱦ��ɫ���Ĵ���
const char* vertexShaderCode = R"(#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
            
out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;
            
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;
    TexCoords = aTexCoords;
    gl_Position = projection * view * vec4(FragPos, 1.0);
}
)";

const char* fragmentShadeCode = R"(#version 330 core
out vec4 FragColor;

struct Material
{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light
{
    vec3 position;
    vec3 color;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;
  
uniform vec3 viewPos;
uniform Material material;
uniform Light light;
uniform bool useMaterial;
uniform vec3 objectColor;
void main()
{
    //vec3 lightColor = vec3(1.0, 1.0, 1.0);
    //vec3 objectColor = vec3(0.5, 0.5, 0.5);
   
    vec3 ambient;
    if(useMaterial){
        ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;
    }
    else{
        ambient = light.ambient * light.color;
    }

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    
    vec3 diffuse;
    if(useMaterial){
       diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;
    }
    else{
        diffuse = light.diffuse * diff * light.color;       
    }

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec;
    vec3 specular;
    vec3 result;
    if(useMaterial){
        spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        specular = light.specular * spec * texture(material.specular, TexCoords).rgb;
        result = ambient + diffuse + specular;
    }
    else{
        spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
        specular = light.specular * spec * light.color;
        result = (ambient + diffuse + specular) * objectColor;
    }

    FragColor = vec4(result, 1.0);
}
)";



FoxShaderProgram::FoxShaderProgram(QObject* parent)
{
    m_shaderProgram = new QOpenGLShaderProgram(parent);
	// ���Ĭ�ϵĶ�����ɫ��
    m_shaderProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderCode);
    m_shaderProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShadeCode);
    m_shaderProgram->link();
    m_objectColor[0] = { 0.5f };
    m_objectColor[1] = { 0.5f };
    m_objectColor[2] = { 0.5f };
}

FoxShaderProgram::~FoxShaderProgram(){}

void FoxShaderProgram::shaderBind()
{
    m_shaderProgram->bind();
}

void FoxShaderProgram::shaderRelease()
{
    m_shaderProgram->release();
}

void FoxShaderProgram::setObjectColor(float r, float g, float b)
{
    m_shaderProgram->bind();
    // ����ģ����ɫ
    m_shaderProgram->setUniformValue("objectColor", r, g, b);
}

void FoxShaderProgram::setMatrix4x4(QMatrix4x4& projection, QMatrix4x4& view, QMatrix4x4& model)
{
    m_shaderProgram->bind();
    // ����ͶӰ���� ��ͼ���� ģ�;���
    m_shaderProgram->setUniformValue("projection", projection);
    m_shaderProgram->setUniformValue("view", view);
    m_shaderProgram->setUniformValue("model", model);

}

void FoxShaderProgram::setUseMaterial(bool useMaterial = false)
{
    m_shaderProgram->bind();
    // �����Ƿ�ʹ�ò���
    m_shaderProgram->setUniformValue("useMaterial", useMaterial);
}

void FoxShaderProgram::setLighting(std::shared_ptr<FoxLighting> lighting)
{
    m_shaderProgram->bind();
    // ͨ���ƹ���������õƹ�����
    m_shaderProgram->setUniformValue("light.position", lighting->getPosition());
    m_shaderProgram->setUniformValue("light.color", lighting->getLightingColor());
    m_shaderProgram->setUniformValue("light.ambient", lighting->getAmbient());
    m_shaderProgram->setUniformValue("light.diffuse", lighting->getDiffuse());
    m_shaderProgram->setUniformValue("light.specular", lighting->getSpecuar());
}

void FoxShaderProgram::setVertexAttributeBuffe(const char* name, int offset, int tupleSize, int stride)
{
    m_shaderProgram->setAttributeBuffer(name, GL_FLOAT, offset, tupleSize, stride);
    m_shaderProgram->enableAttributeArray(name);
}



void FoxShaderProgram::useShaderProgram(bool useMaterial,QVector3D& viewPosition, QMatrix4x4& projection, QMatrix4x4& view, QMatrix4x4& model)
{
    m_shaderProgram->bind();
    m_shaderProgram->setUniformValue("useMaterial", useMaterial);
    // ������ɫ
    m_shaderProgram->setUniformValue("objectColor", m_objectColor[0], m_objectColor[1], m_objectColor[2]);

    // ------------------------------------------------
    // 2024-01-16
    // �����еƹܵ����� ���½�����Ķ�������װ���ƹ�����
    // ------------------------------------------------
    
    m_shaderProgram->setUniformValue("light.position", QVector3D(5.0f, 10.0f, 30.0f));
    m_shaderProgram->setUniformValue("light.color", QVector3D(1.0f, 1.0f, 1.0f));
    m_shaderProgram->setUniformValue("light.ambient", QVector3D(0.3f, 0.3f, 0.3f));
    m_shaderProgram->setUniformValue("light.diffuse", QVector3D(0.7f, 0.7f, 0.7f));
    m_shaderProgram->setUniformValue("light.specular", QVector3D(1.0f, 1.0f, 1.0f));


    // ------------------------------------------------
    // 2024-01-16
    // ���ò��� ���濴��Ҫ��Ҫ������һ��foxTexture���ڹ�������
    // ------------------------------------------------
    m_shaderProgram->setUniformValue("material.specular", QVector3D(0.5f, 0.5f, 0.5f));
    m_shaderProgram->setUniformValue("material.shininess", 64.0f);

    // ���ù۲�����
    QVector3D viewPos = viewPosition;
    m_shaderProgram->setUniformValue("viewPos", viewPos);

    // ����������ɫ��������
    m_shaderProgram->setUniformValue("projection", projection);
    m_shaderProgram->setUniformValue("view", view);
    m_shaderProgram->setUniformValue("model", model);
}

QOpenGLShaderProgram* FoxShaderProgram::getShaderProgram()
{
    return m_shaderProgram;
}

void FoxShaderProgram::setShaderProgram(QOpenGLShaderProgram* shaderProgram)
{
    m_shaderProgram = shaderProgram;
}



