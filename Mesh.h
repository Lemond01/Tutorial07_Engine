#pragma once
#include "Mesh.h"

Mesh::Mesh(ID3D11Device* device, const std::vector<Vertex>& vertices, const std::vector<WORD>& indices)
{
    CreateVertexBuffer(device, vertices);
    CreateIndexBuffer(device, indices);
}

Mesh::~Mesh()
{
    if (m_pIndexBuffer)
        m_pIndexBuffer->Release();

    if (m_pVertexBuffer)
        m_pVertexBuffer->Release();
}

void Mesh::CreateVertexBuffer(ID3D11Device* device, const std::vector<Vertex>& vertices)
{
    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(Vertex) * vertices.size();
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = 0;

    D3D11_SUBRESOURCE_DATA initData;
    ZeroMemory(&initData, sizeof(initData));
    initData.pSysMem = vertices.data();

    device->CreateBuffer(&bd, &initData, &m_pVertexBuffer);

    m_vertexCount = static_cast<UINT>(vertices.size());
}

void Mesh::CreateIndexBuffer(ID3D11Device* device, const std::vector<WORD>& indices)
{
    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(WORD) * indices.size();
    bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    bd.CPUAccessFlags = 0;

    D3D11_SUBRESOURCE_DATA initData;
    ZeroMemory(&initData, sizeof(initData));
    initData.pSysMem = indices.data();

    device->CreateBuffer(&bd, &initData, &m_pIndexBuffer);

    m_indexCount = static_cast<UINT>(indices.size());
}

void Mesh::Render(ID3D11DeviceContext* context)
{
    UINT stride = sizeof(Vertex);
    UINT offset = 0;

    context->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
    context->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);
    context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // Render the mesh
    context->DrawIndexed(m_indexCount, 0, 0);
}

