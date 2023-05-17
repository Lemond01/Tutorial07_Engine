#include "Objeto.h"
#include "Mesh.h"
#include "Engine.h"

Objeto::Objeto(ID3D11Device* device): m_mesh(device)
{
    // Inicializar posici�n, rotaci�n y escala del objeto
    m_position = XMFLOAT3(0.0f, 0.0f, 0.0f);
    m_rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
    m_scale = XMFLOAT3(1.0f, 1.0f, 1.0f);

    // Crear y configurar los v�rtices del objeto
    std::vector<Vertex>vertices;

    // Agregar los v�rtices necesarios al vector "vertices"
    // Ejemplo:
    vertices.push_back({ XMFLOAT3(-0.5f, -0.5f, -0.5f), XMFLOAT3(0.0f, 0.0f, -1.0f) }); // V�rtice 0
    vertices.push_back({ XMFLOAT3(0.5f, -0.5f, -0.5f), XMFLOAT3(0.0f, 0.0f, -1.0f) });  // V�rtice 1
    vertices.push_back({ XMFLOAT3(-0.5f, 0.5f, -0.5f), XMFLOAT3(0.0f, 0.0f, -1.0f) });  // V�rtice 2
    vertices.push_back({ XMFLOAT3(0.5f, 0.5f, -0.5f), XMFLOAT3(0.0f, 0.0f, -1.0f) });   // V�rtice 3
    // Continuar agregando los v�rtices restantes

    // Crear y configurar los �ndices del objeto
    std::vector<unsigned int>indices;

    // Agregar los �ndices necesarios al vector "indices"
    // Ejemplo:
    indices.push_back(0);  // V�rtice 0
    indices.push_back(1);  // V�rtice 1
    indices.push_back(2);  // V�rtice 2
    indices.push_back(2);  // V�rtice 2
    indices.push_back(1);  // V�rtice 1
    indices.push_back(3);  // V�rtice 3
    // Continuar agregando los �ndices restantes

    // Inicializar el objeto Mesh con los v�rtices e �ndices
    m_mesh.Initialize(device, vertices, indices);
}

Objeto::~Objeto()
{
    // No se requiere liberar recursos expl�citamente, ya que el destructor de la clase Mesh se encarga de ello
}

void Objeto::Update(float deltaTime)
{
    // Actualizar l�gica del objeto en base al deltaTime
    // Ejemplo:
    m_rotation.y +=1.0f * deltaTime; // Rotaci�n en el eje Y con una velocidad de 1 unidad por segundo
}

void Objeto::Render(ID3D11DeviceContext* context)
{
    // Aplicar transformaciones al objeto (posici�n, rotaci�n, escala)
    XMMATRIX worldMatrix = XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z) *
        XMMatrixRotationRollPitchYaw(m_rotation.x, m_rotation.y, m_rotation.z) *
        XMMatrixTranslation(m_position.x, m_position.y, m_position.z);
    // Renderizar el objeto llamando al m�todo Render de la clase Mesh
    m_mesh.Render(context, worldMatrix);
}