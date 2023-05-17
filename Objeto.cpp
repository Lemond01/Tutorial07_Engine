#include "Objeto.h"
#include "Mesh.h"
#include "Engine.h"

Objeto::Objeto(ID3D11Device* device): m_mesh(device)
{
    // Inicializar posición, rotación y escala del objeto
    m_position = XMFLOAT3(0.0f, 0.0f, 0.0f);
    m_rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
    m_scale = XMFLOAT3(1.0f, 1.0f, 1.0f);

    // Crear y configurar los vértices del objeto
    std::vector<Vertex>vertices;

    // Agregar los vértices necesarios al vector "vertices"
    // Ejemplo:
    vertices.push_back({ XMFLOAT3(-0.5f, -0.5f, -0.5f), XMFLOAT3(0.0f, 0.0f, -1.0f) }); // Vértice 0
    vertices.push_back({ XMFLOAT3(0.5f, -0.5f, -0.5f), XMFLOAT3(0.0f, 0.0f, -1.0f) });  // Vértice 1
    vertices.push_back({ XMFLOAT3(-0.5f, 0.5f, -0.5f), XMFLOAT3(0.0f, 0.0f, -1.0f) });  // Vértice 2
    vertices.push_back({ XMFLOAT3(0.5f, 0.5f, -0.5f), XMFLOAT3(0.0f, 0.0f, -1.0f) });   // Vértice 3
    // Continuar agregando los vértices restantes

    // Crear y configurar los índices del objeto
    std::vector<unsigned int>indices;

    // Agregar los índices necesarios al vector "indices"
    // Ejemplo:
    indices.push_back(0);  // Vértice 0
    indices.push_back(1);  // Vértice 1
    indices.push_back(2);  // Vértice 2
    indices.push_back(2);  // Vértice 2
    indices.push_back(1);  // Vértice 1
    indices.push_back(3);  // Vértice 3
    // Continuar agregando los índices restantes

    // Inicializar el objeto Mesh con los vértices e índices
    m_mesh.Initialize(device, vertices, indices);
}

Objeto::~Objeto()
{
    // No se requiere liberar recursos explícitamente, ya que el destructor de la clase Mesh se encarga de ello
}

void Objeto::Update(float deltaTime)
{
    // Actualizar lógica del objeto en base al deltaTime
    // Ejemplo:
    m_rotation.y +=1.0f * deltaTime; // Rotación en el eje Y con una velocidad de 1 unidad por segundo
}

void Objeto::Render(ID3D11DeviceContext* context)
{
    // Aplicar transformaciones al objeto (posición, rotación, escala)
    XMMATRIX worldMatrix = XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z) *
        XMMatrixRotationRollPitchYaw(m_rotation.x, m_rotation.y, m_rotation.z) *
        XMMatrixTranslation(m_position.x, m_position.y, m_position.z);
    // Renderizar el objeto llamando al método Render de la clase Mesh
    m_mesh.Render(context, worldMatrix);
}