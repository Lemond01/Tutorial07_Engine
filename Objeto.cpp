#include "Objeto.h"
#include "Mesh.h"

Objeto::Objeto(ID3D11Device* device, ID3D11DeviceContext* context)
{
    // Inicializar posición, rotación y escala del objeto
    m_position = XMFLOAT3(0.0f, 0.0f, 0.0f);
    m_rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
    m_scale = XMFLOAT3(1.0f, 1.0f, 1.0f);

    // Crear y configurar los vértices del objeto
    std::vector<SimpleVertex>vertices;

    SimpleVertex verticesA[] =
    {
        { XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT2(0.0f, 0.0f) },
        { XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
        { XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f) },
        { XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },

        { XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT2(0.0f, 0.0f) },
        { XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
        { XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f) },
        { XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },

        { XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f) },
        { XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
        { XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT2(1.0f, 1.0f) },
        { XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },

        { XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f) },
        { XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
        { XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT2(1.0f, 1.0f) },
        { XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },

        { XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT2(0.0f, 0.0f) },
        { XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
        { XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT2(1.0f, 1.0f) },
        { XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT2(0.0f, 1.0f) },

        { XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f) },
        { XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT2(1.0f, 0.0f) },
        { XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f) },
        { XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },
    };

    for (int i = 0; i < sizeof(verticesA) / sizeof(SimpleVertex); i++) {
        vertices.push_back(verticesA[i]);
    }

    // Crear y configurar los índices del objeto
    std::vector<WORD>indices;

    WORD indicesA[] =
    {
        3,1,0,
        2,1,3,

        6,4,5,
        7,4,6,

        11,9,8,
        10,9,11,

        14,12,13,
        15,12,14,

        19,17,16,
        18,17,19,

        22,20,21,
        23,20,22
    };

    for (int i = 0; i < sizeof(indicesA) / sizeof(WORD); i++) {
        indices.push_back(indicesA[i]);
    }

    // Inicializar el objeto Mesh con los vértices e índices
    m_mesh = new Mesh(device, vertices, indices, m_pVertexBuffer, m_pIndexBuffer);
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

void Objeto::Render(ID3D11DeviceContext* context, ID3D11Buffer* _g_pCBChangesEveryFrame)
{
    m_mesh->Render(context);
    bool nomap = true;
    while (true) {
        while (nomap) {
            D3D11_MAPPED_SUBRESOURCE mappedResource;
            ZeroMemory(&mappedResource, sizeof(mappedResource));
            HRESULT hr = context->Map(m_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
            if (FAILED(hr)) {
                char buffer[256];
                sprintf_s(buffer, "no hay mapa");
                OutputDebugStringA(buffer);
            }
            SimpleVertex* vertices = static_cast<SimpleVertex*>(mappedResource.pData);
            for (int i = 0; i < 24; i++) {
                SimpleVertex& vertex = vertices[i];
                char buffer[256];
                sprintf_s(buffer, "Vertex %d: x=%f y=%f z=%f\n", i, vertices[i].Pos.x, vertices[i].Pos.y, vertices[i].Pos.z);
                OutputDebugStringA(buffer);
            }
            nomap = false;
        }
    }
    // Aplicar transformaciones al objeto (posición, rotación, escala)
    XMMATRIX worldMatrix = XMMatrixIdentity() * XMMatrixTranslationFromVector(XMLoadFloat3(&m_position));
    // Renderizar el objeto llamando al método Render de la clase Mesh
    CBChangesEveryFrame cb;
    cb.mWorld = XMMatrixTranspose(worldMatrix);
    context->UpdateSubresource(_g_pCBChangesEveryFrame, 0, NULL, &cb, 0, 0);
    context->DrawIndexed(m_mesh->getVertexCount(), 0, 0);
}
