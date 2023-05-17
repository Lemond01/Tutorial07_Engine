#include "Mesh.h"

Mesh::Mesh(ID3D11Device* device, const std::vector<SimpleVertex>& vertices, const std::vector<WORD>& indices, ID3D11Buffer* vB, ID3D11Buffer* iB)
{
    CreateVertexBuffer(device, vertices);
    CreateIndexBuffer(device, indices);
    m_pVertexBuffer = vB;
    m_pIndexBuffer = iB;
}

void SetBuffers() {

}

Mesh::~Mesh()
{
    if (m_pIndexBuffer)
        m_pIndexBuffer->Release();

    if (m_pVertexBuffer)
        m_pVertexBuffer->Release();
}


void Mesh::CreateVertexBuffer(ID3D11Device* device, const std::vector<SimpleVertex>& vertices)
{
    SimpleVertex* vertexArray = new SimpleVertex[vertices.size()];
    for (int i = 0; i < vertices.size(); i++) {
        vertexArray[i] = vertices[i];
    }

    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.Usage = D3D11_USAGE_DYNAMIC;
    bd.ByteWidth = sizeof(SimpleVertex) * vertices.size();
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    D3D11_SUBRESOURCE_DATA initData;
    ZeroMemory(&initData, sizeof(initData));
    initData.pSysMem = vertexArray;

    device->CreateBuffer(&bd, &initData, &m_pVertexBuffer);

    m_vertexCount = static_cast<UINT>(vertices.size());
}

void Mesh::CreateIndexBuffer(ID3D11Device* device, const std::vector<WORD>& indices)
{
    WORD* indexArray = new WORD[indices.size()];
    for (int i = 0; i < indices.size(); i++) {
        indexArray[i] = indices[i];
    }
    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.Usage = D3D11_USAGE_DYNAMIC;
    bd.ByteWidth = sizeof(WORD) * indices.size();
    bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    D3D11_SUBRESOURCE_DATA initData;
    ZeroMemory(&initData, sizeof(initData));
    initData.pSysMem = indexArray;

    device->CreateBuffer(&bd, &initData, &m_pIndexBuffer);

    m_indexCount = static_cast<UINT>(indices.size());
}

void Mesh::Render(ID3D11DeviceContext* context)
{
    UINT stride = sizeof(SimpleVertex);
    UINT offset = 0;

    context->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
    context->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);
    context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}